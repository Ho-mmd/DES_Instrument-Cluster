#include <mcp_can.h>
#include <mcp_can_dfs.h>
#include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>

#define CAN0_INT 2
MCP_CAN CAN0(9);

#define WheelDiameter 0.065 
#define SensorDiameter 0.0025 

#define WheelRadius 0.0325
#define WheelCircumference (2 * PI * WheelRadius) 

float RPM_w = 0;
const byte PulsesPerRevolution = 2;
const unsigned long ZeroTimeout = 100000;
const byte numReadings = 2;

volatile unsigned long LastTimeWeMeasured;
volatile unsigned long PeriodBetweenPulses = ZeroTimeout + 1000;
volatile unsigned long PeriodAverage = ZeroTimeout + 1000;
unsigned long FrequencyRaw;
unsigned long FrequencyReal;
unsigned long RPM;
unsigned int PulseCounter = 1;
unsigned long PeriodSum;

unsigned long LastTimeCycleMeasure = LastTimeWeMeasured;
unsigned long CurrentMicros = micros();
unsigned int AmountOfReadings = 1;
unsigned int ZeroDebouncingExtra;
unsigned long readings[numReadings];
unsigned long readIndex;  
unsigned long total; 
unsigned long average;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(3), Pulse_Event, RISING);
  delay(1000);

  while (CAN_OK != CAN0.begin(CAN_500KBPS)) {
    Serial.println("CAN BUS Shield init fail");
    Serial.println("Init CAN BUS Shield again");
    delay(100);
  }
  Serial.println("CAN BUS Shield init ok!");
}

void loop() {
  LastTimeCycleMeasure = LastTimeWeMeasured;
  CurrentMicros = micros();
  if (CurrentMicros < LastTimeCycleMeasure) {
    LastTimeCycleMeasure = CurrentMicros;
  }
  FrequencyRaw = 10000000000 / PeriodAverage;
  if (PeriodBetweenPulses > ZeroTimeout - ZeroDebouncingExtra || CurrentMicros - LastTimeCycleMeasure > ZeroTimeout - ZeroDebouncingExtra) {
    FrequencyRaw = 0;  // Set frequency as 0.
    ZeroDebouncingExtra = 2000;
  } else {
    ZeroDebouncingExtra = 0;
  }
  FrequencyReal = FrequencyRaw / 10000;

  RPM = FrequencyRaw / PulsesPerRevolution * 60;
  RPM = RPM / 10000;
  total = total - readings[readIndex];
  readings[readIndex] = RPM;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;

  RPM_w = RPM * (SensorDiameter / WheelDiameter);
  double speed_mps = (RPM_w * WheelCircumference) / 60;

  Serial.print("\tRPM: ");
  Serial.print(RPM_w);
  Serial.print("\tSpeed: ");
  Serial.println(speed_mps);



  byte rpmData[8];
	float tempRPM = RPM_w;
	float tempSpeed = speed_mps;
	memcpy(rpmData, &tempRPM, 4);
	memcpy(rpmData + 4, &tempSpeed, 4);


    // Send the CAN message.
    // The first argument is the message ID.
    // The second argument is the length of the message.
    // The third argument is the pointer to the message data.
    CAN0.sendMsgBuf(0x100, 0, 8, rpmData);
}

void Pulse_Event() {
  PeriodBetweenPulses = micros() - LastTimeWeMeasured;
  LastTimeWeMeasured = micros();
  if (PulseCounter >= AmountOfReadings)  {
    PeriodAverage = PeriodSum / AmountOfReadings;
    PulseCounter = 1;
    PeriodSum = PeriodBetweenPulses;

    int RemapedAmountOfReadings = map(PeriodBetweenPulses, 40000, 5000, 1, 10);
    RemapedAmountOfReadings = constrain(RemapedAmountOfReadings, 1, 10);
    AmountOfReadings = RemapedAmountOfReadings;
  } else {
    PulseCounter++;
    PeriodSum = PeriodSum + PeriodBetweenPulses;
  }
}
