/*
 * Coop_Controler
 * Written by Nick Weinstock
 * BOTL Farm
 * A program to atomate a chicken coop
 */

#include <Wire.h>  //needed for RTC Library to function
//---------------------------#include <DS3231.h> //RTC library
#include <EEPROM.h>  //for keeping variables in memory after power outge
#include <Dusk2Dawn.h> // include library for sunrise/sunset
#include <RTClib.h>  //to show time

//------------------------DS3231 clock;
//------------------------RTCDateTime dt;
RTC_DS3231 rtc;
/*
int relayPin1 = 6; //define relay pin
int relayPin2 = 5; //define relay pin
int relayPin3 = 4; //define relay pin
int relayPin4 = 3; //define relay pin
*/

int relayPin1 = 13; //define relay pin
int relayPin2 = 12; //define relay pin
int relayPin3 = 14; //define relay pin
int relayPin4 = 27; //define relay pin

float MinLightNeeded; //total minutes of light needed
float HoursLightNeeded; //total hours of light needed
bool DSTStatus = false; //the status of DST.
bool LightModeStatus = false; //the status of light mode
float CurrentTotalLight;
bool DoorModeStatus = false; //the status of door mode
bool DoorStatus = false; //the open/close status of door
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
float OpenDoorOffset; //the amount of minutes offset from sunries to open the door
float CloseDoorOffset; //the amount of miuntes offset from sunset to close the door
float OpenDoorMin; //minutes since midnight the door will open
char OpenDoorTime[] = "00:00"; //time the door opens
float CloseDoorMin; //Minutes since midnight the door will close
char CloseDoorTime[] = "00:00"; //time the door closes
float MenuTimeout; //milaseconds of timeout for menu
float MenuTimeoutSeconds; //seconds of timeout for menu
int SerialData;
float NestBarMin; //minutes since midnight nest bars will be relsed
char NestBarTime[] = "00:00"; //time the Nest bars will be released
//float maxChangeperday = 10; //max minutes of daylight change per day
//float currentTotalLight;  //current amount of total light

Dusk2Dawn ashford(41.9199, -72.1757, -5); //set location and utc time


//===================================================
//===================================================

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

 
  EEPROM.begin(512); // initialize EEPROM with predefined size

  Serial.begin(115200); //start serial display
  //-------------------------clock.begin(); //Initialize DS3231
  if (! rtc.begin()) {
Serial.println("Couldn't find RTC");
while (1);
}

  initialSetup(); //only need to use this at initial setup or reprograming the RTC. Uncomment nesicary parts at initial setup function

  //lightCheck(); //check to see if relays are working
  //doorCheck(); //check to see if actuator is working
  //nestBarCheck(); //check to see if nest bar relese is working
  delay(2000);
  Serial.println("-------------------------------");
  checkEEPROM(); //looks for stored variables after power outage
  Serial.println("-------------------------------"); Serial.println("");
  delay(MenuTimeout);
}

//===================================================
//===================================================

void loop()
{
  Serial.println("============================");
  Serial.println("Screen Refresh");
  Serial.println("============================");
  Serial.println();
  //------------------------------dt = clock.getDateTime(); //get the current time form the RTC
  //------------------------------DateTime now = rtc.now(); //get the current time form the RTC
  doGeneralMath(); //all the universal calculations.
  doLightMath();  //all the lighting calcualtions
  doDoorMath(); //all the door calculations
  doNestBarMath(); //all the nest bar calculations
  controlLight(); //turn the relay on and off as necisary
  controlDoor(); //open or close the door
  controlNestBars(); //release the nest bars
  Serial.println("");
  Serial.println("*****************************");
  printGeneralStatus(); //display the time and stuff
  requestInput(); //prompt user for serial input. (mainMenu tab)
  delay(MenuTimeout);
  mainMenu(); //Check to see if input is coming in form serial monitor
}

//===================================================
//===================================================

void resetSerial()
{
  // reset the serial monitor to clear data
  Serial.end();
  Serial.begin(115200);
  delay(MenuTimeout);
}
