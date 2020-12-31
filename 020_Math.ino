//===================================================
//===================================================

void doGeneralMath ()
{
  DateTime now = rtc.now();
  MinSinceMid = now.hour() * (60) + now.minute(); //calculate current time in minutes since midnight

  SunriseMin = ashford.sunrise(now.year(), now.month(), now.day(), DSTStatus); //get sunrise minutes since midnight
  SunsetMin = ashford.sunset(now.year(), now.month(), now.day(), DSTStatus); //get sunset minutes since midnight

  Dusk2Dawn::min2str(SunriseTime, SunriseMin); //converting Sunrise minutes to actual time
  Dusk2Dawn::min2str(SunsetTime, SunsetMin); //converting Sunset minutes to actual time
}

//===================================================
//===================================================

void doLightMath()
{
  MinNaturalLight = SunsetMin - SunriseMin; //amount of naural sunlight minutes
  HoursNaturalLight = MinNaturalLight / 60; //amount of naural sunlight hours

  MinArtificialLight = MinLightNeeded - MinNaturalLight;  //amount of needed artificial light

  StartLightMin = SunriseMin - MinArtificialLight; //calculate what time should the light come on
  Dusk2Dawn::min2str(StartLightTime, StartLightMin); //convert minutes to string
}

//===================================================
//===================================================

void doDoorMath()
{
  OpenDoorMin = SunriseMin + OpenDoorOffset; //calculate door open time in minutes since midnight
  Dusk2Dawn::min2str(OpenDoorTime, OpenDoorMin); //convert minutes to string

  CloseDoorMin = SunsetMin + CloseDoorOffset; //calculate door open time in minutes since midnight
  Dusk2Dawn::min2str(CloseDoorTime, CloseDoorMin); //convert minutes to string
}

//===================================================
//===================================================

void doNestBarMath()  //set the nest box release time to the lesser value of open door time or start light time
{
  if (LightModeStatus==1)
  {
    NestBarMin=min(SunriseMin-20,StartLightMin)+2;
  }
  else 
  {
    NestBarMin=min(SunriseMin-20,OpenDoorMin)+2;
  }

   Dusk2Dawn::min2str(NestBarTime, NestBarMin); //convert minutes to string
}

//===================================================
//===================================================

void DSTStatusToWords()
{
  if (DSTStatus == 1) {
    Serial.println ("We are in Daylight Savings Time");
  }
  if (DSTStatus == 0) {
    Serial.println ("We are not in Daylight Savings Time");
  }
}

//===================================================
//===================================================

void LightModeStatusToWords()
{
  if (LightModeStatus == 1) {
    Serial.println ("Suplimneted light mode enabled");
  }
  if (LightModeStatus == 0) {
    Serial.println ("Suplimneted light mode disabled");
  }
}

//===================================================
//===================================================

void DoorModeStatusToWords()
{
  if (DoorModeStatus == 1) {
    Serial.println ("Automatic door mode enabled");
  }
  if (DoorModeStatus == 0) {
    Serial.println ("Automatic door mode disabled");
  }
}

//===================================================
//===================================================

void DoorStatusToWords()
{
  if (DoorStatus == 1) {
    Serial.println ("The door should be open");
  }
  if (DoorStatus == 0) {
    Serial.println ("The door should be closed");
  }
}
