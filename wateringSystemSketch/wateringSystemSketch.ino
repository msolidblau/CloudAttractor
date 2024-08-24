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







void checkZone1() {
  if (relay1Setting == true) {
    digitalWrite(zone1Pin, HIGH);
  }else{
    digitalWrite(zone1Pin, LOW);
  }
}


void checkZone2() {
  if (relay2Setting == true) {
    digitalWrite(zone2Pin, HIGH);
  }else{
    digitalWrite(zone2Pin, LOW);
  }
}


void checkZone3() {
  if (relay3Setting == true) {
    digitalWrite(zone3Pin, HIGH);
  }else{
    digitalWrite(zone3Pin, LOW);
  }
}


void checkZone4() {
  if (relay4Setting == true) {
    digitalWrite(zone4Pin, HIGH);
  }else{
    digitalWrite(zone4Pin, LOW);
  }
}


void startTimer(){
  startTime = millis(); // Update the global startTime variable
}



void autoCheck(){

  if (uniSchedule.isActive()) {

    delay(1000);
    startTimer();
    relay1Setting = true;
    int elapsedTime = startTime - millis()
    if(elapsedTime * 1000 >= zone1Timer){
      relay1Setting = false;
    }


    delay(1000);
    startTimer();
    relay1Setting = true;
    int elapsedTime = startTime - millis()
    if(elapsedTime * 1000 >= zone2Timer){
      relay2Setting = false;
    }


    delay(1000);
    startTimer();
    relay1Setting = true;
    int elapsedTime = startTime - millis()
    if(elapsedTime * 1000 >= zone3Timer){
      relay3Setting = false;
    }


    delay(1000);
    startTimer();
    relay1Setting = true;
    int elapsedTime = startTime - millis()
    if(elapsedTime * 1000 >= zone4Timer){
      relay4Setting = false;
    }
    StartTime = 0;

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
  hum = dht.readHumidity();
  heatIndex = dht.computeHeatIndex(temp, hum, false); 

  if (hum >= maxHumidity) {
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
      checkZone2();
      checkZone3();
      checkZone4();
    }
  }
}



















