//===================================================
//===================================================
void requestInput()
{
  Serial.println("*****************************");
  Serial.println("Menu. Enter number in Serial Monitor");
  Serial.println("1-lighting");
  Serial.println("2-door");
  Serial.println("3-nest box");
  Serial.println("4-setup");
  Serial.println("5-full status");
  Serial.println("*****************************"); Serial.println("");
}

//===================================================
//===================================================

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
      nestBoxMenu();
    }
    else if (SerialData == 4)
    {
      setupMenu();
    }
    else if (SerialData == 5)
    {
      printGeneralStatus();
      printLightStatus();
      printDoorStatus();
      delay(MenuTimeout); //aditional timeouts for extended viewing
      resetSerial();
    }
    //hidden shortcuts
    else if (SerialData == 31)  //release nest box bars
    {
      releaseNestBars();
      resetSerial();
    }
    else if (SerialData == 23)  //automatic door menu
    {
      incomingDoorMode();
    }
    else if (SerialData == 24)  //manual door control menu
    {
      manualDoorControl();
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
