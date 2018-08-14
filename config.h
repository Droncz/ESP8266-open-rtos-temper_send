#ifndef CONFIG_H
#define CONFIG_H

//******** PINs connections *********************
#define GPIO_LED 2
#define GPIO_BTN 0
//***********************************************

//******** Definitions for the I2C bus **********
#define BUS     (0)
// #define SCL_PIN (1)
// #define SDA_PIN (2)
#define SCL_PIN (5)
#define SDA_PIN (4)
#define I2C_MASTER_WRITE 0x0   /*!< I2C write data */
#define I2C_MASTER_READ 0x1   /*!< I2C read data */
// uint8_t slave_addr = 0x5c;
// uint8_t reg_addr = 0x1f;
// uint8_t reg_data;
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


// For the delays...
#define SECOND (1000 / portTICK_PERIOD_MS)

// Global variables definition:
extern float temperature;
extern float humidity;
extern float pressure;

#endif // ifndef CONFIG_H
