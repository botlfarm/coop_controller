//===================================================
//===================================================
void setupMenu()
{
  Serial.println("*****************************");
  Serial.println("Setup Menu. Enter number in Serial Monitor");
  Serial.println("1-Set Date");
  Serial.println("2-Set Time");
  Serial.println("3-Toggle DST");
  Serial.println("4-Set Location");
  Serial.println("5-Set Menu Timeout");
  Serial.println("*****************************"); Serial.println("");
  delay(MenuTimeout);

  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();

    if (SerialData == 1)
    {
      setCurrentDate();
    }
    else if (SerialData == 2)
    {
      setCurrentTime();
    }
    else if (SerialData == 3)
    {
      DSTToggle();
    }
    else if (SerialData == 4)
    {
      setLocation();
    }
    else if (SerialData == 5)
    {
      setMenuTimeout();
    }
    else
    {
      Serial.println("Invalid entry. Serial reads this");
      Serial.println(SerialData);
      Serial.println("Back to main menu");
      resetSerial();
    }
  }
}

//===================================================
//===================================================

void setCurrentDate()
{
  Serial.println("Menu not enabled yet");
      Serial.println("Back to main menu");
      resetSerial();
}

//===================================================
//===================================================

void setCurrentTime()
{
  Serial.println("Menu not enabled yet");
      Serial.println("Back to main menu");
      resetSerial();
}

//===================================================
//===================================================

void DSTToggle()
{
  DSTStatusToWords();
  Serial.println("*****************************");
  Serial.println("DST Status Menu. Enter number in Serial Monitor");
  Serial.println("1-Enable DST");
  Serial.println("2-Disable DST");
  Serial.println("*****************************"); Serial.println("");
  resetSerial();
  
  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();
    if (MinSinceMid < 61) //cant change the DST status if it is earlier than 1am. this will give a negative number to the clock
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("Wait until after 1 am to change the DST staus");
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
      resetSerial();
    }

    else if (SerialData == 1)
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("DST enabled");
      DSTStatus = true;
      EEPROM.write(0, DSTStatus);
      EEPROM.commit();
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");

      DateTime now = rtc.now(); //get the current time form the RTC
      DateTime future (now + TimeSpan(0,1,0,0));
      rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour()+1, now.minute(), now.second()));  //Set the clock
      resetSerial();
    }
    else if (SerialData == 2)
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("DST disabled ");
      DSTStatus = false;
      EEPROM.write(0, DSTStatus);
      EEPROM.commit();
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");

      DateTime now = rtc.now(); //get the current time form the RTC
      rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour()-1, now.minute(), now.second()));  //Set the clock
      resetSerial();
    }
    else
    {
      Serial.println("Invalid entry. Serial reads this");
      Serial.println(SerialData);
      Serial.println("Back to main menu");
      resetSerial();
    }
  }
}

//===================================================
//===================================================

void setLocation()
{
  Serial.println("Menu not enabled yet");
  Serial.println("Back to main menu");
  resetSerial();
}

void setMenuTimeout()
{
  Serial.print("Current menu timeout "); Serial.print(MenuTimeoutSeconds); Serial.println(" seconds");
  Serial.println("Enter new menu timeout in seconds");
  resetSerial();

  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();
    if (SerialData > 3  && SerialData <60)
    {
      MenuTimeoutSeconds = SerialData; 
      EEPROM.write(40, MenuTimeoutSeconds);
      EEPROM.commit();

      Serial.println("++++++++++++++++++++++++++++++");
      Serial.print("Changing menu timeout to: "); Serial.print(MenuTimeoutSeconds); Serial.println(" seconds");
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
      resetSerial();
    }
    else
    {
      Serial.println("Invalid entry. Value must be between 3 and 60. Serial reads this");
      Serial.println(SerialData);
      Serial.println("Back to main menu");
      resetSerial();
    }
  }
}
