#include "./Functionality.h"

float floatCurentTemperatureValue;
static float lastTemperatureValue = 10;

void InitFunctionality(){
    pinMode(PinPowerCooler, OUTPUT);
    digitalWrite(PinPowerCooler, HIGH);
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
            lastTemperatureValue = 99;
        }  
    }
}

void vControlCooler(){
    float TemperatureSet = getStatusSet_Temperature_Firebase();
    bool coolerPower = getEvent_ON_OFF_Firebase();

    Serial.println("---------------------");
    Serial.print("Temperatura setata: ");
    Serial.println(TemperatureSet);
    Serial.print("Temperatura live: ");
    Serial.println(floatCurentTemperatureValue);
    Serial.println("---------------------");

    if (coolerPower == True) {
        if (TemperatureSet <= floatCurentTemperatureValue ){
            digitalWrite(PinPowerCooler, HIGH);
            Serial.println("---------INTRA PE HIGH------------");
        }else{
            digitalWrite(PinPowerCooler, LOW);
            Serial.println("---------INTRA PE LOW------------");
        }    
    }else if (coolerPower == False){
        digitalWrite(PinPowerCooler, LOW);
    }     
}



