#include <Servo.h>
#include <U8g2lib.h>
#include <Wire.h>

// OLED display
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// Pins
const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 12;

// Servo object
Servo myServo;

// Variables
long duration;
int distance;

const int minAngle = 0;
const int maxAngle = 180;
const int numReadings = 3;      // number of samples per position
const int radarRadius = 52;     

// pulseIn timeout in microseconds (allow up to ~500 cm)
const unsigned long PULSE_TIMEOUT = 30000UL; // 30 ms -> ~510 cm

void setup() {
  Serial.begin(9600);   // Sending data to UNO 2

  myServo.attach(servoPin);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  u8g2.begin();
}

void loop() {
  // Sweep Left → Right
  for (int a = minAngle; a <= maxAngle; a += 5) {
    myServo.write(a);
    delay(20);                 // give servo time to move and settle

    distance = getAverageDistance();
    displayRadar(a, distance);

    sendSerialData(a, distance);
  }

  // Sweep Right → Left
  for (int a = maxAngle; a >= minAngle; a -= 5) {
    myServo.write(a);
    delay(40);

    distance = getAverageDistance();
    displayRadar(a, distance);

    sendSerialData(a, distance);
  }
}

int getAverageDistance() {
  long total = 0;
  int validCount = 0;

  // pause servo briefly while taking quick readings to reduce interference
  for (int i = 0; i < numReadings; i++) {
    int d = getDistance();
    Serial.print("RAW d: ");
    Serial.println(d);
    if (d >= 0 && d <= 300) {   // accept 0..300 cm as valid
      total += d;
      validCount++;
    }
    delay(10);
  }

  if (validCount == 0) return -1;   // no valid reading
  return (int)(total / validCount);
}

int getDistance() {
  // Ensure trig LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(4);

  // trigger a 10us pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Wait for echo; use timeout (microseconds)
  unsigned long dur = pulseIn(echoPin, HIGH, PULSE_TIMEOUT);
  if (dur == 0) {
    // no echo (timeout)
    return -1;
  }
  // convert to distance in cm
  int distCm = (int)( (dur * 0.034) / 2.0 );
  if (distCm > 300) distCm = 300; // clamp for display
  return distCm;
}

// SEND DATA TO ARDUINO 2
void sendSerialData(int angle, int distance) {
  if (distance < 0) {
    Serial.print(angle);
    Serial.println(",-1");
  } else {
    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
  }
}

void displayRadar(int angle, int distance) {
  u8g2.clearBuffer();
  drawRadarBackground();

  float scale = (float)radarRadius / 300.0;
  float r = 0.0;
  if (distance > 0) r = distance * scale;

  int cx = 64;
  int cy = 64 - 12;

  int x = cx + (int)(r * cos(radians(angle)));
  int y = cy - (int)(r * sin(radians(angle)));

  u8g2.drawLine(cx, cy, x, y);

  if (distance > 0 && distance <= 300) {
    u8g2.drawDisc(x, y, 3);
  }

  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(0, 64);
  u8g2.print("A:");
  u8g2.print(angle);
  u8g2.print(" D:");
  if (distance < 0) u8g2.print("--");
  else u8g2.print(distance);
  u8g2.print("cm");

  u8g2.sendBuffer();
}

void drawRadarBackground() {
  int cx = 64;
  int cy = 64 - 12;

  u8g2.drawLine(cx, cy - radarRadius, cx, cy);
  u8g2.drawLine(cx - radarRadius, cy, cx + radarRadius, cy);

  for (int i = 1; i <= 3; i++) {
    u8g2.drawCircle(cx, cy, i * radarRadius / 3);
  }

  for (int a = 0; a <= 180; a += 30) {
    int x = cx + cos(radians(a)) * radarRadius;
    int y = cy - sin(radians(a)) * radarRadius;
    u8g2.drawLine(cx, cy, x, y);
  }
}
