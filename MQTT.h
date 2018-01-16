  #ifndef _MQTT_h
  #define _MQTT_h
  #include "Arduino.h"
// planning to use MQTT for sorting out better library partitioning 



void MQTTSendQ1 (char* topic, uint8_t * payload) ;
void testConnection  (int Number);
void MQTTSend (char* topic, uint8_t * payload) ;




void  MQTT_Setup(void);
boolean MQTT_Connected(void);
void MQTT_Loop(void);
void DebugMsgSend (char* topic, char* payload) ;
void DebugSprintfMsgSend(int CX);
void reconnect(void); 

  #endif

