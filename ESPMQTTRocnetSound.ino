

#define _LOCO_SERVO_Driven_Port 1    // if using as mobile (LOCO) node.. node becomes a loco with servo on port D "1"  for motor control
// #define _RFID 1  // if using rfid reader
//#define _DefaultPrintOut 1 // for printing the defaults on eprom save  
// #define _Use_Wifi_Manager // uncomment this to use a "standard" fixed SSID and Password
#define _Audio 1 //use Earle F Philhowers's audio libraries and external dac for audio
//#define _ForceDefaultEEPROM /


#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
#ifdef _Use_Wifi_Manager
       #include <WiFiManager.h>
#else
       #include "Secrets.h"
       String wifiSSID = SSID_RR;
       String wifiPassword = PASS_RR; 
#endif
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//if using Really Small Message Broker need to use 3_1 not 3_1_1
// change PubSubClient. h line 19 to define 3_1 to this: 
//
//#define MQTT_VERSION MQTT_VERSION_3_1  /// needed for rsmb  
//
#include <PubSubClient.h>






#include <Servo.h>
#include <EEPROM.h>

//const char* mqtt_server = "192.168.0.11";

WiFiClient espClient;
PubSubClient client(espClient);

uint8_t wifiaddr;
uint8_t ip0;
uint8_t ip1;
uint8_t    subIPH;
uint8_t    subIPL;


//const int port = 4321;  //1235 for loconet, 4321 for Rocnet 1883 for MQTT

IPAddress ipBroad;
IPAddress mosquitto;


#include "Defaults.h";
#include "Subroutines.h";
//#include "SV.h";
#include "RocSUBS.h";
#include "Ports.h";

#ifdef _Audio
#include "Chuff.h";  
#endif

#ifdef _RFID
 #include <SPI.h>
 #include <MFRC522.h> //   mine is modified to give 10Mhz with ESP  #define SPI_CLOCK_DIV_4 10000000  #define myClock  10000000 // replaces    SPI_CLOCK_DIV4
 #include "RFID_Subs.h";
#endif



void ConnectionPrint() {
  Serial.println("");
  Serial.println("---------------------------Connected-----------------------");
  Serial.print (" Connected to SSID:");
  Serial.print(WiFi.SSID());
  Serial.print("  IP:");
  Serial.println(WiFi.localIP());
  //Serial.println("-----------------------------------------------------------");      
 
}




void reconnect() {
  char ClientName[80];
  char myName[15] = "RocNetESPNode:";
  sprintf(ClientName, "%s%i", myName, RocNodeID);
  // Loop until we're reconnected 
  digitalWrite (NodeMcuPortD[SignalLed] , HIGH) ; ///   turn on
  PrintTime(" Attempting MQTT connection attempt #");
  Serial.print(connects);
  while (!client.connected()) {
   
    Serial.print(" trying:");
    Serial.print(mosquitto);
    Serial.println("  ");
    // Attempt to connect

    if (client.connect(ClientName)) {
      Serial.println();
       // cx = sprintf ( DebugMsg, "%s Connected at:%d.%d.%d.%d",ClientName,ip0,ip1,subIPH,subIPL);
    if (mosquitto[3] != RN[14] ){   //RN[14] is the MQQT broker address, save if changed
       RN[14]=mosquitto[3];
       WriteEEPROM();
       Data_Updated=true; 
       EPROM_Write_Delay = millis()+Ten_Sec; 
                                }
      // can advise this node is connected now:
       DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "%s Connected at:%d.%d.%d.%d",ClientName,ip0,ip1,subIPH,subIPL));
      
      //FlashMessage(" ------Connected to MQQT---------",1,400,100);
      // ... and now subscribe to topics  http://wiki.rocrail.net/doku.php?id=rocnet:rocnet-prot-en#groups

      client.subscribe("rocnet/lc", 1 ); //loco
      client.subscribe("rocnet/#", 0);   // everything
     // client.subscribe("PiNg", 0);  // my ping...
     /*   or do it individually.......

        client.subscribe("rocnet/dc",0);
        client.subscribe("rocnet/cs",0);
        client.subscribe("rocnet/ps",0);
        client.subscribe("rocnet/ot",1);
        client.subscribe("rocnet/sr",0); // to allow reflection check of my sensor events
      */
     
     // delay(100);

       EPROM_Write_Delay = millis();
     
    } else {
      //Serial.print(" failed, rc=");
      //Serial.print(client.state()); 
     // 
     connects=connects+1;
    if (connects>=10){  mosquitto[3] = mosquitto[3]+1;
    if (mosquitto[3]>=50){mosquitto[3]=3;}   }   // limit mqtt broker to 3-50 to save scan time
    delay(10);
    client.setServer(mosquitto, 1883);   // Hard set port at 1833
      Serial.println(" try again ...");
      //FlashMessage(".... Failed connect to MQTT.. attempting reconnect",4,250,250);
      // Wait   before retrying  // perhaps add flashing here so when it stops we are connected?
      delay(100);
      digitalWrite (NodeMcuPortD[SignalLed] , LOW) ; ///   turn OFF
    }
  }
}


void Status(){

  Serial.println("-----------------------------------------------------------");
  Serial.println("-----------------------------------------------------------");
  Serial.println(  "                  ESPWIFIROCNET V4    "); 
  Serial.println("-----------------------------------------------------------");
  Serial.print(  "                    revision:");
  Serial.print(SW_REV); Serial.println();
  Serial.println("-----------------------------------------------------------");
  WiFi.setOutputPower(0.0); //  0 sets transmit power to 0dbm to lower power consumption, but reduces usable range.. trying 30 for extra range
#ifdef _Use_Wifi_Manager
   WiFiManager wifiManager;  // this does not use eeprom to store ssid  !!
  //reset settings - for testing
  //wifiManager.resetSettings();

  wifiManager.autoConnect("ROCNODE ESP AP");  //ap name (with no password) to be used if last ssid password not found
#else
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
  while (WiFi.status() != WL_CONNECTED) {delay(500);Serial.print(".");}
 
#endif
  
  
  ipBroad = WiFi.localIP();
/*
//Alternate "normal" connection to wifi
  Serial.print(F("Initialising. Trying to connect to:"));
  Serial.println(SSID_RR);
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
  while (WiFi.status() != WL_CONNECTED) {delay(500);Serial.print(".");}
  Serial.println();
  Serial.println(WiFi.localIP());
  ipBroad=WiFi.localIP();
*/     
  //if you get here you have connected to the WiFi

  ip0=ipBroad[0];
  ip1=ipBroad[1];
  subIPH = ipBroad[2];
  subIPL = ipBroad[3];
  wifiaddr = ipBroad[3];
  ConnectionPrint();
  //Serial.println(wifiaddr);
  ipBroad[3] = 255; //Set broadcast to local broadcast ip e.g. 192.168.0.255 // used in udp version of this program
 
 //   ++++++++++ MQTT setup stuff   +++++++++++++++++++++
  mosquitto[0] = ipBroad[0]; mosquitto[1] = ipBroad[1]; mosquitto[2] = ipBroad[2];
  mosquitto[3] = RN[14];                //saved mosquitto address, where the broker is! saved as cv49, 
  Serial.print(" Mosquitto will first try to connect to:");
  Serial.println(mosquitto);
  client.setServer(mosquitto, 1883);   // Hard set port at 1833
  //client.setServer(mqtt_server, 1883); // old hard set...
  client.setCallback(MQTTFetch);



  //  ------------------ IF rfid -------------------------
#ifdef  _RFID
  Serial.println("------------------------ MFRC 522 testing -----------------");
  //   * Setup rfidstuff *************************
  SPI.begin();        // Init SPI bus//
  mfrc522.PCD_Init(); // Init MFRC522 card
  mfrc522.PCD_SetRegisterBitMask(mfrc522.RFCfgReg, (0x07 << 4)); //https://github.com/miguelbalboa/rfid/issues/43 //If you set Antenna Gain to Max it will increase reading distance
  byte readReg = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  if ((readReg == 0x00) || (readReg == 0xFF)) { //missing reader
    Serial.println(" Reader absent");
  } else {
    Serial.println(" Reader Present ");  //would like to have spi speed here.
    bReaderActive = true;
  }
#endif
  RocNodeID = getTwoBytesFromMessageHL(RN, 1);
  Serial.println("------------------------- RocNet Node ---------------------");
  Serial.print(  "                   My ROCNET NODE ID:");
  Serial.println(RocNodeID);
  //  ------------------ IF rfid -------------------------
#ifdef _LOCO_SERVO_Driven_Port
  //++++++++++++++++++++Print Debug and Current setup information stuff    +++++++++++++++++++++++++++++
  Serial.println("---------------------- LOCO Setup   -----------------------");
  Serial.print(  "          Short 'Locomotive Address' is");
  Serial.print (CV[1]);
  Serial.println();
  Serial.println("-------------------------- PORT Setup ---------------------");
  Loco_motor_servo_demand = 90;
 // pinMode(NodeMcuPortD[BACKLight], OUTPUT);   // see defaults line 90 for settings
 // pinMode(NodeMcuPortD[FRONTLight], OUTPUT);
 // pinMode(NodeMcuPortD[SignalLed], OUTPUT);  //is also ..
 digitalWrite (NodeMcuPortD[FRONTLight], 1);  //Turn off direction lights
 digitalWrite (NodeMcuPortD[BACKLight], 1); //Turn off direction lights
#endif


}

void setup() {  
    Serial.begin(115200);
   // ota stuff  Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]

 #ifdef _LOCO_SERVO_Driven_Port 
  ArduinoOTA.setHostname("WiFiRocnetLOCO");
  #else
 ArduinoOTA.setHostname("WiFiRocnetSTATIC");
 #endif
  // No authentication by default
  //ArduinoOTA.setPassword((const char *)"123");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  //---------------------end ota stuff -------
  
  
  POWERON = true;
  Ten_Sec = 10000;

  SetPortPinIndex();  //sets up nodemcucross references 

//  ----------------------Setup from eeprom
  Data_Updated = false;
  EEPROM.begin(1024);

  if ((EEPROM.read(255) == 0xFF) && (EEPROM.read(256) == 0xFF)) { //eeprom empty, first run. Can also set via CV[8]=8
    Serial.println(" ******* EPROM EMPTY....Setting Default EEPROM values *****");
    SetDefaultSVs();
    WriteEEPROM();
    EPROM_Write_Delay = millis() + Ten_Sec;
    EEPROM.commit();
    delay(100);
  } 
  
  
  //if
  // Get the stored / initial values...

  ReadEEPROM();     //set the RN and CV registers

  
  #ifdef _LOCO_SERVO_Driven_Port 
     NodeChanneloptions[_LOCO_SERVO_Driven_Port]=0;  // force the "_LOCO_SERVO_Driven_Port Id to be NOT a servo as far as the main code is concerned so other code can do accel and decel?
  #endif
  MyLocoLAddr = CV[18] + ((CV[17] & 0x3F) * 256);
  MyLocoAddr = CV[1]; ///
  CV[8] = 0x0D; // DIY MFR code
  CV[7] = 0x03; //ver

  Status();

 
  

 

  Motor_Speed = 0;
  SPEED = 0;
  OLDSPEED = 0;
  connects = 0;
  oldconnects = 0;

  POWERON = true;
  WaitUntill = millis();

  SensorOutput_Inactive = true;

  RFIDCycle = millis();
  LoopTimer = millis();
  LocoCycle = millis();
  EPROM_Write_Delay = millis();
  LenDebugMessage = 1;
  DebugMessage[0] = 0xFF;
 
  PortSetupReport();  // sends port configuration to serial monitor
  digitalWrite (NodeMcuPortD[SignalLed], HIGH) ;  /// turn On
  // set the servos neutral here??
  // ReadInputPorts();
  for (int i = 0 ; i <= 8; i++) {
    lastButtonState[i] = digitalRead(NodeMcuPortD[i]);
    ButtonState[i] = 0; // just set them all 0 at this stage 
    PortTimingDelay[i] = millis();
    ServoOffDelay[i] = millis() + 10000;
  }

  
  ResetWiFi = false;
  MSGReflected = true;
  MsgSendTime = millis();
  lastsec = millis();
  secs=0;
  mins=0;
  hrs=0;
  for (int i = 0 ; i <= 127; i++) {
    DebugMessage[i] = 0;
  }
  // for interrupt when we add them later versions...
  //attachInterrupt(pin,hiInterrupt,RISING);


  // Serial.println("------------------------ Starting main loop ---------------");
  FlashMessage(" ----------Entering Main Loop----------  ", 5, 150, 150);
     PrintTime("Start");
CV[47]=131; //Defaults to showing MQQT messages,Serial messages and the D4 lightflashing at loop frequency (approximates to "On" when working!...
   for (int i = 0 ; i <= 8; i++) {
    SDelay[i] = 1000;
    SDemand[i] = 90;
    NodeChannelLastUpdated[i] = millis();
  }
#ifdef _Audio
  SetUpChuff();
#endif
#ifdef  _DefaultPrintOut  // give a printout of whats set in the eeprom..
    Serial.println("-----------------CURRENT EEPROM SETTNGS --------------");
    WriteEEPROM();
    Serial.println(" ----// end of saved EEPROM set of defaults----");
  EEPROM.commit();
  delay(1000);
#endif
 }  /// end of setup ///////


//+++++++++++++++++++++++++++++++++++++++++++++++++MAIN LOOP++++++++++++++++++++++++++++++++++++++++++++

void hiInterrupt(int i) {

}
void loInterrupt(int i) {

}




void loop() {
#ifdef _Audio
  AudioLoop(1);
  SoundEffects();
  if (TimeToChuff()){Chuff();
  //SteamOnStarted=millis();digitalWrite(SteamOutputPin,HIGH);
  }
#endif
  digitalWrite (NodeMcuPortD[SignalLed] , LOW) ; ///   turn OFF signal lamp
  ArduinoOTA.handle();
  // new MQTT stuff, & check we are connected.. 
  if (!client.connected()) {
    #ifdef _LOCO_SERVO_Driven_Port
    SetServo(_LOCO_SERVO_Driven_Port,90);   // mod      (90);  // STOP motor servo 
    #endif
    connects = connects + 1;
    reconnect();
  }
  client.loop(); //gets wifi messages etc..
  //connects=0;   /////??????
 // experiment in qos  
 /* if (oldconnects != connects) {
    oldconnects = connects;  char DebugMsg[120]; int cx; cx = sprintf ( DebugMsg, "Reconnected, total connects now:%d", connects);
    DebugMsgSend("debug", DebugMsg);
  }
  */
  // Stop the motor if you lose connection  //
  if (( MSGReflected == false) && (millis() >= MsgSendTime + 200)) {
    #ifdef  _LOCO_SERVO_Driven_Port
    SetServo(_LOCO_SERVO_Driven_Port,90);   // mod      (90);  
    #endif
    MQTTSendQ1 (SentTopic, SentMessage);
    DebugSprintfMsgSend("debug",sprintf ( DebugMsg, "*RESENDING sensor msg--  "));
  }  //pseudo QoS1 resend

  if (millis() >= lastsec + 1000 ) {
    lastsec = lastsec + 1000;
    secs = secs + 1;
    Serial.print(".");
    digitalWrite (NodeMcuPortD[SignalLed] , HIGH) ; ///   turn On
     }
  


 //Switch these on and to check timing via oscilloscope and signal led 
 
 //   Phase = !Phase;
 //   digitalWrite(NodeMcuPortD[SignalLed], Phase);
 // 

  LoopTimer = micros();
  

  // +++++++++++++++can reset wifi on command "update node to sw 0"
  if ( ResetWiFi == true) { //reset settings - for testing purposes
#if _SERIAL_DEBUG
    Serial.println("  +++++++++++  RESETTING WiFi  +++++++++++++++  " );
    Serial.println("  +++++++++++  You will need to access the AP and browse 192.168.4.1  +++++++++++++++  " );
#endif
#ifdef _Use_Wifi_Manager
    WiFiManager wifiManager; wifiManager.resetSettings(); wifiManager.startConfigPortal("ROCNODE ESP AP"); //ap name (with no password) to be used if ssid password not stored/found
#else
  //  ESP.reset();
    #endif
    ResetWiFi = false; FlashMessage(" ++++++++ RESET AP Completed ++++++++ ", 10, 300, 300);

    ConnectionPrint();
  }
  // +++++++++++++++

  // +++++++++++++commit any changed writes to the  Eprom and change the ports if they have been altered..
  if ((millis() >= EPROM_Write_Delay) && (Data_Updated)) {              // commit EEPROM only when needed..
    Data_Updated = false;
    DebugMsgSend("debug","Commiting EEPROM");
    Serial.println("Commiting EEPROM");

    DetachServo(-1);   // switches off ALL servos
    delay(50);
    EEPROM.commit();
    PortSetupReport();  //make any port direction changes.
    delay(50);
    // +++++++++  Set up other things that may have been changed...+++++++++
    RocNodeID = getTwoBytesFromMessageHL(RN, 1);
    MyLocoLAddr = CV[18] + ((CV[17] & 0x3F) * 256);
    MyLocoAddr = CV[1];
                                                        }
  // +++++++++++END commit to EPROM

#ifdef _RFID
  checkRFID();
#endif

//periodic updates and checks

#ifdef  _LOCO_SERVO_Driven_Port
  //CV[1] = RocNodeID;  force Loco addr = rocnode addr
  //CV[18] = RocNodeID; // set loco addr= node in case it was altered...l
   ServoOffDelay[_LOCO_SERVO_Driven_Port] = millis() + 10000;  // reset the servooff delay for servo 0, which is the motor...
  if (POWERON == false) { // Track power off, stop the motor, zero the motor servo immediately
    SPEED=0;
    SDemand[_LOCO_SERVO_Driven_Port]=90;
    SetServo(_LOCO_SERVO_Driven_Port,90 );   // mod      (90);
  }
  else {                             // force all the bits to make servo '_LOCO_SERVO_Driven_Port' controlled by CV's
     SDemand[_LOCO_SERVO_Driven_Port] = Loco_motor_servo_demand;
     NodeChannelonsteps[_LOCO_SERVO_Driven_Port] = CV[3];
     NodeChanneloffsteps[_LOCO_SERVO_Driven_Port] = CV[4]; // set acc and decc !!
     NodeChanneloffposH[_LOCO_SERVO_Driven_Port]=1;
     NodeChanneloffposL[_LOCO_SERVO_Driven_Port]=145;
     NodeChannelonposH[_LOCO_SERVO_Driven_Port]=1;
     NodeChannelonposL[_LOCO_SERVO_Driven_Port]=145;
     NodeChanneloptions[_LOCO_SERVO_Driven_Port] = 32 + 10; // KEEP this i/o as a "SERVO" output regardless, 10= delay to use for servo changes = 100ms rate ;
    //NodeChanneloptions[_LOCO_SERVO_Driven_Port]=0;  // force the "_LOCO_SERVO_Driven_Port Id to be NOT a servo as far as the main code is concerned
  }
#endif


  SERVOS();
  FLASHING();

  ReadInputPorts();
  DETACH();     // check if servos need detaching...
  DoRocNet();   // do any messages ! includes... if (Message_Length >=1)

  //delay(5);   // slow this down for tests
  
  
} //void loop



