void incomingSerialDSTToggle()
{
  Serial.print("DST Status: "); DSTStatusToWords();
  Serial.println("Enter 1 to enable DST and 0 to disable DST");
  resetSerial();
  
  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();
    if (MinSinceMid < 61) //cant change the DST status if it is earlier than 1am. this will give a negative number to the clock
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("Wait until after 1 am to change the DST staus");
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
      resetSerial();
    }

    else if (SerialData == 1)
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("DST enabled");
      DSTStatus = true;
      EEPROM.update(0, DSTStatus);
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");

      dt = clock.getDateTime(); //get the current time form the RTC
      clock.setDateTime(dt.year, dt.month, dt.day, dt.hour + 1, dt.minute, dt.second);  //Set the clock
      resetSerial();
    }
    else if (SerialData == 0)
    {
      Serial.println("++++++++++++++++++++++++++++++");
      Serial.println("DST disabled ");
      DSTStatus = false;
      EEPROM.update(0, DSTStatus);
      Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");

      dt = clock.getDateTime(); //get the current time form the RTC
      clock.setDateTime(dt.year, dt.month, dt.day, dt.hour - 1, dt.minute, dt.second); //Set the clock
      resetSerial();
    }
    else
    {
      Serial.println("Invalid entry. Serial reads this");
      Serial.println(SerialData);
      Serial.println("Back to main menu");
      resetSerial();
    }
  }
}
