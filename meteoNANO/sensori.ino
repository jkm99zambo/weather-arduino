void readBmp(float &bmp_t,int &bmp_p){
  bmp_t=bmp.readTemperature();
  bmp_p=bmp.readPressure();
}

void readDht(float &dht_t,int &humidity) {
  DHT.read22(DHTPIN);
  dht_t=DHT.temperature;
  humidity=DHT.humidity;
}

