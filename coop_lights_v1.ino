//note "min" in variables is for minutes not minimum

//needed for rtc
#include <Wire.h>
#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;

//set output pins for relay
int relayPin = 6;

// include library for sunrise/sunset
#include <Dusk2Dawn.h>

//vatiable for hours of sunlight
float MinLightNeeded=960; //16 hours

void setup() {

// start serial display for troubleshooting
  Serial.begin(9600);
  
// Initialize DS3231
  clock.begin();

  //this is to set the clock. ony run this once
  //clock.setDateTime(__DATE__, __TIME__);    

  //used for manually setting clock for testing
   // clock.setDateTime(2020, 9, 18, 6, 31, 00);

  //set relay pins
  pinMode(relayPin, OUTPUT);

}

  
void loop()
{

//set location and utc time
 Dusk2Dawn ashford(41.9199, -72.1757, -4);
 
dt = clock.getDateTime();

//calculate current time in minutes since midnight
 float MinSinceMid=dt.hour*(60)+dt.minute;

//get sunrise/set minutes since midnight
  float SunriseMin = ashford.sunrise(dt.year, dt.month, dt.day, false);
  float SunsetMin = ashford.sunset(dt.year, dt.month, dt.day, false);

//converting Sunris/set minutes to actual time 
  char SunriseTime[] = "00:00";
  Dusk2Dawn::min2str(SunriseTime, SunriseMin);
  char SunsetTime[] = "00:00";
  Dusk2Dawn::min2str(SunsetTime, SunsetMin);


//amount  Naural sunlight
 float MinNaturalLight = SunsetMin-SunriseMin;
 float HoursNaturalLight = MinNaturalLight/60; 

 //amount  needed artificial light
float MinArtificialLight = MinLightNeeded-MinNaturalLight;

//calculate what time should the light come on
float StartLightMin = SunriseMin-MinArtificialLight;
char StartLightTime[] = "00:00";
  Dusk2Dawn::min2str(StartLightTime, StartLightMin);


if (MinArtificialLight<=15){      //If artifical light is neded for less than 15 min do nothing. make sure relay is off
  digitalWrite(relayPin, LOW);
  Serial.print("a");Serial.println("");}  //troubleshooting
else if (MinSinceMid>SunriseMin) {   //is the current time is later than sunrise than turn off relay
  digitalWrite(relayPin, LOW);
  Serial.print("b");Serial.println("");}  //troubleshooting
else if (MinSinceMid>=StartLightMin){   //if the current time is later than turn light on time than turn the light on
  digitalWrite(relayPin, HIGH);
  Serial.print("c");Serial.println("");}  //troubleshooting
else {
 digitalWrite(relayPin, LOW);
 Serial.print("d");Serial.println("");} //troubleshooting

 
//print troublshooting data to serial
  Serial.print("*****************************");Serial.println("");
  Serial.print("Current date and time: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  Serial.print("todays sunrise: "); Serial.print(SunriseMin);Serial.print(" or  "); Serial.print(SunriseTime); Serial.println("");
  Serial.print("todays sunset: "); Serial.print(SunsetMin);Serial.print(" or  "); Serial.print(SunsetTime); Serial.println("");
  Serial.print("hours  natural light: ");Serial.print(HoursNaturalLight);Serial.println("");
  Serial.print("Min  Artificial light needed: ");Serial.print(MinArtificialLight);Serial.println("");
  Serial.print("Start Light time: ");Serial.print(StartLightTime);Serial.println("");
  Serial.print("Start Light min since midnight: ");Serial.print(StartLightMin);Serial.println("");
  Serial.print("Minutes since midnight: ");Serial.print(MinSinceMid);Serial.println("");
  Serial.print("*****************************");Serial.println("");Serial.println("");


}
 
