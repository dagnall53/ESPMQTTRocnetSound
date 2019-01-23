#ifndef NVSettingInterface_h
 #define NVSettingInterface_h

 //the #include statment and code go here...
 #include "Arduino.h"
 #include "Directives.h"
  
 #include <EEPROM.h>
  #define _EEPROMdebug //adds serial debug help 
 const byte numChars = 32; //max size I will allow the saved ssid, password and throttle name 
 const int Serial_EEPROM_Starts = 1025;
 const int EEPROM_Serial_store_Size=256; 
 const int BrokerEEPROMLocation =Serial_EEPROM_Starts;
 const int ssidEEPROMLocation = Serial_EEPROM_Starts+10;
 const int passwordEEPROMLocation = ssidEEPROMLocation+numChars;
 


 
 int MSG_content_length();
 void CheckForSerialInput();
 void recvWithEndMarker(); //Gets data <receivedChars> from serial interface
 void showNewData() ;    //shows recieved (serial) <receivedChars> data on serial terminal, useful for debugging 
 void WriteWiFiSettings();
 void TestFillEEPROM(int d);
 void writeString(int add,String data);  //defned here to allow use later but before its properly defined..
 String read_String(int add);             //defned here to allow use later but before its defined..
 void recvWithEndMarker() ;
 void showNewData();



#endif
