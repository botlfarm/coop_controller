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
  EEPROM.put(25, DoorStatus);
}

//===================================================
//===================================================

void openDoor()
{
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin3, LOW);
  DoorStatus = 1;
  EEPROM.put(25, DoorStatus);
}

//===================================================
//===================================================

void stopDoor()
{
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin3, HIGH);
}
