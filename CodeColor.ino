#include <Arduino.h>

#define RED 0
#define GREEN 1
#define BLUE 2

//Pin configuration
const char HUE_S0 = 6;
const char HUE_S1 = 5;
const char HUE_S2 = 4;
const char HUE_S3 = 3;
const char HUE_OUT = 2;

int rgbValues[3] = {};

void redColorSensor();

void setup() 
{
  
  Serial.begin(9600);        // Using standard baudrate

  //Getting the pinmodes set
  
