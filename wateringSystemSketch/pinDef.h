#include "Arduino.h"
#include <DHT.h>
#include <DHT_U.h>
#include "thingProperties.h"


//set relay pins
const int zone1Pin = 2;
const int zone2Pin = 4;
const int zone3Pin = 7;
const int zone4Pin = 8;


const int devled = 13;

//setup DHT
#define DHTPIN 12
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float heatIndex;

// Maximum humidity variable
int maxHum = 70;

unsigned long startTime;
unsigned long elapsedTime;