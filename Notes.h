/*  REFERENCE data.. Do not INCLUDE in the main file....


  This program is designed to work with Rocrail, as a Rocnode.
  All rights etc in Rocrail are owned by Rocrail..
  Visit the excellent Rocrail site to explore more: http://wiki.rocrail.net/doku.php?id=rocnet:rocnet-prot-en


  STATIONARY Interface
  Ths code acts as a ROCNODE, with a programmable ID,
  It allows access to 8 ESP8266 ports, all selectable as either INPUTS or OUTPUTS via the Rocrail Programming/Rocnet/Setup interface.
  FOR THIS CODE,  "PORT 1"  and "CHANNEL 1" both operate on SAME physical pin D1 .. etc on the NodeMCU.

  Invert, Blink and Toggle should all work for "outputs".
  Invert should work for inputs.
  Setting "SERVO"  on the "PIO3 Channel" tab will make the selected port a Servo output.
  Servo Blink works and makes the servo oscillate, based on steps and delay.
  Changes to values are stored in the EEPROM, Some parts of the settings have an updated ten second delay, so that multiple changes result in only one EEPROM commit.

  REPORTING is NOT functional.

  LOCO interface
  The code also includes an MRFC522 interface, using Pins D0,D4, and D5,D6,D7. I have modified my MRFC522 code to allow different (faster) SPI speeds, but it should work with the standard library.
  This was intended to allow use as a "LOCO" .
  In this configuration, D2 and D3 are front and back lights, and D8 is a Servo driver to the Loco motor

   The code includes interface for CV values, and expects to be "programmed using the POM".
   It can send back values to Rocrail 's programming tab..
   MAKE SURE that you have the CV set in the interface!. ALL locos will try to respond if CV[1]=0 (and long address is 0)
   Once set, you should be able to address an individual loco and set and change CV.s
   Setting CV[13] = 13 will force a reset to default values for the whole ESP.
  The motor drive has been updated
    Loco_motor_servo_demand= 90+(CV[2]+ (SPEED*CV[5])/100);
    CV[5](100) is the servo setting for "100%" forward speed
    CV[2](10) is the servo setting to just start the motor forward
    CV[3] is acceleration (1 is slow, 5 is fast)
    CV[4] isdecelleration (1 slow, 5 fast)
    CV[6] (MID) is NOT USED 
   
    CV[48] (100) is  a reverse servo offset (subtracts CV48]-100) from any negative servo demands (but not used)
     (REVERSE) Loco_motor_servo_demand= 90-(CV[2]+ (SPEED*CV[5])/100)-(CV[48]-100); ;
    
    CV[47],bit 7  enables some timing outputs on D4, for cycle testing.  
                  Bit 0 enables Serial debug print meg  (x01)
                  Bit 1 enables Mqqt debug msgs to "debug" topic (x02)
                                                                  (x04)
                  Bit 3 enables Mqqt copy of rx msg to debug topic (x08)
                  bit 4 copy Mqtt sends to serial                    (x10) 
                  Bit 5 enables Roc message review                  (x20)
                  bit 6 notifies "not understoods"                   (x40)  
                  bit 7  enables some timing outputs on D4, for cycle testing.  (x80)


  WHEN USING ROCRAIL TO PROGRAM CV's, Select the loco (this selects the MQQT interafce) then program on Main(POM) (checkboxes acc off and Direct off)

  WIFI interface:
  I have used the WiFiManager, so on first run, the ESP will start an Access point "ROCNODE ESP AP".
  You should connect to this and point your browser to 192.168.4.1 This will start the interface to allow you to scan networks, select with network to connect to and enter passwords.
  Subsequent starts will use the selected SSID and password.
  If you need to change the SSID, you can Restart the Access Point by going to Rocrail Programming/Rocnet/Setup, select the ID of the node you wish to change, and then go to "Update" tab.
  Here, poll, and you should get a number appearinng in the "new revision" box. CHANGE this to "0000", and then press UPDATE. and confirm this.
  The Node will then restart the Access point and after connecting to it, you can change the SSID etc to allow you to use the Node with a different network.

  From Ver 110 you can program OTA. 
  Make sure the node is on and connected BEFORE switching on the arduino interface, and that you have set up the arduino correctly for OTA ..
  If you have, youshould see extra "Network Ports" lines on the "ports selection. Choose the one you want to update and upload as usual.. 


  Now the BAD news...

  Despite calling the subroutines ".h".. they are really .cpp, and I have not made proper ".h" files for them.. if you would like to help, I would love to have them "properly" written.


