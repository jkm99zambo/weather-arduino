// giallo SCL


/**************************************************************************************************************************************
  Questo sketch utilizza tutti i sensori sullo stesso arduino UNO, per problemi di memoria la parte dell'LCD è momentaneamente commentata
  Quando una parte di sensori verrà spostata sul NANO si potrà utilizzare anche l'LCD
***************************************************************************************************************************************/


#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <VirtualWire.h>


#define DHTPIN 3

dht DHT;


#define FTPWRITE

File myFile;
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display


// this must be unique
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x59, 0x67 };

// change to your network settings
IPAddress ip( 192, 168, 1, 25 );
IPAddress gateway( 192, 168, 1, 1 );
IPAddress subnet( 255, 255, 255, 0 );

// change to your server
IPAddress server( 31, 170, 165, 119 );

EthernetClient client;
EthernetClient dclient;

char outBuf[128];
char outCount;

int counter = 0;

// change fileName to your file (8.3 format!)
char fileName[13] = "sensors.htm";



void setup() {
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  Serial.begin(9600);
  Serial.println("Partenza");
  lcd.init();
  vw_set_rx_pin(7);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000); // Bits per sec
  /*pinMode(13,OUTPUT);
    digitalWrite(13,HIGH); //Al pin 13 è collegata l'alimentazione del modulo bluetooth  */
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  digitalWrite(10, HIGH);
  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  digitalWrite(10, HIGH);
  delay(10000);
  vw_rx_start();
}

void loop() {
  int temperature_int, humidity_int, humidity_ext, value;
  int pressure,temperature_ext;

  readDht(temperature_int, humidity_int);
  receive(temperature_ext,humidity_ext,pressure);
  
  MakeFile(temperature_ext, temperature_int, pressure, humidity_int, humidity_ext);
  
  if (counter == 0)
    value = temperature_int;
  if (counter == 1)
    value = temperature_ext;
  if (counter == 2)
    value = humidity_int;
  if (counter == 3)
    value = humidity_ext;
  Lcd(counter, value);
  counter++;
  if (counter > 3)
    counter = 0;
  doFTP();
  delay(5000);
}
