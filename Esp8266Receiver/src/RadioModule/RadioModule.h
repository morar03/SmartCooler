#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <iostream>
#include <string>
#include "Arduino.h"
#include "./NetworkConnection/NetworkConnection.h"

void initRadioModule(void);
bool getAndConvertRadioMessage(float* temperatureValue);
