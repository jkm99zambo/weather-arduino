#include <VirtualWire.h>
#include <Wire.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <dht.h>

#define DHTPIN 13

Adafruit_BMP280 bmp;

dht DHT;


void setup() {
  bmp.begin();
  Serial.begin(9600);
  vw_set_tx_pin(3);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
}

void loop() {
  float bmp_t, dht_t;
  int humidity, temperature, pressure;
  readBmp(bmp_t,pressure);
  readDht(dht_t,humidity);
  
  temperature=(dht_t+bmp_t)/2;
  senddata(temperature,humidity,pressure);
  delay(5000);
}
