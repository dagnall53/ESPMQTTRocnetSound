#ifndef _Globals_h
  #define _Globals_h
  #include <Arduino.h> //needed 
uint16_t SW_REV = 22; 

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


  #define NodeMCUPinD[SignalLed] 2 //same as PIN D4!

*/
/*//sound volumes references 
CV[100]=127; //Overall volume control
CV[101]=127; //volume for F1 
CV[102]=127;
CV[103]=127;
CV[104]=127;
CV[105]=127;
CV[106]=127;
CV[107]=127;
CV[108]=127; //Volume for F8

CV[110]=127; //volume for chuffs
CV[111]=127; //volume for Brake Squeal
//
*/  

//stuff for ssid reset
boolean  ResetWiFi;
  



char DebugMsg[127];
char temp_msg[31];
//#include "SV.h"

//one cross reference for each port   
uint8_t NodeMCUPinD[12];



uint8_t recMessage[128];
uint8_t sendMessage[128];
uint8_t TOPIC[20];
char DebugMessage[128];
uint8_t LenDebugMessage;


//any MQTT Stuff??
uint32_t MsgSendTime;
boolean MSGReflected;
uint8_t SentMessage[128];
uint8_t SentMessage_Length;
String SentTopic;
int connects;
int oldconnects;



uint8_t Message_Length;
boolean Message_Decoded;

boolean  SensorOutput_Inactive ;

boolean DealtWith  ;
boolean POWERON;
boolean LOCO ;
boolean Phase;

uint16_t MyLocoAddr ;
uint8_t Loco_motor_servo_demand = 0 ;
uint8_t Loco_servo_last_position;
bool Last_Direction;
bool Last_Set_Dir;

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

//uint16_t ROCNode_Status; ?not needed now

char Nickname[35];
uint8_t hrs;
uint8_t mins;
uint8_t secs;   
uint32_t lastsec;

#endif
