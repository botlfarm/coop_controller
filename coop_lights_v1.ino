// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

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
int MinLightNeeded=960; //16 hours

void setup() {
  // set up the LCD's number  columns and rows:
  lcd.begin(16, 2);

// start serial display for troubleshooting
  Serial.begin(9600);
  
// Initialize DS3231
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);    
  
  pinMode(relayPin, OUTPUT);
}

//set location and utc time
 Dusk2Dawn ashford(41.9199, -72.1757, -4);
  
void loop()
{
dt = clock.getDateTime();

//get sunrise/set minutes since midnight
  int SunriseMin = ashford.sunrise(dt.year, dt.month, dt.day, false);
  int SunsetMin = ashford.sunset(dt.year, dt.month, dt.day, false);

//converting Sunris/set minutes to actual time
  char SunriseTime[] = "00:00";
  Dusk2Dawn::min2str(SunriseTime, SunriseMin);
  char SunsetTime[] = "00:00";
  Dusk2Dawn::min2str(SunsetTime, SunsetMin);

//amount  Naural sunlight
 int MinNaturalLight = SunsetMin-SunriseMin;
 float HoursNaturalLight = MinNaturalLight/60; //this is giving a whole number. needs to be fixed!!!

 //amoun  needed artificial light
int MinArtificialLight = MinLightNeeded-MinNaturalLight;

 
//print troublshooting data to serial
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

//display current date, time, sunrise, sunset on lcd
  lcd.clear();
  lcd.print("Current Date");
  lcd.setCursor(0, 1);
  lcd.print(dt.year);   lcd.print("-");
  lcd.print(dt.month);  lcd.print("-");
  lcd.print(dt.day);    lcd.print(" ");
  delay(4000);
  lcd.clear();
  lcd.print("Current Time");
  lcd.setCursor(0, 1);
  lcd.print(dt.hour);   lcd.print(":");
  lcd.print(dt.minute); lcd.print(":");
  lcd.print(dt.second); 
  delay(4000);
  lcd.clear();
  lcd.print("Sun Rise");
  lcd.setCursor(0, 1);
  lcd.print(SunriseTime); 
  delay(4000);
  lcd.clear();
  lcd.print("Sun Set");
  lcd.setCursor(0, 1);
  lcd.print(SunsetTime); 
  delay(4000);
  lcd.clear();
  lcd.print("Hours Nat Light");
  lcd.setCursor(0, 1);
  lcd.print(HoursNaturalLight); 
  delay(4000);



  //prep for relay
  //digitalWrite(relayPin, HIGH);    // turn the relay on (HIGH is the voltage level)
  //delay(2000);                     // wait for a second
  //digitalWrite(relayPin, LOW);    // turn the relay off by making the voltage LOW
  //delay(2000);  
  }
