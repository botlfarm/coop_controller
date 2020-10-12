void printGeneralStatus()
{
  Serial.print("Current date: "); Serial.print(dt.year);  Serial.print("-"); Serial.print(dt.month);  Serial.print("-"); Serial.println(dt.day);
  Serial.print("Current time: "); Serial.print(dt.hour);  Serial.print(":"); Serial.print(dt.minute); Serial.print(":"); Serial.print(dt.second);  Serial.print(" or "); Serial.print(MinSinceMid); Serial.println(" minutes since midnight");
  Serial.print("DST Status: "); DSTStatusToWords();
  Serial.print("Todays sunrise: "); Serial.print(SunriseTime); Serial.print(" or "); Serial.print(SunriseMin); Serial.println(" minutes since midnight");
  Serial.print("Todays sunset: "); Serial.print(SunsetTime); Serial.print(" or "); Serial.print(SunsetMin); Serial.println(" minutes since midnight");
}

void printLightStatus()
{
  Serial.print("Natural light: "); Serial.print(HoursNaturalLight); Serial.print(" hours, or "); Serial.print (MinNaturalLight); Serial.println( " minutes");
  Serial.print("Requested amount of total light:  "); Serial.print(HoursLightNeeded); Serial.print(" hours, or "); Serial.print (MinLightNeeded); Serial.println( " minutes");
  Serial.print("Artificial light needed: "); Serial.print(MinArtificialLight / 60); Serial.print(" hours, or "); Serial.print (MinArtificialLight); Serial.println( " minutes");
  Serial.print("Start Artifical lights: "); Serial.print(StartLightTime); Serial.print(" or "); Serial.print(StartLightMin); Serial.println(" minutes since midnight");
}

void printDoorStatus()
{
  Serial.print("Door Open offset from sunrise: "); Serial.print(OpenDoorOffset); Serial.println(" minutes ");
  Serial.print("Door Open Time: "); Serial.print(OpenDoorTime); Serial.print(" or "); Serial.print(OpenDoorMin); Serial.println(" minutes since midnight");
  Serial.print("Door Close offset from sunrise: "); Serial.print(CloseDoorOffset); Serial.println(" minutes ");
  Serial.print("Door Close Time: "); Serial.print(CloseDoorTime); Serial.print(" or "); Serial.print(CloseDoorMin); Serial.println(" minutes since midnight");
}
