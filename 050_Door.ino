//===================================================
//===================================================

void controlDoor()
{
  if (DoorModeStatus == 1)
  {
    autoDoorControlMode();
  }
  else if (DoorModeStatus == 0)
  {
    Serial.println("Automatic door mode disabled");
    DoorStatusToWords();
  }
}

void autoDoorControlMode()
{
  if (MinSinceMid > OpenDoorMin && MinSinceMid < CloseDoorMin)
  {
    openDoor();
    DoorStatusToWords();
  }
  else
  {
    closeDoor();
    DoorStatusToWords();
  }
}

//===================================================
//===================================================

void closeDoor()
{
  digitalWrite(relayPin2, LOW);
  digitalWrite(relayPin3, HIGH);
  DoorStatus = 0;
  EEPROM.write(25, DoorStatus);
  EEPROM.commit();
}

//===================================================
//===================================================

void openDoor()
{
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin3, LOW);
  DoorStatus = 1;
  EEPROM.write(25, DoorStatus);
  EEPROM.commit();
}

//===================================================
//===================================================

void stopDoor()
{
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin3, HIGH);
}

//===================================================
//===================================================

void snowDump()
{
  int count = 60;  //how many seconds  the snow dump runs for
  while (count > 0) 
  {
    Serial.print("Snow dump activated. "); Serial.print(count); Serial.println(" seconds remaining");
    closeDoor();
    delay (1000);
    count--;
  }
  Serial.println("Snow dump complete");
  openDoor();
}
