#include "MQTT.h"
#include <Arduino.h> //needed 
 //  #include "Globals.h" 

extern uint8_t Message_Length;
extern boolean Message_Decoded;
extern uint8_t CV[256];
extern uint8_t RN[256];
extern char Nickname[35];
extern uint8_t hrs;
extern uint8_t mins;
extern uint8_t secs;  
extern char DebugMsg[127];
extern uint8_t NodeMCUPinD[12];
extern int connects;
extern boolean  Data_Updated;

extern uint32_t EPROM_Write_Delay;
extern uint32_t Ten_Sec;

extern uint32_t MsgSendTime;
extern boolean MSGReflected;
extern uint8_t SentMessage[128];
extern uint8_t SentMessage_Length;
extern String SentTopic;
// globals used 

#include <PubSubClient.h>
#include <WiFiClient.h>
WiFiClient espClient;
PubSubClient client(espClient);
//if using Really Small Message Broker and not Mosquitto, you will need to use V 3_1 not 3_1_1
//so change PubSubClient. h line 19 to define '3_1' like this: 
//#define MQTT_VERSION MQTT_VERSION_3_1  ///needed for rsmb  


extern IPAddress mosquitto;


extern uint16_t RocNodeID;
extern void PrintTime(String MSG) ;
extern void WriteEEPROM(void);
extern uint8_t ip0;
extern uint8_t ip1;
extern uint8_t subIPH;
extern uint8_t subIPL;


extern void copyUid (byte *buffOut, byte *buffIn, byte bufferSize) ;
extern bool compareUid(byte *buffer1, byte *buffer2, byte bufferSize) ;
extern void dump_byte_array(byte* buffer, byte bufferSize) ;

extern uint32_t PingSendTime;
extern boolean  PingReflected;



extern uint8_t ROC_netid;
extern uint16_t ROC_recipient;
extern uint16_t ROC_sender;
extern uint8_t ROC_group;
extern uint8_t ROC_code;
extern uint8_t ROC_len;
extern uint8_t ROC_Data[200];
#define Recipient_Addr  1   //use with SetWordIn_msg_loc_value(sendMessage,Recipient_Addr,data  , or get sender or recipient addr  
#define Sender_Addr 3       //use with SetWordIn_msg_loc_value(sendMessage,Sender_Addr,data   
extern int IntFromPacket_at_Addr(uint8_t* msg, uint8_t highbyte);
//uint8_t ROC_OUT_DATA[200];
//uint16_t RocNodeID;



//extern void MQTTFetch (char* topic, byte* payload, unsigned int Length) ;
void MQTTFetch (char* topic, byte* payload, unsigned int Length) { //replaces rocfetch
  //do a check on length matching payload[7] ??

  if ((strncmp("PiNg", topic, 4) == 0)) {
    Message_Length = 0; Message_Decoded = true;         //do not bother to do work on this, its a copy of what I sent
    if (RocNodeID == ((payload[0] << 8) + payload[1])) {
      PingReflected = true;
    }
    return;
  }
  if ((strncmp("rocnet/ht", topic, 9) == 0)) {
    Message_Length = 0;
    Message_Decoded = true;
    return;
  }

  Message_Length = Length;
  if (Message_Length >= 1) {

    digitalWrite (NodeMCUPinD[SignalLed], HIGH) ;  ///turn On
    ROC_netid = payload[0];
    ROC_recipient = IntFromPacket_at_Addr(payload, Recipient_Addr);
    ROC_sender = IntFromPacket_at_Addr(payload, Sender_Addr);
    ROC_group = payload[5];
    ROC_code = payload[6];
    ROC_len = payload[7];
    for (byte i = 1; i <= ROC_len; i++) {
      ROC_Data[i] = payload[7 + i];
    }
    Message_Decoded = false;
    #ifdef _SERIAL_MQTT_DEBUG
      Serial.print("*MQTT Received [");
      Serial.print(topic);
      Serial.print("] ");
      dump_byte_array(payload, Message_Length);
    #endif

    if ((SentTopic == topic) && (compareUid(SentMessage, payload, Message_Length))) {
      MSGReflected = true;
    
      DebugSprintfMsgSend( sprintf ( DebugMsg, "*Sensor Confirmed Address:%d state:%d", ROC_Data[4], ROC_Data[3]));
      
    }
  }
}                                                 //*Sensor Seen Node:%d Address:%d state:%d

void MQTTSendQ1 (String topic, uint8_t * payload) { //QoS1 version
  uint8_t Length;
  digitalWrite (NodeMCUPinD[SignalLed], HIGH) ;  ///turn On
  Length = payload[7] + 8;
  MsgSendTime = millis();
  MSGReflected = false;
  copyUid(SentMessage, payload, 128); //nb  dest, source,
  SentMessage_Length = Length;
  SentTopic=topic;
  //strncpy(SentTopic, topic, 20);     //nb dest, source
  #ifdef _SERIAL_MQTT_DEBUG
 
    Serial.print("*QOS 0 POST with check for 'reflection'[");
    Serial.print(topic);
    Serial.print("] ");
    dump_byte_array(payload, Length);
    Serial.println();

  #endif
  client.publish(topic.c_str(), payload, Length); //send as qos 0..for now
}
void testConnection  (int Number) {
  digitalWrite (NodeMCUPinD[SignalLed], HIGH) ;  ///turn On
  PingSendTime = millis();
  PingReflected = false;
  byte id[2];
  id[0] = Number >> 8;
  id[1] = Number & 0xFF;
  client.publish("PiNg", id, 2); //,strlen(payload));//send as qos 0..
}

void MQTTSend (String topic, uint8_t * payload) { //replaces rocsend
  uint8_t Length;
  digitalWrite (NodeMCUPinD[SignalLed], HIGH) ;  ///turn On
  Length = payload[7] + 8;

#ifdef _SERIAL_MQTT_DEBUG

    Serial.println();
    Serial.print("*MQTT POST [");
    Serial.print(topic);
    Serial.print("] ");
    dump_byte_array(payload, Length);
    Serial.println();

#endif

  client.publish(topic.c_str(), payload, Length);

}


//++++++++++ MQTT setup stuff   +++++++++++++++++++++
void MQTT_Setup(void){
  
  client.setServer(mosquitto, 1883);   //Hard set port at 1833
  //client.setServer(mqtt_server, 1883); //old hard set version...
  client.setCallback(MQTTFetch);
}


boolean MQTT_Connected(void){
  return client.connected();
}

void MQTT_Loop(void){
    client.loop(); //gets wifi messages etc..
}
extern uint16_t MyLocoAddr ;
void DebugMsgSend (String topic, char* payload) { //use with mosquitto_sub -h 127.0.0.1 -i "CMD_Prompt" -t debug -q 0
  char DebugMsgLocal[127];
    char DebugMsgTemp[127];
  int cx;
 
  #ifdef _LOCO_SERVO_Driven_Port
  cx= sprintf ( DebugMsgTemp, " Node:%d Loco:%d(%s) Msg<%s>", RocNodeID, MyLocoAddr,Nickname, payload);
  #else
  cx= sprintf ( DebugMsgTemp, " Node:%d (%s) Msg:%s", RocNodeID, Nickname, payload);
  #endif

   //add timestamp to outgoing message
if ((hrs==0)&&(mins==0)){//not Synchronised yet..
  cx=sprintf(DebugMsgLocal," Time not synchronised yet %s",DebugMsgTemp);
   }
   else {cx=sprintf(DebugMsgLocal,"<%02d:%02d:%02ds> %s",hrs,mins,secs,DebugMsgTemp);
         }
//
    //Serial.printf("\n *Debug Message:%s Msg Length:%d \n",DebugMsgLocal,cx);
    Serial.printf("\n *Debug Message:%s  \n",DebugMsgLocal);

 
    if ((cx <= 120)) {
      client.publish(topic.c_str(), DebugMsgLocal, strlen(DebugMsgLocal));
                     }
    if ((cx >= 120) && (strlen(payload) <= 100)) {
      cx= sprintf ( DebugMsgLocal, "MSG-%s-", payload);
      client.publish(topic.c_str(), DebugMsgLocal, strlen(DebugMsgLocal));
                                          }//print just msg  line
    if (strlen(payload) >= 101) {
      cx= sprintf ( DebugMsgLocal, "Node:%d Loco:%d Time %d:%d:%ds Msg TOO Big to print", RocNodeID, MyLocoAddr, hrs, mins, secs);
      client.publish(topic.c_str(), DebugMsgLocal, strlen(DebugMsgLocal));
    }

 }


  void DebugSprintfMsgSend(int CX){ //allows use of Sprintf function in the "cx" location
  DebugMsgSend ("debug", DebugMsg);
  delay(5);
}
extern bool ScanForBroker;
void reconnect() {
  char ClientName[80];
  char myName[15] = "RocNetESPNode:";
  sprintf(ClientName, "%s%i", myName, RocNodeID);
  //Loop until we're reconnected 
  digitalWrite (NodeMCUPinD[SignalLed] , SignalON) ; ///turn on
  PrintTime(" Attempting MQTT connection attempt #");
  Serial.print(connects);
  while (!client.connected()) {
   
    Serial.print(" trying:");
    Serial.print(mosquitto);
    Serial.println("  ");
    //Attempt to connect

    if (client.connect(ClientName)) {
      Serial.println();
       //DebugSprintfMsgSend( sprintf ( DebugMsg, "%s Connected at:%d.%d.%d.%d",ClientName,ip0,ip1,subIPH,subIPL);
    if (mosquitto[3] != RN[14] ){   //RN[14] is the MQQT broker address, save if changed
       DebugSprintfMsgSend( sprintf ( DebugMsg, "%s Forcing RN[14] was %d. to %d",ClientName,RN[14],mosquitto[3]));
       RN[14]=mosquitto[3];
       WriteEEPROM();
       Data_Updated=true; 
       EPROM_Write_Delay = millis()+Ten_Sec; 
         }
      //can advise this node is connected now:
       DebugSprintfMsgSend( sprintf ( DebugMsg, "%s Connected at:%d.%d.%d.%d",ClientName,ip0,ip1,subIPH,subIPL));
      
      //FlashMessage(" ------Connected to MQQT---------",1,400,100);
      //... and now subscribe to topics  http://wiki.rocrail.net/doku.php?id=rocnet:rocnet-prot-en#groups

      client.subscribe("rocnet/lc", 1 ); //loco
      client.subscribe("rocnet/#", 0);   //everything
     //client.subscribe("PiNg", 0);  //my ping...for my qos 1 attempt
     /*   or do it individually.......

        client.subscribe("rocnet/dc",0);
        client.subscribe("rocnet/cs",0);
        client.subscribe("rocnet/ps",0);
        client.subscribe("rocnet/ot",1);
        client.subscribe("rocnet/sr",0); //to allow reflection check of my sensor events
      */
     
       delay(100);
       EPROM_Write_Delay = millis();
    
    } else {
      //Serial.print(" failed, rc=");
      //Serial.print(client.state()); 
     //
     connects=connects+1;
    if ((connects>=5) && ScanForBroker){  mosquitto[3] = mosquitto[3]+1; 
                       Serial.println(" Search for MQTT broker - incrementing addresses");
                       #ifdef myBrokerSubip 
                       mosquitto[3]= BrokerAddr  //change to force set  BrokerAddrDefault as your broker last ip address (defined in secrets)..
                       #endif
                       if (mosquitto[3]>=50){mosquitto[3]=3;}   }   //limit mqtt broker to 3-50 to save scan time
    delay(100);
    client.setServer(mosquitto, 1883);   //Hard set port at 1833
    Serial.print(" Trying broker address ending :");Serial.print(mosquitto[3]);Serial.println(" ...");
      //FlashMessage(".... Failed connect to MQTT.. attempting reconnect",4,250,250);
      //Wait   before retrying  //perhaps add flashing here so when it stops we are connected?
    delay(100);
    digitalWrite (NodeMCUPinD[SignalLed] , SignalOFF) ; ///turn OFF
    }
  }
}

