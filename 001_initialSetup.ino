void initialSetup()
{
  //the RTC clock should be initally set to non DST time

  //this is to set the clock to computer time, uncomment the next 1 line
  //clock.setDateTime(__DATE__, __TIME__);

  //used for manually setting clock if computer times is not right, uncomment the next 1 line
  //clock.setDateTime(2020, 10, 31, 1, 58, 00);

  //set the initla state of the DSTStatus in eeprom, uncomment the next 1 line
  //DSTStatus = true; //set DSTStatus to true if it is Daylight Savings Time or false if it is Standard time
  //EEPROM.update(0, DSTStatus);  

  //set the initla amount of light needed, uncomment next 2 lines
  //MinLightNeeded = 960;  // set this ro the number of minutes you want of light
  //EEPROM.put(5, MinLightNeeded);

  //set the light mode status, uncomment next 2 lines
  //LightModeStatus = true;  //set LightModeStatus to true if to enble suplimental light mode or false to disable 
  //EEPROM.put(10, LightModeStatus);

  //set the current total light,Artificial plus natural uncomment next 2 lines
  //CurrentTotalLight = 960;  
  //EEPROM.put(15, CurrentTotalLight);

  //set the door mode status, uncomment next 2 lines
  //DoorModeStatus = true;  //set DoorModeStatus to true if to enble auto door mode or false to disable 
  //EEPROM.put(20, DoorModeStatus);

  //set the door mode status, uncomment next 2 lines
  //DoorStatus = true;  //set DoorStatus to true if open and fale if closed
  //EEPROM.put(25, DoorStatus);

  //set the initla amount of door opeing offset from sunrise, uncomment next 2 lines
  //OpenDoorOffset = 30;  // set this to the number of minutes you want of light
  //EEPROM.put(30, OpenDoorOffset);

  //set the initla amount of close opeing offset from sunset, uncomment next 2 lines
  //CloseDoorOffset = 30;  // set this to the number of minutes you want of light
  //EEPROM.put(35, CloseDoorOffset);

  //set the initla menu timout, uncomment next 2 lines
  //MenuTimeout = 10000;  // set this ro the number of milleseconds you want between menu changes
  //EEPROM.put(40, MenuTimeout);
}
