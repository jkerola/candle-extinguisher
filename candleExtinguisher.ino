#include <Servo.h>
Servo servo;
int ledPin = 10;
int servoPin = 8;
int photoPin = A0;
String n = "";

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
  digitalWrite(ledPin, HIGH);
  Serial.println("pois");
  Serial.println(analogRead(photoPin));
  servo.write(180);
  delay(2000);
  

  digitalWrite(ledPin, LOW);
  Serial.println("pois");
  Serial.println(analogRead(photoPin));
  servo.write(0);
  delay(2000);
}
