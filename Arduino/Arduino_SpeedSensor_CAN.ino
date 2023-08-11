#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>

#define SPEED_SENSOR_PIN 3
#define SPEED_SENSOR_INTERRUPT 1  // Uno, Nano, Mini, other 328-based boards: 0=pin2, 1=pin3
#define CAN0_INT 2                // CAN interrupt pin
MCP_CAN CAN0(9);                  // Set CS to pin 9

volatile unsigned long count = 0;
volatile unsigned long lastPulseTime = 0;

/** Values for calculating RPM */
#define PPR 20
#define WheelDiameter 0.065   // m
#define SensorDiameter 0.025  // m

// Wheel diameter is 6.5 cm, radius is 3.25 cm or 0.0325 m.
#define WheelRadius 0.0325                         // m
#define WheelCircumference (2 * PI * WheelRadius)  // m

unsigned long prevTime = 0;
float RPM_w = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SPEED_SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(SPEED_SENSOR_INTERRUPT, pulseHandler, RISING);

  while (CAN_OK != CAN0.begin(CAN_500KBPS)) {
    Serial.println("CAN BUS Shield init fail");
    Serial.println("Init CAN BUS Shield again");
    delay(100);
  }
  Serial.println("CAN BUS Shield init ok!");
}

void loop() {
  if (millis() - lastPulseTime >= 2000) {  // If no pulse is detected for 2 seconds, set RPM to 0
    RPM_w = 0;
  }

  if (millis() - prevTime >= 500) {  // Calculate RPM every 0.5 second
    if (count >= PPR) {
      unsigned long deltaTime = millis() - lastPulseTime;               // The time difference between the current and last pulse
      float rotationRate = (float)count / PPR;                          // The number of sensor wheel rotations
      unsigned long RPM_sensor = (60000.0 / deltaTime) * rotationRate;  // RPM of the sensor wheel

      RPM_w = RPM_sensor * (SensorDiameter / WheelDiameter);  // Convert to the RPM of the wheel
      count = 0;
      lastPulseTime = millis();
    }

    double speed_mps = (RPM_w * WheelCircumference) / 60;

    Serial.print("RPM_w: ");
    Serial.println(RPM_w);
    Serial.print("Speed (m/s): ");
    Serial.println(speed_mps, 1);
    prevTime = millis();

    // Send the data via CAN bus
    byte rpmData[8];
    float tempRPM = RPM_w;
    float tempSpeed = speed_mps;
    memcpy(rpmData, &tempRPM, 4);
    memcpy(rpmData + 4, &tempSpeed, 4);

    // CAN 메시지를 전송합니다.
    // 첫 번째 인자는 메시지 ID입니다.
    // 두 번째 인자는 메시지의 길이입니다.
    // 세 번째 인자는 메시지 데이터의 포인터입니다.
    CAN0.sendMsgBuf(0x100, 0, 8, rpmData);
  }
}

void pulseHandler() {
  count++;
  lastPulseTime = millis();
}
