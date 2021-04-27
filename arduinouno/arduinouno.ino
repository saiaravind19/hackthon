#include <SoftwareSerial.h>
SoftwareSerial s(5, 6);
#include <OneWire.h>
#include <DallasTemperature.h>
int temperatureF=0;
// GPIO where the DS18B20 is connected to
const int oneWireBus = 3;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);
void setup()
{
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();
  s.begin(9600);
}

void loop() {
    sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
   temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");

  if (s.available() > 0)
  {
    s.write(temperatureF);
  }
    delay(1000);
}
