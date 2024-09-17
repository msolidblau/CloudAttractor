#include "Arduino.h"

#include "thingProperties.h"
#include "matrix.h"




//set relay pins
const int zone1Pin = 8;
const int zone2Pin = 9;
const int zone3Pin = 10;
const int zone4Pin = 11;


const int devled = 13;

//setup DHT
#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float heatIndex;

// Maximum humidity variable
int maxHum = 70;


unsigned long relay1StartTime;
unsigned long relay2StartTime;
unsigned long relay3StartTime;
unsigned long relay4StartTime;
bool waterLock;
int delayTime = 2000;