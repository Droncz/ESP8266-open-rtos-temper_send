#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <espressif/esp_common.h>
#include <dht/dht.h>
#include <esp/gpio.h>

#include "config.h"
#include "cgi.h"


//Template code for the counter on the index page.
static int hitCounter=0;
int tplCounter(HttpdConnData *connData, char *token, void **arg) {
	char buff[128];
	if (token==NULL) return HTTPD_CGI_DONE;

	if (strcmp(token, "counter")==0) {
		hitCounter++;
		sprintf(buff, "%d", hitCounter);
	}
	httpdSend(connData, buff, -1);
	return HTTPD_CGI_DONE;
}


//Template code for the led page.
int tplSwitch(HttpdConnData *connData, char *token, void **arg) {
	char buff[128];
	bool led1, led2;

	if (token==NULL) return HTTPD_CGI_DONE;

	led1 = gpio_read(GPIO_LED);
	led2 = gpio_read(GPIO_LED);

	strcpy(buff, "Unknown");
	if (strcmp(token, "ledstate1a")==0) {
		if (led1) {
			strcpy(buff, "checked");
		} else {
			strcpy(buff, "");
		}
	}else
	if (strcmp(token, "ledstate1b")==0) {
		if (!led1) {
			strcpy(buff, "checked");
		} else {
			strcpy(buff, "");
		}
	}else
	if (strcmp(token, "ledstate2a")==0) {
		if (led2) {
			strcpy(buff, "checked");
		} else {
			strcpy(buff, "");
		}
	}else
	if (strcmp(token, "ledstate2b")==0) {
		if (!led2) {
			strcpy(buff, "checked");
		} else {
			strcpy(buff, "");
		}
	}

	httpdSend(connData, buff, -1);
	return HTTPD_CGI_DONE;
}

//Cgi that turns the LED on or off according to the 'led' param in the POST data
int cgiSwitch(HttpdConnData *connData) {
	int len, currLedState;
	char buff[128];
	
	if (connData->conn==NULL) {
		//Connection aborted. Clean up.
		return HTTPD_CGI_DONE;
	}

	len=httpdFindArg(connData->post->buff, "led1", buff, sizeof(buff));
	// printf("LED1 POST = %s\n", connData->post->buff);
	// printf("  found = %s\n", buff);
	if (len!=0) {
		currLedState=atoi(buff);
	
		if (currLedState) {
        	gpio_write(GPIO_LED, 1);
		} else {
        	gpio_write(GPIO_LED, 0);
		}
	}
    
    len=httpdFindArg(connData->post->buff, "led2", buff, sizeof(buff));
	// printf("LED2 POST = %s\n", connData->post->buff);
	// printf("  found = %s\n", buff);
    if (len!=0) {
        currLedState=atoi(buff);
		if (currLedState) {
			gpio_write(GPIO_LED, 1);
		} else {
	        gpio_write(GPIO_LED, 0);
		}
	}

	httpdRedirect(connData, "switch.tpl");
	return HTTPD_CGI_DONE;
}


int tplMoisture(HttpdConnData *connData, char *token, void **arg) {
	char buff[128];
	// float analogVolts;
	int chartValue, analogValue;

	if (token==NULL) return HTTPD_CGI_DONE;

	analogValue = sdk_system_adc_read();
    // analogVolts = (analogValue * 3.08) / 1024;
    chartValue = 100 - 100 * (analogValue - WET_SENSOR) / (DRY_SENSOR - WET_SENSOR);
	// sucho = 100 - 100 * (1000 - 400) / 600 = 100 - 100 * 1 = 0
	// napůl = 100 - 100 * (700 - 400) / 600 = 100 - 100 * 0,5 = 50
	// mokro = 100 - 100 * (400 - 400) / 600 = 100 - 100 * 0 = 100
	if (strcmp(token, "analogValue")==0) {
		sprintf(buff, "%4d", analogValue);
	// } else if (strcmp(token, "analogVolts")==0) {
	// 	sprintf(buff, "%5.2f", temperature);
	} else if (strcmp(token, "chartValue")==0) {
		sprintf(buff, "%d", chartValue);
	}
	
	httpdSend(connData, buff, -1);
	return HTTPD_CGI_DONE;
}

// Template for the index page
int tplDHT12(HttpdConnData *connData, char *token, void **arg) {
	char buff[128];

	if (token==NULL) return HTTPD_CGI_DONE;

	// Values reading is done periodically in the "MeasurementTask" task.
	// printf("Token = %s\n", token);

	if (strcmp(token, "temp")==0) {
		sprintf(buff, "%5.2f", temperature);
		// printf("temp = %5.2f, buff = %s\n", temperature, buff);
	} 
	else if (strcmp(token, "pres")==0) {
	 	sprintf(buff, "%5.2f", pressure);
		// printf("pres = %5.2f, buff = %s\n", pressure, buff);
	} 
	else if (strcmp(token, "humi")==0) {
		sprintf(buff, "%5.2f", humidity);
		// printf("humi = %5.2f, buff = %s\n", humidity, buff);
	}

	httpdSend(connData, buff, -1);
	return HTTPD_CGI_DONE;
}
