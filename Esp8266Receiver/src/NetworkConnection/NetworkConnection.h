#include <iostream>
#include <string>
#include <cstdio>

#include <Arduino.h>

// Include the Wi-Fi library
#include <ESP8266WiFi.h>

// Include the library for change AP to STM
#include <WiFiManager.h>

// Include the Firebase library      
#include <FirebaseESP8266.h>

// THE SECRET CREDETIALS
#include "envCredentials.h"

//Defined Digital Pin for the button of change form AP in STA 
#define APSTAbutton D6

//Defined True and False with 1 and 0 
#define True 1
#define False 0



void wifiConnect(void);
void vcheckNetworkButtonConnection(void);
bool getStatusConnection(void);
void InitValueDatabase(void);
bool getEvent_ON_OFF_Firebase(void);
void setEvent_ON_OFF_Firebase(bool event_ON_OFF_Firebase);
float getStatusLive_Temperature_Firebase(void);
void setStatusLive_Temperature_Firebase(float StatusLiveTemperature);
std::string ConcatRouteDevices(std::string string1, std::string string2);
float StringToFloat(std::string string);
float getStatusSet_Temperature_Firebase(void);