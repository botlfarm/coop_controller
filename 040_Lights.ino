void controlLight()
{
 if (LightModeStatus==1)
  {
    autoLightControlMode();
  }
 else if (LightModeStatus==0)
 {
  Serial.println("Suplimental light mode disabled");
 }
}

void autoLightControlMode()
{
  if (MinArtificialLight <= 20) //If artifical light is neded for less than 20 min do nothing. make sure relay is off
  {
    digitalWrite(relayPin1, HIGH);
    Serial.println("Less than 20 minutes of artificial light is needed. Lights should be off.");
  }
  else if (MinSinceMid > SunriseMin + 20) //if the current time is later than sunrise plus 20 minutes than turn off relay
  {
    digitalWrite(relayPin1, HIGH);
    Serial.println("It is later than 20 minutes after sunrise. Lights should be off.");
  }
  else if (MinSinceMid >= StartLightMin) //if the current time is later than turn light on time than turn the light on
  {
    digitalWrite(relayPin1, LOW);
    Serial.println("It is before 20 minutes after sunrise and the artifical light should be on");
  }
  else
  {
    digitalWrite(relayPin1, HIGH);
    Serial.println("It is before the artifical light needs to turn on. Lights should be off.");
  }
}
