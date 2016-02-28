#include <AccelStepper.h>
#include <MultiStepper.h>

#define HALFSTEP 4

// Motor pin definitions
#define motor1Pin1  13     // IN1 on the ULN2003 driver 1
#define motor1Pin2  12     // IN2 on the ULN2003 driver 1
#define motor1Pin3  11     // IN3 on the ULN2003 driver 1
#define motor1Pin4  10     // IN4 on the ULN2003 driver 1

#define motor2Pin1  7      // IN1 on the ULN2003 driver 2
#define motor2Pin2  6      // IN2 on the ULN2003 driver 2
#define motor2Pin3  5      // IN3 on the ULN2003 driver 2
#define motor2Pin4  4      // IN4 on the ULN2003 driver 2

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper s1(HALFSTEP, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);
AccelStepper s2(HALFSTEP, motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);


// Setup Charachteristics:
#define stepsPerRevolution 513   // 513 Steps per Revolution.
#define rotationLength 1      //Length of the string by one rotation 

// ---------------
// Initialisation
 
  float x;        //current Position
  float y;

//  float lastX;  // last Position, currently unused
//  float lastY;  
  
#define x1 0   //Position S1
#define y1 0
#define x2 10  //Position S2
#define y2 0

#define x0 5   //Position Start
#define y0 5

  //needed Variables 
  float c1;
  float c2;
  float c10;
  float c20;
  float delta1;
  float delta2;
  
  float lastLength1;
  float lastLength2;

// ----------------

void setup() {
  Serial.begin(9600);
  defineSetup();

  
  //Testing
  Serial.println("move to in Length : ");
  moveToInLength(5,10);
  delay(2000);
  
  
}

void loop() {
  runboth(4000);
}





// vvvvvvvvvvvvvvvvvvvv    Controlling Methods vvvvvvvvvvvvv
void defineSetup() {
  //needs to run once:
  Serial.println("Setup : ");
  Serial.println("getLengthOf c10 & c20 : ");
  c10 = getLengthOf(1,x0,y0); // Initial Lengths
  c20 = getLengthOf(2,x0,y0);
  lastLength1 = c10; //not in use 
  lastLength2 = c20;  // ""
  s1.setCurrentPosition(lengthToSteps(c10));
  s2.setCurrentPosition(lengthToSteps(c20));
  

  //Speed controlling
  s1.setAcceleration(10);
  s2.setAcceleration(10);
  s1.setMaxSpeed(100);
  s2.setMaxSpeed(100);
  delay(1000);
}

void moveToInLength(float xx, float yy){
  Serial.println("get length of xx,yy");
  Serial.println(lengthToSteps(getLengthOf(1,xx,yy)));
  Serial.println(lengthToSteps(getLengthOf(2,xx,yy)));
  s1.moveTo(lengthToSteps(getLengthOf(1,xx,yy)));
  s2.moveTo(lengthToSteps(getLengthOf(2,xx,yy)));
}

void runboth(int q){  // how many times run should be exicuted (multiplied by 1000)
  for(int i = 0; i<(1000*q); i++){
    s1.run();
    s2.run();
  }
}
 
float getLengthOf(int p, float a, float b) {
if (p==1){
   c1 = sqrt(abs((sq(x1-a)))+abs((sq(y1-b))));
   Serial.print("c1 : ");Serial.println(c1);
   return c1;
}
else if (p==2){
  c2 = sqrt(abs(sq(x2-a))+abs(sq(y2-b)));
  Serial.print("c2 : ");Serial.println(c2);
  return c2;
}
else {
  Serial.println("Error in getLengthOf");
  delay(5000);
}}

int lengthToSteps(float l){
  float s = stepsPerRevolution/rotationLength * l;  
  return s;
}

float stepsToLength(int s){
  float l = rotationLength/stepsPerRevolution * s;
  return l;
}
