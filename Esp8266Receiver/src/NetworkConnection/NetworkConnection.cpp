
#include "NetworkConnection.h"


const std::string SeriesDevice = Serial_Number_Device;


const std::string RouteCoolerPower_ON_OFF_Firebase = ConcatRouteDevices(SeriesDevice, "/CoolerPower_ON_OFF_Firebase");
const std::string RouteStatusLive_Temperature_Firebase = ConcatRouteDevices(SeriesDevice,"/liveStatus_Temperature_Firebase");
const std::string RouteStatusSet_Temperature_Firebase = ConcatRouteDevices(SeriesDevice,"/setStatus_Temperature_Firebase");

// WiFiManager
// Local intialization. Once its business is done, there is no need to keep it around
WiFiManager wifiManager;

//Define Firebase Data object
FirebaseData fbdo;

bool static FailConnectWifi = False;

void wifiConnect(void) {
  
  // Uncomment and run it once, if you want to erase all the stored information
  // wifiManager.resetSettings();
  pinMode(LED_BUILTIN_AUX, OUTPUT);
  delay(2000);

  //Button change form AP in STA
  pinMode(APSTAbutton, INPUT_PULLUP);
  
  wifiManager.setConfigPortalTimeout(180);
  digitalWrite(LED_BUILTIN_AUX, LOW);
  if(!wifiManager.autoConnect("Smart Cooler AP")) {
    FailConnectWifi = True;
  }

  if (!FailConnectWifi){
    // if you get here you have connected to the WiFi
    Serial.println("Connected to Wifi.");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Serial.println("Connected to Database.");
    digitalWrite(LED_BUILTIN_AUX, HIGH);
  }
}

void vcheckNetworkButtonConnection(void){
  if ( digitalRead(APSTAbutton) == LOW ) {
     delay(100);
    if( digitalRead(APSTAbutton) == LOW ){
      Serial.println("Button Pressed");
      delay(3000); // STM delay hold
      if( digitalRead(APSTAbutton) == LOW ){
        Serial.println("Start Config AP Smart Cooler");
        digitalWrite(LED_BUILTIN_AUX, LOW);
        wifiManager.startConfigPortal("Smart Cooler AP");
        ESP.restart();  
      }
    } 
  }
}

bool getStatusConnection(void){
  return !FailConnectWifi;
}

void InitValueDatabase(void) {
  Firebase.setBool(fbdo, RouteCoolerPower_ON_OFF_Firebase, true);
  Firebase.setFloat(fbdo, RouteStatusLive_Temperature_Firebase, 99);
  // Firebase.setFloat(fbdo, RouteStatusSet_Temperature_Firebase, 6);
}

bool getEvent_ON_OFF_Firebase(void){
  Firebase.getBool(fbdo, RouteCoolerPower_ON_OFF_Firebase);
  bool TriggerEvent_ON_OFF = fbdo.boolData();
  return TriggerEvent_ON_OFF;
}

void setEvent_ON_OFF_Firebase(bool event_ON_OFF_Firebase){
  Firebase.setBool(fbdo, RouteCoolerPower_ON_OFF_Firebase, event_ON_OFF_Firebase);
}

float getStatusLive_Temperature_Firebase(void){
  Firebase.getFloat(fbdo, RouteStatusLive_Temperature_Firebase);
  return fbdo.floatData();
}

void setStatusLive_Temperature_Firebase(float StatusLiveTemperature){
  Firebase.setFloat(fbdo,RouteStatusLive_Temperature_Firebase, StatusLiveTemperature);
}

float getStatusSet_Temperature_Firebase(void){
  Firebase.getFloat(fbdo, RouteStatusSet_Temperature_Firebase);
  float Temperature = fbdo.floatData();

  return Temperature;
} 

std::string ConcatRouteDevices(std::string string1, std::string string2){
   std::string RouteConcat = "Devices/";
   RouteConcat += string1;
   RouteConcat += string2;
   return RouteConcat;
 }

float StringToFloat(std::string string){
  float number = std::stod(string);
  return number;
 };
