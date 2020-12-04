//===================================================
//===================================================
void nestBoxMenu()
{
  Serial.println("*****************************");
  Serial.println("Nest Box Menu. Enter number in Serial Monitor");
  Serial.println("1-Manualy release nest box bars");
  Serial.println("*****************************"); Serial.println("");
  delay(MenuTimeout);

  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();

    if (SerialData == 1)
    {
      releaseNestBars();
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
