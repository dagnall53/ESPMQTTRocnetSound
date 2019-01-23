#include "NVSettingInterface.h"
 
extern String wifiSSID ;
extern String wifiPassword;
//extern void OLED_5_line_display(String L1,String L2,String L3,String L4,String L5);
//extern void OLED_5_line_display_p(String L1,String L2,String L3,String L4,String L5);
extern int BrokerAddr;
//  #include "Globals.h"
extern uint8_t NodeMCUPinD[12];//
extern bool Data_Updated;
extern uint32_t EPROM_Write_Delay;
// globals 
 char receivedChars[numChars];   //an array to store the received data
 boolean newData = false;
 char rx_byte;  //to try serial input
 int SerioLevel; //for the serial interface for updates

int MSG_content_length(){
  int Length;
  int i;
  bool EOM; 
  Length =0;i=0;
  EOM=false;
  while (!EOM && i<=numChars) {
       if (receivedChars[i] == 0){EOM=true;Length=i;}
       i++;
       }
  return Length;
}



void CheckForSerialInput(){
  String MSGText;
  String MSGText1;
  String MSGText2;
  String MSGText3;
  String MSGText4;
    String TestData;
    long Timestarted;
    long FlashTime;
    bool UpdateInProgress;
    //will try to change wifiSSID,wifiPassword
    UpdateInProgress=false;
    if (wifiSSID=="Router Name"){UpdateInProgress=true;Serial.println(" Forcing request for new entries as Default Router name has not been set in Secrets.h");
                                    Serial.println("--Serial port update Started--");
                                    Serial.print("  SSID currently is <");Serial.print(wifiSSID);Serial.print("> Password is <");Serial.print(wifiPassword); Serial.println(">");
                                    Serial.println("Type in New SSID");newData = false;SerioLevel=1;
                                    //OLED_5_line_display("EEPROM settings required","Use Serial port @115200","To enter new data"," ","");
                                 }else{
                                    Serial.println("");
                                    Serial.println(F("       --- To enter new wifi SSID / Password type 'xxx' BEFORE wifi connects--- "));
                                    Serial.println(F("                   -- Use 'Newline' OR 'CR' to end input line  --"));
                                    Serial.println(F("Starting~~~~~~~~~~~~~~~~~~~~~~~~waiting~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Timeout "));
                                    delay(100);
                                    //delayD_5_line_display_p("","","","Pausing for Serial I/O","type 'xxx' to start");
                                       }
    Timestarted=millis();
    FlashTime=millis();
    bool LAMP;
  
    while ((millis()<= Timestarted+4000) || UpdateInProgress) {
      if ((millis()>= FlashTime) && !UpdateInProgress) { LAMP=!LAMP; FlashTime=millis()+50; Serial.print(">");digitalWrite (NodeMCUPinD[SignalLed] , LAMP) ;}
      delay(1); //Allow esp to process other events .. may not be needed, but here to be safe..                                      
      recvWithEndMarker();
      if (newData == true) {TestData=receivedChars;
                          //Serial.print("<");Serial.print(TestData);Serial.print("> Looking for {");Serial.print(LookFor);Serial.println("}");
                          switch (SerioLevel){ 
                          case 0:
                                 if (TestData=="xxx\0"){
                                    UpdateInProgress=true;
                                    //display.clear(); display.drawString(64, 32, "Type in New SSID"); display.display();
                                    //OLED_5_line_display("Type in New SSID",""," ","","");
                                    Serial.println("-");
                                    Serial.println("--Update EEPROM Started--");
                                    Serial.print("  SSID currently is <");Serial.print(wifiSSID);Serial.println(">"); 
                                    Serial.println("Type in New SSID");newData = false;SerioLevel=1;
                                     }
                          break;
                          case 1: if(MSG_content_length()>1) {wifiSSID=receivedChars;} newData = false;SerioLevel=2;
                          MSGText1="SSID     <";
                          MSGText1+=wifiSSID;
                          MSGText1+=">";
                                   //OLED_5_line_display(MSGText1,"Type Password"," "," "," ");
                                  //display.clear(); display.drawString(64, 12, MSGText); display.display();
                                   Serial.print(" SSID<");Serial.print(wifiSSID);Serial.print("> current Password<");Serial.print(wifiPassword); Serial.println(">");
                                   Serial.println("Type in New Password");
                                    
                          break;

                          case 2:   
                                 if(MSG_content_length()>1) {wifiPassword=receivedChars;} newData = false;SerioLevel=3;
                                 MSGText2="Password <";
                                 MSGText2+=wifiPassword;
                                 MSGText2+=">";
                                 //OLED_5_line_display(MSGText1,MSGText2,"Broker addr?"," "," ");  //display.drawString(64, 24, MSGText); display.display();
                                 Serial.print(" SSID<");Serial.print(wifiSSID);Serial.print("> Password<");Serial.print(wifiPassword); Serial.println(">");
                                 Serial.print("Broker Addr:");Serial.println(BrokerAddr);Serial.println("Type in MQTT Broker address");
                                    
                          break;
                          case 3:
                                 if(MSG_content_length()>1) {BrokerAddr= TestData.toInt();} newData = false;SerioLevel=4;
                                 MSGText3="Broker Addr<";
                                 MSGText3+=BrokerAddr;
                                 MSGText3+=">";
                                 //OLED_5_line_display(MSGText1,MSGText2,MSGText3," This Throttle's Name ?","");
                                 //display.drawString(64, 32, MSGText); display.display();
                                 Serial.print("Broker Addr:");Serial.print(BrokerAddr);Serial.print(" WiFi SSID<");Serial.print(wifiSSID);Serial.print("> Password<");Serial.print(wifiPassword); Serial.println(">");
                                 Serial.println("Please type 'sss' to save, or 'rrr' to return to start");
                          
                          break;
                          case 4:
                                Serial.print("Settings are: Broker Addr:");Serial.print(BrokerAddr);Serial.print(" WiFi SSID<");Serial.print(wifiSSID);Serial.print("> Password<");Serial.print(wifiPassword); Serial.println(">");
                                 if (TestData=="sss\0"){
                                    //display.clear(); display.drawString(64, 32, "EEPROM Updated"); display.display();
                                    Serial.println("I will now save this data and continue");
                                    WriteWiFiSettings();
                                    UpdateInProgress=false;
                                    newData = false;SerioLevel=5;
                                    }
                             else {
                              if (TestData=="rrr\0"){ 
                                //OLED_5_line_display("Resuming Serial Input","Type in xxx to restart",""," ","");
                                //display.clear(); display.drawString(64, 46, "Type xxx to resume input"); display.display();
                                Serial.println("-----------------");Serial.println("---Starting again---");Serial.println(" Type xxx again to re-start sequence");
                                newData = false;SerioLevel=0;
                                 }else{Serial.println("Please type 'sss' to save, or 'rrr' to return to start");newData = false;}
                                  }
                         
                          break;

                          case 5:
                            newData = false;
                            Serial.println("Wait to try reconnect, or turn off to restart with new values");

                          break;
                          default:
                            newData = false;
                            Serial.println("Not Understood");  
                          break; 
                         }
                          
                            }
      showNewData();  //only shows results if newData=true  and not understood (can happen if looping after a rrr)
      } //end of main while serial input loop
      Serial.println("");Serial.println("");
}


void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
       while (Serial.available() > 0 ) { 
           rc = Serial.read();
           if ((rc != 10)&&(rc != 13) ){ 
                receivedChars[ndx] = rc;
                ndx++; 
                if (ndx >= numChars) { ndx = numChars - 1;} //truncate if too bit to avoid filling up  
                                       }
                                       else { 
                                         newData = true;receivedChars[ndx] = '\0'; //replace NL/CR with /0 terminator. Mark that new data is available, but do not increment ndx
                                             }
                                        }ndx = 0; //once all serial data has been processed, reset the ndx pointer
}

void showNewData() {
    if (newData == true) {
                Serial.println(" ");
                Serial.print("Seen but not understood <");
                Serial.print(receivedChars);Serial.println(">    ");
              //to assist debug serial io //Serial.print("Ascii is <"); for (int i=0; i<=(numChars) ;i++) { Serial.print(int(receivedChars[i]));Serial.print("> <");}
                newData = false;}
    }





void WriteWiFiSettings(){
    Serial.println(" --Writing the SSID, Password, BrokerAddr and Throttle_Name to EEPROM-- ");
    writeString(ssidEEPROMLocation,wifiSSID);delay(10);
    writeString(passwordEEPROMLocation,wifiPassword);delay(10);
    EEPROM.write(BrokerEEPROMLocation,BrokerAddr);delay(10);
    EPROM_Write_Delay = millis() + 1000;
    EEPROM.commit();Data_Updated = false;delay(100);
}

void TestFillEEPROM(int d){
  #ifdef _EEPROMdebug
  Serial.print("~~~WARNING--FILLING EEPROM with int<");Serial.print(d);Serial.println(">~~");
  #endif
    for(int i=Serial_EEPROM_Starts;i<=(Serial_EEPROM_Starts+EEPROM_Serial_store_Size);i++) { EEPROM.write(i,d); }
     EEPROM.commit();delay(100);//
}

void writeString(int add,String data){  //from add, write data
  int _size = data.length();
  int i;
#ifdef _EEPROMdebug
       Serial.print("Writing :");Serial.print(_size);Serial.print(" bytes of data <");Serial.print(data);Serial.print("> at EEprom index starting:");Serial.println(int(add));
#endif
  for(i=0;i<_size;i++) { if ((add+i) < (Serial_EEPROM_Starts+EEPROM_Serial_store_Size)){EEPROM.write(add+i,data[i]);
                                       //Serial.print("Writing<");Serial.print(data[i]);Serial.print(">  to offset:");Serial.print(i);Serial.print("  index:");Serial.println(add+i);
                                                       } //write the data up to the point it would overflow the eeprom
                                       else{ //Serial.print("Stopping overflow Ignoring <");Serial.print(data[i]);Serial.print("> ");
                                           } 
                                       }
                                       //Got all the data, so add the \0
                        if ((add+i) <= (Serial_EEPROM_Starts+EEPROM_Serial_store_Size-1)){
                                       EEPROM.write(add+i,'\0');
                                       //Serial.print("Adding end_mark     to offset:");Serial.print(i);Serial.print("  index:");Serial.println(add+i);
                                        } 
                                       else{
                                        EEPROM.write(Serial_EEPROM_Starts+EEPROM_Serial_store_Size,'\0');
                                        //Serial.print("Adding end mark at end EEPRom size index:");Serial.println(Serial_EEPROM_Starts+EEPROM_Serial_store_Size);
                                        }
                        //Add termination null character for String Data
}
 
 
String read_String(int add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len;
  unsigned char k;
    //#ifdef _EEPROMdebug
    //Serial.print("Starting Read EEprom Data at Addr<");Serial.print(int(add));Serial.println("> ");
    //#endif
  len=0;
  k=EEPROM.read(add);
    while((k != '\0') && (len<99) && ((len+add)<=(Serial_EEPROM_Starts+EEPROM_Serial_store_Size)))   //Read until null character, or 100 or end of eeprom
  {     
    k=EEPROM.read(add+len);
    //#ifdef _EEPROMdebug
    //Serial.print(len);Serial.print("  ");Serial.print(add+len);Serial.print("  ");Serial.println(k);
    //#endif
    data[len]=k; 
    len++;
  }
  data[len]='\0';
  #ifdef _EEPROMdebug
  Serial.print("EEprom data from Addr:");Serial.print(int(add));Serial.print(" is <");Serial.print(data);Serial.println("> ");
  #endif
    return String(data);
}



