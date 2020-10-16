void requestInput()
{
  Serial.println("*****************************");
  Serial.println("Menu. Enter number in Serial Monitor");
  Serial.println("1-lighting");
  Serial.println("2-door");
  Serial.println("3-setup");
  Serial.println("*****************************"); Serial.println("");
}

void mainMenu()

{
  if (Serial.available() > 0) // reply only when you receive data:
  {
    SerialData = Serial.parseInt();

    if (SerialData == 1)
    {
      lightMenu();
    }
    else if (SerialData == 2)
    {
      doorMenu();
    }
    else if (SerialData == 3)
    {
      setupMenu();
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
