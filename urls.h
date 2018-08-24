
CgiUploadFlashDef uploadParams={
	.type=CGIFLASH_TYPE_FW,
	.fw1Pos=0x2000,
	.fw2Pos=((FLASH_SIZE*1024*1024)/2)+0x2000,
	.fwSize=((FLASH_SIZE*1024*1024)/2)-0x2000,
	.tagName=LIBESPHTTPD_OTA_TAGNAME
};

HttpdBuiltInUrl builtInUrls[]={
	{"*", cgiRedirectApClientToHostname, "esp8266.nonet"},
	{"/", cgiRedirect, "/index.tpl"},
	{"/index.tpl", cgiEspFsTemplate, tplCounter},
	{"/switch.tpl", cgiEspFsTemplate, tplSwitch},
	{"/switch.cgi", cgiSwitch, NULL},
	{"/dht12.tpl", cgiEspFsTemplate, tplDHT12},
	{"/moisture.tpl", cgiEspFsTemplate, tplMoisture},
//	{"/led.tpl", cgiEspFsTemplate, tplLed},
//	{"/led.cgi", cgiLed, NULL},
#ifndef ESP32
	{"/flash/", cgiRedirect, "/flash/index.html"},
	{"/flash/next", cgiGetFirmwareNext, &uploadParams},
	{"/flash/upload", cgiUploadFirmware, &uploadParams},
	{"/flash/reboot", cgiRebootFirmware, NULL},
#endif
//Routines to make the /wifi URL and everything beneath it work.
//Enable the line below to protect the WiFi configuration with an username/password combo.
//	{"/wifi/*", authBasic, myPassFn},
	{"/wifi", cgiRedirect, "/wifi/wifi.tpl"},
	{"/wifi/", cgiRedirect, "/wifi/wifi.tpl"},
	{"/wifi/wifiscan.cgi", cgiWiFiScan, NULL},
	{"/wifi/wifi.tpl", cgiEspFsTemplate, tplWlan},
	{"/wifi/connect.cgi", cgiWiFiConnect, NULL},
	{"/wifi/connstatus.cgi", cgiWiFiConnStatus, NULL},
	{"/wifi/setmode.cgi", cgiWiFiSetMode, NULL},

//	{"/websocket/ws.cgi", cgiWebsocket, myWebsocketConnect},
//	{"/websocket/echo.cgi", cgiWebsocket, myEchoWebsocketConnect},

//	{"/test", cgiRedirect, "/test/index.html"},
//	{"/test/", cgiRedirect, "/test/index.html"},
//	{"/test/test.cgi", cgiTestbed, NULL},

	{"*", cgiEspFsHook, NULL}, //Catch-all cgi function for the filesystem
	{NULL, NULL, NULL}
};
