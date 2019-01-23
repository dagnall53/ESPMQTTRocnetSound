#ifndef _Directives_h
 #define _Directives_h


#define Pi03_Start_At 1
#define Pi03_End_At 8

#define Pi02_Start_At 1
#define Pi02_End_At 8

 #define SignalLed 0 //NodeMCU D0! expects LED +resistor to +ve! DO not change this..
 #define SignalON LOW  //defined so I can change the "phase of the SignalLED" easily.
 #define SignalOFF HIGH

//#define _LOCO_SERVO_Driven_Port 1  //if using as mobile (LOCO) decoder node.. node becomes a loco with servo on port D "1"  for motor control
 //#define _LocoPWMDirPort  3         //add this second Port if using PWM loco motor control Using "3" assumes a L293 inputs driven from port D(_LOCO_SERVO_Driven_Port) and D(_LocoPWMDirPort)
                                     //
 //assume if a loco then you need front and back lights...
 #ifdef _LOCO_SERVO_Driven_Port
  #define BACKLight 2  //NodeMCU D2
  #define FRONTLight 5 //NodeMCU D5
//#define SteamOutputPin 6
 #endif




//---------------AUDIO--------------------

//#define _AudioDAC  //to use Earle F Philhowers's audio libraries and I2C dac for audio 
//#define _AudioNoDAC  //to use Earle F Philhowers's audio libraries and his clever single transistor 1 bit oversampling dac for audio (connect D9 (rx)to base of NPN via a 1K, Emitter to ground and Collector is drive to speaker connected to V+) 

//--- audio dac interface control ports---These are set depending on the two defines above..

 #if defined (_AudioDAC) || defined(_AudioNoDAC)
    #define _Audio              //RX/D9, D8, and D4 pins.defined below    
    #define I2SDAC_LRC 4  //D4 is used in no dac because of default i2s settings (is i2s clock?) but can be used as input if you need the pin in no dac..
                           //but needs to be defined in order for NoDac to work
    #define I2SDAC_DIN 9   //D9/rx used for both Audio types, is main transistor base drive for NoDac 
 #endif
 #ifdef _AudioDAC
     #define I2SDAC_CLK 8 //D8 used by DAC only
 #endif 
//-- end of audio defines


//----SET THESE WHEN INITIALLY SETTING UP THE CODE -------------- to set the eeprom to reasonably sensible defaults.
//from ver 15 equivalents to these should be automatically set if the eeprom is empty.. So they may not be needed, but if you have to reset anything, they may be useful.
//If used, After running ONCE with them set, comment them out and re-program so that the loco addr and pin functions etc can be set via rocrail

//#define _ForceRocnetNodeID_to_subIPL //stops the ability of rocnet to change the node number, but prevents the possibility of two nodes having same node number
//#define _ForceDefaultEEPROM //
//#define _Force_Loco_Addr 3 

//#define _DefaultPrintOut 1 //Set this so you can capture your own "defaults" and put them in the RocSubs:SetDefaultSVs() function 

 //---------------------------------------------------------------end of main compiler #defines--------------
 //old define

 //#define _RFID 1  //if using rfid reader THIS IS AN OLD part of the code and not tested recently. 
 //               It adds a RFID reader and sends sensor messages depending on the RFID tag "read.
 //               it's interaction with the new code is UNTESTED.

 //#define _Use_Wifi_Manager //uncomment this to use a "standard" fixed SSID and Password
 //----------------DEBUG Defines 
 ////Debug settings

 // uncomment thes to add extra debug messages.
 // a minimum number of Mqtt debug message will always be set to allow monitoring of node status 
 //(typically the time synch is very useful to tell a node is prenet and working.) 
//#define _SERIAL_DEBUG 
//#define _SERIAL_Audio_DEBUG 
//#define _SERIAL_SUBS_DEBUG 
//#define _showRocMSGS
//#define _SERIAL_MQTT_DEBUG
//#define _SERVO_DEBUG //(enables debug messages in set motor speed rc and pwm

#endif
