#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "-5ZwsQielaJIEHo7DnE2IRekxuN8odxJ";
char ssid[] = "vasantharao";
char pass[] = "9440160280";


int val;
#define REPORTING_PERIOD_MS     1000
BlynkTimer timer;
int bpm = 81;
int per = 95;
int a = 0;
int b = 0;
PulseOximeter pox;
uint32_t tsLastReport = 0;
WidgetLCD bly(V7);
WidgetLCD lcd(V10);

int i;
int arr[] = {
  518,
  510,
  496,
  498,
  535,
  605,
  691,
  800,
  886,
  877,
  717,
  589,
  548,
  519,
  502,
  514,
  521,
  512,
  501,
  502,
  505,
  506,
  507,
  509,
  511,
  521,
  523,
  530,
};
void onBeatDetected()
{
  Serial.println("Beat!");
}

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  a = 1;
  Serial.print(a);
}
BLYNK_WRITE(V1) {
  GpsParam gps(param);
  float latitude = param[0].asFloat();
  float longitude = param[1].asFloat();
  lcd.clear();
  lcd.print(0, 0, "Lat:");
  lcd.print(5, 0, latitude);
  lcd.print(0, 1, "Lon:");
  lcd.print(5, 1, longitude);
  lcd.clear();
}
void myTimerEvent1()
{
  bpm = 0;
  per = 0;
  b = 1;
}

void setup()
{
  bly.clear();


  Serial.begin(9600);


  Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 100, 10), 8080);
  Blynk.virtualWrite(V3, per);
  Blynk.virtualWrite(V4, 97);

  // timer.setInterval(34000L, myTimerEvent);
  //timer.setInterval(50000L, myTimerEvent1);



}

void loop()
{ 
  Blynk.virtualWrite(V3, 95);
  Blynk.virtualWrite(V4, 97);
  if (i <= 27 ) {
    Blynk.virtualWrite(V2, bpm);

    Blynk.virtualWrite(V8, arr[i]);

    //Serial.println(arr[i]);

    i++; bly.clear();
    delay(1);
  }
  else{
    i=0;
  }
   if (i >= 27 && a == 0) {
     i = 0;

    }
    if (a == 1) {
     Blynk.virtualWrite(V8, 500);
     Serial.println(500);
    }
    if (b == 1) {
     Blynk.virtualWrite(V2, bpm);
     Blynk.virtualWrite(V3, per);
     Blynk.virtualWrite(V4, 97);
     Serial.println("patient crit");
     bly.print(0, 0, "ID:1 critical");

    
  // Make sure to call update as fast as possible
  Blynk.run();
  timer.run();



}
