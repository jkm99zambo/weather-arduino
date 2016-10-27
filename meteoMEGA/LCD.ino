void Lcd(int possibility, int value) {    //possibilitys 0:T int, 1:T ext 2:Humidity int 3:Humidity ext 4:Pressure
  lcd.init();                  
  // Print a message to the LCD.
  lcd.backlight();
  if(!possibility || possibility==1) {   
    lcd.print("T");
    lcd.setCursor(1,0);
    lcd.print("e");
    lcd.setCursor(2,0);
    lcd.print("m");
    lcd.setCursor(3,0);
    lcd.print("p");
    lcd.setCursor(4,0);
    lcd.print("e");
    lcd.setCursor(5,0);
    lcd.print("r");
    lcd.setCursor(6,0);
    lcd.print("a");
    lcd.setCursor(7,0);
    lcd.print("t");
    lcd.setCursor(8,0);
    lcd.print("u");
    lcd.setCursor(9,0);
    lcd.print("r");
    lcd.setCursor(10,0);
    lcd.print("a");
    if(possibility) {
      lcd.setCursor(12,0);
      lcd.print("e");
      lcd.setCursor(13,0);
      lcd.print("x");
      lcd.setCursor(14,0);
      lcd.print("t");
    }
    else {
      lcd.setCursor(12,0);
      lcd.print("i");
      lcd.setCursor(13,0);
      lcd.print("n");
      lcd.setCursor(14,0);
      lcd.print("t");
    }
    lcd.setCursor(15,0);
    lcd.print(":");
  }
  else if(possibility==2 || possibility==3) {
    lcd.print("U");
    lcd.setCursor(1,0);
    lcd.print("m");
    lcd.setCursor(2,0);
    lcd.print("i");
    lcd.setCursor(3,0);
    lcd.print("d");
    lcd.setCursor(4,0);
    lcd.print("i");
    lcd.setCursor(5,0);
    lcd.print("t");
    lcd.setCursor(6,0);
    lcd.print("a");
    lcd.setCursor(7,0);
    lcd.print("'");
    if(possibility==2) {
      lcd.setCursor(9,0);
      lcd.print("i");
      lcd.setCursor(10,0);
      lcd.print("n");
      lcd.setCursor(11,0);
      lcd.print("t");
    }
    else {
      lcd.setCursor(9,0);
      lcd.print("e");
      lcd.setCursor(10,0);
      lcd.print("x");
      lcd.setCursor(11,0);
      lcd.print("t");
    }
    lcd.setCursor(12,0);
    lcd.print(":");
  }
  else if(possibility==4) {
    lcd.print("P");
    lcd.setCursor(1,0);
    lcd.print("r");
    lcd.setCursor(2,0);
    lcd.print("e");
    lcd.setCursor(3,0);
    lcd.print("s");
    lcd.setCursor(4,0);
    lcd.print("s");
    lcd.setCursor(5,0);
    lcd.print("i");
    lcd.setCursor(6,0);
    lcd.print("o");
    lcd.setCursor(7,0);
    lcd.print("n");
    lcd.setCursor(8,0);
    lcd.print("e");
    lcd.setCursor(10,0);
    lcd.print(":");
  }

  lcd.setCursor(0,1);
  lcd.print(value);
  lcd.setCursor(1,1);  
  if(value/10>=1) {
    if(value/100>=1){
      lcd.print(value%100);
      lcd.setCursor(2,1);
      lcd.print(value%10);
    }
    else
      lcd.print(value%10);
  }
}
