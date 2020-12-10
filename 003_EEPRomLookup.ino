//===================================================
//===================================================

void checkEEPROM()
{
  Serial.print("Last updated: "); Serial.print(__DATE__); Serial.print(" "); Serial.println(__TIME__);
  Serial.println("Getting stored data from EEPROM");
  checkDSTStatus(); //check stored DST state on EEPROM
  checkLightNeededStatus(); //check for stored minutes of needed light on EEPROM
  checkLightModeStatus(); //check for stored light mode status
  //checkCurrentTotalLight(); //check stored current total light on EEPROM
  checkDoorModeStatus(); //check for stored door mode status
  checkDoorStatus(); //check for stored door position
  checkOpenDoorOffset();
  checkCloseDoorOffset();
  checkMenuTimeout();
}

//===================================================
//===================================================

void checkDSTStatus()
{
  DSTStatus = EEPROM.read(0);
  DSTStatusToWords();
}

//===================================================
//===================================================

void checkLightNeededStatus()
{
  EEPROM.get(5, MinLightNeeded);
  Serial.print("Light needed after restart: "); Serial.println(MinLightNeeded,0);
  HoursLightNeeded = MinLightNeeded / 60; //calcualte hours of light needed
}

//===================================================
//===================================================

void checkLightModeStatus()
{
  LightModeStatus = EEPROM.read(10);
  LightModeStatusToWords();
}

//===================================================
//===================================================


void checkCurrentTotalLight()
{
  /*
  Serial.print("Current total light after restart: ");
  EEPROM.get(15, currentTotalLight);
  Serial.println(currentTotalLight);
  */
}


//===================================================
//===================================================

void checkDoorModeStatus()
{
  DoorModeStatus = EEPROM.read(20);
  DoorModeStatusToWords();
}

//===================================================
//===================================================

void checkDoorStatus()
{
  DoorStatus = EEPROM.read(25);
  DoorStatusToWords();
}

//===================================================
//===================================================

void checkOpenDoorOffset()
{
  EEPROM.get(30, OpenDoorOffset);
  Serial.print("Open door offset: "); Serial.print(OpenDoorOffset,0); Serial.println(" minutes");
}

//===================================================
//===================================================

void checkCloseDoorOffset()
{
  EEPROM.get(35, CloseDoorOffset);
  Serial.print("Close door offset: "); Serial.print(CloseDoorOffset,0); Serial.println(" minutes");
}

//===================================================
//===================================================

void checkMenuTimeout()
{
  EEPROM.get(40, MenuTimeout);
  Serial.print("Menu Timeout: "); Serial.print(MenuTimeout,0); Serial.println(" milliseconds");
}
