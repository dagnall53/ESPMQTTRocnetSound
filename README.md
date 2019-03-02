# Please now use https://github.com/dagnall53/WiRocS 

##
This code is not being updated anymore.. --
## there is a significant bug I only found after uploading
When running and attached to a serial terminal, the serial terminal disconnects after about 10 secs, but he code continued working. However, when run stand alone, the node has problems starting up and without the serial interface connected, I cannot yet see why this is happening. I will fix it, but if you need code urgently please use the previous version (V21) which is available at https://github.com/dagnall53/ESPWIFIRocnet


# ESPMQTTRocnetSound
This is a significant upgrade to my ESPWIFIRocnet project, adding .wav based two channel sound effects for the Loco.
This version also has improved PWM drive for locos.

Please note that there a lot of compiler directives (#defines) set in "Directives.h", these allow the code to be set up for a range of different uses and available hardware.

Video of a test with the 3d printed loco: https://www.youtube.com/watch?v=Pg5r6MZDhww

When the code is compiled as a "LOCO" decoder (By including the #define "loco_Servo_driven_port" directive) it gives full control over a loco's motor and front and rear lights and plays "chuff" and "whistle" sound effects that are very similar to those available from commercial DCC sound decoders. All the sounds are WAV files and can be uploaded using a built in FTP server. 

The interface is designed to be used as a Node in a RocRail http://wiki.rocrail.net/doku.php controlled model railway and uses the RocNet (http://wiki.rocrail.net/doku.php?id=rocnet:rocnet-prot-en) protocol with an MQTT interface using the PubSubClient https://github.com/knolleary/pubsubclient. 

The code should compile and set up as a loco with an address of 3 (say) which can initially be forced by "#define "Force_Loco_Addr 3". The Rocnode ID will be dependant on your router (or you can use #define "ForceRocnetNodeID_to_subIPL"). Look at the serial terminal to see how the code is setting istself up!.

From V22, I have added a Serial interface that gives you 3 seconds from the board starting up during which you can interface with the booard via a serial terminal set at 115200 baud. 
To initiate setting/changeing the Wifi settings, type xxx(cr) into your termnal emulator. 
The interface should then change and ask you to change WiFi router/password etc. 
Pressing sss when finished will save the settings to EEPROM for next time.
If using PuTTY, you can set "Answerback to ^E" to "xxx^M" this should automatically start the setting sequence, but I have had some issues with this. Using the ARduino terminal with an xxx typed in the send box (and newline selected) allows you to press return or SEND wilst the node is doing its 3 second timeout, and this reliably enters the serial setting process. 

The MQTT stuff will initially look for an address set up during the Serial interface sequence, or set in Secrets, and can search for a MQTT broker from 192.168.0.3 to 192.168.0.50. The code is not set up for passwords, but this could be added. This search range can be changed in MQTT:reconnect (MQTT.cpp line 269). To set to a single address, set the #define myBrokerSubip in secrets You can pprevent huntiing for adddresses by setting  bool ScanForBroker = falsein secrets. 

I use Mosquitto on the same PC that runs Rocrail (note that RocRail will need the MQTT address explicitly in its controller setup).  

The MQTT in this program includes a "debug" message that can be subscribed to to give an indication of what s going on. I use it mainly to moonitor/check that nodes are still connected.  Run "mosquitto_sub -h 127.0.0.1 -i "CMD_Prompt" -t debug -q 0" on the PC that is running Mosquitto and you will see the debug messages. They are very useful to check things are running. (change the IP address to the PC running Mosquitto address if you run this on another computer).

The code includes ArduinoOTA updating. I have compiled, and uploaded over OTA, the code on both ESP8266 4M options (3M SPIFF and 1M SPIFF). Obviously with the 3M option, you can have longer or more sound effects. The "data" set of sound clips in the Git needs 3M SPIFFS. 

## Disclaimers and Thanks
All this code is released under the GPL, and all of it is to be used at your own risk.  
The sound effects playing system used is based on Earle F Philhower's ESP8266Audio library,https://github.com/earlephilhower/ESP8266Audio.
The MQTT capability comes from the PubSubClient https://github.com/knolleary/pubsubclient. 
The code can use WiFi Manager https://github.com/tzapu/WiFiManager.


## Prerequisites  (from ESP8266Audio)
First, make sure you are running the 2.4-rc2 or GIT head version of the Arduino libraries.
You can use GIT to pull right from GitHub: see https://github.com/esp8266/Arduino/blob/master/README.md#using-git-version for detailed instructions.
Alternatively, install using the Arduino Boards manager by using the following URL and selecting 2.4.0-rc2:
https://github.com/esp8266/Arduino/releases/download/2.4.0-rc2/package_esp8266com_index.json
Install the ESP8266Audio library and the SPI driver library in your ~/Arduino/libraries

## First Install
From Ver 21 the eeprom should automatically be set to sensible values if it was not already programmed, but if you have trouble try to forcibly set to known defaults by folowing these instructions: 
When FIRST setting up your NodeMCU or Wemos board, set (uncomment) these directives: {  #define _ForceRocnetNodeID_to_subIPL  #define _ForceDefaultEEPROM  #define _Force_Loco_Addr 8 }

Set the "Force_Loco_Addr" to the address you prefer (3)?

Change the "secrets" to your router...

Thn Upload the SPIFF data and then program the board (FLASH size 4M ,3M SPIFFS). Providing you have rocrail and a MQTT broker running it should connect and say "sound system Initiated". 

lastly comment out the "_Force" directives so you can set names etc by Rocrail. and Re-Programm the board.


## Audio clips
You will need SPIFFS Installed, and will need to upload the provided data subdirectory to the ESP8266. 
My data need the larger 3M SPIFF file setting. 
I have tried to individually attribute all the clips in the "data" directory, but they are mainly sounds I have cut from videos of the IOW railway or Bluebell Terriers in operation. F1 is the Ivor the Engine theme tune.. There are some alternate Chuff sets, if you cut out the Ivor sound and some of the chuffs, it will fit the 1M SPIFFS limit if you prefer.

If you have audio, a stationary node can now play the F1-F8 sounds by Rocrail sending commands to "ports" 11-18. This could be useful for adding sounds at a station. 

### Technical
The Chuff sequence uses four samples that are truncated and sequenced if the chuff period is reduced, giving a realistic (I think) effect for slow speeds. This is the same technique apparently used for commercial DCC sounds.
I have from V22 added code to modify the 4 phase wav sounds used at slow speeds to a one wav file repeated at a quarter of the rate at higher speeds. This is experimental. 

## Hardware
The hardware expects to use a 12C DAC such as a Adafruit's I2SDAC or a Beyond9032 DAC connected "DIN" to D9/RX  "LRC" to D4 and "CLK" to D8 (D numbers are NodeMCU pin references). (setsed with Adafruit board, but not te Beyond board)
As the LOCO default, the Front light is D3, Back light is D2, and a "Signal Led" is on D5 to provide indications that messages are being received etc..
The Loco Servo motor controller is on D1. 
This leaves a few ports of later upgrades such as servo controlled couplers.
Port D4 (LRC) Reports as being used, but is available on the NODAC version if you need it (see https://github.com/earlephilhower/ESP8266Audio/issues/32 )


## Playing sounds
For any node with Audio enabled, The system should say "Sound System Initiated" on start up. 

A loco will play chuffs when the speed is greater than about 2MPH. Pressing the "F" buttons on the loco controller will play sound effects such as whistles, Brake Squeal and Bells.. 
Function F9 switches on / off the chuffs, which can be played simultaneously with the main f1-8 sound effects. 

For a stationary node, providing you have the audio enabled, a RocRail "output" can be used to trigger playing the F1-F8 sounds. The Rocrail output should be set to Bus (Rocrail id of the node), with Address 11 sounding F1 Address 12,F2 etc. It works best if the Rocrail Output Type setting is set to "push button".   

The volume of each "F" effect is controlled by a CV: These are defaulted to 127, but can be changed using normal DCC "CV change" procedures: 

CV[100]=127; // Overall volume control

CV[101]=127; //volume for F1 

CV[102]=127;

CV[103]=127;

CV[104]=127;

CV[105]=127;

CV[106]=127;

CV[107]=127;

CV[108]=127; // Volume for F8

CV[110]=127; // volume for chuffs

CV[111]=127; // volume for Brake Squeal


## "LOCO" interface
 The code is for use as a "LOCO" or mobile node when the define  _LOCO_SERVO_Driven_Port is set 
 The "#define _LOCO_SERVO_Driven_Port 1" defines that port D1 will be a (servo controlled or PWM controlled) motor driver for the locomotive. 
 Ports D5 and D2 default as Front and Back Lights.
 Port D0 is a signal LED to show operation and flashes during transmissions etc.
 If using a PWM motor drive, a second port "_LocoPWMDirPort" needs to be define. I use D3 for this in my hardware.
 
   The code includes interfaces for CV read/write values, and expects to be "programmed using the POM".
   It can send back values to Rocrail 's programming tab..
   MAKE SURE that you have the CV set in the RocRAil interface!. ALL locos shoud try to respond if CV[1]=0 (and long address is 0)
   - The "Default" for the eeprom is set as Address=3. 
   Once you are recieving data in the programming interface, you should be able to read, set and change change CV.s
   Setting CV[8] = 13 will force a reset to default values for the whole ESP. (should reset loco to Address 3, providing this is set in the defaults.)
  
  The RocNode ID, and node "nickname" can be set via the normal Rocrail "Programming/Rocnet" tab, once the #defaults "_Force" are commented out
    
 The motor drive CV controls are as follows:  
 CV[2] sets the Minimum "voltage" setting. 
        To this is added eiter CV[66] or CV[95] (depending on direction (Fwd and reverse trims).
        It is assumed that the CV[2] value sets the motor at a minimum speed, expected to be 3mph.
        CV[5] is then used as a multiplier on any speed above the minimum, increasing the "voltage drive linearly.
        
  A Kick Start function has been added that momentarily (Time duration set by CV[65]) kicks the motor to 40 to start it. 

A Maximum speed possible given the CV values is calculated and used to limit the set speed. 
With the PWM,  precise( 0-1023 speed steps) are possible, but the RC servo control is limited to  1 degree steps from 1 to 179 degrees.
       
My experience is that the PWM allows better slow speed control, but lower top speed, whereas the RC has higher top speed but poor low speed control. 
    
The Chuff period computation uses the speed demand as an assumed MPH value to produce a "ChuffPeriod" that is used to trigger chuffs. ChuffPeriod is set in 'Chuff.cpp" line 73 onwards. . Line 69 has SetChuffPeriod(2590/MotorSpeed); By changing the constant "2590" in that location, the chuff to wheel rotation rate can be altered to get best effect for your loco. 
Using a wheel mounted sensor (not yet implemented) may be necessary for preciscion control.

F0 switches the lights on / off.
    
## "Stationary" interface   
IF not set as Loco, the code allows full Rocrail control over D1 to D8 ports. 
The default settings give a set of defaults derived from a saved eprom set for a station.

This set sets 1-4 as pwm outputs (for Lights) ( BUT be careful of the strange logic in the L293 motor driver board if you use it for pwm lighting) I personally only 2 lines to try and avoid confusion. Without the L293 driver, the ports work more intuitively. (The L293 is not simply four inverters!!)

D5 AND D6 are sensor inputs for using with hall switches

D7 and D8 are servo outputs for points.

Port D8 has a physical pull down on some hardware that prevents it being used as an input with internal pull up.  

## MORE:
There are some further detailed notes on the use of the hardware and using the code with Rocrail in the two PDFs. 

 
 
   
  
  
