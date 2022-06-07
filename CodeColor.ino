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

// Setting Global variable
int rgbValues[3] = {};

void redColorSensor();

void setup() 
{
  //Setting up serial monitor
  Serial.begin(9600);        // Using standard baudrate

  //Getting the pinmodes set
  pinMode(HUE_S0, OUTPUT);
  pinMode(HUE_S1, OUTPUT);
  pinMode(HUE_S2, OUTPUT);
  pinMode(HUE_S3, OUTPUT);
  pinMode(HUE_OUT, INPUT); 

//Maximum frequency setup
digitalWrite(HUE_S0, HIGH);
digitalWrite(HUE_S1, HIGH);

delay(500);
}


void loop() 
{
  readColorSensor();

  // Display Color Sensor Reading
  Serial.print("Red| Green| Blue| Intensity: ");
  Serial.print(rgbValues[RED]);
  Serial.print(" | ");
  Serial.print(rgbValues[GREEN]);
  Serial.print(" | ");
  Serial.print(rgbValues[BLUE]);
  Serial.print(" | ");

  // Detect the primary color component
  if (rgbValues[RED] < rgbValues[BLUE] && rgbValues[RED] < rgbValues[GREEN]) 
  {
    Serial.println("RED");
  } else if (rgbValues[GREEN] < rgbValues[BLUE] && rgbValues[GREEN] < rgbValues[RED]) 
  {
    Serial.println("GREEN");
  } else if (rgbValues[BLUE] < rgbValues[GREEN] && rgbValues[BLUE] < rgbValues[RED]) 
  {
    Serial.println("BLUE");
  } else
  {    Serial.println("NO FILTER");
  }

  //delay between readings
  delay(2000);
}

void readColorSensor() 
{
  //Read Red
  digitalWrite(HUE_S2, LOW);
  digitalWrite(HUE_S3, LOW);
  rgbValues[0] = pulseInLong(HUE_OUT , HIGH);

  //Read Green
  digitalWrite(HUE_S2, HIGH);
  digitalWrite(HUE_S3, HIGH);
  rgbValues[1] = pulseInLong(HUE_OUT , HIGH);


  //Read Blue
  digitalWrite(HUE_S2, LOW);
  digitalWrite(HUE_S3, HIGH);
  rgbValues[2] = pulseInLong(HUE_OUT , HIGH);

  //No Filter
  digitalWrite(HUE_S2, HIGH);
  digitalWrite(HUE_S3, LOW);
  rgbValues[3] = pulseInLong(HUE_OUT , HIGH);
}
