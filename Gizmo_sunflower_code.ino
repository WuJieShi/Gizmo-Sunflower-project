const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
#include <Servo.h>
Servo myservo; 

// Global Variables
volatile int pos = 0;
volatile int no = 0;  
int check = 0;
int MAX_PWM = 10;
int MIN_PWM = 0;
int yes = 0;

// Light Sensor Values
int frontvalue = 0;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int speeds = 60;

// Pins
int MOTOR_AIN1 = 5;
int MOTOR_AIN2 = 6;
int front = A0;
int right = A2;
int left = A3;
int back = A1;
int LED = 13;



void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   myservo.attach(9);
 pinMode(MOTOR_AIN1, OUTPUT);
 pinMode(MOTOR_AIN2, OUTPUT);
 pinMode(front, INPUT);
 pinMode(right, INPUT);
 pinMode(left, INPUT);
 pinMode(back, INPUT);
 attachInterrupt(digitalPinToInterrupt(3),MicFunc,RISING); //The interrupt catches a rise in the 
 //the signal it then bypasses the other loops and goes to mic func.
}

void loop() {

    digitalWrite(LED,HIGH);
  if (no==1){
    delay (200);
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);
    no = 0;
  }
  }
  
  frontvalue = analogRead(front);
  value1 = analogRead(left);
  value2 = analogRead(back);
  value3 = analogRead(right);
  Serial.println(frontvalue);
  Serial.println(value1);
  Serial.println(value2);
  Serial.println(value3);
    
 if(value1 -50 >= frontvalue and value1 > value3 or value2-50 >= frontvalue and value2 > value3){
 digitalWrite(MOTOR_AIN1, HIGH); //If the left or back sensor has a larger value the motor will spin left
 digitalWrite(MOTOR_AIN2, LOW);
 Serial.print("Turning left");
}
 else if(value3 -50 >= frontvalue) {
  digitalWrite(MOTOR_AIN1, LOW); //If the right sensor has a larger value the motor will spin right
  digitalWrite(MOTOR_AIN2,HIGH);
  Serial.print("Turning right toward the light");
 }
 // front has the biggest value the motor will not turn
 else if(frontvalue+50 > value1 and frontvalue+50 > value2 and frontvalue+50 > value3){
 Serial.print("Front is brightest");
 digitalWrite(MOTOR_AIN1, LOW);
 digitalWrite(MOTOR_AIN2, LOW);
 delay(100);
 }
 delay(1000);
   }

void MicFunc (){
  digitalWrite(LED,LOW);
   digitalWrite(MOTOR_AIN1, LOW);
 digitalWrite(MOTOR_AIN2, LOW);
  myservo.write(180);              // tell servo to go to position in variable 'pos'
  no = 1; //GLOBAL VARIABLE it tells me the interrupt system ran
  }
