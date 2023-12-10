#include "./Functionality.h"

double doubleCurentTemperatureValue;
static double lastTemperatureValue;
static unsigned long lastCallTime = 0;

void InitFunctionality(){
    pinMode(PinPowerCooler, OUTPUT);
    digitalWrite(PinPowerCooler, HIGH);
}


void vCheckTemperatureAndUpdateInFirebase(){
    if (getAndConvertRadioMessage()){
        if ((lastTemperatureValue/1 )!= (doubleCurentTemperatureValue/1)){
            setStatusLive_Temperature_Firebase(doubleCurentTemperatureValue);
            lastTemperatureValue = doubleCurentTemperatureValue;
        }
    }else{
        digitalWrite(PinPowerCooler, HIGH);
    }
}

void vControlCooler(){
    
    double TemperatureSet = getStatusSet_Temperature_Firebase();
    if (millis() - lastCallTime >= 1000){
        if (TemperatureSet <= doubleCurentTemperatureValue ){
             digitalWrite(PinPowerCooler, HIGH);
        }else{
            digitalWrite(PinPowerCooler, LOW);
        }
        lastCallTime = millis();
    } 
}