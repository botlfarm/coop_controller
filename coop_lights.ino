//This program will get todays sunrise and sunset, than calculate when to turn on the lights

#include <Wire.h>  //needed for RTC Library to function
#include <DS3231.h> //RTC library
#include <EEPROM.h>  //for keeping variables in memory after power outge
#include <Dusk2Dawn.h> // include library for sunrise/sunset

DS3231 clock;
RTCDateTime dt;

int relayPin1 = 6; //define relay pin
int relayPin2 = 5; //define relay pin
int relayPin3 = 4; //define relay pin
int relayPin4 = 3; //define relay pin
int Button1Pin = 9;  //define DST button pin

float MinLightNeeded; //total minutes of light needed
float HoursLightNeeded; //total hours of light needed
bool DSTStatus = false; //the status of DST. 
char DSTStatusWords[36]; //converting the DST status into actual words
float MinSinceMid; //minutes since midnight
float SunriseMin; //sunrise in minutes since midnight
float SunsetMin; //sunset in minutes since midnight
char SunriseTime[] = "00:00"; //sunrise in readable time
char SunsetTime[] = "00:00"; //sunset in redable time
float MinNaturalLight; //minutes of natural sunlight
float HoursNaturalLight; //hours of naturl sunlight
float MinArtificialLight; //minutes of artifical light
float StartLightMin; //how many minutes after midnight to turn on the lights
char StartLightTime[] = "00:00"; //the time the lights turn on
float OpenDoorOffset=30; //the amount of minutes offset from sunries to open the door
float CloseDoorOffset=30; //the amount of miuntes offset from sunset to close the door
float OpenDoorMin; //minutes since midnight the door will open
char OpenDoorTime[] = "00:00"; //time the door opens
float CloseDoorMin; //Minutes since midnight the door will close
char CloseDoorTime[] = "00:00"; //time the door closes
//float maxChangeperday = 10; //max minutes of daylight change per day
//float currentTotalLight;  //current amount of total light

Dusk2Dawn ashford(41.9199, -72.1757, -5); //set location and utc time

void setup()
{
  pinMode(relayPin1, OUTPUT); //set relay pin
  pinMode(relayPin2, OUTPUT); //set relay pin
  pinMode(relayPin3, OUTPUT); //set relay pin
  pinMode(relayPin4, OUTPUT); //set relay pin
  digitalWrite(relayPin1, HIGH);
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin3, HIGH);
  digitalWrite(relayPin4, HIGH);
  pinMode(Button1Pin, INPUT_PULLUP); //set up DST button pin

  Serial.begin(9600); //start serial display 
  clock.begin(); //Initialize DS3231

  initialSetup(); //only need to use this at initial setup or reprograming the RTC. Uncomment nesicary parts at initialSetup function

  lightCheck(); //check to see if relays are working
  doorCheck(); //check to see if actuator is working
  Serial.println("-------------------------------");
  checkLightNeededStatus(); //check for stored minutes of needed light on EEPROM
  checkDSTStatus(); //check stored DST state on EEPROM
  //checkCurrentTotalLight(); //check stored current total light on EEPROM
  Serial.println("-------------------------------"); Serial.println("");
  delay(4000);
}

void loop()
{
  buttonPush();  //see if DST putton is being pushed
  incomingSerialData();  //get input form user for amount of hours requested
  dt = clock.getDateTime(); //get the current time form the RTC
  doGeneralMath(); //all the universal calculations.
  doLightMath();  //all the lighting calcualtions
  doDoorMath(); //all the door calculations
  Serial.println("*****************************");
  printGeneralStatus(); //display the time and stuff
  Serial.println("");
  printLightStatus(); //Print light stuff
  Serial.println("");
  printDoorStatus(); //Print door stuff
  Serial.println("*****************************");
  controlLight(); //turn the relay on and off as necisary
  controlDoor(); //open or close the door
  requestInput(); //prompt user for putton press or serial input
  delay(15000);
}

void initialSetup()
{
  //the RTC clock should be initally set to non DST time

  //this is to set the clock to computer time, uncomment the next 1 line
  //clock.setDateTime(__DATE__, __TIME__);

  //used for manually setting clock if computer times is not right, uncomment the next 1 line
  //clock.setDateTime(2020, 10, 31, 1, 58, 00);

  //set the initla state of the DSTStatus in eeprom, uncomment the next 1 line
  //EEPROM.update(0, DSTStatus);  //set DSTStatus to true if it is Daylight Savings Time or false if it is Standard time

  //set the initla amount of light needed, uncomment next 2 lines
  //MinLightNeeded = 960;  // set this ro the number of minutes you want of light
  //EEPROM.put(1, MinLightNeeded);
}

void lightCheck()
{
  Serial.println("*****************************");
  Serial.println("Checking if lights are working.");
  delay(1000);
  Serial.println("Light on 3 seconds");
  digitalWrite(relayPin1, LOW);
  delay(3000);
  Serial.println("Lights off 3 seconds");
  digitalWrite(relayPin1, HIGH);
  delay(3000);
  Serial.println("Flash lights");
  digitalWrite(relayPin1, LOW);
  delay(1000);
  digitalWrite(relayPin1, HIGH);
  delay(500);
  Serial.println("Light check complete");
  Serial.println("*****************************"); Serial.println("");
  delay(2000);
}

void doorCheck() 
{
  Serial.println("*****************************");
  Serial.println("Checking if door is working.");
  delay(1000);
  Serial.println("Close for 3 seconds");
  closeDoor();
  delay(3000);
  Serial.println("Stop door for 3 seconds");
  stopDoor();
  delay(3000);
  Serial.println("Open door for 3 seconds");
  openDoor();
  delay(3000);
  stopDoor();
  Serial.println("Door check complete");
  Serial.println("*****************************"); Serial.println("");
  delay(2000);
}

void checkLightNeededStatus() {
  Serial.print("Light needed after restart: ");
  EEPROM.get(1, MinLightNeeded);
  Serial.println(MinLightNeeded);
  HoursLightNeeded = MinLightNeeded / 60; //calcualte hours of light needed
}

void checkDSTStatus()
{
  Serial.print("DST status after restart: ");
  DSTStatus = EEPROM.read(0);
  DSTStatusToWords();
}
/*
void checkCurrentTotalLight()
{
  Serial.print("Current total light after restart: ");
  EEPROM.get(4, currentTotalLight);
  Serial.println(currentTotalLight);
}
*/

void buttonPush() {

  if (digitalRead(Button1Pin) == LOW && MinSinceMid < 61) //cant change the DST status if it is earlier than 1am. this will give a negative number to the clock
  {
    Serial.println("++++++++++++++++++++++++++++++");
    Serial.println("Wait until after 1 am to change the DST staus");
    Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
  }

  else if (digitalRead(Button1Pin) == LOW && DSTStatus == false)
  {
    Serial.println("++++++++++++++++++++++++++++++");
    Serial.println("DST enabled");
    DSTStatus = true;
    EEPROM.update(0, DSTStatus);
    Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");

    dt = clock.getDateTime(); //get the current time form the RTC
    clock.setDateTime(dt.year, dt.month, dt.day, dt.hour + 1, dt.minute, dt.second);  //Set the clock
    delay(2000);
  }
  else if (digitalRead(Button1Pin) == LOW && DSTStatus == true)
  {
    Serial.println("++++++++++++++++++++++++++++++");
    Serial.println("DST disabled ");
    DSTStatus = false;
    EEPROM.update(0, DSTStatus);
    Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");

    dt = clock.getDateTime(); //get the current time form the RTC
    clock.setDateTime(dt.year, dt.month, dt.day, dt.hour - 1, dt.minute, dt.second); //Set the clock
    delay(2000);
  }
}

void incomingSerialData()
{
  if (Serial.available() > 0) // reply only when you receive data:
  {
    MinLightNeeded = Serial.parseInt(); // read the incoming byte:
    EEPROM.put(1, MinLightNeeded);
    HoursLightNeeded = MinLightNeeded / 60; //calcualte hours of light needed

    Serial.println("++++++++++++++++++++++++++++++");
    Serial.print("Changing minutes of light needed to: "); Serial.print(MinLightNeeded); Serial.print(" minutes, or "); Serial.print(HoursLightNeeded); Serial.println(" hours ");
    Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
    delay(2000);

    // reset the serial monitor to clear data
    Serial.end();
    Serial.begin(9600);
  }
}

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
  Serial.print("Requested amount of sunlight:  "); Serial.print(HoursLightNeeded); Serial.print(" hours, or "); Serial.print (MinLightNeeded); Serial.println( " minutes");
  Serial.print("Artificial light needed: "); Serial.print(MinArtificialLight / 60); Serial.print(" hours, or "); Serial.print (MinArtificialLight); Serial.println( " minutes");
  Serial.print("Start Artifical lights: "); Serial.print(StartLightTime); Serial.print(" or "); Serial.print(StartLightMin); Serial.println(" minutes since midnight");
}

void printDoorStatus()
{
  Serial.print("Door Open offset from sunrise: "); Serial.print(OpenDoorOffset); Serial.println(" minutes ");
  Serial.print("Door Open Time: "); Serial.print(OpenDoorTime); Serial.print(" or "); Serial.print(OpenDoorMin); Serial.println(" minutes since midnight");
  Serial.print("Door Open offset from sunrise: "); Serial.print(CloseDoorOffset); Serial.println(" minutes ");
  Serial.print("Door Close Time: "); Serial.print(CloseDoorTime); Serial.print(" or "); Serial.print(CloseDoorMin); Serial.println(" minutes since midnight");
}

void controlLight()
{
  if (MinArtificialLight <= 20) //If artifical light is neded for less than 20 min do nothing. make sure relay is off
  {
    digitalWrite(relayPin1, HIGH);
    Serial.println("Less than 20 minutes of artificial light is needed. Lights should be off.");
  }
  else if (MinSinceMid > SunriseMin + 20) //if the current time is later than sunrise plus 20 minutes than turn off relay
  {
    digitalWrite(relayPin1, HIGH);
    Serial.println("It is later than 20 minutes after sunrise. Lights should be off.");
  }
  else if (MinSinceMid >= StartLightMin) //if the current time is later than turn light on time than turn the light on
  {
    digitalWrite(relayPin1, LOW);
    Serial.println("It is before 20 minutes after sunrise and the artifical light should be on");
  }
  else
  {
    digitalWrite(relayPin1, HIGH);
    Serial.println("It is before the artifical light needs to turn on. Lights should be off.");
  }
}

void controlDoor()
{
  if (MinSinceMid > OpenDoorMin && MinSinceMid < CloseDoorMin)
  {
    openDoor();
    Serial.println("The door should be open.");
  }
  else
  {
    closeDoor();
    Serial.println("The door should be closed.");
  }
}

void requestInput()
{
  Serial.println("*****************************");
  Serial.println("Press and hold button to toggle DST");
  Serial.println("Enter minutes of sunlight required if you want to change it");
  Serial.println("720=12h, 780=13h, 840=14h, 900=15h, 960=16h");
  Serial.println("*****************************"); Serial.println("");
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

void closeDoor() 
{
    digitalWrite(relayPin2, LOW);
    digitalWrite(relayPin3, HIGH);
}

void openDoor() 
{
    digitalWrite(relayPin2, HIGH);
    digitalWrite(relayPin3, LOW);
}

void stopDoor() 
{
    digitalWrite(relayPin2, HIGH);
    digitalWrite(relayPin3, HIGH);
}
