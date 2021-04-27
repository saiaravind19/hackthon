#include <Wire.h>
#include "MAX30100_PulseOximeter.h"



#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "81Y6PSoD-Oy0hDFMHtLncpVZjHO2B22J";
char ssid[] = "A1601";
char pass[] = "12345678";


#define REPORTING_PERIOD_MS     1000

PulseOximeter pox;
float BPM, SpO2;
uint32_t tsLastReport = 0;

void onBeatDetected()
{
  Serial.println("Beat!");
}


void setup()
{
  Serial.begin(115200);
  Wire.begin(D1, D2);
  pinMode(16, OUTPUT);
  Blynk.begin(auth, ssid, pass);

  Serial.print("Initializing pulse oximeter..");

  // Initialize the PulseOximeter instance
  // Failures are generally due to an improper I2C wiring, missing power supply
  // or wrong target chip
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  // Register a callback for the beat detection
  pox.setOnBeatDetectedCallback(onBeatDetected);

}

void loop()
{
  // Make sure to call update as fast as possible
  pox.update();
  Blynk.run();
  BPM = pox.getHeartRate();
  SpO2 = pox.getSpO2();
  Blynk.virtualWrite(V1, BPM);
  Blynk.virtualWrite(V2, SpO2);
  if (millis() - tsLastReport > REPORTING_PERIOD_MS)
  {
    Serial.print("Heart rate:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / SpO2:");
    Serial.print(pox.getSpO2());
    Serial.println("%");
    tsLastReport = millis();
  }

}
