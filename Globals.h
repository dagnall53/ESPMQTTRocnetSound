#ifndef _globals_h
  #define _globals_h
  
uint16_t SW_REV = 21; 

/* PIN References... Also defined somewhere else in the esp included code so do not unhide this section!!!...
  static const uint8_t D0   = 16;  and Red Led on NodeMcu V2 (not present on NodeMCU v3)
  static const uint8_t D1   = 5;
  static const uint8_t D2   = 4;
  static const uint8_t D3   = 0;
  static const uint8_t D4   = 2;  and Blue Led on ESP8266 also is i2c clk?
  static const uint8_t D5   = 14;
  static const uint8_t D6   = 12;
  static const uint8_t D7   = 13;
  static const uint8_t D8   = 15;
  static const uint8_t D9   = 3;
  static const uint8_t D10  = 1;


  #define NodeMCUPinD[SignalLed] 2 // same as PIN D4!

*/

// stuff for ssid reset
boolean  ResetWiFi;
  

//// Debug settings
#define _SERIAL_DEBUG  1
#define _SERIAL_SUBS_DEBUG 1

char DebugMsg[127];
//#include "SV.h"

//one cross reference for each port   
uint8_t NodeMCUPinD[12];



uint8_t recMessage[128];
uint8_t sendMessage[128];
uint8_t TOPIC[20];
char DebugMessage[128];
uint8_t LenDebugMessage;


// any MQTT Stuff??
uint32_t MsgSendTime;
boolean MSGReflected;
uint8_t SentMessage[128];
uint8_t SentMessage_Length;
char SentTopic[20];
int connects;
int oldconnects;



uint8_t Message_Length;
boolean Message_Decoded;

boolean  SensorOutput_Inactive ;

boolean DealtWith  ;
boolean POWERON;
boolean LOCO ;
boolean Phase;


boolean bReaderActive = false;

int RFIDSTATE ;
uint32_t RFIDCycle;
uint8_t RFIDDots;
boolean  Data_Updated;
uint32_t EPROM_Write_Delay;
uint32_t Ten_Sec = 10000;
uint32_t OneDay = 8640000;
uint32_t MSTimer;

uint8_t CV[256];
uint8_t RN[256];

uint16_t ROCNode_Status;

char* Nickname;
uint8_t hrs;
uint8_t mins;
uint8_t secs;   
uint32_t lastsec;

#endif
