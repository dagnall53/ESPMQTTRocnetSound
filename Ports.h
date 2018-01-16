
boolean ButtonState[12] ;
int lastButtonState[12];
//

uint32_t PortTimingDelay[12];
//int DebounceDelayCount  =  2 ; //read the same signal 2 times before accepting it

//int CRD_SENSOR ;

uint8_t Motor_Speed = 0 ;



uint16_t ServoLastPos[10];
uint32_t WaitUntill;




//servo settings   
int SDemand[12];

//uint32_t servoDelay[12];
//int SloopDelay = 2;  //100 is about 4 seconds with 50ms delay in loop
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



//
// Stuff to work the ports on the ESP
void DoLocoMotor(void);
void READ_PORT( int i);
void ReadInputPorts(void);
void PortMode(int i);
void PortSetupReport(void);
boolean Debounce (int i);
int FlashHL(int state, int port);
void FLASHING(void); 
void DetachServo(int i);
void DETACH(void);
void SetServo( int i, uint16_t value);
uint16_t servoLR(int state, int port);
void SERVOS(void);


void DoLocoMotor(void){
  
  //CV[1] = RocNodeID;  force Loco addr = rocnode addr
  //CV[18] = RocNodeID; // set loco addr= node in case it was altered...l
   ServoOffDelay[_LOCO_SERVO_Driven_Port] = LoopTimer + 10000;  // reset the servooff delay for servo 0, which is the motor...
  if (POWERON == false) { // Track power off, stop the motor, zero the motor servo immediately
    Speed_demand=0;
    SDemand[_LOCO_SERVO_Driven_Port]=90;
    SetServo(_LOCO_SERVO_Driven_Port,90 );   // mod      (90);
  }
  else {                             // force all the bits to make servo '_LOCO_SERVO_Driven_Port' controlled by CV's
     SDemand[_LOCO_SERVO_Driven_Port] = Loco_motor_servo_demand;
     Pi03_Setting_onsteps[_LOCO_SERVO_Driven_Port] = CV[3];
     Pi03_Setting_offsteps[_LOCO_SERVO_Driven_Port] = CV[4]; // set acc and decc !!
     Pi03_Setting_offposH[_LOCO_SERVO_Driven_Port]=1;
     Pi03_Setting_offposL[_LOCO_SERVO_Driven_Port]=145;
     Pi03_Setting_onposH[_LOCO_SERVO_Driven_Port]=1;
     Pi03_Setting_onposL[_LOCO_SERVO_Driven_Port]=145;
     Pi03_Setting_options[_LOCO_SERVO_Driven_Port] = 32 + 10; // KEEP this i/o as a "SERVO" output regardless, 10= delay to use for servo changes = 100ms rate ;
    //Pi03_Setting_options[_LOCO_SERVO_Driven_Port]=0;  // force the "_LOCO_SERVO_Driven_Port Id to be NOT a servo as far as the main code is concerned
  }
}

void READ_PORT( int i) {
  boolean STATE;
  uint8_t TEMP;
  uint16_t senderADDR;
  if (((IO_Select_PortD[i] & 0x01) == 1) && ((Pi03_Setting_options[i] & 32) != 32))  { // only do this if this port is an "INPUT" and not a "SERVO"
    if (Debounce(i)) { // debounce is true if switch changed

      if (((IO_Select_PortD[i] & 32) == 32)  && (digitalRead(NodeMCUPinD[i]) == 1)) {
        ButtonState[i] = !ButtonState[i]; // only change on one state..
      }
      if ((IO_Select_PortD[i] & 32) == 32)   {
        STATE = ButtonState[i];
      }
      else {
        STATE = digitalRead(NodeMCUPinD[i]);
      }
      if ((IO_Select_PortD[i] & 64) == 64)   {
        STATE = !STATE;
      }
#if _SERIAL_DEBUG
      Serial.print ("Change on IO port : ");
      Serial.print(i);
      Serial.print(" State");
      Serial.println(STATE);
#endif
      SendPortChange(RocNodeID, STATE, i);

      if (STATE && (DelaySetting_for_PortD[i] >= 1)) {
        PortTimingDelay[i] = millis() + (DelaySetting_for_PortD[i] * 10);
      }

    }
  }
}// end read port



void ReadInputPorts() {

  // Check for port changes +++++++++++++++++++++++++++++++++++++
  if (!bReaderActive) {
    for (int i = 1 ; i <= 8; i++) {
      READ_PORT(i);
    }
  }
  else {
    READ_PORT(1);
    // only port 1  is fully user available.
  }
}

void PortMode(int i) {
  boolean hardset;
  hardset = false;
  Serial.print (" Port :");
  Serial.print (i);
  switch (i) {
   case _LOCO_SERVO_Driven_Port:
                      Serial.print(F(" used as LOCO MOTOR "));
                      IO_Select_PortD[i] = 0;
                      Pi03_Setting_options[i] = 42;
                      hardset =true;
                      break;
  case SignalLed:  
                      Serial.print(F(" is SignalLED  Output "));
                      pinMode(NodeMCUPinD[SignalLed], OUTPUT);
                      IO_Select_PortD[i] = IO_Select_PortD[i] & 0xFE;  
                      hardset =true;
                      break;
  case FRONTLight:
                      Serial.print (F(" is FRONTLight  Output "));
                      pinMode(NodeMCUPinD[FRONTLight], OUTPUT);
                      IO_Select_PortD[i] = IO_Select_PortD[i] & 0xFE; 
                      hardset =true;
                      break;
  case BACKLight:
                      Serial.print (F(" is BACKLight  Output "));
                      pinMode(NodeMCUPinD[BACKLight], OUTPUT);
                      IO_Select_PortD[i] = IO_Select_PortD[i] & 0xFE; 
                      hardset =true;
                      break;
 #ifdef SteamOutputPin
  case SteamOutputPin:
                     Serial.print (F(" is SteamPulse  Output "));
                      pinMode(NodeMCUPinD[SteamOutputPin], OUTPUT);
                       Pi03_Setting_options[i] = 0;
                      IO_Select_PortD[i] = IO_Select_PortD[i] & 0xFE; 
                      hardset =true;
                      break;

 #endif

                      
  #ifdef _Audio
  case I2SDAC_DIN:Serial.print (F(" is DIN used by Audio"));
                      IO_Select_PortD[i] = 0; Pi03_Setting_options[i] = 0;
                             hardset =true;
                      break;
                      #endif
                      #ifdef _AudioDAC
  case I2SDAC_LRC:Serial.print (F(" is LRC used by AudioDAC"));
                      IO_Select_PortD[i] = 0; Pi03_Setting_options[i] = 0;
                             hardset =true;
                      break;
  case I2SDAC_CLK:Serial.print (F(" is CLK used by AudioDAC"));
                      IO_Select_PortD[i] = 0; Pi03_Setting_options[i] = 0;
                             hardset =true;
                      break;
  #endif
  default:  // set according to Pi03_Setting_options[i] and IO_Select_PortD[i]
    
    //in 1 out 0
    if ((Pi03_Setting_options[i] & 32) == 32) {
      Serial.print (F(" is Servo"));
      pinMode(NodeMCUPinD[i], OUTPUT);
      IO_Select_PortD[i] = bitClear (IO_Select_PortD[i], 0 );
                    }
    else {
      if ((IO_Select_PortD[i] & 0x01) == 1) {
        pinMode(NodeMCUPinD[i], INPUT_PULLUP);
        Serial.print (F(" is Input with pullup"));
      }
      if ((IO_Select_PortD[i] & 0x01) == 0) {
        pinMode(NodeMCUPinD[i], OUTPUT);
        Serial.print (F(" is Output"));
      }
    }
    break;           
  }//end of switch
    
    // TODO would be good to add more explicit identification of what ports are set to with different channel options etc..
    if (hardset) {Serial.print(F( "(FIXED)"));}
    
          Serial.print (F(" NodePortType :"));
          Serial.print (IO_Select_PortD[i]);
          Serial.print (F("  Pi03_Setting_options"));
          Serial.println (Pi03_Setting_options[i]);
    
  }


void PortSetupReport() {
  int i;

  if (!bReaderActive) {
    #ifdef  _RFID
        Serial.println("            Reader Absent ....all ports available");
        Serial.println("");
    #endif 
    for (int i = 0 ; i <= 8; i++) {   //  port 0 as it has drive limitations

      PortMode(i);
    }
  }
  else {
    // only port 4 is user available.
    PortMode(4);
  }
 // Serial.println("all Ports set");
}
// moved from from subroutines
boolean Debounce (int i) {  // Tests for inputs having changed,
  boolean SwitchSensed;
  SwitchSensed = false ;
  if ((lastButtonState[i] != digitalRead(NodeMCUPinD[i])) && (millis() >= PortTimingDelay[i])) {
    SwitchSensed = true;
    lastButtonState[i] = digitalRead(NodeMCUPinD[i]);
    //    DebounceCount[i] =0 ;
    PortTimingDelay[i] = millis() + ((DelaySetting_for_PortD[i] * 10) + 1);
  }


  return (SwitchSensed);
}
//below here was x2 in subroutines

int FlashHL(int state, int port) {
  int value;
  if (state == 0) {
    value = (Pi03_Setting_offposH[port] * 256) + Pi03_Setting_offposL[port];
  }
  if (state == 1) {
    value = (Pi03_Setting_onposH[port] * 256) + Pi03_Setting_onposL[port];
  }
  value = ((value / 4)); // set the PWM  range 0-1023
  return (value) ;
}

void FLASHING() {
  boolean set;
  for (uint8_t port = 1; port <= 8; port++) {
    set = !(ButtonState[port]); // get phasing right so "no flash" is same high or low state as the non blink state
    if ((IO_Select_PortD[port] & 193) == 192) { set = !set; }// invert action if "invert", "an output" and "port blink" set ?  
    
      if (((IO_Select_PortD[port] & 129) == 128)&&( ((Pi03_Setting_options[port] & 32) != 32))) { // make sure its an output '0' and has port blink '128' set! and is NOT a Servo
      if ((set) && (millis() >= PortTimingDelay[port]) && (DelaySetting_for_PortD[port] >= 1)) {
       
        if ((Pi03_Setting_options[port] & 128) == 128) {// is  a 'channel' blink set  if so, use PWM outputs
          if (SDemand[port] == FlashHL(1, port)) {
            SDemand[port] = FlashHL(0, port);
          }
          else {
            SDemand[port] = FlashHL(1, port);
          }
          analogWrite(NodeMCUPinD[port], SDemand[port]);
        }
        else {                                        // its a digital output so just invert current state
          digitalWrite(NodeMCUPinD[port], !digitalRead(NodeMCUPinD[port]));
        }
        PortTimingDelay[port] = millis() + (DelaySetting_for_PortD[port] * 10);
      }
      

    }
  }
}


void DetachServo(int i) {
   switch (i) {
    case -1: {
        Serial.println(" ---- Switching OFF ALL Servos---");
      //  Loco_LOCO_SERVO_Driven_Port.detach();
        myservo1.detach();
        myservo2.detach();
        myservo3.detach();
        myservo4.detach();
        myservo5.detach();
        myservo6.detach();
        myservo7.detach();
        myservo8.detach();
      }
      break;
    case 1: {
        myservo1.detach();
      }
      break;
    case 2: {
        myservo2.detach();
      }
      break;
    case 3: {
        myservo3.detach();
      }
      break;
    case 4: {
        myservo4.detach();
      }
      break;
    case 5: {
        myservo5.detach();
      }
      break;
    case 6: {
        myservo6.detach();
      }
      break;
    case 7: {
        myservo7.detach();
      }
      break;
    case 8: {
        myservo8.detach();
      }
      break;
  }
 
}

void DETACH() {
 int i;
 for (int i = 1 ; i <= 8; i++) { //up to 8 servos.. but not  loco servo!. 
    if ( (millis() >= ServoOffDelay[i])  && ( (Pi03_Setting_options[i] & 32) == 32) ) { // double check its actually a servo !!, as this is called from two places{
        ServoOffDelay[i]=millis()+OneDay;  // set one day ahead as a simple way to avoid setting it again next time around... Moving the servo will reset it to millis anyway
      
        Serial.printf("\n Switching OFF Servo:%i ",i);
        //Serial.print(" Switching OFF Servo:");
        //Serial.println(i);
        DetachServo(i);
            
                                                                                   }
                                  }
 }
extern void SetChuffPeriod(long Setting);
void SetServo( int i, uint16_t value) { // uses 0-180
  long MotorSpeed;
  uint16_t SavedValue;
  if ((Pi03_Setting_options[i] & 32) == 32) { // double check, as this is called from two places
    ServoLastPos[i]=value;

#ifdef _Audio      // set chuff period here?
        if ((i==_LOCO_SERVO_Driven_Port)) {
            // if changes to motor speed, change chuff period:

// typical servo to speed elationship  servodemand = 90 + CV[2] + ((Speed_demand * CV[5])/240) ;
             //                        servodemand = 90 - CV[6] - ((Speed_demand * CV[5])/240) ; // revoffset separate from fwd offset  CV[6] is "V(mid)", but used as reverse offset
            SavedValue=value;  // make sure we what we are working with..
            if (SavedValue>= 90){ SavedValue=SavedValue-CV[2]+1;
                                  if (SavedValue>= 91) { MotorSpeed=(SavedValue-90)*240/CV[5]; }
                                  else {MotorSpeed=0;}  }                // rebuild in speed units not degrees.. first, get rid of offset or you get silly speed readings
                             else{SavedValue=SavedValue+CV[6]-1;
                                  if (SavedValue<= 89) { MotorSpeed=(90-SavedValue)*240/CV[5]; }
                                  else {MotorSpeed=0;}   }                  //(so that the chuff slows with the motor slowing down
           
            SetChuffPeriod(2000);
            if (MotorSpeed<=0){SetChuffPeriod(2000);}                 
            else{SetChuffPeriod(4000/MotorSpeed);}      /// Proper calcs below, but you will probably need to play with the value to fit your motor speed settings etc.
               //10mph=259ms quarter chuff rate at 10MPH 
                                                                    //we have 1609*10 m/hr = 16090/3600 m per second = 4.46 m per second
                                                                    // wheel of 1.4m dia is 4.4 circumference, so we have ~ 1 rotation per second
                                                                    // so with 4 chuffs per rev we get ~250ms "chuffperiod" at 10MPH
                        
          }  
        
#endif
    switch (i) {
    
      case 1: {
          if (!myservo1.attached()) { 
            myservo1.attach(D1);
          }
          myservo1.write(value);
          }
        break;
      case 2: {
          if (!myservo2.attached()) {
            myservo2.attach(D2);
          }
          myservo2.write(value);
        }
        break;
      case 3: {
          if (!myservo3.attached()) {
            myservo3.attach(D3);
          }
          myservo3.write(value);
        }
        break;
      case 4: {
          if (!myservo4.attached()) {
            myservo4.attach(D4);
          }
          myservo4.write(value);
        }
        break;
      case 5: {
          if (!myservo5.attached()) {
            myservo5.attach(D5);
          }
          myservo5.write(value);
        }
        break;
      case 6: {
          if (!myservo6.attached()) {
            myservo6.attach(D6);
          }
          myservo6.write(value);
        }
        break;
      case 7: {
          if (!myservo7.attached()) {
            myservo7.attach(D7);
          }
          myservo7.write(value);
        }
        break;
      case 8: {
          if (!myservo8.attached()) {
            myservo8.attach(D8);
          }
          myservo8.write(value);
        }
        break;
    }  // switch
   
  
                                   }// double check its a servo 
}// end 

uint16_t servoLR(int state, int port) {
  int value;
  value = 375; // == mid , 90 degrees
  if (state == 0) {
    value = (Pi03_Setting_offposH[port] * 256) + Pi03_Setting_offposL[port];
  }
  if (state == 1) {
    value = (Pi03_Setting_onposH[port] * 256) + Pi03_Setting_onposL[port];
  }
  value = ((value - 150) * 2) / 5; // set the servo immediately range 150-600 = 0 to 180
  return   (value);
}

void SERVOS() {              // attaches and detaches servos, accelerates to demanded positions etc..

  int ServoPositionNow;
  int offset;
  int steps;
  int SERVOSET;
  int set;
  uint32_t LocalTimer;
  int MotorSpeed;
  LocalTimer=millis();
  for (int i = 1 ; i <= 8; i++) { //up to 8 servos..  _LOCO_SERVO_Driven_Port is the LOCO motor servo 
    if ((Pi03_Setting_options[i] & 32) == 32) { //only if this port is a "servo"... To address a channel instead of a port the port type servo must be set on the interface tab of switches and outputs
      if (millis() >= (Pi03_Setting_LastUpdated[i] + (Pi03_Setting_options[i] & 15) * 10)) { // do update only at the required delay update rate
        offset = SDemand[i] - ServoLastPos[i];
        ServoPositionNow=ServoLastPos[i];
        
 //      #if _SERVO_DEBUG
 //      DebugSprintfMsgSend( sprintf ( DebugMsg, " (line 413) Servo[%d] Last Pos:%d  Demand:%d Offset:%d ",i,ServoLastPos[i], SDemand[i],offset);
 //          
//       #endif
        if ((abs(offset) <= 3) && ((IO_Select_PortD[i] & 129) == 128)  && (ButtonState[i] == 1) ) { //changes demand if within 3 of demand and reversing...needs inv to operate on buttonstate, ???as it will not switch off if inv..
//          #if _SERVO_DEBUG
//              DebugSprintfMsgSend( sprintf ( DebugMsg, " ( 372) Using Reversing code");
 //             
//          #endif
          ServoOffDelay[i] = LocalTimer + 2000; // not sure if this is needed, but we will not be switching off soon! 
          if (SDemand[i] == servoLR(1, i)) {
                         SDemand[i] = servoLR(0, i);
                                            }
               else {
                     SDemand[i] = servoLR(1, i);
                    }
                                   } //if abs offset <=3
     
        if (offset != 0) {
          ServoOffDelay[i] = LocalTimer + 2000; // 2s sec off timer start but only do if the servo is NOT in the final position, when its in final position, it does NOT update
          if (ButtonState[i]) {
            steps = Pi03_Setting_onsteps[i];
          }
          else {
            steps = Pi03_Setting_offsteps[i];
          }
          if (steps == 0) {
            SERVOSET = SDemand[i];
          #if _SERVO_DEBUG
              DebugSprintfMsgSend( sprintf ( DebugMsg, " ( line 460 ) Set Immediately"));
               #endif
          }
          else {
            if (abs(offset) >= steps) { 
              offset = (offset * steps) / abs(offset);  //offset is now either the error or steps, whichever is less
                                      }
                                      
            SERVOSET = ServoPositionNow + offset;
            if ((SERVOSET) >= 180) {
              SERVOSET = 180;
            }
            if ((SERVOSET) <= 0  ) {
              SERVOSET = 0; // range for servo is 0-180
            }
          }
#if _SERVO_DEBUG
//NOTE Sending serial messages adds about 200ms delay in the loop !.
 //   DebugSprintfMsgSend( sprintf ( DebugMsg, "( 425 ) Servo[%d] SERVOSET:%d",i,SERVOSET);
 //   DebugMsgSend("debug", DebugMsg);
    DebugSprintfMsgSend( sprintf ( DebugMsg, "Time(%d) Servo[%d] to {%d} by moving:%d steps from:%d towards:%d",LocalTimer,i,SDemand[i],offset,ServoPositionNow,SDemand[i]));

#endif
         // Pi03_Setting_LastUpdated[i] = (Pi03_Setting_LastUpdated[i] + (Pi03_Setting_options[i] & 15) * 10);
          Pi03_Setting_LastUpdated[i] = LocalTimer ;
          SetServo( i, SERVOSET);
          
        } // offset != 0

        
      } // time to do an update
    } //if servo
  } // end i 1..8 loop

}//end servos


