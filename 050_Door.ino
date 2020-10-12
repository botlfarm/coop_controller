void controlDoor()
{
  if (MinSinceMid > OpenDoorMin && MinSinceMid < CloseDoorMin)
  {
    openDoor();
    Serial.println("The door should be open.");
  }
  else
  {
    closeDoor();
    Serial.println("The door should be closed.");
  }
}

void closeDoor()
{
  digitalWrite(relayPin2, LOW);
  digitalWrite(relayPin3, HIGH);
}

void openDoor()
{
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin3, LOW);
}

void stopDoor()
{
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin3, HIGH);
}
