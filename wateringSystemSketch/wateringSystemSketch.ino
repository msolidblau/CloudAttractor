#include <DHT.h>
#include <DHT_U.h>
#include "pinDef.h"
#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;

void setup() {
  matrix.begin();




  Serial.begin(9600);
  delay(1500);

  //wifi setup
  matrix.loadSequence(LEDMATRIX_ANIMATION_WIFI_SEARCH);
  matrix.play(true);
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo(); 
  Serial.println(WiFi.status());

  //ArduinoStartup animation
  matrix.play(false);
  matrix.loadSequence(LEDMATRIX_ANIMATION_STARTUP);
  matrix.play(true);

  //turn on dht
  dht.begin();

  mode = 1; 
  
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


  delay(1500);
  matrix.play(false);
  delay(50);
  matrix.loadFrame(LEDMATRIX_CLOUD_WIFI);
}





const uint32_t zone4[] = {
  0xfa412,
  0x423e4048,
  0x4f84000,
  66
};


const uint32_t zone3[] = {
  0xf9e10,
  0x22044088,
  0x4f9c000,
  66
};


const uint32_t zone2[] = {
  0xf8e11,
  0x12024048,
  0x8f9f000,
  66
};


const uint32_t zone1[] = {
  0xf8610,
  0xa2124028,
  0x2f8f000,
  66
};


const uint32_t off[] = {
  0x7198b,
  0x38a28bb8,
  0xa2722000,
  66
};





void matrixzone1() {
  matrix.loadFrame(zone1);
}

void matrixzone2() {
  matrix.loadFrame(zone2);
}

void matrixzone3() {
  matrix.loadFrame(zone3);
}

void matrixzone4() {
  matrix.loadFrame(zone4);
}

void matrixReturnNormal() {
  matrix.loadFrame(LEDMATRIX_CLOUD_WIFI);
}



void checkZone1() {

  if (relay1Setting == true) {
    digitalWrite(zone1Pin, HIGH);
    matrixzone1();
  } else {
    delay(200);
    digitalWrite(zone1Pin, LOW);
  }
}


void checkZone2() {

  if (relay2Setting == true) {
    digitalWrite(zone2Pin, HIGH);
    matrixzone2();
  } else {
    delay(200);
    digitalWrite(zone2Pin, LOW);
  }
}


void checkZone3() {

  if (relay3Setting == true) {
    digitalWrite(zone3Pin, HIGH);
    matrixzone3();
  } else {
    delay(200);
    digitalWrite(zone3Pin, LOW);
  }
}


void checkZone4() {

  if (relay4Setting == true) {
    digitalWrite(zone4Pin, HIGH);
    matrixzone4();
  } else {
    delay(200);
    digitalWrite(zone4Pin, LOW);
  }
}



void autoCheck() {
  if(uniSchedule.isActive()){
    if(relay1Setting == false){
      relay1Setting = true;
      startTime = millis();
      checkZone1();
    }
    delay(50);
    if(relay1Setting == true && millis() - startTime >= zone1Time){
      relay2Setting == true;
      startTime == millis();
      checkZone2();
    }
    delay(50);
    if(relay2Setting == true && millis() - startTime >= zone2Time){
      relay3Setting == true;
      startTime == millis();
      checkZone3();
    }
    delay(50);
    if(relay3Setting == true && millis() - startTime >= zone3Time){
      relay4Setting == true;
      startTime == millis();
      checkZone4();
    }
    delay(50);
    if(relay4Setting == true && millis() - startTime >= zone4Time){
      cycles++;
      Serial.println("cycle complete");
      Serial.println("log: ");
      Serial.print(cycles);
      relay1Setting = false;
      relay2Setting = false;
      relay3Setting = false;
      relay4Setting = false;
    }
    











  }else{
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


  //if humidity is at certain level
  if (humidity >= maxHumidity) {
    humidityOveride = true;
    //turn everything off
    relay1Setting = false;
    relay2Setting = false;
    relay3Setting = false;
    relay4Setting = false;



    //if not then carry on.
  } else {
    humidityOveride = false;

    //off
    if (mode == 1) {
      relay1Setting = false;
      relay2Setting = false;
      relay3Setting = false;
      relay4Setting = false;
    }

    //automatic
    if (mode == 2) {
      autoCheck();
    }

    //manual
    if (mode == 3) {

      if(mode == 3 && relay4Setting == false){
        checkZone1();
        Serial.println("z1c");
      }else{
        Serial.println("Override Failed");
      }

      
      if(mode == 3 && relay1Setting == false){
        delay(50);
        checkZone2();
        Serial.println("z2c");
      }else{
        Serial.println("Override Failed");
      }


      if(mode == 3 && relay2Setting == false){
        delay(50);
        checkZone3();
        Serial.println("z3c");
      }else{
        Serial.println("Override Failed");
      }

      
      if(mode == 3 && relay2Setting == false){
        delay(50);
        checkZone4();
        Serial.println("z4c");
      }else{
        Serial.println("Override Failed");
      }

      
    }
  }
}



















//  Useless code //

void onRelay1SettingChange() {
}
void onRelay2SettingChange() {
}
void onRelay3SettingChange() {
}
void onRelay4SettingChange() {
}
void onUniScheduleChange() {
}
void onZone1TimeChange() {
}
void onZone2TimeChange() {
}
void onZone3TimeChange() {
}
void onZone4TimeChange() {
}
void onMaxHumidityChange() {
}
void onTempChange() {
}
void onModeChange() {
  matrixReturnNormal();
}
