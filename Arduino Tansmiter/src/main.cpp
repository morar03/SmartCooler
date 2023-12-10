#include <Arduino.h>


#include <OneWire.h>
#include <DallasTemperature.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);	

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

void setup()
{
    Serial.begin(9600);	  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
  // Send the command to get temperatures
    sensors.requestTemperatures(); 
    float temperature = sensors.getTempCByIndex(0);
  // float temperature = -224.5;

    char msg [10];
    dtostrf(temperature, 4,1, msg);

    Serial.println(msg);
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
}