#define SignalLed 0 // NodeMCU D0! expects LED +resistor to +ve!
#define SignalON LOW  // defined so I can change the "phase of the SignalLED" easily.
#define SignalOFF HIGH

#define _LOCO_SERVO_Driven_Port 1    // if using as mobile (LOCO) node.. node becomes a loco with servo on port D "1"  for motor control


#ifdef _LOCO_SERVO_Driven_Port 1 
  #define FRONTLight 3 // NodeMCU D3
  #define BACKLight 2  // NodeMCU D2
  #define SteamOutputPin 7
#endif


// #define _RFID 1  // if using rfid reader
//#define _DefaultPrintOut 1 // for printing the defaults on eprom save so you can save them in the RocSubs:SetDefaultSVs() function 
// #define _Use_Wifi_Manager // uncomment this to use a "standard" fixed SSID and Password

//#define _AudioDAC  // to use Earle F Philhowers's audio libraries and I2C dac for audio 
#define _AudioNoDAC  //  to use Earle F Philhowers's audio libraries and his clever single transistor 1 bit oversampling dac for audio 

// I could probably be cleverer with this set!!
#ifdef _AudioNoDAC
#define _Audio // sets some compiler stuff
#endif
#ifdef _AudioDAC
#define _Audio // sets some compiler stuff
#endif



//----SET THESE WHEN INITIALLY SETTING UP THE CODE to set the eeprom to reasonably sensible defaults.
// Then comment them out and re-program so that the loc addr etc can be set via rocrail
//#define _ForceRocnetNodeID_to_subIPL // stops the ability of rocnet to change the node number, but prevents the possibility of two nodes having same node number
//#define _ForceDefaultEEPROM //
//#define _Force_Loco_Addr 8 

//---------------------------------------------------------------end of compiler #defines--------------
