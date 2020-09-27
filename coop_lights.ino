//This program will get todays sunrise and sunset, than calculate when to turn on the lights

//note "min" in variables is for minutes not minimum

//needed for rtc
#include <Wire.h>
#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;

//for keeping variables in memory after power outge
#include <EEPROM.h>

//set output pins for relay
int relayPin = 6;

// include library for sunrise/sunset
#include <Dusk2Dawn.h>

//vatiable for hours of sunlight
float MinLightNeeded = 960; //16 hours by default
float HoursLightNeeded = 16; //16 hours by default

//setup needed for DST button
int buttonApin = 9;
bool DSTStatus = false;

void setup() {

  // start serial display for troubleshooting
  Serial.begin(9600);

  // Initialize DS3231
  clock.begin();

  //-----------initial set up only-------
  //set the clock. It should be initally set to non DST time
  
  //this is to set the clock to computer time
  //clock.setDateTime(__DATE__, __TIME__);
  
  //used for manually setting clock if computer times is not right
  //clock.setDateTime(2020, 10, 31, 1, 58, 00);

  //set the initla state of the DSTStatus in eeprom
  //EEPROM.update(0, DSTStatus);

  //set relay pins
  pinMode(relayPin, OUTPUT);

  //set up DST button
  pinMode(buttonApin, INPUT_PULLUP);
/*
  //test the relay configuration
  Serial.print("*****************************"); Serial.println("");
  Serial.print("Checking if relay is working. Relay On 5 seconds"); Serial.println("");
  digitalWrite(relayPin, HIGH);
  delay(5000);
  Serial.print("Relay off 5 seconds"); Serial.println("");
  digitalWrite(relayPin, LOW);
  delay(5000);
  Serial.print("Flash relay"); Serial.println("");
    */
  digitalWrite(relayPin, HIGH);
  delay(500);
  digitalWrite(relayPin, LOW);
  Serial.print("Relay check complete"); Serial.println("");
  Serial.print("*****************************"); Serial.println("");Serial.println("");
  delay(1000);

  //check stored DST state on EEPROM using function defined at the end of the code
  checkDSTStatus(); 
}


void loop()
{
//set location and utc time
  Dusk2Dawn ashford(41.9199, -72.1757, -5);
  
  //get input form user for amount of hours requested
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    MinLightNeeded = Serial.parseInt();
    //calcualte hours of light needed
    HoursLightNeeded = MinLightNeeded / 60;

    // display new light requested time:
    Serial.print("++++++++++++++++++++++++++++++"); Serial.println("");
    Serial.print("Changing minutes of light needed to: "); Serial.print(MinLightNeeded); Serial.print(" minutes, or "); Serial.print(HoursLightNeeded); Serial.print(" hours ");Serial.println(""); 
    Serial.print("++++++++++++++++++++++++++++++"); Serial.println("");Serial.println("");
    delay(2000);
    
    //// reset the serial monitor to clear data
    Serial.end();
    Serial.begin(9600);
  }

  //get the current time form the RTC
  dt = clock.getDateTime();

  //calculate current time in minutes since midnight
  float MinSinceMid = dt.hour * (60) + dt.minute;

  //get sunrise/set minutes since midnight
  float SunriseMin = ashford.sunrise(dt.year, dt.month, dt.day, DSTStatus);
  float SunsetMin = ashford.sunset(dt.year, dt.month, dt.day, DSTStatus);

  //converting Sunris/set minutes to actual time
  char SunriseTime[] = "00:00";
  Dusk2Dawn::min2str(SunriseTime, SunriseMin);
  char SunsetTime[] = "00:00";
  Dusk2Dawn::min2str(SunsetTime, SunsetMin);

  //amount  Naural sunlight
  float MinNaturalLight = SunsetMin - SunriseMin;
  float HoursNaturalLight = MinNaturalLight / 60;

  //amount  needed artificial light
  float MinArtificialLight = MinLightNeeded - MinNaturalLight;

  //calculate what time should the light come on
  float StartLightMin = SunriseMin - MinArtificialLight;
  char StartLightTime[] = "00:00";
  Dusk2Dawn::min2str(StartLightTime, StartLightMin);

  Serial.print("*****************************"); Serial.println("");
  Serial.print("Current date: "); Serial.print(dt.year);  Serial.print("-"); Serial.print(dt.month);  Serial.print("-"); Serial.print(dt.day); Serial.println("");
  Serial.print("Current time: "); Serial.print(dt.hour);  Serial.print(":"); Serial.print(dt.minute); Serial.print(":"); Serial.print(dt.second);  Serial.print(" or "); Serial.print(MinSinceMid); Serial.print(" minutes since midnight"); Serial.println("");
  Serial.print("DST Status: "); 
   if(DSTStatus == 1) {
    Serial.print ("We are in Daylight Savings Time");
   } 
   if(DSTStatus == 0) {
    Serial.print ("We are not in Daylight Savings Time");
   }
  Serial.println("");
  Serial.print("Todays sunrise: "); Serial.print(SunriseTime); Serial.print(" or "); Serial.print(SunriseMin); Serial.print(" minutes since midnight"); Serial.println("");
  Serial.print("Todays sunset: "); Serial.print(SunsetTime); Serial.print(" or "); Serial.print(SunsetMin); Serial.print(" minutes since midnight"); Serial.println("");
  Serial.print("Natural light: "); Serial.print(HoursNaturalLight); Serial.print(" hours, or "); Serial.print (MinNaturalLight); Serial.print( " minutes"); Serial.println("");
  Serial.print("Requested amount of sunlight:  "); Serial.print(HoursLightNeeded); Serial.print(" hours, or "); Serial.print (MinLightNeeded); Serial.print( " minutes"); Serial.println("");
  Serial.print("Artificial light needed: "); Serial.print(MinArtificialLight / 60); Serial.print(" hours, or "); Serial.print (MinArtificialLight); Serial.print( " minutes"); Serial.println("");
  Serial.print("Start Artifical lights: "); Serial.print(StartLightTime); Serial.print(" or "); Serial.print(StartLightMin); Serial.print(" minutes since midnight"); Serial.println("");

  if (MinArtificialLight <= 15) {   //If artifical light is neded for less than 15 min do nothing. make sure relay is off
    digitalWrite(relayPin, LOW);
    Serial.print("Less than 15 minutes of artificial light is needed"); Serial.println("");
  }
  else if (MinSinceMid > SunriseMin+15) { //is the current time is later than sunrise plus 15 minutesthan turn off relay
    digitalWrite(relayPin, LOW);
    Serial.print("It is later than 15 minutes after sunrise"); Serial.println("");
  }
  else if (MinSinceMid >= StartLightMin) { //if the current time is later than turn light on time than turn the light on
    digitalWrite(relayPin, HIGH);
    Serial.print("It is before 15 minutes after sunrise and the artifical light should be on"); Serial.println("");
  }
  else {
    digitalWrite(relayPin, LOW);
    Serial.print("It is before the artifical light needs to turn on"); Serial.println("");
  }

  Serial.print("*****************************"); Serial.println("");
  Serial.print("Press and hold button to toggle DST"); Serial.println("");
  Serial.print("Enter minutes of sunlight required if you want to chane it"); Serial.println("");
  Serial.print("720=12h, 780=13h, 840=14h, 900=15h, 960=16h"); Serial.println("");
  Serial.print("*****************************"); Serial.println(""); Serial.println("");

  delay(15000);
  
if (digitalRead(buttonApin) == LOW && DSTStatus==false)
    {
      Serial.print("++++++++++++++++++++++++++++++");Serial.println("");
      Serial.print("DST changed to "); 
      DSTStatus = true;
      EEPROM.update(0, DSTStatus);
      Serial.print(DSTStatus); Serial.println("");
      Serial.print("++++++++++++++++++++++++++++++"); Serial.println("");Serial.println("");

       //get the current time form the RTC
       dt = clock.getDateTime();

       //Set the clock 
       clock.setDateTime(dt.year, dt.month, dt.day, dt.hour+1, dt.minute, dt.second);
        
       delay(2000);
    }
  else if (digitalRead(buttonApin) == LOW && DSTStatus==true)
    {
      Serial.print("++++++++++++++++++++++++++++++"); Serial.println("");
      Serial.print("DST changing to "); 
      DSTStatus = false;
      EEPROM.update(0, DSTStatus);
      Serial.print(DSTStatus); Serial.println("");
      Serial.print("++++++++++++++++++++++++++++++"); Serial.println("");Serial.println("");

       //get the current time form the RTC
       dt = clock.getDateTime();

       //Set the clock 
       clock.setDateTime(dt.year, dt.month, dt.day, dt.hour-1, dt.minute, dt.second);
              
      delay(2000);
    }

}

void checkDSTStatus() {
  Serial.print("-------------------------------"); Serial.println("");
   Serial.print("DST status after restart: ");
   DSTStatus = EEPROM.read(0);
   if(DSTStatus == 1) {
    Serial.println ("true");
   } 
   if(DSTStatus == 0) {
    Serial.println ("false");
   }
   Serial.print("-------------------------------"); Serial.println("");Serial.println("");
   delay(2000);
}
