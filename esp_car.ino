#include "BluetoothSerial.h"


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

BluetoothSerial SerialBT;

//Right motor
#define r_en 22 
#define r_in1 15
#define r_in2 18

//Left motor
#define l_en 23
#define l_in1 19
#define l_in2 21

const int PWMFreq = 20000; /* 1 KHz */
const int PWMResolution = 8;
const int rightMotorPWMSpeedChannel = 4;
const int leftMotorPWMSpeedChannel = 5;

void setup() {
  // put your setup code here, to run once:
 
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name // <------- set this to be the same as the name you chose above!!!!!
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(r_en,OUTPUT);
  pinMode(r_in1,OUTPUT);
  pinMode(r_in2,OUTPUT);
  
  pinMode(l_en,OUTPUT);
  pinMode(l_in1,OUTPUT);
  pinMode(l_in2,OUTPUT);

  //Set up PWM for speed
  ledcSetup(rightMotorPWMSpeedChannel, PWMFreq, PWMResolution);
  ledcSetup(leftMotorPWMSpeedChannel, PWMFreq, PWMResolution);  
  ledcAttachPin(r_en, rightMotorPWMSpeedChannel);
  ledcAttachPin(l_en, leftMotorPWMSpeedChannel); 

  motor(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (SerialBT.available()) {
    char val = SerialBT.read();
    Serial.write(val);
  }
//  Serial.println(val);
}



void motor(int rightMotorSpeed, int leftMotorSpeed)
{
  if (rightMotorSpeed < 0)
  {
    digitalWrite(r_in1,LOW);
    digitalWrite(r_in2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(r_in1,HIGH);
    digitalWrite(r_in2,LOW);      
  }
  else
  {
    digitalWrite(r_in1,LOW);
    digitalWrite(r_in2,LOW);      
  }
  
  if (leftMotorSpeed < 0)
  {
    digitalWrite(l_in1,LOW);
    digitalWrite(l_in2,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(l_in1,HIGH);
    digitalWrite(l_in2,LOW);      
  }
  else
  {
    digitalWrite(l_in1,LOW);
    digitalWrite(l_in2,LOW);      
  }
  
  ledcWrite(rightMotorPWMSpeedChannel, abs(rightMotorSpeed));
  ledcWrite(leftMotorPWMSpeedChannel, abs(leftMotorSpeed));  
}
