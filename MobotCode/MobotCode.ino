/*
 * Code for MoBot Project
 * Fundamentals of Mechanical Engineering
 * 24-101
 *
 * by Sidney Nimako-Boateng
 */


//Library for motor
#include <SparkFun_TB6612.h>


//Pin assignment (Line follower)
const int rightSensor = A1; //GND on Left Side orientation
const int leftSensor = A2;
const int midSensor = A0;

//Line follower constants
const int lineLvl = 200;

//Pin assignment (Motor)
const int rightMotor1 = 2;
const int rightMotor2 = 4;
const int rightMotorVel = 5;

const int leftMotor1 = 7;
const int leftMotor2 = 8;
const int leftMotorVel = 6;

const int stdby = 9;

//Motor constants
//Compensates for physical orientation and motor spin direction
const int offsetL = 1;
const int offsetR = -1;

//Motor instatiation
Motor leftMotor = Motor(leftMotor1, leftMotor2, leftMotorVel, offsetL, stdby);
Motor rightMotor = Motor(rightMotor1, rightMotor2, rightMotorVel, offsetR, stdby);

//Physical variables
const float sensorOffset = 5;
const float radius = 5;
const float velocity = 200;
const int angle = 0;

//Pin assignment (Ultrasonic)
int triggerPin = 10;
int echoPin = 11;

//Ultrasonic variables
long duration;
int distance;


void setup() {
  pinMode(rightSensor, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(midSensor, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //Clear the triggerPin
  digitalWrite(triggerPin, LOW);
  Serial.begin(9600);
}

void loop() {
  driveBot(200,200);
  delay(2000);
  driveBot(0,0);
  delay(1000);
}
/*
 * Ultrasonic demo
 * Place in loop
 */
void ultrasonicDemo() {
  delay(2);
  //Pin high for 10 useconds
  digitalWrite(triggerPin, HIGH);
  delay(10);
  digitalWrite(triggerPin, LOW);

  //Read return time
  duration = pulseIn(echoPin, HIGH);

  //Calculate distanse fromecho time
  distance = duration * 0.034/ 2.0;

  Serial.println(distance);
  delay(200);
}


/*
 * Motor Demo 
 * Place in loop
 */
void motorDemo() {
  turn(0);
  delay(1000);
  leftMotor.brake();
  rightMotor.brake();
  delay(1000);
  turn(20);
  delay(1000);
  leftMotor.brake();
  rightMotor.brake();
  delay(1000);
  turn(-20);
  delay(1000);
  leftMotor.brake();
  rightMotor.brake();
  delay(1000);
}


/*
 * Line reading demo
 * Place in loop
 */
 void lineDemo() {
  readLine();
  delay(2000);
}

void readLineDemo() {
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
}

void readLine() {
  float left = analogRead(leftSensor);
  float right = analogRead(rightSensor);
  float middle = analogRead(midSensor);
  float theta = 0;
  if (left <= lineLvl) {
    theta = 1;
  } else if (right <= lineLvl) {
    theta = 1;
  } else if (middle <= lineLvl){
    theta = 0;
  } else {
    Serial.println("No Line");
  }
  turn(theta);
}
/*
 * Turns the bot to the desired angle from the current
 * NOTE: Straightening requires a turn
 * param(theta): angle to turn to left or right
 * TODO: Consider remapping velocities to max and min on motors
 */
void turn(float theta) {
//  float t = sensorOffset/velocity;
//  Serial.println(t);
//  float w = theta/t;
//  Serial.println(theta);
  float leftWheelVelocity = velocity - theta;
  float rightWheelVelocity = velocity + theta;
  Serial.println(leftWheelVelocity);
  Serial.println(rightWheelVelocity);
//  if (leftWheelVelocity == rightWheelVelocity == 0) {
//    leftMotor.brake();
//    rightMotor.brake();
//  }
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
