/*
   FTP passive client for IDE v1.0.1 and w5100/w5200
   Posted October 2012 by SurferTim
   Modified 6 June 2015 by SurferTim
*/




byte doFTP()
{
#ifdef FTPWRITE
  myFile = SD.open(fileName,FILE_READ);
#else
  SD.remove(fileName);
  myFile = SD.open(fileName,FILE_WRITE);
#endif

  if(!myFile)
  {
    Serial.println(F("SD open fail"));
    return 0;
  }

#ifndef FTPWRITE  
  if(!myFile.seek(0))
  {
    Serial.println(F("Rewind fail"));
    myFile.close();
    return 0;    
  }
#endif

  Serial.println(F("SD opened"));

  if (client.connect(server,21)) {
    Serial.println(F("Command connected"));
  } 
  else {
    myFile.close();
    Serial.println(F("Command connection failed"));
    return 0;
  }

  if(!eRcv()) return 0;

  client.println(F("USER *******"));

  if(!eRcv()) return 0;

  client.println(F("PASS ****"));

  if(!eRcv()) return 0;

  client.println(F("SYST"));

  if(!eRcv()) return 0;

  client.println(F("Type I"));

  if(!eRcv()) return 0;

  client.println(F("PASV"));

  if(!eRcv()) return 0;

  char *tStr = strtok(outBuf,"(,");
  int array_pasv[6];
  for ( int i = 0; i < 6; i++) {
    tStr = strtok(NULL,"(,");
    array_pasv[i] = atoi(tStr);
    if(tStr == NULL)
    {
      Serial.println(F("Bad PASV Answer"));    

    }
  }

  unsigned int hiPort,loPort;

  hiPort = array_pasv[4] << 8;
  loPort = array_pasv[5] & 255;

  Serial.print(F("Data port: "));
  hiPort = hiPort | loPort;
  Serial.println(hiPort);

  if (dclient.connect(server,hiPort)) {
    Serial.println(F("Data connected"));
  } 
  else {
    Serial.println(F("Data connection failed"));
    client.stop();
    myFile.close();
    return 0;
  }

#ifdef FTPWRITE 
  client.print(F("STOR "));
  client.println(fileName);
#else
  client.print(F("RETR "));
  client.println(fileName);
#endif

  if(!eRcv())
  {
    dclient.stop();
    return 0;
  }

#ifdef FTPWRITE
  Serial.println(F("Writing"));

  byte clientBuf[64];
  int clientCount = 0;

  while(myFile.available())
  {
    clientBuf[clientCount] = myFile.read();
    clientCount++;

    if(clientCount > 63)
    {
      dclient.write(clientBuf,64);
      clientCount = 0;
    }
  }

  if(clientCount > 0) dclient.write(clientBuf,clientCount);

#else
  while(dclient.connected())
  {
    while(dclient.available())
    {
      char c = dclient.read();
      myFile.write(c);      
      Serial.write(c); 
    }
  }
#endif

  dclient.stop();
  Serial.println(F("Data disconnected"));

  if(!eRcv()) return 0;

  client.println(F("QUIT"));

  if(!eRcv()) return 0;

  client.stop();
  Serial.println(F("Command disconnected"));

  myFile.close();
  Serial.println(F("SD closed"));
  return 1;
}

byte eRcv()
{
  byte respCode;
  byte thisByte;

  while(!client.available()) delay(1);

  respCode = client.peek();

  outCount = 0;

  while(client.available())
  {  
    thisByte = client.read();    
    Serial.write(thisByte);

    if(outCount < 127)
    {
      outBuf[outCount] = thisByte;
      outCount++;      
      outBuf[outCount] = 0;
    }
  }

  if(respCode >= '4')
  {
    efail();
    return 0;  
  }

  return 1;
}


void efail()
{
  byte thisByte = 0;

  client.println(F("QUIT"));

  while(!client.available()) delay(1);

  while(client.available())
  {  
    thisByte = client.read();    
    Serial.write(thisByte);
  }

  client.stop();
  Serial.println(F("Command disconnected"));
  myFile.close();
  Serial.println(F("SD closed"));
}

void readSD()
{
  myFile = SD.open(fileName,FILE_READ);

  if(!myFile)
  {
    Serial.println(F("SD open fail"));
    return;    
  }

  while(myFile.available())
  {
    Serial.write(myFile.read());
  }

  myFile.close();
}
