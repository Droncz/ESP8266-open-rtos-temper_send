#include <string.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
#include <ssid_config.h>

#include <espressif/esp_common.h>
#include <espressif/esp_wifi.h>
#include <espressif/esp_sta.h>

#include <esp/uart.h>
#include <esp/gpio.h>

#include <paho_mqtt_c/MQTTESP8266.h>
#include <paho_mqtt_c/MQTTClient.h>

#include <libesphttpd/httpd.h>
#include <libesphttpd/httpdespfs.h>
#include <libesphttpd/cgiwifi.h>
#include <libesphttpd/cgiflash.h>
#include <libesphttpd/auth.h>
#include <libesphttpd/espfs.h>
#include <libesphttpd/captdns.h>
#include <libesphttpd/webpages-espfs.h>
#include <libesphttpd/cgiwebsocket.h>
#include <libesphttpd/httpdespfs.h>

#include <rboot-ota/ota-tftp.h>
#include <rboot-ota/rboot-api.h>

#include <dht/dht.h>

#include "cgi.h"
#include "urls.h"

// I2C and DHT pin definitions
#include "config.h"

// these are externally declared in config.h to be used in other files too
float temperature = 0;
float humidity = 0;
float pressure = 0;

SemaphoreHandle_t wifi_alive;
QueueHandle_t publish_queue;

static void beat_task(void *pvParameters) {
    char msg[PUB_MSG_LEN];
    int count = 0;

    while (1) {
        if (!wifi_alive) {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }

        printf("Schedule to publish\r\n");

        snprintf(msg, PUB_MSG_LEN, "%d", count);
        if (xQueueSend(publish_queue, (void *) msg, 0) == pdFALSE) {
            printf("Publish queue overflow\r\n");
        }

        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

static void topic_received(mqtt_message_data_t *md) {
    mqtt_message_t *message = md->message;
    int i;

    printf("Received: ");
    for (i = 0; i < md->topic->lenstring.len; ++i)
        printf("%c", md->topic->lenstring.data[i]);

    printf(" = ");
    for (i = 0; i < (int) message->payloadlen; ++i)
        printf("%c", ((char *) (message->payload))[i]);
    printf("\r\n");

    if (!strncmp(message->payload, "on", 2)) {
        printf("Turning on LED\r\n");
        gpio_write(GPIO_LED, 0);
    } else if (!strncmp(message->payload, "off", 3)) {
        printf("Turning off LED\r\n");
        gpio_write(GPIO_LED, 1);
    }
}

static const char *get_my_id(void) {
    // Use MAC address for Station as unique ID
    static char my_id[13];
    static bool my_id_done = false;
    int8_t i;
    uint8_t x;
    if (my_id_done)
        return my_id;
    if (!sdk_wifi_get_macaddr(STATION_IF, (uint8_t *) my_id))
        return NULL;
    for (i = 5; i >= 0; --i) {
        x = my_id[i] & 0x0F;
        if (x > 9)
            x += 7;
        my_id[i * 2 + 1] = x + '0';
        x = my_id[i] >> 4;
        if (x > 9)
            x += 7;
        my_id[i * 2] = x + '0';
    }
    my_id[12] = '\0';
    my_id_done = true;
    return my_id;
}

static void mqtt_task(void *pvParameters) {
    int ret = 0;
    struct mqtt_network network;
    mqtt_client_t client = mqtt_client_default;
    char mqtt_client_id[20];
    uint8_t mqtt_buf[100];
    uint8_t mqtt_readbuf[100];
    mqtt_packet_connect_data_t data = mqtt_packet_connect_data_initializer;

    mqtt_network_new( &network );
    memset(mqtt_client_id, 0, sizeof(mqtt_client_id));
    strcpy(mqtt_client_id, "ESP-");
    strcat(mqtt_client_id, get_my_id());

    while (1) {
        // Wait for the Wi-fi connectivity to become available
        xSemaphoreTake(wifi_alive, portMAX_DELAY);

        printf("%s: (Re)connecting to MQTT server %s ... ",__func__, MQTT_HOST);
        ret = mqtt_network_connect(&network, MQTT_HOST, MQTT_PORT);
        if( ret ){
            printf("error: %d\n\r", ret);
            taskYIELD();
            continue;
        }
        printf("done\n\r");
        mqtt_client_new(&client, &network, 5000, mqtt_buf, 100, mqtt_readbuf, 100);

        data.willFlag = 0;
        data.MQTTVersion = 4;
        // data.MQTTVersion = 3;
        data.cleansession = 0;
        // data.cleansession = 1;
        data.clientID.cstring = mqtt_client_id;
        data.username.cstring = MQTT_USER;
        data.password.cstring = MQTT_PASS;
        data.keepAliveInterval = 10;
        printf("Send MQTT connect ... ");
        ret = mqtt_connect(&client, &data);
        if (ret) {
            printf("error: %d\n\r", ret);
            mqtt_network_disconnect(&network);
            taskYIELD();
            continue;
        }
        printf("done\r\n");
        mqtt_subscribe(&client, MQTT_SUB_TOPIC, MQTT_QOS1, topic_received);
        xQueueReset(publish_queue);

        while (1) {
            char msg[PUB_MSG_LEN - 1] = "\0";;
            // printf("Enpty message: |%s|\r\n", msg);
            
            while (xQueueReceive(publish_queue, (void *) msg, 0) == pdTRUE) {
                // Fill the MQTT message with some internals for now
                // TickType_t task_tick = xTaskGetTickCount();
                // uint32_t free_heap = xPortGetFreeHeapSize();
                // uint32_t free_stack = uxTaskGetStackHighWaterMark(NULL);
                // snprintf(msg, PUB_MSG_LEN, "%u: free heap %u, free stack %u", task_tick, free_heap, free_stack * 4);
                printf("Received message to publish: |%s|\r\n", msg);
                mqtt_message_t message;
                message.payload = msg;
                message.payloadlen = PUB_MSG_LEN;
                message.dup = 0;
                message.qos = MQTT_QOS1;
                message.retained = 0;
                ret = mqtt_publish(&client, MQTT_PUB_TOPIC, &message);
                if (ret != MQTT_SUCCESS) {
                    printf("error while publishing message: %d\n", ret);
                    break;
                }
            }

            ret = mqtt_yield(&client, 1000);
            if (ret == MQTT_DISCONNECTED)
                break;
        }
        printf("Connection dropped, request restart\n\r");
        mqtt_network_disconnect(&network);
        taskYIELD();
    }
}

static void wifi_task(void *pvParameters) {
    uint8_t status = 0;
    uint8_t retries = 30;
    struct sdk_station_config config = { 
        .ssid = WIFI_SSID,
        .password = WIFI_PASS, };

    printf("%s: Connecting to WiFi\n\r", __func__);
	if (sdk_wifi_set_opmode(STATION_MODE)) {
		printf("Wifi set to station mode\n");
		sdk_wifi_station_set_config(&config);
		sdk_wifi_station_connect();
	} else {
		printf("UNABLE to set Wifi to station mode\n");
	}
    
    while (1) {
        while ((status != STATION_GOT_IP) && (retries)) {
            status = sdk_wifi_station_get_connect_status();
            printf("%s: status = %d\n\r", __func__, status);
            if (status == STATION_WRONG_PASSWORD) {
                printf("WiFi: wrong password\n\r");
                break;
            } else if (status == STATION_NO_AP_FOUND) {
                printf("WiFi: AP not found\n\r");
                break;
            } else if (status == STATION_CONNECT_FAIL) {
                printf("WiFi: connection failed\r\n");
                break;
            }
            vTaskDelay(SECOND);
            --retries;
        }
        if (status == STATION_GOT_IP) {
            printf("WiFi: Connected\n\r");
            xSemaphoreGive( wifi_alive );
            taskYIELD();
        }

        while ((status = sdk_wifi_station_get_connect_status()) == STATION_GOT_IP) {
            xSemaphoreGive( wifi_alive );
            taskYIELD();
        }
        printf("WiFi: disconnected\n\r");
        sdk_wifi_station_disconnect();
        vTaskDelay(SECOND);
    }
}



void Measurement_task(void *pvParameters)
{
    char msg[PUB_MSG_LEN];
    int count = 0;

    printf("%s: started\n\r", __func__);

    // DHT sensors that come mounted on a PCB generally have
    // pull-up resistors on the data pin.  It is recommended
    // to provide an external pull-up resistor otherwise...
    gpio_set_pullup(GPIO_DHT, false, false);
 
    while(1) {
        if (dht_read_float_data(SENSOR_TYPE, GPIO_DHT, &humidity, &temperature)) {
            snprintf(msg, PUB_MSG_LEN, "Measurement #%4d: Humidity: %5.2f%% Temp: %5.2fC", count++, humidity, temperature);
            printf("%s\n\r", msg);
            if (xQueueSend(publish_queue, (void *) msg, 0) == pdFALSE) {
                printf("Publish queue overflow.\r\n");
            }
        } else {
            printf("Could not read data from sensor\n");
        }

        // Delay...
        vTaskDelay(10*SECOND);
    }
}


void OTAinit() {
	int i;

	rboot_config conf = rboot_get_config();

    printf("\r\nCurrently running on flash slot %d / %d.\r\n\r\n",
           conf.current_rom, conf.count);

    printf("Image addresses in flash:\r\n");
    for(i = 0; i <conf.count; i++) {
        printf("%c%d: offset 0x%08x\r\n", i == conf.current_rom ? '*':' ', i, conf.roms[i]);
    }

	printf("Starting OTA TFTP server...");
    ota_tftp_init_server(TFTP_PORT);
}



void user_init(void) {
    uart_set_baud(0, 115200);
    printf("SDK version: %s, free heap %u\n", sdk_system_get_sdk_version(), xPortGetFreeHeapSize());

    gpio_enable(GPIO_LED, GPIO_OUTPUT);
    gpio_write(GPIO_LED, 1);

	espFsInit((void*)(_binary_build_web_espfs_bin_start));
	httpdInit(builtInUrls, 80);
	OTAinit();
    
    wifi_alive = xSemaphoreCreateBinary();
    publish_queue = xQueueCreate(3, PUB_MSG_LEN);
    xTaskCreate(&wifi_task, "wifi_task", 256, NULL, 2, NULL);
    xTaskCreate(&Measurement_task, "Measurement_task", 512, NULL, 3, NULL);
    // xTaskCreate(&beat_task, "beat_task", 256, NULL, 3, NULL);
    xTaskCreate(&mqtt_task, "mqtt_task", 2048, NULL, 4, NULL);

    printf("\nFree heap after init: %u\n", xPortGetFreeHeapSize());
}
