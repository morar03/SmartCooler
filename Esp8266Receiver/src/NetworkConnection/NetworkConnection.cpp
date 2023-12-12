
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

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

void wifiConnect(void) {

  // Uncomment and run it once, if you want to erase all the stored information
  // wifiManager.resetSettings();
  WiFi.mode(WIFI_STA);
  pinMode(LED_BUILTIN, OUTPUT);

  //Button change form AP in STA
  pinMode(APSTAbutton, INPUT_PULLUP);

  // Interrupt for change value(buttonStatus) from EEPROM
  attachInterrupt(digitalPinToInterrupt(APSTAbutton), ISRButtonDetect, FALLING); // trigger when button pressed
  int buttonStatus;
  // Get Value from EEPROM
  EEPROM.get(EEPROM_First_Value, buttonStatus); 

  if (buttonStatus == True){
    Serial.println("Button Reset Detected");
    digitalWrite(LED_BUILTIN, LOW);
    wifiManager.startConfigPortal("Smart Fridge AP");
    digitalWrite(LED_BUILTIN, HIGH);
    EEPROM.put(EEPROM_First_Value, False);
    EEPROM.commit();
  }else {
    Serial.println("Button Reset NO Detected");
    digitalWrite(LED_BUILTIN, HIGH);
    wifiManager.autoConnect("Smart Fridge AP");
  }
  
  // set custom ip for portal
  //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  // fetches ssid and pass from eeprom and tries to connect
  // wifiManager.autoConnect("AutoConnectAP");
  // wifiManager.startConfigPortal("AccesConnect2");
  // or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();
  
  // if you get here you have connected to the WiFi
  Serial.println("Connected to Wifi.");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.println("Connected to Database.");
}

void InitValueDatabase(void) {
  Firebase.setBool(fbdo, RouteCoolerPower_ON_OFF_Firebase, true);
  Firebase.setFloat(fbdo, RouteStatusLive_Temperature_Firebase, 8);
  Firebase.setFloat(fbdo, RouteStatusSet_Temperature_Firebase, 8);
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



void ICACHE_RAM_ATTR ISRButtonDetect(){
  button_time = millis();
  int buttonStatus;
  if (button_time - last_button_time > 500)
  {
    EEPROM.get(EEPROM_First_Value, buttonStatus);

    if (buttonStatus == True){
      EEPROM.put(EEPROM_First_Value, False);
      EEPROM.commit();
      ESP.restart();
    }else {
      EEPROM.put(EEPROM_First_Value, True);
      EEPROM.commit();
      ESP.restart();
    }
    last_button_time = button_time;
  }
}