/*  REFERENCE data.. Do not INCLUDE in the main file....


  This program is designed to work with Rocrail, as a Rocnode.
  All rights etc in Rocrail are owned by Rocrail..
  Visit the excellent Rocrail site to explore more: http://wiki.rocrail.net/doku.php?id=rocnet:rocnet-prot-en

##AUDIO
The code now supports audio for the loco. It uses a 4 phase chuff that is synchronous to the wheel speed (at least roughly) if you get the right factors set.
It also plays 8 sound effects (F1.wav --F8.wav) on pressing the relevant F button on the rocrail trrottle controls. 
The wav files are stored in the SPIFF, and MUST be uploaded to work. See the web for details of how to use SPIFF with Arduino. 
There is a pin defined for synchronous smoke that can be used with "USB humidifier" hardware.
 


  ##STATIONARY Interface
  When not set up as a loco, the code acts as a ROCNODE, (set at the IP address by defalt or with a programmable ID if this option is selected <see notes in the Loco section>)
  It allows access to 8 ESP8266 ports, all selectable as either INPUTS or OUTPUTS via the Rocrail Programming/Rocnet/Setup interface.
  FOR THIS CODE,  "PORT 1"  and "CHANNEL 1" both operate on SAME physical pins (D1 .. D8)  on the NodeMCU.

  Invert, Blink and Toggle should all work for "outputs".
  Invert should work for inputs.
  Setting "SERVO"  on the "PIO3 Channel" tab will make the selected port a Servo output.
  Servo Blink works and makes the servo oscillate, based on steps and delay.
  Changes to values are stored in the EEPROM, Some parts of the settings have an updated ten second delay, so that multiple changes result in only one EEPROM commit.

  REPORTING is NOT functional.

##RFID reader
 The original code included an MRFC522 interface, and this has been retained, but untested in the latest versions. 
  It will be incompatible with the Audio system unless the pinouts are modified.using Pins D0,D4, and D5,D6,D7. 
  I originally modified my MRFC522 code to allow different (faster) SPI speeds, but it should work with the standard library. I believ ethe library has been updated since I last tested it.
  When a Tag is seen it sends a "sensor change" to Rocrail. The sensor address is formed from the tag ID. 
  This was planned to allow the loco to see multiple tags on the track, to self report its position.
It works, but only when the loco is very slow. The response of the tag system is not fast enough to reliably see the tag when the loco is travelling fast.
  

 ##LOCO interface
  
  The LOCO interface now expects a brushed RC servo motor interface on the pin defined by _LOCO_SERVO_Driven_Port
  In this configuration, FRONTLight AND BACKLight operate on defined pins (defined in the .ino)

   The code includes proper dcc interface for CV values, and expects to be "programmed using the POM".
   It can send back values to Rocrail 's programming tab..
   MAKE SURE that you have the CV set in the interface!. It defaults to 3 in the default eeprom settings. (ALL locos will try to respond if CV[1]=0 (and long address is 0) so chaos can be expected)
   Once set, you should be able to address an individual loco and set and change CV.s I would recommend watching the serial terminal a t least the first few times to make sure the address is properly changed.
   Setting CV[13] = 13 will force a reset to default values (and address=3 ) for the whole ESP.
     
    
  WHEN USING ROCRAIL TO PROGRAM CV's, Select the loco (this selects the MQQT interafce) then program on Main(POM) (checkboxes acc off and Direct off)

##WIFI interface:
  I tested with  WiFiManager, and this is a selectable compiler option set n th e.ino. IF selected, on first run, the ESP will start an Access point "ROCNODE ESP AP".
  You should connect to this and point your browser to 192.168.4.1 This will start the interface to allow you to scan networks, select with network to connect to and enter passwords.
  Subsequent starts will use the selected SSID and password.
  If you need to change the SSID, you can Restart the Access Point by going to Rocrail Programming/Rocnet/Setup, select the ID of the node you wish to change, and then go to "Update" tab.
  Here, poll, and you should get a number appearinng in the "new revision" box. CHANGE this to "0000", and then press UPDATE. and confirm this.
  The Node will then restart the Access point and after connecting to it, you can change the SSID etc to allow you to use the Node with a different network.
  I expected this feature to be useful if you take your loco somewhere new, but I think it adds a small amount of instability, and certainly complocates issues if the hardware "loses2 the router.
  I now prefer to use "fixed" router and password, set in Secrets.h to rapidly reconnect in cases of comms loss. 

  From Ver 110 you can program OTA. 
  Make sure the node is on and connected BEFORE switching on the arduino interface, and that you have set up the arduino correctly for OTA ..
  If you have, youshould see extra "Network Ports" lines on the "ports selection. Choose the one you want to update and upload as usual.. 

##ROCNODE ID setting
  I have forced the RocnodeID to be equal to the last part oof the IP Address that the hardware is allocated by the router. This is a compiler directive controlled thing, and 
  I had to put it in when testing with two decoders, and setting them to the "default" Rocnodes in their EEproms, both were set to the same RocnodeID. 
  This caused havoc with the MQTT broker. 
  If you are confident that you can set the RocnodeID (using Rocrail) then you can disable this directive. 
  - but be sure to have only one decoder ON at a time until you have set up the rocnode ID's.
   

## and finally..
I have also moved a lot of definitons and functions around so that the code should be able to be properly separated into .cpp and .h ... but not just yet! 


/* 
 *  
version 150 :Complete modification to where things are stored and defined...
 *  Trying to use single debugmessage so it can be turned off /on and also sends to Mqtt debug
 *  LOTS of #defines in the INO to change the main options.
 *  Forced the Rocnet Node to be the last part of the IP address, to prevent clashes (the default Eprom settings set this to node 2, Fine if you only have 
 *  one Node, but if you have two the MQTT objects violently to having two nodes with the same name. 
 *  This can be turned off once you have nodes well stabilised.
 *  
 *  
 *  
111 Changed to Ver4 as I think this is a significant update

    Revised servo writes and removed serial debug messages from servo operations as these slowed down the update cycle dramatically
    Servo timing now works properly
    but I added a #define so debug messages in servo routines can be shown if needed again 
    Added a #define to switch off WIFImanager, so a fixed SSID and Password can be set up (Password etc in secrets.h)
    If you wish to use this as a loco (mobile) decoder, uncomment the #define _LOCO_SERVO_Driven_Port 1 
    and (in this example) use port D1 to drive a servo type motor controller.
    Ports 2 and 3 default to front and back lights.
    
    Added OTA ability so you do not need to kneel in the mud outside with a USB cable to update the nodes
    ... But you do need to be on the same wifi SSID.... 
       (I think this may be a timing issue in Arduino environment )
    
    Added a Mqqt debug/monitor :  
   
    Default is send to serial port AND MQQT broker, and to have D4 led flash at the main loop operation.
    To view the messages, use mosquitto_sub... I have my MQQT broker on 192.168.0.21 ( a different machine to my monitor machine), so open a command prompt in the mosquitto directoy and run: 
    mosquitto_sub -h 192.168.0.21 -i "CMD_Prompt" -t debug -q 0   
    or if your broker is on the same machine you are working on :
    mosquitto_sub -h 127.0.0.1  -i "CMD_Prompt" -t debug -q 0
    
    message examples: on the minute each node reports Rocnode number andnickname to the debug to show that it is connected...
          Time 19:36:0s Node:12 (Swing) Msg:Still connected. Connects;<null>
          Time 19:36:0s Node:2 (STA_2) Msg:Still connected. Connects;<null>
          Time 19:36:0s Node:4 (-ID 4 ) Msg:Still connected. Connects;<null>

          It also reports "events"  examples below:
                 Time 19:44:10s Node:4 (-ID 4 ) Msg:Setting Output 7 (SERVO) to State(1) = Position:121
                 Time 19:44:15s Node:4 (-ID 4 ) Msg:Setting Output 7 (SERVO) to State(0) = Position:44
    
    
110 improving the loco functionality, making front and rear lights programming (port selection) more consistent. 
109   revised and hard set group 5, msg 7 'read options' (// report addr and status) response , modified msg decoded to ignore any messages sent by this node, that can be reflected back via mqqt glogal sends.
    and modified node shutdown so it turne POWEROn off.. (this actually has no effect as the servos and the lights do not check this variable at the moment)
108 added ability to print eprom settings so that the default settings can have a copy of a "real" set of settings
107 revised location for MQQT server address in RN[14] moved set eepromdefault  to rocsubs (SV now empty) (part of trying to rework with .cpp files)
106 updates the MQQT address if changed and blue led pulses at 1Hz when conected and working.. 
105 does not wait for poweron for servo control

*/ 

