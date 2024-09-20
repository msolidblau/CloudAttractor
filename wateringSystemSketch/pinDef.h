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
int cycles = 0;

unsinged long startTime;

unsinged long zone1Time;
unsinged long zone2Time;
unsinged long zone3Time;
unsinged long zone4Time;
