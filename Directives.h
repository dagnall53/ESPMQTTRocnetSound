
#define _SERVO_DEBUG (enables debug messages in set motor speed rc and pwm

#define SignalLed 0 // NodeMCU D0! expects LED +resistor to +ve!
#define SignalON LOW  // defined so I can change the "phase of the SignalLED" easily.
#define SignalOFF HIGH

#define _LOCO_SERVO_Driven_Port 1  // if using as mobile (LOCO) node.. node becomes a loco with servo on port D "1"  for motor control
#define _LocoPWMDirPort  3         // add this second Port if using PWM loco motor control assumes L293 inputs driven from port D(_LOCO_SERVO_Driven_Port) and D(_LocoPWMDirPort)
                                     //

#ifdef _LOCO_SERVO_Driven_Port
  #define BACKLight 2  // NodeMCU D2
  #define FRONTLight 5 // NodeMCU D5
//  #define SteamOutputPin 6
#endif


// #define _RFID 1  // if using rfid reader
//#define _DefaultPrintOut 1 // for printing the defaults on eprom save so you can save them in the RocSubs:SetDefaultSVs() function 
// #define _Use_Wifi_Manager // uncomment this to use a "standard" fixed SSID and Password

//#define _AudioDAC  // to use Earle F Philhowers's audio libraries and I2C dac for audio 
#define _AudioNoDAC  //  to use Earle F Philhowers's audio libraries and his clever single transistor 1 bit oversampling dac for audio 

// I could probably be cleverer with this set!!
#ifdef _AudioNoDAC
#define _Audio // sets some common audio compiler stuff
#endif
#ifdef _AudioDAC
#define _Audio // sets some common audio compiler stuff
#endif

#ifdef _Audio
                           //RX/D9, D8, and D4 pins.defined below    
    #define I2SDAC_LRC 4  // D4 is used in no dac because of default i2s settings (is i2s clock?) but can be used as input if you need the pin in no dac..
                           // but needs to be defined in order for NoDac to work
    #define I2SDAC_DIN 9   // D9/rx used for both Audio types

#ifdef _AudioDAC
     #define I2SDAC_CLK 8 // D8 used by DAC only
#endif 
#endif


//----SET THESE WHEN INITIALLY SETTING UP THE CODE to set the eeprom to reasonably sensible defaults.
// Then comment them out and re-program so that the loc addr etc can be set via rocrail
//#define _ForceRocnetNodeID_to_subIPL // stops the ability of rocnet to change the node number, but prevents the possibility of two nodes having same node number
//#define _ForceDefaultEEPROM //
//#define _Force_Loco_Addr 3 

//---------------------------------------------------------------end of compiler #defines--------------
