void readDht(int &t,int &h) {
  DHT.read22(DHTPIN);
  t=DHT.temperature;
  h=DHT.humidity;
}

