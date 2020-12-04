//===================================================
//===================================================
void lightMenu()
{
  printLightStatus();
  Serial.println("*****************************");
  Serial.println("Light Menu. Enter number in Serial Monitor");
  Serial.println("1-Light Mode");
  Serial.println("2-Hours requested of light");
  Serial.println("*****************************"); Serial.println("");
  delay(MenuTimeout);
  
  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();

    if (SerialData == 2)
    {
      incomingSerialLightNeeded();
    }
    else if (SerialData == 1)
    {
      incomingLightMode();
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

void incomingSerialLightNeeded()
{
  Serial.print("Requested amount of total light:  "); Serial.print(HoursLightNeeded); Serial.print(" hours, or "); Serial.print (MinLightNeeded); Serial.println( " minutes");
  Serial.println("Enter minutes of light requested");
  Serial.println("720=12h, 780=13h, 840=14h, 900=15h, 960=16h");
  resetSerial();

  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();
    if (SerialData > 20 && SerialData < 1000)
    {
      MinLightNeeded = SerialData; // read the incoming byte:
      EEPROM.put(5, MinLightNeeded);
      HoursLightNeeded = MinLightNeeded / 60; //calcualte hours of light needed

      Serial.println("++++++++++++++++++++++++++++++");
      Serial.print("Changing minutes of light needed to: "); Serial.print(MinLightNeeded); Serial.print(" minutes, or "); Serial.print(HoursLightNeeded); Serial.println(" hours ");
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
      resetSerial();
    }
    else
    {
      Serial.println("Invalid entry. Value must be between 20 and 1000. Serial reads this");
      Serial.println(SerialData);
      Serial.println("Back to main menu");
      resetSerial();
    }
  }
}

//===================================================
//===================================================

void incomingLightMode()
{
  LightModeStatusToWords();
  Serial.println("*****************************");
  Serial.println("Light Mode Menu. Enter number in Serial Monitor");
  Serial.println("1-Enable Suplimental light mode");
  Serial.println("2-Disable suplimental light mode");
  Serial.println("*****************************"); Serial.println("");
  resetSerial();
  
  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();
    if (SerialData == 1)
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("Suplimneted light mode enabled");
      LightModeStatus = true;
      EEPROM.update(10, LightModeStatus);
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
      resetSerial();
    }
    else if (SerialData == 2)
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("Suplimented light mode disabled ");
      LightModeStatus = false;
      EEPROM.update(10, LightModeStatus);
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
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
