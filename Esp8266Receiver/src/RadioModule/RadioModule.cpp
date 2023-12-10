
#include "RadioModule.h"

RH_ASK driver(2000, 4, 5, 0);

void initRadioModule(void){
 if (!driver.init())
         Serial.println("init failed");
}


bool getAndConvertRadioMessage(){
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    delay(10);
    if (driver.recv(buf, &buflen)){
        String receivedMessage = "";
        // Message with a good checksum received, dump it.
       for (int i = 0; i < buflen; i++) {
      receivedMessage += (char)buf[i];
        }
        // Conversion from std::string to double
        Serial.print("Received message: ");
        Serial.println(receivedMessage);
        
        return true; // Conversion succesfull
    }
    Serial.println(driver.recv(buf, &buflen));

    return false;
}