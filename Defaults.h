
/* PIN References... Also defined somewhere else in the esp included code so do not unhide this section!!!...


  static const uint8_t D0   = 16;  and Red Led on NodeMcu V2 (not present on NodeMCU v3)
  static const uint8_t D1   = 5;
  static const uint8_t D2   = 4;
  static const uint8_t D3   = 0;
  static const uint8_t D4   = 2;  and Blue Led on SP8266
  static const uint8_t D5   = 14;
  static const uint8_t D6   = 12;
  static const uint8_t D7   = 13;
  static const uint8_t D8   = 15;
  static const uint8_t D9   = 3;
  static const uint8_t D10  = 1;


  #define NodeMcuPortD[SignalLed] 2 // same as PIN D4!

*/
// stuff for ssid reset
boolean  ResetWiFi;
uint16_t SW_REV = 150;   
/* 
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
    CV[47] controls where the signals are sent; 
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
//// Debug settings
#define _SERIAL_DEBUG  1
#define _SERIAL_SUBS_DEBUG 1
//#define _SERVO_DEBUG 1

#include "SV.h"
/*

  /// Variables for OPC_Peer Xfer
  uint16_t OPCSV;
  uint8_t OPCSub;
  uint8_t OPCdata;
  uint8_t OPCSRCL;
  uint8_t OPCRXTX;



*/


//one for each port and one for each of the  switchable positions  (avoiding address 0 for the moment),
uint8_t NodeMcuPortD[12];
#define SignalLed 5 // NodeMCU D5!
#define FRONTLight 3 // NodeMCU D3
#define BACKLight 2  // NodeMCU D2

#ifdef _Audio
//RX/d9, D8, and D4 pins.defined below
long ChuffPeriod;
uint8_t SoundEffect_Request[3];
#endif

#define AudioRX 9
#define AudioD4 4
#define AudioD8  8  




//servo settings   /// need to be here so that Subroutines.h knows about them...range to 10 to allow for expansion
int SDemand[12];
int SDelay[12];
//uint32_t servoDelay[12];
int SloopDelay = 2;  //100 is about 4 seconds with 50ms delay in loop
int ServoOffDelay[12];


//Servo Loco_LOCO_SERVO_Driven_Port;  // create servo object to control a servo  // servo 0 in ver107 on to be loco, but connected on pin D1. 
Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo
Servo myservo5;  // create servo object to control a servo
Servo myservo6;  // create servo object to control a servo
Servo myservo7;  // create servo object to control a servo
Servo myservo8;  // create servo object to control ... used for loco motors in ver 106 back




boolean ButtonState[12] ;
int lastButtonState[12];
// int DebounceCount[12]  ;
// int OffDelay = 200;  //for debounce about 6 seconds with Delay = 20ms in main loop
uint32_t PortTimingDelay[12];
//int DebounceDelayCount  =  2 ; //read the same signal 2 times before accepting it

//int CRD_SENSOR ;

uint8_t Motor_Speed = 0 ;
uint8_t SPEED = 0 ;
uint8_t OLDSPEED;
uint8_t LastSetSpeed;
uint8_t Loco_motor_servo_demand = 0 ;
uint16_t ServoLastPos[10];
uint32_t WaitUntill;


uint32_t LoopTimer;
uint32_t LocoCycle;


uint8_t DIRF = 0 ;
uint8_t SND = 0 ;
uint16_t MyLocoLAddr ;
uint8_t MyLocoAddr ;


uint8_t recMessage[128];
uint8_t sendMessage[128];
uint8_t TOPIC[20];
char DebugMessage[128];
uint8_t LenDebugMessage;
uint8_t Message_Length;

// any MQTT Stuff??
uint32_t MsgSendTime;
boolean MSGReflected;
uint8_t SentMessage[128];
uint8_t SentMessage_Length;
char SentTopic[20];
int connects;
int oldconnects;




boolean Message_Decoded;

boolean  SensorOutput_Inactive ;

boolean DealtWith  ;
boolean POWERON;
boolean LOCO ;
boolean Phase;


boolean bReaderActive = false;
#define UID_LEN         7
int RFIDSTATE ;
uint32_t RFIDCycle;
uint8_t RFIDDots;
boolean  Data_Updated;
uint32_t EPROM_Write_Delay;
uint32_t Ten_Sec = 10000;
uint32_t OneDay = 8640000;
uint32_t MSTimer;
//describe the subroutines..

//        -----rn subs..-------


uint8_t CV[256];
uint8_t RN[256];



#define NumberOfPorts  8


uint8_t NodePortValue[NumberOfPorts + 1]; // ignore [0] so we can have 1...8
uint8_t NodePortType[NumberOfPorts + 1];
uint8_t NodePortDelay[NumberOfPorts + 1];
uint8_t NodePortConfig[NumberOfPorts + 1];
uint8_t NodePortEvent[NumberOfPorts + 1];
uint8_t NodePortidH[NumberOfPorts + 1]; // idh
uint8_t NodePortidL[NumberOfPorts + 1]; //idl
uint8_t NodePortport[NumberOfPorts + 1];
uint8_t NodeChanneloffposH[NumberOfPorts + 1];
uint8_t NodeChanneloffposL[NumberOfPorts + 1];
uint8_t NodeChannelonposH[NumberOfPorts + 1];
uint8_t NodeChannelonposL[NumberOfPorts + 1];
uint8_t NodeChanneloffsteps[NumberOfPorts + 1];
uint8_t NodeChannelonsteps[NumberOfPorts + 1];
uint8_t NodeChanneloptions[NumberOfPorts + 1];
uint32_t NodeChannelLastUpdated[NumberOfPorts + 1];


uint8_t ROC_netid;
uint16_t ROC_recipient;
uint16_t ROC_sender;
uint8_t  ROC_group;
uint8_t  ROC_code;
uint8_t ROC_len;
uint8_t ROC_Data[200];
uint8_t ROC_OUT_DATA[200];
uint16_t RocNodeID;




uint16_t ROCNode_Status;


#define RN_PACKET_NETID  0
#define RN_PACKET_RCPTH  1
#define RN_PACKET_RCPTL  2
#define RN_PACKET_SNDRH  3
#define RN_PACKET_SNDRL  4
#define RN_PACKET_GROUP  5
#define RN_PACKET_ACTION 6
#define RN_PACKET_LEN    7

#define Recipient_Addr  1   // use with SetWordIn_msg_loc_value(sendMessage,Recipient_Addr,data  , or get sender or recipient addr  
#define Sender_Addr 3       // use with SetWordIn_msg_loc_value(sendMessage,Sender_Addr,data   
#define Code_Request 0<<5
#define Code_Event   1<<5
#define Code_Reply   2<<5

char* Nickname;
uint8_t hrs;
uint8_t mins;
uint8_t secs;   
uint32_t lastsec;
uint32_t PingSendTime;
boolean  PingReflected;

