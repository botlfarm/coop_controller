void initialSetup()
{
  //the RTC clock should be initally set to non DST time

  //this is to set the clock to computer time, uncomment the next 1 line
  //clock.setDateTime(__DATE__, __TIME__);

  //used for manually setting clock if computer times is not right, uncomment the next 1 line
  //clock.setDateTime(2020, 10, 31, 1, 58, 00);

  //set the initla state of the DSTStatus in eeprom, uncomment the next 1 line
  DSTStatus = true; //set DSTStatus to true if it is Daylight Savings Time or false if it is Standard time
  EEPROM.update(0, DSTStatus);  

  //set the initla amount of light needed, uncomment next 2 lines
  MinLightNeeded = 960;  // set this ro the number of minutes you want of light
  EEPROM.put(5, MinLightNeeded);

  //set the initla amount of light needed, uncomment next 2 lines
  LightModeStatus = true;  //set LightModeStatus to true if to enble suplimental light mode or false to disable 
  EEPROM.put(10, LightModeStatus);
}
