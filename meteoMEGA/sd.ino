void MakeFile(int t_ext,int t_int,int pres,int hum_int,int hum_ext) {
  char endline[6]="<br/>";
  int maxtryes=2;
  beginmakefile:;
  if(SD.exists("sensors.htm"))
    SD.remove("sensors.htm");
  myFile = SD.open("sensors.htm", FILE_WRITE);
  if(!myFile){
    myFile.close();
    if(maxtryes) {
      Serial.println("Non sono riuscito ad aprire la scheda");
      maxtryes--;
      delay(100);
      goto beginmakefile;
    }
    return;
  }
  Serial.println("Nel file:");
  Serial.println(t_ext);
  Serial.println(t_int);
  Serial.println(pres);
  Serial.println(hum_int);
  Serial.println(hum_ext);
  
  myFile.println(t_ext);
  myFile.println(endline);
  myFile.println(t_int);
  myFile.println(endline);
  myFile.println(pres);
  myFile.println(endline);
  myFile.println(hum_int);
  myFile.println(endline);
  myFile.println(hum_ext);
  myFile.println(endline);

  myFile.close();
  
}

