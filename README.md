# ESPMQTTRocnetSound
This is a significant upgrade to my ESPWIFIRocnet project, adding .wav based sound effects for the Loco.

Please note that there a lot of compiler directives (#defines) set in "Directives.h", these allow the code to be set up for a range of different uses and available hardware.

Video of an initial test set-up without the loco: https://youtu.be/Vd0HbV_MXVI

As a loco decoder it gives full control over a loco's motor and front and rear lights and plays "chuff" and "whistle" sound effects that are very similar to those available from commercial DCC sound decoders. Its main limitation is that it cannot simultaneously play two tracks, so the "chuff" effects are temporarily muted whilst whistles etc are played.

The interface is designed to be used as a Node in a RocRail http://wiki.rocrail.net/doku.php controlled model railway and uses the RocNet (http://wiki.rocrail.net/doku.php?id=rocnet:rocnet-prot-en) protocol with an MQTT interface using the PubSubClient https://github.com/knolleary/pubsubclient. 

The code should compile and set up as a loco with address 3, Rocnode will be dependant on your router. Look at the serial terminal to see how the code is setting istself up!.
The MQTT stuff will search for a MQTT broker from 192.168.0.3 to 192.168.0.50. The code is not set up for passwords, but this could be added. This range can be changed in the .ino, (line 141) I use Mosquitto on the same PC that runs Rocrail (note that rorail will need the MQTT address explicitly in its controller setup).  

The MQTT in this program includes a "debug" message that can be subscribed to to give an indication of what s going on. I use it mainly to moonitor/check that nodes are still conneced. 

The code includes ArduinoOTA updating. I have compiled, and uploaded over OTA, the code on both ESP8266 4M options (3M SPIFF and 1M SPIFF). Obviously with the 3M option, you can have longer or more sound effects. The "data" set of sound clips in the git should be able to be compiled in the 1M SPIFFS, <just>. 

## Disclaimers and Thanks
All this code is released under the GPL, and all of it is to be used at your own risk.  
The sound effects playing system used is based on Earle F Philhower's ESP8266Audio library,https://github.com/earlephilhower/ESP8266Audio.
The MQTT capability comes from the PubSubClient https://github.com/knolleary/pubsubclient. 
The code can use WiFi Manager https://github.com/tzapu/WiFiManager.


## Prerequisites and Installation (from ESP8266Audio)
First, make sure you are running the 2.4-rc2 or GIT head version of the Arduino libraries.
You can use GIT to pull right from GitHub: see https://github.com/esp8266/Arduino/blob/master/README.md#using-git-version for detailed instructions.
Alternatively, install using the Arduino Boards manager by using the following URL and selecting 2.4.0-rc2:
https://github.com/esp8266/Arduino/releases/download/2.4.0-rc2/package_esp8266com_index.json
Install the ESP8266Audio library and the SPI driver library in your ~/Arduino/libraries

## Audio clips
You will need SPIFFS Installed, and will need to upload the provided data subdirectory to the ESP8266. 
The 1M file limit is quite small, so keep the samples small if you wish to change them.
I have tried to individually attribute all the clips in the "data" directory, but they either come from:
The Free Zimo sounds (http://www.zimo.at/soundprojekte/zimo/EASY-DAMPF/EASY-DAMPF.zip) 
Paul Chettner's free sounds (http://www.zimo.at/soundprojekte/zimo/DA_R_GB_BR4MT/DA_R_GB_BR4MT.zip), 
or sounds I have cut from a video of the IOW railway Terriers in operation.

### Technical
The Chuff sequence uses four samples that are truncated and sequenced if the chuff period is reduced, giving a realistic (I think) effect for slow speeds. This is the same technique apparently used for commercial DCC sounds.

## Hardware
The hardware expects to use a 12C DAC such as a Adafruit's I2SDAC or a Beyond9032 DAC connected "DIN" to D9/RX  "LRC" to D4 and "CLK" to D8 (D numbers are NodeMCU pin references).
As default, the Front light is D3, Back light is D2, and a "Signal Led" is on D5 to provide indications that messages are being received etc..
The Loco Servo motor controller is on D1. 
This leaves a few ports of later upgrades such as servo controlled couplers.


## Playing sounds
The system should say "Sound System Initiaed" on start up. After that it will play chuffs when the speed is greater than about 2MPH. Pressing the "F" buttons on the loco controller will play sound effects such as whistles, Brake Squeal and Bells.. (Unfortunately the system is only single track at the moment, so the chuff is temporarily "disengaged" when the effect is playing. However it is still very effective.


## "LOCO" interface
====================
 The code is mainly for use as a "LOCO" or mobile node. .
 The "#define _LOCO_SERVO_Driven_Port 1" defines that port D1 will be a servo controlled motor driver for the locomotive. 
 Ports D3 and D2 default as Front and Back Lights.
 Port D5 is a signal LED to show operation and flashes during transmissions etc.
 
   The code includes interfaces for CV read/write values, and expects to be "programmed using the POM".
   It can send back values to Rocrail 's programming tab..
   MAKE SURE that you have the CV set in the RocRAil interface!. ALL locos shoud try to respond if CV[1]=0 (and long address is 0)
   - The "Default" for the eeprom is set as Address=3. 
   Once you are recieving data in the programming interface, you should be able to read, set and change change CV.s
   Setting CV[13] = 13 will force a reset to default values for the whole ESP. (should reset loco to Address 3)
  
  The RocNode ID, and node "nickname" should be set via the normal Rocrail "Programming/Rocnet" tab.
    
 The motor drive has been simplified
    Loco_motor_servo_demand= 90+(CV[2]+ (SPEED*CV[5])/100);
    CV[5](100) is the servo setting for "100%" forward speed
       CV[2](10) is the servo setting to just start the motor forward
         I have removed the CV[48] bias to help match forwards and backwards.
      Forwards:  "servodemand= 90+(CV[2]+ (SPEED*CV[5])/100);"
      Backwards "servodemand= 90-(CV[2]+ (SPEED*CV[5])/100);
    
The Chuff period computation uses CV2, and 5 to re-extract the intended speed to generate a "ChuffPeriod" that is used to trigger chuffs. ChuffPeriod is set in 'SetServo@ in the Subroutines.h". By changing the constant "2590" in that location, the chuff to wheel rotation rate can be altered to get best effect for your loco. 
    
   

 
 
   
  
  
