void checkEEPROM()
{
  Serial.println("Getting stored data from EEPROM");
  checkDSTStatus(); //check stored DST state on EEPROM
  checkLightNeededStatus(); //check for stored minutes of needed light on EEPROM
  checkLightModeStatus(); //check for stored light mode status
  //checkCurrentTotalLight(); //check stored current total light on EEPROM

}

void checkDSTStatus()
{
  DSTStatus = EEPROM.read(0);
  DSTStatusToWords();
}

void checkLightNeededStatus()
{
  EEPROM.get(5, MinLightNeeded);
  Serial.print("Light needed after restart: ");
  Serial.println(MinLightNeeded);
  HoursLightNeeded = MinLightNeeded / 60; //calcualte hours of light needed
}

void checkLightModeStatus()
{
  LightModeStatus = EEPROM.read(10);
  LightModeStatusToWords();
}

/*
void checkCurrentTotalLight()
{
  Serial.print("Current total light after restart: ");
  EEPROM.get(15, currentTotalLight);
  Serial.println(currentTotalLight);
}
*/
