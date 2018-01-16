#ifndef _subs_h
#define _subs_h
  #include <Arduino.h> //needed 

//void DebugMsgSend (char* topic, char* payload) ;
//  void DebugSprintfMsgSend(int CX);
void PrintTime(String MSG) ;
int rnSenderAddrFromPacket(unsigned char* rn, int seven);
int rnReceipientAddrFromPacket(unsigned char* rn, int seven) ;
int getTwoBytesFromMessageHL( uint8_t* msg, uint8_t highloc) ;
void SetWordIn_msg_loc_value(uint8_t* msg, uint8_t firstbyte, int value) ;
int IntFromPacket_at_Addr(uint8_t* msg, uint8_t highbyte);
void dump_byte_array(byte* buffer, byte bufferSize) ;
void dump_byte(uint8_t buffer);
uint8_t lnCalcCheckSumm(uint8_t *cMessage, uint8_t cMesLen) ;
uint16_t AddrFull (uint8_t HI, uint8_t LO) ;
void copyUid (byte *buffOut, byte *buffIn, byte bufferSize) ;

bool compareUid(byte *buffer1, byte *buffer2, byte bufferSize) ;

void Show_MSG(void);

void FlashMessage (char* msg, int Repeats, int ON, int Off) ;
void SetPortPinIndex(void);
 
#endif

