#ifndef CGI_H
#define CGI_H

#include <libesphttpd/httpd.h>

// int cgiLed(HttpdConnData *connData);
// int tplLed(HttpdConnData *connData, char *token, void **arg);
int tplCounter(HttpdConnData *connData, char *token, void **arg);
int tplSwitch(HttpdConnData *connData, char *token, void **arg);
int cgiSwitch(HttpdConnData *connData);
int tplMoisture(HttpdConnData *connData, char *token, void **arg);
int tplDHT12(HttpdConnData *connData, char *token, void **arg);

#endif
