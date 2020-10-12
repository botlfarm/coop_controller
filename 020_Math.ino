
void doGeneralMath ()
{
  MinSinceMid = dt.hour * (60) + dt.minute; //calculate current time in minutes since midnight

  SunriseMin = ashford.sunrise(dt.year, dt.month, dt.day, DSTStatus); //get sunrise minutes since midnight
  SunsetMin = ashford.sunset(dt.year, dt.month, dt.day, DSTStatus); //get sunset minutes since midnight

  Dusk2Dawn::min2str(SunriseTime, SunriseMin); //converting Sunrise minutes to actual time
  Dusk2Dawn::min2str(SunsetTime, SunsetMin); //converting Sunset minutes to actual time
}

void doLightMath()
{
  MinNaturalLight = SunsetMin - SunriseMin; //amount of naural sunlight minutes
  HoursNaturalLight = MinNaturalLight / 60; //amount of naural sunlight hours

  MinArtificialLight = MinLightNeeded - MinNaturalLight;  //amount of needed artificial light

  StartLightMin = SunriseMin - MinArtificialLight; //calculate what time should the light come on
  Dusk2Dawn::min2str(StartLightTime, StartLightMin); //convert minutes to string
}

void doDoorMath()
{
  OpenDoorMin = SunriseMin + OpenDoorOffset; //calculate door open time in minutes since midnight
  Dusk2Dawn::min2str(OpenDoorTime, OpenDoorMin); //convert minutes to string

  CloseDoorMin = SunsetMin + CloseDoorOffset; //calculate door open time in minutes since midnight
  Dusk2Dawn::min2str(CloseDoorTime, CloseDoorMin); //convert minutes to string
}

void DSTStatusToWords()
{
  if (DSTStatus == 1) {
    Serial.println ("We are in Daylight Savings Time");
  }
  if (DSTStatus == 0) {
    Serial.println ("We are not in Daylight Savings Time");
  }
}
