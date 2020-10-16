void printGeneralStatus()
{
  Serial.print("Current date: "); Serial.print(dt.year);  Serial.print("-"); Serial.print(dt.month);  Serial.print("-"); Serial.println(dt.day);
  Serial.print("Current time: "); Serial.print(dt.hour);  Serial.print(":"); Serial.print(dt.minute); Serial.print(":"); Serial.println(dt.second);
  DSTStatusToWords();
  Serial.print("Sunrise: "); Serial.println(SunriseTime); 
  Serial.print("Sunset: "); Serial.println(SunsetTime); 
}

void printLightStatus()
{
  Serial.print("Natural light: "); Serial.print(HoursNaturalLight); Serial.print(" hours, or "); Serial.print (MinNaturalLight); Serial.println( " minutes");
  LightModeStatusToWords();
  Serial.print("Requested amount of total light:  "); Serial.print(HoursLightNeeded); Serial.print(" hours, or "); Serial.print (MinLightNeeded); Serial.println( " minutes");
  Serial.print("Artificial light needed: "); Serial.print(MinArtificialLight / 60); Serial.print(" hours, or "); Serial.print (MinArtificialLight); Serial.println( " minutes");
  Serial.print("Start Artifical lights: "); Serial.println(StartLightTime);
}

void printDoorStatus()
{
  Serial.print("Door Open offset from sunrise: "); Serial.print(OpenDoorOffset); Serial.println(" minutes ");
  Serial.print("Door Open Time: "); Serial.println(OpenDoorTime);
  Serial.print("Door Close offset from sunset: "); Serial.print(CloseDoorOffset); Serial.println(" minutes ");
  Serial.print("Door Close Time: "); Serial.println(CloseDoorTime);
}
