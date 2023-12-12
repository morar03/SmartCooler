#include "./CyclicFunctions.h"


unsigned long lastTime90s  = 90000;
unsigned long lastTime1s  = 1000; 

void cyclicFunction90s(unsigned long currentTime) {
  if (currentTime - lastTime90s >= interval90s) {
    lastTime90s = currentTime;

//////////-------90.000MS-------//////////

    vControlCooler();

////////////////////////////////////////////////
  }
}

void cyclicFunction1s(unsigned long currentTime) {
  if (currentTime - lastTime1s >= interval1s) {
    lastTime1s = currentTime;

//////////--------1.000MS--------//////////

    vCheckTemperatureAndUpdateInFirebase();

////////////////////////////////////////////////
  }
}