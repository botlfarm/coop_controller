void lightCheck()
{
  Serial.println("*****************************");
  Serial.println("Checking if lights are working.");
  delay(1000);
  Serial.println("Light on 3 seconds");
  digitalWrite(relayPin1, LOW);
  delay(3000);
  Serial.println("Lights off 3 seconds");
  digitalWrite(relayPin1, HIGH);
  delay(3000);
  Serial.println("Flash lights");
  digitalWrite(relayPin1, LOW);
  delay(1000);
  digitalWrite(relayPin1, HIGH);
  delay(500);
  Serial.println("Light check complete");
  Serial.println("*****************************"); Serial.println("");
  delay(2000);
}

void doorCheck()
{
  Serial.println("*****************************");
  Serial.println("Checking if door is working.");
  delay(1000);
  Serial.println("Close for 3 seconds");
  closeDoor();
  delay(3000);
  Serial.println("Stop door for 3 seconds");
  stopDoor();
  delay(3000);
  Serial.println("Open door for 3 seconds");
  openDoor();
  delay(3000);
  stopDoor();
  Serial.println("Door check complete");
  Serial.println("*****************************"); Serial.println("");
  delay(2000);
}
