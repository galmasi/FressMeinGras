/*
  This code runs a servo and an ultrasound based radar.

  Results are continuously transmitted over serial line as follows:
  <angle in degrees> <distance in cm> <crlf>

  Over the same serial line the radar can be reset with "S"
  or started with a certain scan delay: G<x>, where 
  the scan delay is 100 + 50 * x milliseconds.
*/


#include <Servo.h>

#define trigPin 13
#define echoPin 12
#define servoPin 14

int scan;
int angle;
int dangle;
int wait=200;

Servo servo1;


void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(servoPin, OUTPUT);

  angle = 0;
  dangle=1;
  scan = 0;
  wait=200;

  servo1.attach(A0);
}



void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'S') scan = 0;
    if (c == 'G') {
      scan = 1;
      c=Serial.read();
      wait=(c-'0')*50 + 100;
    }
  }
   
  Serial.print(angle);
  Serial.print(" ");
  if (distance >= 350 || distance <= 0){
    Serial.println("  999");
  }
  else {
    Serial.println(distance);
  }

  
  servo1.write(angle);
  if (scan) angle += dangle;
  if (angle > 178) { dangle = -5; }
  if (angle < 2) { dangle = 5; }
  
  delay(wait);
}

