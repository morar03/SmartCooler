#include "./Functionality.h"

float floatCurentTemperatureValue;
static float lastTemperatureValue = 90;

void InitFunctionality(){
    pinMode(PinPowerCooler, OUTPUT);
    digitalWrite(PinPowerCooler, CoolerOn);
}

void vCheckTemperatureAndUpdateInFirebase(){
    static int counter;
    if (getAndConvertRadioMessage(&floatCurentTemperatureValue)){
        counter = 0;
        float averageTemp = lastTemperatureValue-floatCurentTemperatureValue;
        if ((averageTemp >= 0.5 ) or (averageTemp <= -0.5)){
            float rounding = std::round(floatCurentTemperatureValue * 2) / 2;
            setStatusLive_Temperature_Firebase(rounding);
            lastTemperatureValue = rounding;
        }
    }else{
        counter++;
        if (counter >= debounce){
            vAlertRadio();
        }  
    }
}

void vControlCooler(){
    float TemperatureSet = getStatusSet_Temperature_Firebase();
    bool coolerPower = getEvent_ON_OFF_Firebase();

    if (coolerPower == True) {
        if (TemperatureSet >= lastTemperatureValue ){
            digitalWrite(PinPowerCooler, CoolerOff);
        }else{
            digitalWrite(PinPowerCooler, CoolerOn);
        }    
    }else if (coolerPower == False){
        digitalWrite(PinPowerCooler, CoolerOff);
    }     
}

void vAlertRadio(){
    setStatusLive_Temperature_Firebase(101);
    vBlinkLEDAlert();
    digitalWrite(PinPowerCooler, CoolerOn);
}

void vBlinkLEDAlert(){
    digitalWrite(LED_BUILTIN_AUX, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN_AUX, LOW);
    delay(500);
}


