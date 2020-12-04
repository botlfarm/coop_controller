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
//int Button1Pin = 9;  //define DST button pin

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
int SerialData;
float NestBarMin; //minutes since midnight nest bars will be relsed
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
 

  Serial.begin(9600); //start serial display
  clock.begin(); //Initialize DS3231

  initialSetup(); //only need to use this at initial setup or reprograming the RTC. Uncomment nesicary parts at initialSetup function

  //lightCheck(); //check to see if relays are working
  //doorCheck(); //check to see if actuator is working
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
  dt = clock.getDateTime(); //get the current time form the RTC
  doGeneralMath(); //all the universal calculations.
  doLightMath();  //all the lighting calcualtions
  doDoorMath(); //all the door calculations
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
  Serial.begin(9600);
  delay(MenuTimeout);
}
