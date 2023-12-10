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

// Include the EEPROM library for access to non-volatile memory
#include <EEPROM.h>


// THE SECRET CREDETIALS
#include "envCredentials.h"

// THE SECRET CREDETIALS

// subseqent reset will be considered a doubleee reset.
#define DRD_TIMEOUT 1

// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

// Digital Pin to operate the door
#define actionDoorPin D1

// Size allocation for the value in EEPROM
#define EEPROM_SIZE 1

// Address start for the value in EEPROM
#define EEPROM_First_Value 0

//Defined Digital Pin for the button of change form AP in STA 
#define APSTAbutton D6

//Defined True and False with 1 and 0 
#define True 1
#define False 0



void wifiConnect(void);
void InitValueDatabase(void);
bool getEvent_ON_OFF_Firebase(void);
void setEvent_ON_OFF_Firebase(bool event_ON_OFF_Firebase);
double getStatusLive_Temperature_Firebase(void);
void setStatusLive_Temperature_Firebase(double StatusLiveTemperature);
void ISRButtonDetect();
std::string ConcatRouteDevices(std::string string1, std::string string2);
double StringToDouble(std::string string);
double getStatusSet_Temperature_Firebase(void);