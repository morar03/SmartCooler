
#include "RadioModule.h"

RH_ASK driver(2000, 2, 4, 5);

void initRadioModule(void){
if (!driver.init())
         Serial.println("init failed");
}


bool getAndConvertRadioMessage(float* temperatureValue){
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)){
        String receivedMessage = (char*)buf;
        Serial.print("Received message: ");
        Serial.println(receivedMessage);
        // Conversion from std::string to double
        *temperatureValue = receivedMessage.toFloat();
        Serial.print("Conversia Mesajului: ");
        Serial.println(*temperatureValue);
        return true; // Conversion succesfull
    }
    return false;
}
