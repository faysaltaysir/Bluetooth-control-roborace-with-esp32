/****

                Code Written by,
                    
                    Shan ME 20 , CUET
                    Faysal CSE 20, CUET

          This code is for Racing bot compition , RMA Techday


*****/

#include "BluetoothSerial.h"
#include <Arduino.h>
BluetoothSerial serialBT;

//Bluetooth signal Store in this variable
char btSignal;

//initial Speed
int Speed = 200;

//declare channel for pwm Output
#define L1 0
#define L2 1
#define R1 2
#define R2 3

//PWM Pin for Controlling the speed
int enA = 26; //L1
int enB = 16;
int enC = 21; //R1
int enD = 27;

//motor controlling pin
int IN1 = 12; //L1
int IN2 = 13; //L1
int IN3 = 0;  //L2 
int IN4 = 4;  //L2
int IN5 = 19; //R1
int IN6 = 15;
int IN7 = 32;
int IN8 = 35;

void setup() {
  Serial.begin(115200);

  //Bluetooth Name
  serialBT.begin("TechNerd");

  //output pin declare
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(enD, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);

  // Setup PWM channels
  ledcSetup(L1, 20000, 8);  // Channel 0 for Motor A, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(enA, L1);
  ledcSetup(L2, 20000, 8);  // Channel 0 for Motor A, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(enB, L2);
  
  ledcSetup(R1, 20000, 8);  // Channel 0 for Motor A, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(enC, R1);
  ledcSetup(R2, 20000, 8);  // Channel 0 for Motor A, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(enD, R2);

 

  //Intial State of Car
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, LOW);
}
//int Speed = 100;
void loop() {
//  forward();
//  delay(100000);
  while (serialBT.available()) {
    btSignal = serialBT.read();
    //Serial.println(btSignal);

    if (btSignal == '0') Speed = 100;
    if (btSignal == '1') Speed = 110;
    if (btSignal == '2') Speed = 120;
    if (btSignal == '3') Speed = 130;
    if (btSignal == '4') Speed = 140;
    if (btSignal == '5') Speed = 150;
    if (btSignal == '6') Speed = 180;
    if (btSignal == '7') Speed = 200;
    if (btSignal == '8') Speed = 220;
    if (btSignal == '9') Speed = 240;
    if (btSignal == 'q') Speed = 255;

//to see the incoming signal in serial monitor
    Serial.println(btSignal);
    
  //backward
    if (btSignal == 'B') {
      backward();
    }

  //forward
    else if (btSignal == 'F') {
      forward();
    }

  //LEFT
    else if (btSignal == 'L') {
      left();
    }

  //RIGHT
    else if (btSignal == 'R') {
      right();
    }
    

  //STOP
    else if (btSignal == 'S') {
      stop();
    }
  }
}


//function for control motor
void backward() {
  ledcWrite(L1, Speed);
  ledcWrite(L2, Speed);
  ledcWrite(R1, Speed);
  ledcWrite(R2, Speed);

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  digitalWrite(IN5, 0);
  digitalWrite(IN6, 1);
  digitalWrite(IN7, 0);
  digitalWrite(IN8, 1);  
}


void forward() {
  ledcWrite(L1, Speed);
  ledcWrite(L2, Speed);
  ledcWrite(R1, Speed);
  ledcWrite(R2, Speed);

  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  digitalWrite(IN5, 1);
  digitalWrite(IN6, 0);
  digitalWrite(IN7, 1);
  digitalWrite(IN8, 0);  
}
void left() {
  ledcWrite(L1, Speed);
  ledcWrite(L2, Speed);
  ledcWrite(R1, Speed);
  ledcWrite(R2, Speed);

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  digitalWrite(IN5, 1);
  digitalWrite(IN6, 0);
  digitalWrite(IN7, 1);
  digitalWrite(IN8, 0);  
}

void right() {
  ledcWrite(L1, Speed);
  ledcWrite(L2, Speed);
  ledcWrite(R1, Speed);
  ledcWrite(R2, Speed);

  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  digitalWrite(IN5, 0);
  digitalWrite(IN6, 1);
  digitalWrite(IN7, 0);
  digitalWrite(IN8, 1);  
}

void stop() {
  ledcWrite(L1, 0);
  ledcWrite(L2, 0);
  ledcWrite(R1, 0);
  ledcWrite(R2, 0);

  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  digitalWrite(IN5, 1);
  digitalWrite(IN6, 0);
  digitalWrite(IN7, 1);
  digitalWrite(IN8, 0);  
}
