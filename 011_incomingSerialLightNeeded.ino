void incomingSerialLightNeeded()
{
  printLightStatus();
  Serial.println();
  Serial.println("Enter minutes of light required");
  Serial.println("720=12h, 780=13h, 840=14h, 900=15h, 960=16h");
  resetSerial();

  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();
    if (SerialData > 20 && SerialData < 1000)
    {
      MinLightNeeded = SerialData; // read the incoming byte:
      EEPROM.put(1, MinLightNeeded);
      HoursLightNeeded = MinLightNeeded / 60; //calcualte hours of light needed

      Serial.println("++++++++++++++++++++++++++++++");
      Serial.print("Changing minutes of light needed to: "); Serial.print(MinLightNeeded); Serial.print(" minutes, or "); Serial.print(HoursLightNeeded); Serial.println(" hours ");
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
      resetSerial();
    }
    else
    {
      Serial.println("Invalid entry. Value must be between 20 and 1000. Serial reads this");
      Serial.println(SerialData);
      Serial.println("Back to main menu");
      resetSerial();
    }
  }
}
