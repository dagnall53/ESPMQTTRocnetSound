/** Typical (MISO MOSI SCLK and CS are hard coded in MFRC522....) pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      ESP866            NodeMCU     NUMBER
               Reader/PCD
   Signal      Pin          Pin
   -----------------------------------------------------------------------------------------
   cs                                                      15
   SPI MOSI    MOSI         GPIO13             D7          13
   SPI MISO    MISO         GPIO12             D6          12
   SPI SCK     SCK          GPIO14             D5          14
                            GPIO9              SD2
                            GPIO10             SD3
   RST/Reset   RST          GPIO4              D2          4
   SPI SS      SDA(SS)      GPIO5              D1          5*/

   
//#if defined(ARDUINO_ESP8266_ESP01)

 #include <SPI.h>
 #include <MFRC522.h> //mine is modified to give 10Mhz with ESP  #define SPI_CLOCK_DIV_4 10000000  #define myClock  10000000 //replaces    SPI_CLOCK_DIV4

#define RST_PIN         D0           //Configurable, see typical pin layout above
#define SS_PIN          D1           //Configurable, see typical pin layout above
//Configurable, see typical pin layout above    //setup
//RFID stuff***************************************************************
#define NR_OF_PORTS     1
#define NR_OF_SVS       NR_OF_PORTS * 3 + 3

#define NR_OF_EXT_SVS   100 + NR_OF_PORTS * 3



MFRC522 mfrc522(SS_PIN, RST_PIN);   //Create MFRC522 instance.
MFRC522::MIFARE_Key key;




void setMessageHeader(uint8_t *SendPacketSensor);
uint8_t processXferMess(uint8_t *LnRecMsg, uint8_t *LnSendMsg);
uint8_t lnCalcCheckSumm(uint8_t *cMessage, uint8_t cMesLen);


uint8_t uiLnSendMsbIdx = 12;
uint8_t uiStartChkSen;

uint8_t oldUid[UID_LEN] = {0};

uint8_t SendPacketSensor[16];


//#############################################################

bool delaying;
bool bRFIDactive;
unsigned char i = 0;
unsigned char j = 0;
uint32_t uiDelayTime = 500;
uint32_t RFIDQuietAfterTag = 3000;
#define PICC_REQIDL           0x26
int RFID_status;
int RFID_read = 0;

bool bRFIDquiet;
void SetupRFID(void ){
   Serial.println("------------------------ MFRC 522 testing -----------------");
  //* Setup rfidstuff *************************
  SPI.begin();        //Init SPI bus//
  mfrc522.PCD_Init(); //Init MFRC522 card
  mfrc522.PCD_SetRegisterBitMask(mfrc522.RFCfgReg, (0x07 << 4)); //https://github.com/miguelbalboa/rfid/issues/43 //If you set Antenna Gain to Max it will increase reading distance
  byte readReg = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  if ((readReg == 0x00) || (readReg == 0xFF)) { //missing reader
    Serial.println(" Reader absent");
  } else {
    Serial.println(" Reader Present ");  //would like to have spi speed here.
    bReaderActive = true;
  }
}

void SendUID (uint8_t *UID, uint8_t PHASE, int where ) { //phase 1 =on 0=off
  //uint8_t SendMsg[4];
  int tempaddr;
  int addr;

  addr = UID[1] + (UID[2] * 256);
  addr = 100 + (addr & 127); //function to place all tags within a 127 range , starting at 100.. WILL RESULT IN DUPLICATE TAG ADDRESSES!!
  if (!(addr == 100)) {
#if _SERIAL_DEBUG
    //Serial.print(millis());
    //Serial.print(" ms RFID ");
    //Serial.print (where);
    //Serial.println();
    //   Serial.print(" Addr:");
    //   Serial.print (addr);
    //   Serial.print (" Val:");
    //   Serial.println(PHASE);
#endif
    if (PHASE == 1) {
      SensorOutput_Inactive = false;
      SendPortChange(200, 1, addr) ; //set rocnodeID to 200 for all RFID sends
      //delay(50);
      //SendPortChange(200,1,addr) ;  //double send as experiment to see if this helps
    }
    if (PHASE == 0) {
      SensorOutput_Inactive = true;
      SendPortChange(200, 0, addr); //set rocnodeID to 200 for all RFID sends}//set rocnodeID to 200 for all RFID sends
      //delay(50);
      //SendPortChange(200,0,addr) ;  //double send as experiment to see if this helps
    }
    oldUid[1] = 0;
    oldUid[2] = 0;
  }


}

void checkRFID() {
  //RFIDCycle=RFIDCycle+20;  //check rfid at 20ms intervals   (would be sensible if I coud get this cycle below 20ms !!!)
  if (bReaderActive) {

    //OLD CODE
    if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      //Serial.println("Newcard and Piccreadserial line 107");
      if (!compareUid( mfrc522.uid.uidByte, oldUid, mfrc522.uid.size)) { //NEW  (NOT same UID)
        if (!((oldUid[1] == 0) && (oldUid[2] == 0))) {
          SendUID(oldUid, 0, 2); //clear old uid if it has not been cleared
        }
        SendUID(mfrc522.uid.uidByte, 1, 1);
        RFIDCycle = millis() + RFIDQuietAfterTag; //switched on, so do'nt do any more reading for 2 secs..
        copyUid(oldUid, mfrc522.uid.uidByte,  mfrc522.uid.size); //save in oldUID
        //uiStartTime = millis()+RFIDQuietAfterTag;
        //bRFIDactive=true;
        bRFIDquiet = false;
        //Serial.println("Found new card..line116");
      }//end NOT same UID same
      else { //is the same card still...
        //               Serial.println("Same card..line119");
        // uiStartTime = millis()+RFIDQuietAfterTag;
        RFIDCycle = millis() + RFIDQuietAfterTag; //update time card was seen
      }                                              //same card end..
    } else { //nothing read..

      if ((!bRFIDquiet) && (millis() >= RFIDCycle + uiDelayTime)) {
        //      Serial.println("Nothing read for a while .line 126"); //wait delay before declaring the card gone
        SendUID(oldUid, 0, 3);
        bRFIDquiet = true;
      } //if((uiActTime
    }//nothing read



  }//ifmrfc
}


