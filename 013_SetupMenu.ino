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

void setCurrentDate()
{
  Serial.println("Menu not enabled yet");
      Serial.println("Back to main menu");
      resetSerial();
}

void setCurrentTime()
{
  Serial.println("Menu not enabled yet");
      Serial.println("Back to main menu");
      resetSerial();
}

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
      EEPROM.update(0, DSTStatus);
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");

      dt = clock.getDateTime(); //get the current time form the RTC
      clock.setDateTime(dt.year, dt.month, dt.day, dt.hour + 1, dt.minute, dt.second);  //Set the clock
      resetSerial();
    }
    else if (SerialData == 2)
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("DST disabled ");
      DSTStatus = false;
      EEPROM.update(0, DSTStatus);
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");

      dt = clock.getDateTime(); //get the current time form the RTC
      clock.setDateTime(dt.year, dt.month, dt.day, dt.hour - 1, dt.minute, dt.second); //Set the clock
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

void setLocation()
{
  Serial.println("Menu not enabled yet");
  Serial.println("Back to main menu");
  resetSerial();
}

void setMenuTimeout()
{
  Serial.print("Current menu timeout "); Serial.print(MenuTimeout); Serial.println(" milliseconds");
  Serial.println("Enter new menu timeout in milliseconds");
  resetSerial();

  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();
    if (SerialData > 3000  && SerialData <60000)
    {
      MenuTimeout = SerialData; 
      EEPROM.put(40, MenuTimeout);

      Serial.println("++++++++++++++++++++++++++++++");
      Serial.print("Changing menu timeout to: "); Serial.print(MenuTimeout); Serial.println(" milliseconds");
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
      resetSerial();
    }
    else
    {
      Serial.println("Invalid entry. Value must be between 3000 and 60000. Serial reads this");
      Serial.println(SerialData);
      Serial.println("Back to main menu");
      resetSerial();
    }
  }
}
