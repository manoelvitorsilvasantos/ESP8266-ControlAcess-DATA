#ifndef __CONFIG_H__
#define __CONFIG_H__

//libs
#include <ESP8266WiFi.h>

//ACESS POINT
#define AP_SSID "IOT-ESP8266"
#define AP_PASS "susej_65564747"
#define AP_MAX_CONN 8
#define AP_HIDDEN false
#define AP_CHANNEL 1


IPAddress local_ip(10,0,0,1);
IPAddress gateway(10,0,0,0);
IPAddress subnet(255,255,255,0);

//WIFI
#define WIFI_SSID "BRADESCO"
#define WIFI_PASS "leonam65564747"

#endif
