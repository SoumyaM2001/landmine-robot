#include <SoftwareSerial.h>

// --------- Motor Pins ----------
const int leftForward = 9;
const int leftBackward = 6;
const int rightForward = 3;
const int rightBackward = 5;

// --------- Bluetooth ---------
SoftwareSerial bluetooth(13, 12);   // BT TX=12, RX=13

// --------- Metal Sensor, Buzzer, LEDs ----------
const int sensorPin = 7;    
const int buzzerPin  = 8;
const int led1 = 10;
const int led2 = 11;

int dist = 999;        // distance coming from Arduino 1
int angle = 0;
char command;

int minSpeed = 70;
int minTurn  = 40;

// ---------------- SETUP ----------------
void setup() {

  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);

  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  Serial.begin(9600);        // For Arduino-1
  bluetooth.begin(9600);     // For Bluetooth

  Serial.println("ROBOT READY");
}

// ---------------- STOP FUNCTION ----------------
void stopRobot() {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);
}

// --------------- AMBULANCE SIREN ----------------
void ambulanceSiren(int durationMs) {
  unsigned long start = millis();
  
  while (millis() - start < durationMs) {
    tone(buzzerPin, 800);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(150);

    tone(buzzerPin, 500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    delay(150);
  }

  noTone(buzzerPin);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

// --------------- DISTANCE OBSTACLE CHECK ---------------
void checkObstacle() {

  if (dist > 5 && dist <= 15) {
    stopRobot();

    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    tone(buzzerPin, 500);

    delay(1000);

    noTone(buzzerPin);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
}

// ---------------- METAL CHECK ----------------
void checkMetal() {

  if (digitalRead(sensorPin) == LOW) {

    stopRobot();
    delay(100);

    analogWrite(leftBackward, minSpeed);
    analogWrite(rightBackward, minSpeed);
    delay(200);

    stopRobot();
    ambulanceSiren(3000);
  }
}
// ---------------- MOVEMENT FUNCTIONS ----------------

void moveForward() {
  analogWrite(leftForward, minSpeed);
  analogWrite(rightForward, minSpeed);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightBackward, LOW);
  Serial.println("Forward");
  delay(200);
  stopRobot();
}

void moveBackward() {
  analogWrite(leftBackward, minSpeed);
  analogWrite(rightBackward, minSpeed);
  digitalWrite(leftForward, LOW);
  digitalWrite(rightForward, LOW);
   Serial.println("Backward");
  delay(200);
  stopRobot();
}

void turnRight() {
  analogWrite(leftForward, minSpeed);
  analogWrite(rightForward, minTurn);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightBackward, LOW);
   Serial.println("Right");
  delay(200);
  stopRobot();
}

void turnLeft() {
  analogWrite(rightForward, minSpeed);
  analogWrite(leftForward, minTurn);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightBackward, LOW);
   Serial.println("Left");
  delay(200);
  stopRobot();
}

// ---------------- MAIN LOOP ----------------
void loop() {

  // --- Read Bluetooth (Robot Control) ---
  if (bluetooth.available()) {
    command = bluetooth.read();
  }

  // --- Read From Arduino-1 (Serial) ---
if (Serial.available()) {

  String data = Serial.readStringUntil('\n');
  data.trim();

  if (data.indexOf(',') > 0) {
    int commaIndex = data.indexOf(',');

    angle = data.substring(0, commaIndex).toInt();
    dist  = data.substring(commaIndex + 1).toInt();

    // SEND TO BLUETOOTH APP
    bluetooth.print("A:");
    bluetooth.print(angle);
    bluetooth.print(",D:");
    bluetooth.println(dist);
  }
}

  // --- Safety First ---
  checkMetal();
  checkObstacle();

  // --- Perform Movement ---
  switch (command) {
    case 'F': moveForward(); break;
    case 'B': moveBackward(); break;
    case 'L': turnLeft(); break;
    case 'R': turnRight(); break;
    case 'S': stopRobot(); break;
  }

  delay(50);
}
