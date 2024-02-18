#include <Arduino.h>

#include "./CyclicFunctions/CyclicFunctions.h"

void setup()
{   
    delay(1000);
    Serial.begin(9600);	// Debugging only
    wifiConnect();
    InitValueDatabase();
    initRadioModule();
    InitFunctionality();
}

void loop(){
  unsigned long currentTime = millis();
  if (getStatusConnection()){
    cyclicFunction90s(currentTime);
    cyclicFunction1s(currentTime);
  }else{
    digitalWrite(PinPowerCooler, CoolerOn);
    vBlinkLEDAlert();
    if (currentTime >= interval300s){
      ESP.reset();
    }
  }
  vcheckNetworkButtonConnection();
}
   