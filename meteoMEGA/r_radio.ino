void receive(int &temperature_ext,int &humidity_ext,int &pressure){
   uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;
   Serial.println("Receiving..."); 
   if (vw_get_message(buf, &buflen)) // Non-blocking
   {
     int i;
     char c;
     String str="";
     int v[3];
     int j=0;
     digitalWrite(13, true); // Flash a light to show received good message
     // Message with a good checksum received, dump it.
     Serial.print("Got: ");
      
     for (i = 0; i < buflen; i++)
     {
       c=buf[i];
       if(c==','){
        v[j]=str.toInt();
        j++;
        str="";
       }
       else
        str+=c;
       Serial.print(c);
       Serial.print(" ");
     }
     Serial.println("");
     digitalWrite(13, false);
     temperature_ext=v[0];
     humidity_ext=v[1];
     pressure=v[2];
     Serial.println(temperature_ext);
     Serial.println(humidity_ext);
     Serial.println(pressure);
   }
   else{
    Serial.println("Ricezione fallita");
   }
}

