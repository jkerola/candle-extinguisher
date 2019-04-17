#include <Servo.h>
//Pins
Servo servo;
int ledPin = 10;
int servoPin = 8;
int photoPin = A0;

//needed variables
int lightSamples[10];
int lightAvg;
int lightLimit;

// Key variables!
int waitTime = 8;
int lightThreshold = 15;

int loopCounter = 0;
int inactiveCounter = 0;
boolean deviceActive = false;
boolean calibrationRun = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(photoPin, INPUT);
  pinMode(servoPin, OUTPUT);
  servo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  //take 10 samples of candlelight
  for(int i=0; i<10; i++){
    delay(100);
    lightSamples[i] = analogRead(photoPin);
    //Serial.println(lightSamples[i]);
  }
  
  //calculate average lightlevel
  lightAvg = 0;
  for(int i=0; i<10; i++){
    lightAvg += lightSamples[i];
  }

  lightAvg = lightAvg / 10;

  //set default light levels as limit
  if(calibrationRun){
    lightLimit = lightAvg + lightThreshold;
    calibrationRun = false;
  }

  Serial.println(lightAvg);

  //turn on device if light level high enough
  if(lightAvg >= lightLimit){
    deviceActive = true;
  } else{
    deviceActive = false;
  }

  //main device logic
  if(deviceActive){
    digitalWrite(ledPin, HIGH);
    Serial.println("Kynttilä tunnistettu.");
    loopCounter += 1;

    //if counter reaches X seconds
    if(loopCounter == waitTime){

      //flash led
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(100);

      //run servo
      servo.write(180);
      delay(1500);
      servo.write(0);
      digitalWrite(ledPin, LOW);
      loopCounter = 0;
      
      }
    } else{
      
      //wait a bit before resetting counters
      delay(200);
      inactiveCounter += 1;
      Serial.println("Kynttilä sammunut.");
      digitalWrite(ledPin, LOW);
      if(inactiveCounter == 3){
        loopCounter = 0;
        inactiveCounter = 0;
        Serial.println("Ajastin nollattu.");
      }
  }
  
}
