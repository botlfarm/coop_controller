//This program will get todays sunrise and sunset, than calculate when to turn on the lights

//note "min" in variables is for minutes not minimum

#include <Wire.h>  //needed for RTC Library to function
#include <DS3231.h> //RTC library
#include <EEPROM.h>  //for keeping variables in memory after power outge
#include <Dusk2Dawn.h> // include library for sunrise/sunset

DS3231 clock;
RTCDateTime dt;

int relayPin = 6; //define relay pin
int buttonApin = 9;  //define DST button pin

float MinLightNeeded;
float HoursLightNeeded;
bool DSTStatus = false;
char DSTStatusWords[36];
float MinSinceMid;
float SunriseMin;
float SunsetMin;
char SunriseTime[] = "00:00";
char SunsetTime[] = "00:00";
float MinNaturalLight;
float HoursNaturalLight;
float MinArtificialLight;
float StartLightMin;
char StartLightTime[] = "00:00";

Dusk2Dawn ashford(41.9199, -72.1757, -5); //set location and utc time

void setup()
{
  Serial.begin(9600); //start serial display for troubleshooting
  clock.begin(); //Initialize DS3231

  initialSetup(); //only need to use this at initial setup or reprograming the RTC. Uncomment nesicary parts at initialSetup function

  pinMode(relayPin, OUTPUT); //set relay pin
  pinMode(buttonApin, INPUT_PULLUP); //set up DST button pin

  relayCheck(); //check to see if relays are working
  Serial.println("-------------------------------");
  checkLightNeededStatus(); //check for stored minutes of needed light
  checkDSTStatus(); //check stored DST state on EEPROM using function defined at the end of the code
  Serial.println("-------------------------------"); Serial.println("");
  delay(4000);
}

void loop()
{
  buttonPush();  //see if DST putton is being pushed
  incomingSerialData();  //get input form user for amount of hours requested
  dt = clock.getDateTime(); //get the current time form the RTC
  doMath();  //all the calcualtions
  printStatus();  //display the calculations
  controlRelay();  //turn the relay on and off as necisary
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

void relayCheck()
{
  //test the relay configuration
  Serial.println("*****************************");
  Serial.println("Checking if relay is working. Relay On 5 seconds");
  digitalWrite(relayPin, HIGH);
  delay(5000);
  Serial.println("Relay off 5 seconds");
  digitalWrite(relayPin, LOW);
  delay(5000);
  Serial.println("Flash relay");
  digitalWrite(relayPin, HIGH);
  delay(500);
  digitalWrite(relayPin, LOW);
  Serial.println("Relay check complete");
  Serial.println("*****************************"); Serial.println("");
  delay(1000);
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

void buttonPush() {

  if (digitalRead(buttonApin) == LOW && MinSinceMid < 61) //cant change the DST status if it is earlier than 1am. this will give a negative number to the clock
  {
    Serial.println("++++++++++++++++++++++++++++++");
    Serial.println("Wait until after 1 am to change the DST staus");
    Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");
  }

  else if (digitalRead(buttonApin) == LOW && DSTStatus == false)
  {
    Serial.println("++++++++++++++++++++++++++++++");
    Serial.print("DST enabled");
    DSTStatus = true;
    EEPROM.update(0, DSTStatus);
    Serial.println("++++++++++++++++++++++++++++++"); Serial.println("");

    dt = clock.getDateTime(); //get the current time form the RTC
    clock.setDateTime(dt.year, dt.month, dt.day, dt.hour + 1, dt.minute, dt.second);  //Set the clock
    delay(2000);
  }
  else if (digitalRead(buttonApin) == LOW && DSTStatus == true)
  {
    Serial.println("++++++++++++++++++++++++++++++");
    Serial.print("DST disabled ");
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
void doMath()
{
  MinSinceMid = dt.hour * (60) + dt.minute; //calculate current time in minutes since midnight

  SunriseMin = ashford.sunrise(dt.year, dt.month, dt.day, DSTStatus); //get sunrise minutes since midnight
  SunsetMin = ashford.sunset(dt.year, dt.month, dt.day, DSTStatus); //get sunset minutes since midnight

  Dusk2Dawn::min2str(SunriseTime, SunriseMin); //converting Sunrise minutes to actual time
  Dusk2Dawn::min2str(SunsetTime, SunsetMin); //converting Sunset minutes to actual time

  MinNaturalLight = SunsetMin - SunriseMin; //amount of naural sunlight minutes
  HoursNaturalLight = MinNaturalLight / 60; //amount of naural sunlight hours

  MinArtificialLight = MinLightNeeded - MinNaturalLight;  //amount of needed artificial light

  StartLightMin = SunriseMin - MinArtificialLight; //calculate what time should the light come on
  Dusk2Dawn::min2str(StartLightTime, StartLightMin); //convert minutes to string
}

void printStatus()
{
  Serial.println("*****************************");
  Serial.print("Current date: "); Serial.print(dt.year);  Serial.print("-"); Serial.print(dt.month);  Serial.print("-"); Serial.println(dt.day);
  Serial.print("Current time: "); Serial.print(dt.hour);  Serial.print(":"); Serial.print(dt.minute); Serial.print(":"); Serial.print(dt.second);  Serial.print(" or "); Serial.print(MinSinceMid); Serial.println(" minutes since midnight");
  Serial.print("DST Status: "); DSTStatusToWords();
  Serial.print("Todays sunrise: "); Serial.print(SunriseTime); Serial.print(" or "); Serial.print(SunriseMin); Serial.println(" minutes since midnight");
  Serial.print("Todays sunset: "); Serial.print(SunsetTime); Serial.print(" or "); Serial.print(SunsetMin); Serial.println(" minutes since midnight");
  Serial.print("Natural light: "); Serial.print(HoursNaturalLight); Serial.print(" hours, or "); Serial.print (MinNaturalLight); Serial.println( " minutes");
  Serial.print("Requested amount of sunlight:  "); Serial.print(HoursLightNeeded); Serial.print(" hours, or "); Serial.print (MinLightNeeded); Serial.println( " minutes");
  Serial.print("Artificial light needed: "); Serial.print(MinArtificialLight / 60); Serial.print(" hours, or "); Serial.print (MinArtificialLight); Serial.println( " minutes");
  Serial.print("Start Artifical lights: "); Serial.print(StartLightTime); Serial.print(" or "); Serial.print(StartLightMin); Serial.println(" minutes since midnight");
}

void controlRelay()
{
  if (MinArtificialLight <= 15) //If artifical light is neded for less than 15 min do nothing. make sure relay is off
  {
    digitalWrite(relayPin, LOW);
    Serial.println("Less than 15 minutes of artificial light is needed");
  }
  else if (MinSinceMid > SunriseMin + 15) //is the current time is later than sunrise plus 15 minutesthan turn off relay
  {
    digitalWrite(relayPin, LOW);
    Serial.println("It is later than 15 minutes after sunrise");
  }
  else if (MinSinceMid >= StartLightMin) //if the current time is later than turn light on time than turn the light on
  {
    digitalWrite(relayPin, HIGH);
    Serial.println("It is before 15 minutes after sunrise and the artifical light should be on");
  }
  else
  {
    digitalWrite(relayPin, LOW);
    Serial.println("It is before the artifical light needs to turn on");
  }
}

void requestInput()
{
  Serial.println("*****************************");
  Serial.println("Press and hold button to toggle DST");
  Serial.println("Enter minutes of sunlight required if you want to chane it");
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
