#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "MAX30100_PulseOximeter.h"

// GPIO where the DS18B20 is connected to
const int oneWireBus = 00;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

#define REPORTING_PERIOD_MS     1000
#define TEMP 5000
PulseOximeter pox;
uint32_t tsLastReport = 0;
float temperatureF=0;
void onBeatDetected()
{   sensors.requestTemperatures();
    temperatureF = sensors.getTempFByIndex(0);


  

}


void setup()
{
  Serial.begin(115200);
  Wire.begin(D1, D2);
  Serial.print("Initializing pulse oximeter..");
  sensors.begin();


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

  if (millis() - tsLastReport > REPORTING_PERIOD_MS)
  {

    Serial.print("Heart rate:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / SpO2:");
    Serial.print(pox.getSpO2());
    Serial.println("% ");
    Serial.println(temperatureF);

    tsLastReport = millis();
  }

}
