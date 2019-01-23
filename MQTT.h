  #ifndef _MQTT_h
  #define _MQTT_h
  #include "Arduino.h"
  #include "Directives.h"

//planning to use MQTT for sorting out better library partitioning 

//DEBUG, use with mosquitto_sub -h 127.0.0.1 -i "CMD_Prompt" -t debug -q 0

void MQTTSendQ1 (String topic, uint8_t * payload) ;
void testConnection  (int Number);
void MQTTSend (String topic, uint8_t * payload) ;




void MQTT_Setup(void);
boolean MQTT_Connected(void);
void MQTT_Loop(void);
void DebugMsgSend (String topic, char* payload) ;
void DebugSprintfMsgSend(int CX);
void reconnect(void); 

  #endif

