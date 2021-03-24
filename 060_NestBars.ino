
//===================================================
//===================================================

void controlNestBars()
{
  if (MinSinceMid == NestBarMin) //if the current time is eqial to nest bar release time relese the nest barsbar
  {
    releaseNestBars();
  }
}

//===================================================
//===================================================

void releaseNestBars()  //brefinly enabaling release mechanism 
{
  digitalWrite(relayPin4, LOW);
  Serial.println("Releasing nest box bars");
  delay(1500);
  digitalWrite(relayPin4, HIGH);
  digitalWrite(relayPin5, LOW);
  delay(1500);
  digitalWrite(relayPin5, HIGH);
  digitalWrite(relayPin6, LOW);
  delay(1500);
  digitalWrite(relayPin6, HIGH);
  Serial.println("Colling off solenoids");
  delay(12000);
  Serial.println("Releasing nest box bars again");
  digitalWrite(relayPin4, LOW);
  delay(1500);
  digitalWrite(relayPin4, HIGH);
  digitalWrite(relayPin5, LOW);
  delay(1500);
  digitalWrite(relayPin5, HIGH);
  digitalWrite(relayPin6, LOW);
  delay(1500);
  digitalWrite(relayPin6, HIGH);
  
}
