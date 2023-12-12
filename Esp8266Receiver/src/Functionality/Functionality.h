#include "./NetworkConnection/NetworkConnection.h"
#include "./RadioModule/RadioModule.h"
#include "Arduino.h"


#define PinPowerCooler D5
#define debounce 100

void vCheckTemperatureAndUpdateInFirebase(void);
void vControlCooler(void);
void InitFunctionality(void);
