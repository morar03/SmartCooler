#include <Arduino.h>

#include "./CyclicFunctions/CyclicFunctions.h"




void setup()
{   
    Serial.begin(115200);	// Debugging only
    EEPROM.begin(EEPROM_SIZE);
    wifiConnect();
    InitValueDatabase();
    initRadioModule();
    InitFunctionality();
  
}

void loop(){
  unsigned long currentTime = millis();
  cyclicFunction90s(currentTime);
  cyclicFunction1s(currentTime);
}
   