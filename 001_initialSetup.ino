//===================================================
//===================================================

void initialSetup()
{
  //the RTC clock should be initally set to non DST time

  //this is to set the clock to computer time, uncomment the next 1 line
  //rtc.adjust(DateTime(__DATE__, __TIME__));

  //used for manually setting clock if computer times is not right, uncomment the next 1 line
  //rtc.adjust(DateTime(2020, 10, 31, 1, 58, 00));

  //set the initla state of the DSTStatus in eeprom, uncomment the next 1 line
  //DSTStatus = true; //set DSTStatus to true if it is Daylight Savings Time or false if it is Standard time
  //EEPROM.write(0, DSTStatus);  
  //EEPROM.commit();

  //set the initla amount of light needed, uncomment next 2 lines
  //MinLightNeeded = 960;  // set this ro the number of minutes you want of light
  //EEPROM.write(5, MinLightNeeded / 10); // devided by ten to fit in eeprom
  //EEPROM.commit();

  //set the light mode status, uncomment next 2 lines
  //LightModeStatus = true;  //set LightModeStatus to true if to enble suplimental light mode or false to disable 
  //EEPROM.write(10, LightModeStatus);
  //EEPROM.commit();

/*
  //set the current total light,Artificial plus natural uncomment next 2 lines
  CurrentTotalLight = 960;  
  EEPROM.write(15, CurrentTotalLight);
  EEPROM.commit();
*/

  //set the door mode status, uncomment next 2 lines
  //DoorModeStatus = true;  //set DoorModeStatus to true if to enble auto door mode or false to disable 
  //EEPROM.write(20, DoorModeStatus);
  //EEPROM.commit();

  //set the door mode status, uncomment next 2 lines
  //DoorStatus = true;  //set DoorStatus to true if open and fale if closed
  //EEPROM.write(25, DoorStatus);
  //EEPROM.commit();

  //set the initla amount of door opeing offset from sunrise, uncomment next 2 lines
  //OpenDoorOffset = 30;  // set this to the number of minutes you want of light
  //EEPROM.write(30, OpenDoorOffset);
  //EEPROM.commit();

  //set the initla amount of close opeing offset from sunset, uncomment next 2 lines
  //CloseDoorOffset = 30;  // set this to the number of minutes you want of light
  //EEPROM.write(35, CloseDoorOffset);
  //EEPROM.commit();

  //set the initla menu timout, uncomment next 2 lines
  //MenuTimeoutSeconds = 10; // set this to the number of seconds you want between menu changes
  //MenuTimeout = MenuTimeoutSeconds * 1000;  
  //EEPROM.write(40, MenuTimeoutSeconds);
  //EEPROM.commit();
}
