// Configuration.h

#ifndef DHT_H
// Included for sensor types
#include "DHT.h"
#endif

#ifndef __WLAN_H__
// Included for security mode options
#include "utility/wlan.h"
#endif

#define LED_STATUS_PIN  6
#define LED_ERROR_PIN   5

#define DHT_PIN         2
#define DHT_TYPE        DHT22

#define WIFI_INTERRUPT  3
#define WIFI_ENABLE     7
#define WIFI_CHIPSELECT 10

#define SERVER_ADDRESS  IPAddress(192, 168, 0, 100)
#define SERVER_PORT     9487


// Private Configration info not included in repo
// Comment it out to use the definitions below instead
#include "PrivateConfiguration.h"

#ifndef PRIVATECONFIGURATION_H
#define WIFI_SSID       "YourSSID"
#define WIFI_SECURITY   WLAN_SEC_WPA2
#define WIFI_PASSWORD   "YourPassword"
#endif
