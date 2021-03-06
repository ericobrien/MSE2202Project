#include <CharliePlexM.h>
#include <Servo.h>
#include <I2CEncoder.h>
#include <Wire.h>
#include <uSTimer2.h>

//DEBUGGERS
#define DEBUG_HALL_SENSOR
#define DEBUG_ULTRASONIC

//Hall Sensor Stuff
#define NOFIELD 505L
#define TOMILLIGAUSS 976L//AT1324: 5mV = 1 Gauss, 1024 analog steps to 5V  

//Data variables
unsigned long HallSensorValue = 0;
unsigned long UltrasonicDistance = 0;

Servo LftMtr;
Servo ArmBend;
Servo ArmBase;
Servo RgtMtr;
Servo Grip;
Servo Wrist;
I2CEncoder LftEncdr;
I2CEncoder RgtEncdr;
I2CEncoder ArmBaseEncdr;
I2CEncoder ArmBendEncdr;

//Mode Selector Variables
unsigned int ModeIndex = 0;
unsigned int ModeIndicator[6] = {
  0x00, //Default Mode (Mode 0)
  0x00FF, //Mode 1
  0x0F0F, //Mode 2
  0x3333, //Calibrate Line Tracker to Dark
  0xAAAA, //Calibrate Motors (might not need)
  0xFFFF
};

//pins
const int LftMtrPin = 4;
const int RgtMtrPin= 5;//*******
const int ArmBasePin = 0;//********
const int ArmBendPin = 0;//********
const int WristPin = 0;//********
const int GripPin = 0;//********
const int HallRgt = A0;//********
const int HallLft = A0;//********
const int HallGrip = A0;//********
const int GripLight = A0;//********
const int UltraLft = 0;//********
const int UltraRgt = 0;//********
const int UltrasonicPing = 7;
const int UltrasonicData = 6;
const unsigned HallSensor1 = A0;
const unsigned HallSensor2 = A1;

int MovFst = 2200;
int Stop = 1600;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  pinMode(LftMtrPin, OUTPUT);
  LftMtr.attach(LftMtrPin);
  LftEncdr.zero();
  
  pinMode(RgtMtrPin, OUTPUT);
  RgtMtr.attach(RgtMtrPin);
  RgtEncdr.zero();
  
  pinMode(ArmBasePin, OUTPUT);
  ArmBase.attach(ArmBasePin);
  ArmBaseEncdr.zero();
  
  pinMode(ArmBendPin, OUTPUT);
  ArmBend.attach(ArmBendPin);
  ArmBendEncdr.zero();
  pinMode(7, INPUT);
  
  //ultrasonic setup
  pinMode(UltrasonicPing, OUTPUT);
  pinMode(UltrasonicData, INPUT);
 
}
void loop(){
  DebuggerModule();
}
//functions

void DebuggerModule(){
  //Debugger module -> all debugger code can go here
  #ifdef DEBUG_HALL_SENSOR
    Serial.println((analogRead(HallSensor1) - NOFIELD) * TOMILLIGAUSS / 1000);
  #endif
  
  #ifdef DEBUG_ULTRASONIC
    Serial.print("Time (microseconds): ");
    Serial.print(UltrasonicDistance*58, DEC);
    Serial.print(", cm's: ");
    Serial.println(UltrasonicDistance);
  #endif
}

void Ping(){
  //Ping Ultrasonic
  digitalWrite(UltrasonicPing, HIGH);
  delayMicroseconds(10);//delay for 10 microseconds while pulse is in high
  digitalWrite(UltrasonicPing, LOW); //turns off the signal
  UltrasonicDistance = (pulseIn(UltrasonicData, HIGH, 10000)/58);
}

//Mode 1
void Look() {
  //if already found tesseract-> run 'Return', else-> robot starts looking for tesseracts, 
  //if detects tesseract stops and runs 'PickUp'
  //needs to keep track of position? for 'GoHome' /OR/ 'GoHome' can find home position from where it is
  //needs collision avoidance system -> runs 'Countermeasures'?
}
void Countermeasures(){
  //robot reacts to interference by other robot, after safe returns to 'Look'
}
void PickUp() {
  //robot has deteced tesseract in 'Look' and uses arm to pick it up, after picked up runs 'GoHome'
  
}
void GoHome() {
  //robot calculates and saves position and returns to base after tesseract picked up, runs 'Look'
};
void Return() {
  //robot is at start and has already picked up a tesseract, return to last position where tesseract was picked up, continue with 'Look'
}


//Mode 2

long UltrasonicDuration, UtrasonicInches, Ultrasonic_cm;
void Check(){
  //robot continiously checks wall to see if there is a tesseract available, if found runs 'Move'
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  delayMciroseconds(2);
  digitalWrite(6, HIGH);
  delayMicroseconds(5);
  digitalWrite(6, LOW);
  
  pinMode(7, INPUT);
  UltrasonicDuration = pulseIn(7, HIGH);
  /*
  UtrasonicInches = microsecondsToInches(UltrasonicDuration);
  Ultrasonic_cm = microsecondsToCentimeters(UltrasonicDuration);
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial("cm");
  Serial.printIn();
*/  
  delay(100);
  
  
}
void Move(){
//robot picks up tesseract from wall, drives under beam and hangs tesseract on overhang, returns back under beam, runs 'Check'
}



//requires timer system and tesseracts picked up counter 


