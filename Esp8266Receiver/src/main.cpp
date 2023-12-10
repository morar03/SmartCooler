#include <Arduino.h>

#include "./Functionality/Functionality.h"



void setup()
{
    Serial.begin(9600);	// Debugging only
    EEPROM.begin(EEPROM_SIZE);
    wifiConnect();
    InitValueDatabase();
    initRadioModule();
    InitFunctionality();
}

void loop()
{
   if (getEvent_ON_OFF_Firebase() == True) {
        vCheckTemperatureAndUpdateInFirebase();
        vControlCooler();
    }else{
        vCheckTemperatureAndUpdateInFirebase();
        digitalWrite(PinPowerCooler, HIGH);
    }
}
   