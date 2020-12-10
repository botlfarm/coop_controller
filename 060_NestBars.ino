
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
  delay(800);
  digitalWrite(relayPin4, HIGH);
}
