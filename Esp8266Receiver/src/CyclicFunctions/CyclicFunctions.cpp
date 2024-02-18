#include "./CyclicFunctions.h"

unsigned long lastTime300s  = 0;
unsigned long lastTime90s  = 0;
unsigned long lastTime10s  = 0;


void cyclicFunction90s(unsigned long currentTime) {
  if (currentTime - lastTime90s >= interval90s) {
    lastTime90s = currentTime;

//////////-------90.000MS-------//////////

    vControlCooler();

////////////////////////////////////////////////
  }
}

void cyclicFunction1s(unsigned long currentTime) {
  if (currentTime - lastTime10s >= interval10s) {
    lastTime10s = currentTime;

//////////--------10.000MS--------//////////

    vCheckTemperatureAndUpdateInFirebase();

////////////////////////////////////////////////
  }
}