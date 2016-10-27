void senddata(int temperature,int humidity, int pressure) {
  char msg[50];
  sprintf(msg,"%d,%d,%d,",temperature,humidity,-pressure);
  Serial.println("Sending:");
  Serial.println(msg);
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();
}

