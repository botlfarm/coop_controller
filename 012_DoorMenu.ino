void doorMenu()
{
  printDoorStatus();
  Serial.println("*****************************");
  Serial.println("Door Menu. Enter number in Serial Monitor");
  Serial.println("1-Open Offset");
  Serial.println("2-Close Offset");
  Serial.println("3-Toggle Manual/Automatic");
  Serial.println("4-Manual operation");
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
      incomingDoorMode();
    }
    else if (SerialData == 4)
    {
      manualDoorControl();
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
      EEPROM.put(30, OpenDoorOffset);

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
      EEPROM.put(35, CloseDoorOffset);

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

void incomingDoorMode()
{
  DoorModeStatusToWords();
  Serial.println("*****************************");
  Serial.println("Door Mode Menu. Enter number in Serial Monitor");
  Serial.println("1-Enable automatic door mode");
  Serial.println("2-disable automatic door mode");
  Serial.println("*****************************"); Serial.println("");

  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();
    if (SerialData == 1)
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("Automaic door mode enabled");
      DoorModeStatus = true;
      EEPROM.update(20, DoorModeStatus);
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
      resetSerial();
    }
    else if (SerialData == 2)
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("Automatic door mode disabled");
      DoorModeStatus = false;
      EEPROM.update(20, DoorModeStatus);
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

void manualDoorControl()
{
  Serial.println("*****************************");
  Serial.println("Mnual Door Menu. Enter number in Serial Monitor");
  Serial.println("1-Open Door");
  Serial.println("2-Close Door");
  Serial.println("3-Stop Door");
  Serial.println("*****************************"); Serial.println("");
  resetSerial();
  
  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();
    if (SerialData == 1)
    {
      openDoor();
      DoorStatusToWords();
      resetSerial();
    }
    else if (SerialData == 2)
    {
      closeDoor();
      DoorStatusToWords();
      resetSerial();
    }
    else if (SerialData == 3)
    {
      stopDoor();
      Serial.println("Door Stoped");
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
