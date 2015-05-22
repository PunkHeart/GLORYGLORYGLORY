/* 
 * //////////////////////////////////////////////////
 * // GLORY GLORY GLORY
 * //////////////////////////////////////////////////
 *
 * This script pressurizes and deflates a soft robotic penis whenever someone walks by it. 
 *
 * @author: PunkHeart AKA Billy Noble 
 * @date:   16 May 2015 
 *
 * released under a creative commons "Attribution-NonCommercial-ShareAlike 2.0" license
 * http://creativecommons.org/licenses/by-nc-sa/2.0/de/
 *
 * Much of this code was borrowed, liberally from others. Specifically from Kristian Goehlke: http://playground.arduino.cc/Code/PIRsense
 *  
 */

/////////////////////////////
//VARS
//the time we give the sensor to calibrate
int foreplay = 30;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 100;  

boolean lockLow = true; 
boolean takeLowTime;  
boolean cockhard = false; //is the dick already hard? don't let it explode!

int pirPin = 2;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;
int motorSpeedPin = 11; //attached to a stepper motor drive L293 chip
int motorOnPin = 10; //3-6v mini airpump
int solenoidPin=9; //5v solendoid
int speed = 125;
int numHardons = 0; //how many times have I gotten it up?


/////////////////////////////
//SETUP
void setup(){
  Serial.begin(9600);

  //PIR STUFF
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  //PUMP STUFF
  pinMode(motorOnPin, OUTPUT);
  pinMode(motorSpeedPin, OUTPUT);
  digitalWrite(motorOnPin, HIGH);

  //SOLENOID STUFF
  pinMode(solenoidPin, OUTPUT);
  analogWrite(solenoidPin, 0);

  //give the sensor some time to calibrate
  Serial.print("Trying to resist the inevitable ");
  for(int i = 0; i < foreplay; i++){
    Serial.print(".");
    delay(500);
  }
  Serial.println(" fuck it.");
  Serial.println("LET'S GET IT ON.");
  delay(50);
}

////////////////////////////
//LOOP
void loop(){
  
  if(numHardons <= 0){
    analogWrite(solenoidPin, 255);
    delay(3000);
    Serial.println("---");
    Serial.print("I'm ready for my first hardon at ");
    Serial.print(millis()/1000);
    Serial.println(" sec"); 
    cockhard = false;
  }
  
  delay(3000);
  numHardons = numHardons +1;

  if(cockhard == false && digitalRead(pirPin) == HIGH){
    digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state THIS IS CRUCIAL for debugging.
    digitalWrite(motorOnPin, HIGH);
    int speed = 125;
    int maxSpeed = random(150, 180); //random makes each erection a little different
    for (speed = 125; speed <= maxSpeed; speed++){ 
      analogWrite(motorSpeedPin, speed);
      delay(50);
    }
    Serial.println("---");
    Serial.print("I got an erection at ");
    Serial.print(millis()/1000);
    Serial.println(" sec"); 
    delay(1000);
    cockhard = true;
  }
  
  int time = millis();
  
  if(cockhard == true && digitalRead(pirPin) == HIGH){
    digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
    digitalWrite(motorOnPin, LOW); //turn the motor off for a while, save batteries
    Serial.print("I'm so hard. ");      //output
    Serial.print((millis() - pause)/1000);
    Serial.println(" sec");
    delay(50);  
  }

  if(lockLow){  
    //makes sure we wait for a transition to LOW before any further output is made:
    lockLow = false;           
    delay(200);
  }         
  takeLowTime = true;

  if(digitalRead(pirPin) == LOW){       
    digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state
    digitalWrite(motorOnPin, LOW);
    if(takeLowTime){
      lowIn = millis();          //save the time of the transition from high to LOW
      takeLowTime = false;       //make sure this is only done at the start of a LOW phase
    }

    //if the sensor is low for more than the given pause, 
    //we assume that no more motion is going to happen


    if(lockLow == false && cockhard == true){  
      analogWrite(solenoidPin, 255); //let the air out 
      delay(3000);    
      Serial.print("I went flaccid at ");      //output
      Serial.print((millis() - pause)/1000);
      Serial.println(" sec.");
      cockhard = false;
      delay(50);
    }

    if(lockLow == false && !cockhard){
      //makes sure this block of code is only executed again after 
      //a new motion sequence has been detected
      lockLow = true;       
      Serial.print("Looking for love. ");      //output
      Serial.print((millis() - pause)/1000);
      Serial.println(" sec.");
      delay(50);
    }
  }
}



