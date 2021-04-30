# coop_Controller

Intention is to automate a chicken coop  

# Materials:  
* Arduino Mega 2560  
* ds1307 RTC  
* 4 Channel DC 5V Relay Module https://www.amazon.com/gp/product/B07DN8DTRW/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1  
* power suply module  
* usb adapter from arduino board to phone (variable dependingon phone) https://www.amazon.com/gp/product/B071G6NLHJ/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1  
* 12 V Deep cycle battery  
* Solar panel https://www.amazon.com/gp/product/B07TTMF3FZ/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1  
* Cabinet lock (for roost latch)https://www.amazon.com/gp/product/B0714DT68D/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1  
* Springs (may be nesisary for lowering roosts) https://www.amazon.com/gp/product/B008RGAUDQ/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1  
* linar actuator (door operation) https://www.amazon.com/gp/product/B07HNTPB87/ref=ppx_yo_dt_b_asin_title_o09_s00?ie=UTF8&psc=1  
* DC bulbs and bulb sockets https://www.amazon.com/gp/product/B07JQ8JHF4/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1&fpw=alm  
* Battery voltage monitor (hopefulyl this will be coded at some point) https://www.amazon.com/gp/product/B08LKSB2VN/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1  
  
  
This will get current sunrise and sun set times based on date and coordinate location (location is hard prograed in code)  
All variables that you can change will get stored in EPROM so duing a power shortage all current states will be restored.   
Initial set up functions should be un commented the first time the program is run. This sets the dfault variables in the EEPROM and sets the time clock.  
Once initial set up is run comment out the setup functions and reload the brogram to the board.   
  
Once setup your phone is connected to the board through USB to use as the interface. This will only need to be used for changing settings.  
ArduinoDroid https://play.google.com/store/apps/details?id=name.antonsmirnov.android.arduinodroid2 has a usefull serial monitor.  
  
# Doors  
Controlled with relay #2 and #3. These need to be wired to reverse current flow.  
Im automatic mode you can set the open and close offset from sunrise and sunset for your doors. they will open and close at the desired time.  
In maual mode you can open, close or stop the door  
There is a snow dump option. When thisis selected the door will close for 60 seconds then reopen. Giving you time to clear snow off the door.  
  
# Lights  
Controlled with realy #1  
When suplimental light mode is enabled you can tell it how many hours of total light you want your coop to have.  
It will calculate when to turn the lights on to reach the total amount of light you requested.  
Note that artifical ligt will come on in the moring so all the hens are in the coop already.  
It will stay on for 20 minutes past sunrise as this is the aproxamate time in testign that it was needed to not get darker in the coop afte rthe lights turn off.  
If less than 20 minutes of artifical light is needed than no light will be provided.  

# Roosts  
Controlled with relay #4  
The cabintet latches hold the roosts in a closed position.  
The progran calculates the earlest relese time to be 2 minuts after the hens are woken up.  
If in automatic light mode it will open when the lights come on.  
If the light mode is diabled then it will open when the door opens.  
In all cases sunrise is the latest the roosts will open.  


