#include <OneWire.h>
#include <DallasTemperature.h>

#include <LiquidCrystal_I2C.h>
#include<Wire.h>

#define BLYNK_PRINT Serial
int bpm = 81;
int per = 97;

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// GPIO where the DS18B20 is connected to
float temperatureF = 0;
const int oneWireBus = 14;

int crit = 0;
OneWire oneWire(oneWireBus);

DallasTemperature sensors(&oneWire);
WidgetLCD bly(V7);
char auth[] = "rDM93mA3QVhAr29ywXJwVAIf4kcYX3Hi";
char ssid[] = "vasantharao";
char pass[] = "9440160280";


byte customChar[8] = {
  0x00,
  0x0A,
  0x1F,
  0x1F,
  0x1F,
  0x0E,
  0x04,
  0x00
};

void setup()
{
  Wire.begin();
  bly.clear();
  lcd.init();
  lcd.backlight();
  lcd.createChar(1, customChar);
  lcd.setCursor(0, 0);

  Serial.begin(115200);
  sensors.begin();
  Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 100, 10), 8080);  lcd.clear();
}

void temp()
{ 
  Serial.println("ºF");
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 0);
  Blynk.virtualWrite(V4, 0);
  Blynk.virtualWrite(V8, 500);



}

void loop() {
  Blynk.run();
  temp();
}
