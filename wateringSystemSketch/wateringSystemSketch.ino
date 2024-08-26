#include "pinDef.h"
#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;

void setup(){
  matrix.begin();


  
  //Wifi Setup
  Serial.begin(9600);
  delay(1500); 
  matrix.loadSequence(LEDMATRIX_ANIMATION_WIFI_SEARCH);
  matrix.play(true);
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  Serial.println(WiFi.status());
  matrix.play(false);
  matrix.loadSequence(LEDMATRIX_ANIMATION_STARTUP);
  
  matrix.play(true);
  
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


  delay(1500);
  matrix.play(false);
  delay(50);
  matrix.loadFrame(LEDMATRIX_CLOUD_WIFI);
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

/*
const uint32_t rain[] = {
	{
		0x7c18220,
		0x12021fc0,
		0x44155111,
		66
	},
	{
		0x7c18220,
		0x12021fc1,
		0x11155044,
		66
	}
};


*/

void matrixzone1(){
  matrix.loadFrame(zone1);
}

void matrixzone2(){
  matrix.loadFrame(zone2);
}

void matrixzone3(){
  matrix.loadFrame(zone3);
}

void matrixzone4(){
  matrix.loadFrame(zone4);
}

void matrixReturnNormal(){
  matrix.loadFrame(LEDMATRIX_CLOUD_WIFI);

}



void checkZone1() {
  //flashDl();
  if (relay1Setting == true) {
    digitalWrite(zone1Pin, HIGH);
    matrixzone1();
  }else{
    delay(200);
    digitalWrite(zone1Pin, LOW);
  }
}


void checkZone2() {
  //flashDl();
  if (relay2Setting == true) {
    digitalWrite(zone2Pin, HIGH);
    matrixzone2();
  }else{
    delay(200);
    digitalWrite(zone2Pin, LOW);
  }
}


void checkZone3() {
  //flashDl();
  if (relay3Setting == true) {
    digitalWrite(zone3Pin, HIGH);
    matrixzone3();
  }else{
    delay(200);
    digitalWrite(zone3Pin, LOW);
  }
}


void checkZone4() {
  //flashDl();
  if (relay4Setting == true) {
    digitalWrite(zone4Pin, HIGH);
    matrixzone4();
  }else{
    delay(200);
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


    //matrix.loadSequence(rain);
    //matrix.play(true);

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

    if (mode >= 4){
      matrix.loadSequence(LEDMATRIX_ANIMATION_BUG);
      matrix.play(true);
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
 matrixReturnNormal();
}