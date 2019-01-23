#include <Stepper.h>


boolean ButtonState[12] ;
int lastButtonState[12];
//

uint32_t PortTimingDelay[12];
//int DebounceDelayCount  =  2 ; //read the same signal 2 times before accepting it

//int CRD_SENSOR ;

uint8_t Motor_Speed = 0 ;
uint32_t Motor_Setting_Update_Time;


uint16_t ServoLastPos[10];
uint32_t WaitUntill;




//servo settings   
int SDemand[12];

//uint32_t servoDelay[12];
//int SloopDelay = 2;  //100 is about 4 seconds with 50ms delay in loop
int ServoOff_Delay_Until[12];


//Servo Loco_LOCO_SERVO_Driven_Port;  //create servo object to control a servo  //servo 0 in ver107 on to be loco, but connected on pin D1. 
Servo myservo1;  //create servo object to control a servo
Servo myservo2;  //create servo object to control a servo
Servo myservo3;  //create servo object to control a servo
Servo myservo4;  //create servo object to control a servo
Servo myservo5;  //create servo object to control a servo
Servo myservo6;  //create servo object to control a servo
Servo myservo7;  //create servo object to control a servo
Servo myservo8;  //create servo object to control ... used for loco motors in ver 106 back

//conditional externs 
#ifdef _Audio 
extern uint8_t SoundEffect_Request[3];
extern void SetChuffPeriodFromSpeed(uint16_t value);
//extern void SetChuffPeriodFromServoPos(uint16_t value);

#endif


//
//Stuff to work the ports on the ESP
void SetMotorSpeed(uint8_t SpeedDemand,uint8_t dirf); 
uint16_t SetLocoMotorRC(int LocoPort, uint16_t SpeedDemand,bool dir); //RC  Speed demand range is approx mph  and outputs the speedemenad in case it limits it
uint16_t SetLocoMotorPWM(int LocoPort, uint16_t SpeedDemand,bool dir);  //PWM Speed demand range is approx mph  and outputs the speedemenad in case it limits it
void ImmediateStop(void);
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

//the actual code follows
bool IsServo(uint8_t index){
 return ((Pi03_Setting_options[index] & 32) == 32);
}

bool IsPWM(uint8_t index){
return ((Pi03_Setting_options[index] & 128) == 128);
}


void SetMotorSpeed(uint8_t SpeedDemand,uint8_t dirf){ //lc dirf to avoid confusion with DIRF ?
#ifdef _LOCO_SERVO_Driven_Port 
int servodemand;
int Brake_trigger_speed;
bool Dir;
          Speed_demand = SpeedDemand;
          Brake_trigger_speed= (CV[2]+((CV[3]+CV[4])/2));
          if (Speed_demand>=120) {Speed_demand=120;} //set a max speed (trying to find a bug in pwm speed 
          Dir=bitRead(dirf, 5 );  
          DebugSprintfMsgSend( sprintf ( DebugMsg, " Set Speed<%d> Dir<%d> Lights<%d>",SpeedDemand, bitRead(DIRF,5),bitRead(DIRF,4)));  //X is hex d is decimal
        //  DebugSprintfMsgSend( sprintf ( DebugMsg, " SFX %x %x %x  sound on%d ",SoundEffect_Request[1],SoundEffect_Request[2],SoundEffect_Request[3],(bitRead(SoundEffect_Request[2],0)==1))); /// 
#ifdef _Audio
//do brakes here
          if ((Last_Speed_demand >= Brake_trigger_speed ) && (SpeedDemand ==0)&&(bitRead(SoundEffect_Request[2],0)==1)){ //  play if speed was above Vtart + acc step and F9 is chuffs on
                     #ifdef _SERIAL_Audio_DEBUG   
                       DebugSprintfMsgSend( sprintf ( DebugMsg, " Brakes Last speed %d   Trigger speed %d ", Last_Speed_demand, Brake_trigger_speed)); 
                     #endif  
                       BeginPlay(1,"/brakes.wav",CV[111]); //brakes.wav should be a brake squeal sample to be played as we stop. 
                       }  
          // SetChuffPeriodFromSpeed(SpeedDemand);  set here for instant sfx period change,,set at line 371 or thereabouts to change gradually with acc/decc

                       
#endif 
//check for lights off          
          if  (!(bitRead(dirf, 4))) {  //lights off
                digitalWrite (NodeMCUPinD[FRONTLight], 1);
                digitalWrite (NodeMCUPinD[BACKLight], 1);
                                  }
                               
         if ((Speed_demand==0)&&(Last_Speed_demand!=0)) {Dir=Last_Direction;}              //keep the lights in the right direction until stopped?     
         else {Last_Direction=Dir;}    //catches rocrail issue where direction changes if 0 is pressed. keeps lights on in correct phase until stop, but changes if 0 repeatedly pressed                              
                             
//setup the lights
          //---------do Direction Lights but not  Servo settings---------------
   if (bitRead(CV[29], 0)) {         //need to account for the  cv29 bit 0....
            if (Dir) {
                           if  (bitRead(dirf, 4)) { //front lights on
                digitalWrite (NodeMCUPinD[FRONTLight], 0);
                digitalWrite (NodeMCUPinD[BACKLight], 1);
              }
            }
            else {
              if  (bitRead(dirf, 4)) {//lights on
                digitalWrite (NodeMCUPinD[BACKLight], 0);
                digitalWrite (NodeMCUPinD[FRONTLight], 1);
              }
            }
                          } //cv29 bit 0 = 1
          else {   //cv29 bit 0  =0
            if (Dir) {
                if  (bitRead(dirf, 4)) {
                digitalWrite (NodeMCUPinD[BACKLight], 0); //back light on
                digitalWrite (NodeMCUPinD[FRONTLight], 1);
              }
            }
            else {
               if  (bitRead(dirf, 4)) {
                digitalWrite (NodeMCUPinD[FRONTLight], 0);
                digitalWrite (NodeMCUPinD[BACKLight], 1);
              }
            }
          }  //cv29 is 1
          DoLocoMotor();
#endif     
} 

  



uint16_t SetLocoMotorRC(int LocoPort, uint16_t SpeedDemand,bool dir){  //RC servo is set  0 to 180  
  uint8_t value;
uint8_t servodemand;
uint16_t MinSpeed;
uint16_t AdditionalSpeedDemand;
bool STOPdemand;
uint16_t Max_Speed;
  STOPdemand=false;
if (SpeedDemand==0) { STOPdemand=true; }

MinSpeed = 5; //RC min speed is higher than PWM...this is the actual (scale mph) speed when the motor is running as slow as it can reliablly
//concept  : Min speed voltage is set by CV 2, with CV 65 orCV 95 trim added and is "MinSpeed"  The rest is linearly added related to by  CV 5
//90 = CV[2] + ((max * CV[5])/10) ;
//90-CV[2]= (max * CV[5])/10 ;
//10*(90-CV[2])= max * CV[5] ;
//(10*(90-CV[2]))/CV[5]= max ;
  Max_Speed= (3+((10*(90-CV[2]+CV[66]) )/CV[5])); //needed correcting for rc with trims
  if (dir){   Max_Speed= (3+((10*(90-CV[2]+CV[95]) )/CV[5])); }
if (SpeedDemand>=Max_Speed){SpeedDemand=Max_Speed;}  //limit the max speed here so it also limits the chuff settings.

   
if (POWERON){  

 //SET SPEED TO 3 (MPH) AND ADJUST cv2  FOR EXACT 3MPH SPEED.. use CV 65 (fwd) and CV 95 (rev) to get exact. 
 //THEN SET CV 5 FOR 10 MPH (OR HIGHER) ACCURATE SPEED

//

if (SpeedDemand<=MinSpeed){AdditionalSpeedDemand=0;}//how much faster am I asking for?
else {AdditionalSpeedDemand=SpeedDemand-MinSpeed; }

if (AdditionalSpeedDemand<= 0){ AdditionalSpeedDemand=0; SpeedDemand=MinSpeed;}
if (AdditionalSpeedDemand>= 100){ AdditionalSpeedDemand=100;}

//concept  : Min speed is set by CV 2, with CV 66 orCV 95 trim added and is "MinSpeed"  The rest is linearly added related to by  CV 5
servodemand = CV[2] + ((AdditionalSpeedDemand * CV[5])/10) ;

if (bitRead(CV[29], 0)) {         //need to account for the  cv29 bit 0....
if (dir) {servodemand = 90- servodemand -CV[95]; }  //trims.. aiming for 0-1024, with 10 mph = about 1rpm swap cv 2 or 6 depending on direction
    else {servodemand = 90+ servodemand +CV[66]; }
    }
else {if (dir){servodemand =  90+servodemand +CV[66]; } 
    else {servodemand = 90- servodemand -CV[95]; }
    }


if (STOPdemand) { servodemand=90; }
          if (servodemand >= 179) { servodemand = 179; }
          if ((servodemand) <= 1  ) {  servodemand = 1;} //servo range held to    1-179
     
#ifdef _SERVO_DEBUG
DebugSprintfMsgSend( sprintf ( DebugMsg, "RC motor speed:%d dir<%d>  servo setting:%d (max from CV's:%d)",SpeedDemand,dir, servodemand,Max_Speed));      
#endif        
         SetServo(LocoPort, servodemand );
         Loco_servo_last_position=servodemand;
         
  
}else {
   SetServo(LocoPort, 90 );}
  if (STOPdemand) {SpeedDemand=0;}
return SpeedDemand;    
}


uint16_t SetLocoMotorPWM(int LocoPort, uint16_t SpeedDemand,bool dir){  //PWM Speed demand range is approx mph  
  uint8_t value;
  uint16_t PWMdemand;
  uint16_t MinSpeed;
  uint16_t AdditionalSpeedDemand;
  bool STOPdemand;
  uint16_t Max_Speed;
  #ifdef _LocoPWMDirPort
  Max_Speed= 3+((1023-(CV[2]*10)+CV[66])/CV[5]);  //fwd trim is 66
  if (dir){  Max_Speed= 3+((1023-(CV[2]*10)+CV[95])/CV[5]);}
  if (SpeedDemand>=Max_Speed){SpeedDemand=Max_Speed;}  //limit the max speed here so it also limits the chuff settings.

  if (POWERON){
  STOPdemand=false;
  if (SpeedDemand==0) { STOPdemand=true; }
  MinSpeed = 3; //this is the actual (scale mph) speed when the motor is running as slow as it can reliablly
  //to do
 //SET SPEED TO 3 (MPH) AND ADJUST cv2  FOR EXACT 3MPH SPEED.. use CV 66 (fwd) and CV 95 (rev) to get exact. 
 //THEN SET CV 5 FOR 10 MPH (OR HIGHER) ACCURATE SPEED
 //set pwm port to direction

if (SpeedDemand<=MinSpeed){AdditionalSpeedDemand=0;}
else {AdditionalSpeedDemand=SpeedDemand-MinSpeed; }//how much faster am I asking for?
if (AdditionalSpeedDemand<= 0){ AdditionalSpeedDemand=0; SpeedDemand=MinSpeed;}
if (AdditionalSpeedDemand>= 100){ AdditionalSpeedDemand=100;}

//concept  : Min speed is set by CV 2, with CV 66 orCV 95 trim added and is "MinSpeed"  The rest is linearly added related to by  CV 5
PWMdemand =  ((CV[2]*10) + (AdditionalSpeedDemand * CV[5]));
if (bitRead(CV[29], 0)) {         //need to account for the  cv29 bit 0....
if (dir) {PWMdemand = PWMdemand +CV[95]; }  //trims.. aiming for 0-1024, with 10 mph = about 1rpm swap cv 2 or 6 depending on direction
    else {PWMdemand =  PWMdemand +CV[66]; }
    }
else {if (dir){PWMdemand =  PWMdemand +CV[66]; } 
    else {PWMdemand = PWMdemand +CV[95]; }
    }

if (PWMdemand>=1023) {PWMdemand=1023;}
if (PWMdemand<=0) {PWMdemand=0;}
if (STOPdemand) { PWMdemand=0; }

 //if (POWERON){
         //DebugSprintfMsgSend( sprintf ( DebugMsg, "PWM motor speed:%d dir<%d>  PWM setting:%d (max from CV's:%d)",SpeedDemand,dir, PWMdemand,Max_Speed));
         
  //       }
if (bitRead(CV[29], 0)) {         //need to account for the  cv29 bit 0....
if (dir){
analogWrite(NodeMCUPinD[_LocoPWMDirPort] , PWMdemand);
digitalWrite (NodeMCUPinD[LocoPort] , false) ;
#ifdef _SERVO_DEBUG
DebugSprintfMsgSend( sprintf ( DebugMsg, "1 PWM motor speed:%d dir<%d>  PWM setting:%d  ",SpeedDemand,dir, PWMdemand));
#endif
}
else{
analogWrite( NodeMCUPinD[LocoPort], PWMdemand);
digitalWrite (NodeMCUPinD[_LocoPWMDirPort] , false) ;
#ifdef _SERVO_DEBUG
DebugSprintfMsgSend( sprintf ( DebugMsg, "2 PWM motor speed:%d dir<%d>  PWM setting:%d  ",SpeedDemand,dir, PWMdemand));
#endif
}}
else{  //inverted direction
if (dir){
analogWrite( NodeMCUPinD[LocoPort], PWMdemand);
digitalWrite (NodeMCUPinD[_LocoPWMDirPort] , false) ;
#ifdef _SERVO_DEBUG
DebugSprintfMsgSend( sprintf ( DebugMsg, "3 PWM motor speed:%d dir<%d>  PWM setting:%d  ",SpeedDemand,dir, PWMdemand));
#endif
}
else{
analogWrite(NodeMCUPinD[_LocoPWMDirPort] , PWMdemand);
digitalWrite (NodeMCUPinD[LocoPort] , false) ;
#ifdef _SERVO_DEBUG
DebugSprintfMsgSend( sprintf ( DebugMsg, "4 PWM motor speed:%d dir<%d>  PWM setting:%d  ",SpeedDemand,dir, PWMdemand));
#endif
}
}



}else {
//power off!
   digitalWrite( NodeMCUPinD[LocoPort], false);
   digitalWrite (NodeMCUPinD[_LocoPWMDirPort] , false) ;
    } 
  #endif
    if (STOPdemand) {SpeedDemand=0;}
  return SpeedDemand;
}

void ImmediateStop(void){
  uint16_t Speed;
    #ifdef _LOCO_SERVO_Driven_Port 
   #ifndef _LocoPWMDirPort
               Speed= SetLocoMotorRC(_LOCO_SERVO_Driven_Port,0,0);
   #endif
   #ifdef _LocoPWMDirPort
               Speed=SetLocoMotorPWM(_LOCO_SERVO_Driven_Port,0,0);//
   #endif
   #endif
  }


void DoLocoMotor(void){  //uses Last_Speed_demand and Speed_demand to set servo or pwm including slowing and acceleration  calls SetChuffPeriodFromSpeed 
 #ifdef _LOCO_SERVO_Driven_Port

  int offset;
  int steps;
  uint16_t SPEEDSET;
  bool Dir;
  uint16_t currentspeed;


   Dir=bitRead(DIRF, 5 );
   ServoOff_Delay_Until[_LOCO_SERVO_Driven_Port] = millis() + 10000;  //reset the servo off delay for the motor...
   if (POWERON == false) { //Track power off, stop the motor, zero the motor servo immediately
                        ImmediateStop();    }
       else {   //Power is ON 
                         
         if ((millis() >= Motor_Setting_Update_Time)&& ( (Last_Speed_demand != Speed_demand)||(Dir!= Last_Set_Dir))) { //do updates only at the required delay update rate or a change
          Motor_Setting_Update_Time=millis() +100; //do update only at the  100ms delay update rate
          offset = Speed_demand-Last_Speed_demand;  //how far from the demand are we
                 
      //speed up or decellerate?
          if (abs(Speed_demand) >= abs(Last_Speed_demand)) {  //we are accelerating...
                                  steps = CV[3];    }
                    else    {     steps = CV[4];    } //must be slowing down
                    
          if (abs(offset) >= abs(steps)) { //quite a way to go 
                      if (offset>=0){ //Speed demand is higher than last demand
                                    SPEEDSET=Last_Speed_demand+steps; }   //offset is now either the error or steps, whichever is less4
                                     else {SPEEDSET=Last_Speed_demand-steps; }
                       }
                      else {SPEEDSET=Speed_demand; } //Offset smaller than difference so just set to demand
      
    //if ((Speed_demand==0)&&(offset<=0)&&(Dir!=Last_Set_Dir) ) {
    //Dir=!bitRead(DIRF, 5 );
     //DebugSprintfMsgSend( sprintf ( DebugMsg, "205 Inverting direction"));
     //} //if slowing to speed = 0, at reversing terminals dir has already been inverted by rocrail so invert to prevent rapid servo reversal
       
         
       
        //DebugSprintfMsgSend( sprintf ( DebugMsg, "Do Loco Motor Last speed:%d offset%d  New speed:%d Direction:%d",Last_Speed_demand,offset, SPEEDSET,Dir));

//-----------------KICK START MOTOR
    int SP;  //changed to a CV[65] related timer value 
    int TI;
    SP=40;
    TI=CV[65];
    if((Last_Speed_demand==0)&&(Speed_demand!=0)){//give a quick kick pulse to ensure starting from stopped. This works well with pwm, but not as well with servo
        #ifndef _LocoPWMDirPort
                SP=SetLocoMotorRC(_LOCO_SERVO_Driven_Port,SP,Dir);
                delay(TI*2); //wait for this long before going to "correct" speed, longer for servo than pwm
                         //DebugSprintfMsgSend( sprintf ( DebugMsg, "Kick start motor speed%d Time:%dms  Dir%d",SP,TI*2,Dir));
         #endif
        #ifdef _LocoPWMDirPort
                SP=SetLocoMotorPWM(_LOCO_SERVO_Driven_Port,SP,Dir);//
               delay(TI); //wait for this long before going to "correct" speed
                       // DebugSprintfMsgSend( sprintf ( DebugMsg, "Kick start motor speed%d Time:%dms  Dir%d",SP,TI,Dir));
        #endif
                                           }
//-end ----------------KICK START MOTOR
  
//do the motor drivers....        
      #ifndef _LocoPWMDirPort
               currentspeed = SetLocoMotorRC(_LOCO_SERVO_Driven_Port,SPEEDSET,Dir);
      #endif
      #ifdef _LocoPWMDirPort
               currentspeed = SetLocoMotorPWM(_LOCO_SERVO_Driven_Port,SPEEDSET,Dir);
      #endif
    if(Last_Speed_demand != Speed_demand){
          #ifdef _Audio      //sets up chuff period if speed changed here so it works with acceleration etc
               SetChuffPeriodFromSpeed(SPEEDSET);   
          #endif //is audio
                                        }
                                             
     Last_Speed_demand=SPEEDSET;  
     Last_Set_Dir=Dir;          
      } //update time
     
      } //else for the power on check
    
 #endif //is loco
}

void READ_PORT( int i) {
  boolean STATE;
  uint8_t TEMP;
  uint16_t senderADDR;
  if (((Pi02_Port_Settings_D[i] & 0x01) == 1) && (IsServo(i)))  { //only do this if this port is an "INPUT" and not a "SERVO"
    if (Debounce(i)) { //debounce is true if switch changed

      if (((Pi02_Port_Settings_D[i] & 32) == 32)  && (digitalRead(NodeMCUPinD[i]) == 1)) {
        ButtonState[i] = !ButtonState[i]; //only change on one state..
      }
      if ((Pi02_Port_Settings_D[i] & 32) == 32)   {
        STATE = ButtonState[i];
      }
      else {
        STATE = digitalRead(NodeMCUPinD[i]);
      }
      if ((Pi02_Port_Settings_D[i] & 64) == 64)   {
        STATE = !STATE;
      }
#ifdef _SERIAL_DEBUG
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
}//end read port



void ReadInputPorts() {

  //Check for port changes +++++++++++++++++++++++++++++++++++++
  if (!bReaderActive) {
    for (int i = 1 ; i <= 8; i++) {
      READ_PORT(i);
    }
  }
  else {
    READ_PORT(1);
    //only port 1  is fully user available.
  }
}

void PortMode(int i) {
  boolean hardset;
  hardset = false;
  Serial.print (" Port :");
  Serial.print (i);
  switch (i) {
  #ifdef _LOCO_SERVO_Driven_Port
      case _LOCO_SERVO_Driven_Port:
                      Serial.print(F(" LOCO MOTOR "));
                      Pi02_Port_Settings_D[i] = 0;
                      Pi03_Setting_options[i] = 42;
                      hardset =true;
      #ifdef _LocoPWMDirPort
                      Serial.print(F(" PWM "));
                      Pi03_Setting_options[i] = 128;
      #endif
            break;
  #endif

  #ifdef _LocoPWMDirPort
      case _LocoPWMDirPort:
                      Serial.print(F(" LOCO PWM dir "));
                      pinMode(NodeMCUPinD[_LocoPWMDirPort], OUTPUT);
                      Pi02_Port_Settings_D[i] = Pi02_Port_Settings_D[i] & 0xFE; 
                      hardset =true;
      break;
  #endif

     case SignalLed:  
                      Serial.print(F(" is SignalLED  Output "));
                      pinMode(NodeMCUPinD[SignalLed], OUTPUT);
                      Pi02_Port_Settings_D[i] = Pi02_Port_Settings_D[i] & 0xFE;  
                      hardset =true;
      break;
                      
  #ifdef _LOCO_SERVO_Driven_Port  
      case FRONTLight:
                      Serial.print (F(" is FRONTLight  Output "));
                      pinMode(NodeMCUPinD[FRONTLight], OUTPUT);
                      Pi02_Port_Settings_D[i] = Pi02_Port_Settings_D[i] & 0xFE; 
                      hardset =true;
       break;
       case BACKLight:
                      Serial.print (F(" is BACKLight  Output "));
                      pinMode(NodeMCUPinD[BACKLight], OUTPUT);
                      Pi02_Port_Settings_D[i] = Pi02_Port_Settings_D[i] & 0xFE; 
                      hardset =true;
        break;
  #endif                      
  #ifdef SteamOutputPin
        case SteamOutputPin:
                     Serial.print (F(" is SteamPulse  Output "));
                     pinMode(NodeMCUPinD[SteamOutputPin], OUTPUT);
                     Pi03_Setting_options[i] = 0;
                     Pi02_Port_Settings_D[i] = Pi02_Port_Settings_D[i] & 0xFE; 
                     hardset =true;
         break;

  #endif

                      
  #ifdef _Audio  
        
     #ifdef _AudioDAC   
        case I2SDAC_LRC:Serial.print (F(" is LRC used by Audio"));
                      Pi02_Port_Settings_D[i] = 0; Pi03_Setting_options[i] = 0;
                             hardset =true;
        break;            
        case I2SDAC_CLK:Serial.print (F(" is CLK used by Audio DAC"));
                      Pi02_Port_Settings_D[i] = 0; Pi03_Setting_options[i] = 0;
                             hardset =true;
        break;
      
                    
        case I2SDAC_DIN:Serial.print (F(" is DIN used by Audio DAC"));
                      Pi02_Port_Settings_D[i] = 0; Pi03_Setting_options[i] = 0;
                             hardset =true;
        break;
     #else
        case I2SDAC_LRC:Serial.print (F(" is LRC used by Audio, with Speaker Drive from D("));Serial.print(I2SDAC_DIN);Serial.print(") Both ");
                      Pi02_Port_Settings_D[i] = 0; Pi03_Setting_options[i] = 0;
                             hardset =true;
        break;
        case I2SDAC_DIN:Serial.print (F(" (RX) is Speaker Drive used by Audio"));
                      Pi02_Port_Settings_D[i] = 0; Pi03_Setting_options[i] = 0;
                             hardset =true;
        break;
     #endif
        
  #endif  


  default:  //set according to Pi03_Setting_options[i] and Pi02_Port_Settings_D[i]
    
    //in 1 out 0
    if (IsServo(i)) {
      Serial.print (F(" is Servo"));
      pinMode(NodeMCUPinD[i], OUTPUT);
      Pi02_Port_Settings_D[i] = bitClear (Pi02_Port_Settings_D[i], 0 );
                    }
                    else{
      if (IsPWM(i)) {
      Serial.print (F(" is PWM"));
      pinMode(NodeMCUPinD[i], OUTPUT);
      Pi02_Port_Settings_D[i] = bitClear (Pi02_Port_Settings_D[i], 0 );
                    }}
                    
    
      if ((Pi02_Port_Settings_D[i] & 0x01) == 1) {
        pinMode(NodeMCUPinD[i], INPUT_PULLUP);
        Serial.print (F(" is Input with pullup"));
      }
      if ((Pi02_Port_Settings_D[i] & 0x01) == 0) {
        pinMode(NodeMCUPinD[i], OUTPUT);
        Serial.print (F(" Output"));
         }
    
    break;           
  }//end of switch
    if ((Pi02_Port_Settings_D[i]&128)==128) {Serial.print (F(" {flashing} "));}
    //TODO would be good to add more explicit identification of what ports are set to with different channel options etc..
    if (hardset) {Serial.print(F( "(FIXED)"));}
    
          Serial.print (F(" Pi02 PortType :"));
          Serial.print (Pi02_Port_Settings_D[i]);
          Serial.print (F("  Pi03_Setting_options:"));
          Serial.println (Pi03_Setting_options[i]);
    
  }


void PortSetupReport() {
  int i;

if (!bReaderActive) {
    #ifdef  _RFID
        Serial.println("            Reader Absent ....all ports available");
        Serial.println("");
    #endif 
    #ifdef _Audio
       for (int i = 0 ; i <= 9; i++) {   //if audio, show RX/D9 NB port 0 as it has drive limitations (now used as signal led so included)
    #else
       for (int i = 0 ; i <= 8; i++) {   //NB port 0 as it has drive limitations (now used as signal led so included)
    #endif
    
    
      PortMode(i);
    }
  }
  else {
    //only port 4 is user available.
    PortMode(4);
  }
}

//moved here from  subroutines
boolean Debounce (int i) {  //Tests for inputs having changed,
  boolean SwitchSensed;
  SwitchSensed = false ;
  if ((lastButtonState[i] != digitalRead(NodeMCUPinD[i])) && (millis() >= PortTimingDelay[i])) {
    SwitchSensed = true;
    lastButtonState[i] = digitalRead(NodeMCUPinD[i]);
    //DebounceCount[i] =0 ;
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
  value = ((value / 4)); //set the PWM  range 0-1023
  return (value) ;
}

void FLASHING() {
  boolean set;
  for (uint8_t port = 1; port <= 8; port++) {
    set = !(ButtonState[port]); //get phasing right so "no flash" is same high or low state as the non blink state
    if ((Pi02_Port_Settings_D[port] & 193) == 192) { set = !set; }//invert action if "invert", "an output" and "port blink" set ?  
    
      if (((Pi02_Port_Settings_D[port] & 129) == 128)&& (!IsServo(port))) { //make sure its an output '0' and has port blink '128' set! and is NOT a Servo
      if ((set) && (millis() >= PortTimingDelay[port]) && (DelaySetting_for_PortD[port] >= 1)) {
       
        if (IsPWM(port)) {//has 'channel' blink set  if so, use PWM outputs
          if (SDemand[port] == FlashHL(1, port)) {
            SDemand[port] = FlashHL(0, port);
          }
          else {
            SDemand[port] = FlashHL(1, port);
          }
          analogWrite(NodeMCUPinD[port], SDemand[port]);
        }
        else {                                        //its a digital output so just invert current state
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
      //Loco_LOCO_SERVO_Driven_Port.detach();
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
 for (int i = 1 ; i <= 8; i++) { //up to 8 servos..  no check here for loco servo!. 
    if ( (millis() >= ServoOff_Delay_Until[i])  && ( IsServo(i) ) ) { //double check its actually a servo !!, as this is called from two places{
        ServoOff_Delay_Until[i]=millis()+OneDay;  //set one day ahead as a simple way to avoid setting it again next time around... Moving the servo will reset it to millis anyway
      
        Serial.printf("\n Switching OFF Servo:%i ",i);
        //Serial.print(" Switching OFF Servo:");
        //Serial.println(i);
        DetachServo(i);
                                                                                       }
                                  }
             }





void SetServo( int i, uint16_t value) { //uses 0-180
  long MotorSpeed;
  uint16_t SavedValue;
  
  if (IsServo(i)) { //double check, as this is called from two places
    ServoLastPos[i]=value;
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
    }  //switch
   
  
                                   }//double check its a servo 
}//end 

uint16_t servoLR(int state, int port) {
  int value;
  value = 375; //== mid , 90 degrees
  if (state == 0) {
    value = (Pi03_Setting_offposH[port] * 256) + Pi03_Setting_offposL[port];
  }
  if (state == 1) {
    value = (Pi03_Setting_onposH[port] * 256) + Pi03_Setting_onposL[port];
  }
  value = ((value - 150) * 2) / 5; //set the servo immediately range 150-600 = 0 to 180
  return   (value);
}

void SERVOS() {              //attaches and detaches servos, accelerates to demanded positions etc..

  int ServoPositionNow;
  int offset;
  int steps;
  int SERVOSET;
  int set;
  uint32_t LocalTimer;
  int MotorSpeed;
  LocalTimer=millis();
  for (int i = 1 ; i <= 8; i++) { //up to 8 servos.. originally,  _LOCO_SERVO_Driven_Port was just another srvo used here but with different settings  
#ifdef _LOCO_SERVO_Driven_Port    
    if (i!=_LOCO_SERVO_Driven_Port){ //not for loco 
#endif
    if (IsServo(i)) { //only if this port is a "servo"... To address a channel instead of a port the port type servo must be set on the interface tab of switches and outputs
        if (millis() >= (Pi03_Setting_LastUpdated[i] + (Pi03_Setting_options[i] & 15) * 10)) { //do update only at the required delay update rate
                 offset = SDemand[i] - ServoLastPos[i];  //how far from the S_demand are we
                 ServoPositionNow=ServoLastPos[i]; 
    
    if ((abs(offset) <= 3) && ((Pi02_Port_Settings_D[i] & 129) == 128)  && (ButtonState[i] == 1) ) { //REVERSING :changes demand if within 3 of demand and reversing...needs inv to operate on buttonstate, ???as it will not switch off if inv..
//#ifdef _SERVO_DEBUG
//     DebugSprintfMsgSend( sprintf ( DebugMsg, " ( 506) Using Reversing code"));
//#endif
           ServoOff_Delay_Until[i] = LocalTimer + 2000; //keep servo active for at least 2 sec from now, we are a long way from our final position. 
          if (SDemand[i] == servoLR(1, i)) {    SDemand[i] = servoLR(0, i);   }
               else                        {    SDemand[i] = servoLR(1, i);   }
                                   } //end of REVERSING CODE 
     
        if (abs(offset) != 0) {  //we are not at the right position yet....
          ServoOff_Delay_Until[i] = LocalTimer + 2000; //2s sec off timer start but only do if the servo is NOT in the final position, when its in final position, it does NOT update
          if (ButtonState[i]) {   steps = Pi03_Setting_onsteps[i];  }
               else           {   steps = Pi03_Setting_offsteps[i]; }
              
          if (steps == 0)     {   SERVOSET = SDemand[i];
//#ifdef _SERVO_DEBUG
//                           DebugSprintfMsgSend( sprintf ( DebugMsg, "Set Servo Immediately"));
//#endif
                              }
       else {    //steps not == zero
       //if (i!=_LOCO_SERVO_Driven_Port){ //not for loco 
        steps=1; //force steps to 1 to prevent a strange servo behaviour where the servo jitters unstably around the end position.. which does not affect the RC controller for some reason 
       //}
            if (abs(offset) >= abs(steps)) { offset = (offset * steps) / abs(offset);  //offset is now either the error or steps, whichever is less
                                           }                            
            SERVOSET = ServoPositionNow + offset;
            if ((SERVOSET) >= 180) { SERVOSET = 180; }
            if ((SERVOSET) <= 0  ) {  SERVOSET = 0; } //range for servo is 0-180
            }
#ifdef _SERVO_DEBUG
 //NOTE Sending serial messages adds about 200ms delay in the loop !.
 //if (i!=_LOCO_SERVO_Driven_Port){ //not for loco 
//DebugSprintfMsgSend( sprintf ( DebugMsg, "Moving Servo[%d] from current position(%d) to demand:{%d}degrees by moving:%d steps ",i,ServoPositionNow,SDemand[i],offset));
 //}
#endif
          Pi03_Setting_LastUpdated[i] = LocalTimer ;
          SetServo( i, SERVOSET);       

        } //offset != 0
      } //time to do an update
    } //if servo
#ifdef _LOCO_SERVO_Driven_Port    
    } //if not loco
#endif
  } //end i 1..8 loop
}//end servos


