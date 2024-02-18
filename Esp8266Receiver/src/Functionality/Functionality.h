#include "./NetworkConnection/NetworkConnection.h"
#include "./RadioModule/RadioModule.h"
#include "Arduino.h"


#define PinPowerCooler D5
#define debounce 100
#define debounceBlink 10
#define CoolerOn LOW
#define CoolerOff HIGH


void vCheckTemperatureAndUpdateInFirebase(void);
void vControlCooler(void);
void InitFunctionality(void);
void vAlertRadio(void);
void vBlinkLEDAlert(void);
