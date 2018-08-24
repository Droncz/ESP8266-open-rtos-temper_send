#ifndef CONFIG_H
#define CONFIG_H

//******** PINs connections *********************
#define GPIO_LED 2
#define GPIO_BTN 0
//***********************************************

//******** Definitions for the I2C bus **********
#define I2C_BUS (0)
#define SCL_PIN (5)
#define SDA_PIN (4)
#define I2C_MASTER_WRITE 0x0   /*!< I2C write data */
#define I2C_MASTER_READ 0x1   /*!< I2C read data */
//***********************************************

//******** DHT senzor definitions ***************
// uint8_t const dht_gpio = 4;
#define GPIO_DHT (4)
// const dht_sensor_type_t sensor_type = DHT_TYPE_DHT11;
#define SENSOR_TYPE (dht_sensor_type_t)DHT_TYPE_DHT12
//***********************************************

//******** MOSQUITTO CONNECTION *****************
/* You can use http://test.mosquitto.org/ to test mqtt_client instead
 * of setting up your own MQTT server */
#define MQTT_HOST ("192.168.1.21")
#define MQTT_PORT 1883

#define MQTT_USER NULL
#define MQTT_PASS NULL

#define MQTT_PUB_TOPIC "esp8266/status"
#define MQTT_SUB_TOPIC "esp8266/control"

#define PUB_MSG_LEN 64
// #define PUB_MSG_LEN 16
//***********************************************

//******** Soil moisture sensor levels **********
// What are the border levels of the sensor found by testing
#define DRY_SENSOR 1024
#define WET_SENSOR 400
//***********************************************


//******** SSD1306 OLED display******************
// Next line selects I2C or SPI display connection 
// #define I2C_CONNECTION

// Change this according to you schematics and display size
#define DISPLAY_WIDTH  128
#define DISPLAY_HEIGHT 64

#ifdef I2C_CONNECTION
    #define PROTOCOL SSD1306_PROTO_I2C
    #define ADDR     SSD1306_I2C_ADDR_0
#else
    #define PROTOCOL SSD1306_PROTO_SPI4
    #define CS_PIN   15
    #define DC_PIN   12
#endif
//***********************************************



// For the delays...
#define SECOND (1000 / portTICK_PERIOD_MS)

// Global variables definition:
extern float temperature;
extern float humidity;
extern float pressure;
// extern uint16_t analogValue;

#endif // ifndef CONFIG_H
