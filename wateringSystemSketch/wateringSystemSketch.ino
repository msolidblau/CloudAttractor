#include "pinDef.h"

void setup(){

  //Wifi Setup
  Serial.begin(9600);
  delay(1500); 
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  Serial.println(WiFi.status());


  //turn on dht
  dht.begin();

  //set pin modes
  pinMode(zone1Pin, OUTPUT);
  pinMode(zone2Pin, OUTPUT);
  pinMode(zone3Pin, OUTPUT);
  pinMode(zone4Pin, OUTPUT);

  //turn all pins off
  relay1Setting = false;
  relay2Setting = false;
  relay3Setting = false;
  relay4Setting = false;
}


void flashDl(){
  digitalWrite(devled, HIGH);
  delay(300);
  digitalWrite(devled, LOW);
  delay(300);
  digitalWrite(devled, HIGH);
  delay(300);
  digitalWrite(devled, LOW);
  delay(300);
}




void checkZone1() {
  //flashDl();
  if (relay1Setting == true) {
    digitalWrite(zone1Pin, HIGH);
  }else{
    digitalWrite(zone1Pin, LOW);
  }
}


void checkZone2() {
  //flashDl();
  if (relay2Setting == true) {
    digitalWrite(zone2Pin, HIGH);
  }else{
    digitalWrite(zone2Pin, LOW);
  }
}


void checkZone3() {
  //flashDl();
  if (relay3Setting == true) {
    digitalWrite(zone3Pin, HIGH);
  }else{
    digitalWrite(zone3Pin, LOW);
  }
}


void checkZone4() {
  //flashDl();
  if (relay4Setting == true) {
    digitalWrite(zone4Pin, HIGH);
  }else{
    digitalWrite(zone4Pin, LOW);
  }
}


void startTimer(){
  startTime = millis(); // Update the global startTime variable
}





void autoCheck() {
  if (uniSchedule.isActive()) {
    startTimer(); // Start the timer
    relay1Setting = true;
    delay(1000); // Wait for 1 second
    elapsedTime = millis() - startTime; // Calculate elapsed time
    if (elapsedTime >= zone1Time * 1000) { // Compare with zone1Time in milliseconds
      relay1Setting = false;
    }

    startTimer(); // Start the timer for the next zone
    relay2Setting = true;
    delay(1000); // Wait for 1 second
    elapsedTime = millis() - startTime; // Calculate elapsed time
    if (elapsedTime >= zone2Time * 1000) {
      relay2Setting = false;
    }

    startTimer(); // Start the timer for the next zone
    relay3Setting = true;
    delay(1000); // Wait for 1 second
    elapsedTime = millis() - startTime; // Calculate elapsed time
    if (elapsedTime >= zone3Time * 1000) {
      relay3Setting = false;
    }

    startTimer(); // Start the timer for the next zone
    relay4Setting = true;
    delay(1000); // Wait for 1 second
    elapsedTime = millis() - startTime; // Calculate elapsed time
    if (elapsedTime >= zone4Time * 1000) {
      relay4Setting = false;
    }
    startTime = 0; // Reset startTime
  } else {
    relay1Setting = false;
    relay2Setting = false;
    relay3Setting = false;
    relay4Setting = false;
  }
}




void loop() {
  ArduinoCloud.update();
  
  // Read data from DHT sensor
  temp = dht.readTemperature();
  humidity = dht.readHumidity();
  heatIndex = dht.computeHeatIndex(temp, humidity, false); 

  if (humidity >= maxHumidity) {
    humidityOveride = true;
    relay1Setting = false;
    relay2Setting = false;
    relay3Setting = false;
    relay4Setting = false;
  } else {
    humidityOveride = false;


    if(mode == 1){
      relay1Setting = false;
      relay2Setting = false;
      relay3Setting = false;
      relay4Setting = false;
    }


    if(mode == 2){
      autoCheck();
    }


    if(mode == 3){
      checkZone1();
      delay(50);
      checkZone2();
      delay(50);
      checkZone3();
      delay(50);
      checkZone4();
    }
  }
}






        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        

void onRelay1SettingChange()  {
}
void onRelay2SettingChange()  {
}
void onRelay3SettingChange()  {
}
void onRelay4SettingChange(){
}
void onUniScheduleChange()  {
}
void onZone1TimeChange()  {
}
void onZone2TimeChange()  {
}
void onZone3TimeChange()  {
}
void onZone4TimeChange()  {
}
void onMaxHumidityChange()  {
}
void onTempChange()  {
}
void onModeChange()  {
}