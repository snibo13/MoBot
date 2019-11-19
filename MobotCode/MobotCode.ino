//Library for motor
#include <SparkFun_TB6612.h>


//Error fixing
int TODO = 5;


//Pin assignment (Line follower)
const int rightSensor = A1; //GND on Left Side orientation
const int leftSensor = A2;
const int midSensor = A0;


const int lineLvl = 200;

//Pin assignment (Motor)
int rightMotor1 = 2;
int rightMotor2 = 4;
int rightMotorVel = 5;

int leftMotor1 = 7;
int leftMotor2 = 8;
int leftMotorVel = 6;

int stdby = 9;

//Compensates for physical orientation and motor spin direction
int offsetL = 1;
int offsetR = 1;

Motor leftMotor = Motor(leftMotor1, leftMotor2, leftMotorVel, offsetL, stdby);
Motor rightMotor = Motor(rightMotor1, rightMotor2, rightMotorVel, offsetR, stdby);

//Physical variables
const float sensorOffset = 5;
const float radius = 5;
const float velocity = 50;
const int angle = 0;

//Pin assignment (Ultrasonic)
int triggerPin = TODO;
int echoPin = TODO;

//Ultrasonic variables
long duration;
int distance;


void setup() {
  pinMode(rightSensor, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(midSensor, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

//Motor demo
//void loop() {
//  turn(0);
//  delay(1000);
//  leftMotor.brake();
//  rightMotor.brake();
//  delay(1000);
//  turn(20);
//  delay(1000);
//  leftMotor.brake();
//  rightMotor.brake();
//  delay(1000);
//  turn(-20);
//  delay(1000);
//  leftMotor.brake();
//  rightMotor.brake();
//  delay(1000);
//}


//Line reading demo
void loop() {
  readLine();
  delay(2000);
}

void readLine() {
  float left = analogRead(leftSensor);
  float right = analogRead(rightSensor);
  float middle = analogRead(midSensor);
  float theta = 0;
  if (left <= lineLvl) {
    Serial.println("Left");
  } else if (right <= lineLvl) {
    Serial.println("Right");
  } else if (middle <= lineLvl){
    Serial.println("Center");
  } else {
    Serial.println("No Line");
  }
//  turn(theta);
}

/*
 * Turns the bot to the desired angle from the current
 * NOTE: Straightening requires a turn
 * param(theta): angle to turn to left or right
 */
void turn(float theta) {
  float t = sensorOffset/velocity;
  Serial.println(t);
  float w = theta/t;
  Serial.println(theta);
  float leftWheelVelocity = velocity - w;
  float rightWheelVelocity = velocity + w;
  Serial.println(leftWheelVelocity);
  Serial.println(rightWheelVelocity);
  if (leftWheelVelocity == rightWheelVelocity == 0) {
    leftMotor.brake();
    rightMotor.brake();
  }
  driveBot(leftWheelVelocity, rightWheelVelocity);
}

/*
 * Writes the voltages necessary to drive the left and
 * right wheels at the desired velocity
 * param leftWheelVelocity, rightWheelvelocity
 */
void driveBot(float lVelocity, float rVelocity) {
    leftMotor.drive(lVelocity, 1000);
    rightMotor.drive(rVelocity, 1000);
    
}
void readDistance() {

}
