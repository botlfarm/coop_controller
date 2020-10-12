void doorMenu()
{
  printDoorStatus();
  Serial.println("*****************************");
  Serial.println("Door Menu. Enter number in Serial Monitor");
  Serial.println("1-Open Offset");
  Serial.println("2-Close Offset");
  Serial.println("3-Toggle Manual/Automatic");
  Serial.println("*****************************"); Serial.println("");
  delay(MenuTimeout);
  
  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();

    if (SerialData == 1)
    {
      incomingSerialOpenOffset();
    }
    else if (SerialData == 2)
    {
      incomingSerialCloseOffset();
    }
    else if (SerialData == 3)
    {
      doorAutoToggle();
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
void incomingSerialOpenOffset()
{
  Serial.println("Enter open offset requested");
  resetSerial();

  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();
    if (SerialData > -240 && SerialData < 240)
    {
      OpenDoorOffset = SerialData; // read the incoming byte:
      //EEPROM.put(1, MinLightNeeded);

      Serial.println("++++++++++++++++++++++++++++++");
      Serial.print("Changing open door offset from sunrise to: "); Serial.print(OpenDoorOffset); Serial.println(" minutes");
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
      resetSerial();
    }
    else
    {
      Serial.println("Invalid entry. Value must be between -240 and 1000. Serial reads this");
      Serial.println(SerialData);
      Serial.println("Back to main menu");
      resetSerial();
    }
  }
}

void incomingSerialCloseOffset()
{
  Serial.println("Enter close offset requested");
  resetSerial();

  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();
    if (SerialData > -240 && SerialData < 240)
    {
      CloseDoorOffset = SerialData; // read the incoming byte:
      //EEPROM.put(1, MinLightNeeded);

      Serial.println("++++++++++++++++++++++++++++++");
      Serial.print("Changing close door offset from sunset to: "); Serial.print(CloseDoorOffset); Serial.println(" minutes");
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
      resetSerial();
    }
    else
    {
      Serial.println("Invalid entry. Value must be between -240 and 1000. Serial reads this");
      Serial.println(SerialData);
      Serial.println("Back to main menu");
      resetSerial();
    }
  }
}

void doorAutoToggle()
{
  Serial.print("Door Mode: "); //DSTStatusToWords();
  Serial.println("Enter 1 for automatic door and 0 for manual door");
  // reset the serial monitor to clear data
  resetSerial();
  
  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();
    if (SerialData == 1)
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("Automatic door mode");
      //DSTStatus = true;
      //EEPROM.update(0, DSTStatus);
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
    }
    else if (SerialData == 0)
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("Manual door mode");
      //DSTStatus = false;
      //EEPROM.update(0, DSTStatus);
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
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
