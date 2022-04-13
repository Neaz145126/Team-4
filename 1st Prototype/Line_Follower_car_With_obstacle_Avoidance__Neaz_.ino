
//including the libraries
#include <AFMotor.h>
#include <NewPing.h>

//defining pins and variables
#define left A0
#define right A2
#define TRIG A3
#define ECHO A5
#define MAX_DISTANCE 100

NewPing sonar (TRIG, ECHO, MAX_DISTANCE);


//defining motors
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);



void setup() {
  TCCR0B = TCCR0B & B11111000 | B00000010 ;
  //declaring pin types
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  //begin serial communication
  Serial.begin(9600);

}

void loop() {
  //printing values of the sensors to the serial monitor
  Serial.println(analogRead(left));

  Serial.println(analogRead(right));

  int duration, distance;
  // Output pulse with 1ms width on trigPin
  digitalWrite(TRIG, HIGH);
  delay(1);
  digitalWrite(TRIG, LOW);
  // Measure the pulse input in echo pin
  duration = pulseIn(ECHO, HIGH);
  // Distance is half the duration devided by 29.1 (from datasheet)
  distance = (duration / 2) / 29.1;

  if (distance <= 13) {
    motor1.run(RELEASE);
    motor1.setSpeed(0);
    motor2.run(RELEASE);
    motor2.setSpeed(0);
    motor3.run(RELEASE);
    motor3.setSpeed(0);
    motor4.run(RELEASE);
    motor4.setSpeed(0);
    delay(100);
  }

  else
  {
    //line detected by both
    if (!analogRead(left) == 0 && !analogRead(right) == 0)
    {
      //Forward
      motor1.run(BACKWARD);
      motor1.setSpeed(150);
      motor2.run(BACKWARD);
      motor2.setSpeed(150);
      motor3.run(BACKWARD);
      motor3.setSpeed(150);
      motor4.run(BACKWARD);
      motor4.setSpeed(150);
    }
    //line detected by left sensor
    else if ((!digitalRead(right) == 0) && digitalRead(left) == 0) {
      //turn RIGHT
      motor1.run(FORWARD);
      motor1.setSpeed(200);
      motor2.run(FORWARD);
      motor2.setSpeed(200);
      motor3.run(BACKWARD);
      motor3.setSpeed(200);
      motor4.run(BACKWARD);
      motor4.setSpeed(200);

    }
    //line detected by right sensor
    else if (digitalRead(right) == 0 && !digitalRead(left) == 0) {
      //turn LEFT
      motor1.run(BACKWARD);
      motor1.setSpeed(200);
      motor2.run(BACKWARD);
      motor2.setSpeed(200);
      motor3.run(FORWARD);
      motor3.setSpeed(200);
      motor4.run(FORWARD);
      motor4.setSpeed(200);

    }
    //line detected by none
    else if (digitalRead(left) == 0 && digitalRead(right) == 0)
    {
      //stop
      motor1.run(RELEASE);
      motor1.setSpeed(0);
      motor2.run(RELEASE);
      motor2.setSpeed(0);
      motor3.run(RELEASE);
      motor3.setSpeed(0);
      motor4.run(RELEASE);
      motor4.setSpeed(0);

    }
  }


}
