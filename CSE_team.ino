/*                 Code by
 *                  Faysal cse 20
 *                  Shan ME 20
 */ 

#include "BluetoothSerial.h"


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

BluetoothSerial SerialBT;

#define RPWM1 13
#define LPWM1 14

#define RPWM2 26
#define LPWM2 33

const int pwmFreq = 20000;
const int pwmRes = 8;
const int rightMtrChannel1 = 4;
const int rightMtrChannel2 = 5;
const int leftMtrChannel1 = 6;
const int leftMtrChannel2 = 7;

//Bluetooth signal Store in this variable
char btSignal;

//initial Speed
int Speed = 100;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("PanjabiWala");
  Serial.println("Bluetooth is On");
  pinMode(RPWM1,OUTPUT);
  pinMode(LPWM1,OUTPUT);
  pinMode(RPWM2,OUTPUT);
  pinMode(LPWM2,OUTPUT);

ledcSetup(rightMtrChannel1,pwmFreq,pwmRes);
ledcSetup(rightMtrChannel2,pwmFreq,pwmRes);

ledcSetup(leftMtrChannel1,pwmFreq,pwmRes);
ledcSetup(leftMtrChannel2,pwmFreq,pwmRes);

ledcAttachPin(RPWM1,rightMtrChannel1);
ledcAttachPin(LPWM1,rightMtrChannel2);
ledcAttachPin(RPWM2,leftMtrChannel1);
ledcAttachPin(LPWM2,leftMtrChannel2);


}
  
int out1=250;

void loop() {
    while (SerialBT.available()) {
    btSignal = SerialBT.read();
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
  ledcWrite(rightMtrChannel1, 0);
  ledcWrite(rightMtrChannel2, Speed);
  
  ledcWrite(leftMtrChannel1, 0);
  ledcWrite(leftMtrChannel2, Speed); 
  }

void forward() {
  ledcWrite(rightMtrChannel1, 0);
  ledcWrite(rightMtrChannel2, Speed);
  
  ledcWrite(leftMtrChannel1, Speed);
  ledcWrite(leftMtrChannel2, 0);
   
}

void left() {
  ledcWrite(rightMtrChannel1, 150);
  ledcWrite(rightMtrChannel2, 0);
  
  ledcWrite(leftMtrChannel1, 150);
  ledcWrite(leftMtrChannel2, 0);
   
}

void right() {
  
  ledcWrite(rightMtrChannel1, 150);
  ledcWrite(rightMtrChannel2, 0);
  
  ledcWrite(leftMtrChannel1, 0);
  ledcWrite(leftMtrChannel2, 150); 
  
}

void stop() {
  ledcWrite(rightMtrChannel1, 0);
  ledcWrite(rightMtrChannel2, 0);
  
  ledcWrite(leftMtrChannel1, 0);
  ledcWrite(leftMtrChannel2, 0);
}
  
