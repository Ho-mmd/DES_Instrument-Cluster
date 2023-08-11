#include <Arduino.h>
#include <SPI.h>

#define SPEED_SENSOR_PIN 3
#define SPEED_SENSOR_INTERRUPT 1 // Uno, Nano, Mini, other 328-based boards: 0=pin2, 1=pin3

volatile unsigned long count = 0;
volatile unsigned long lastPulseTime = 0;

/** Values for calculating RPM */
#define PPR 20
#define WheelDiameter 0.065 // m
#define SensorDiameter 0.025 // m

// Wheel diameter is 6.5 cm, radius is 3.25 cm or 0.0325 m.
#define WheelRadius 0.0325 // m
#define WheelCircumference (2 * PI * WheelRadius) // m

unsigned long prevTime = 0;
unsigned long RPM_w = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SPEED_SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(SPEED_SENSOR_INTERRUPT, pulseHandler, RISING);
}

void loop() {
  if (millis() - lastPulseTime >= 2000) { // If no pulse is detected for 2 seconds, set RPM to 0
    RPM_w = 0;
  } 

  if (millis() - prevTime >= 500) { // Calculate RPM every 0.5 second
    if (count >= PPR) {
      unsigned long deltaTime = millis() - lastPulseTime; // The time difference between the current and last pulse
      float rotationRate = (float)count / PPR; // The number of sensor wheel rotations
      unsigned long RPM_sensor = (60000.0 / deltaTime) * rotationRate; // RPM of the sensor wheel

      RPM_w = RPM_sensor * (SensorDiameter / WheelDiameter); // Convert to the RPM of the wheel
      count = 0;
      lastPulseTime = millis();
    }

    double speed_mps = (RPM_w * WheelCircumference) / 60;
    
  /*
      if (speed_mps < 10.0) { // Filter out any speeds above 10 m/s
      Serial.print("RPM_w: ");
      Serial.println(RPM_w);
      Serial.print("Speed (m/s): ");
      Serial.println(speed_mps, 1);
    }
    
   */
   // If we consider the value which is over 10 m/s as noise, Then use this codes and make comment out the below codes
   

  
    Serial.print("RPM_w: ");
    Serial.println(RPM_w);
    Serial.print("Speed (m/s): ");
    Serial.println(speed_mps, 1);
   
    prevTime = millis();
  }
}

void pulseHandler() {
  count++;
  lastPulseTime = millis();
}
