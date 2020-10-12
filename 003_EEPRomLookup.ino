void checkLightNeededStatus()
{
  Serial.print("Light needed after restart: ");
  EEPROM.get(1, MinLightNeeded);
  Serial.println(MinLightNeeded);
  HoursLightNeeded = MinLightNeeded / 60; //calcualte hours of light needed
}

void checkDSTStatus()
{
  Serial.print("DST status after restart: ");
  DSTStatus = EEPROM.read(0);
  DSTStatusToWords();
}
/*
  void checkCurrentTotalLight()
  {
  Serial.print("Current total light after restart: ");
  EEPROM.get(4, currentTotalLight);
  Serial.println(currentTotalLight);
  }
*/
