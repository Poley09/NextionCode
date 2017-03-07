// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
#include <Wire.h>
#include <Time.h>

#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include "Nextion.h"
#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

unsigned long lastmillis = 0;
  
//byte inByte, pageNum, buttonNum;
//String message;
//int party1, party2, shadowFax, pegasus, numMessages, numBytes, endBytes;

DHT dht(DHTPIN, DHTTYPE);

// Declare a text object [page id:0,component id:1, component name: "t0"].
// to talk to the display
NexButton b0 = NexButton(2, 1, "b0");
NexButton b1 = NexButton(1, 8, "b0");
NexText t1 = NexText(1, 9, "t1");
NexText t5 = NexText(1, 10, "t5");
//NexText t2 = NexText(1, 18, "t2");


NexTouch *nex_listen_list[] = 
{
    &b0,
    &b1,
    NULL
};

char buffer[100] = {0};

void setup() {
  nexInit();
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  b0.attachPop(b0PopCallback, &b0);
  b1.attachPop(b1PopCallback, &b1);
  dbSerialPrintln("setup done");
  dht.begin();
}

void b0PopCallback(void *ptr) {
digitalWrite(LED_BUILTIN, HIGH);
}

void b1PopCallback(void *ptr) {
digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  
  nexLoop(nex_listen_list);

  if (millis() - lastmillis == 1000) {/*Uptade every one second, this will be equal to reading frecuency (Hz).*/

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");

  //==============================
  //Display the Temperature in °F
  //==============================
  uint16_t valFahr;
  memset(buffer, 0, sizeof(buffer));
  valFahr = t;
  itoa(valFahr, buffer, 10);
  t1.setText(buffer);

  //==========================
  //Display the Humidity in %
  //==========================
  uint16_t valHumid;
  memset(buffer, 0, sizeof(buffer));
  valHumid = h;
  itoa(h, buffer, 10);
  t5.setText(buffer);

//  nexLoop(nex_listen_list);
lastmillis = millis(); // Uptade lasmillis
  }
}
