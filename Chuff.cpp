
#include "Chuff.h"


#ifdef _Audio                       //see   https://github.com/earlephilhower/ESP8266Audio
  #include "AudioFileSourceSPIFFS.h"      
  #include "AudioGeneratorWAV.h"
  #include "AudioOutputMixer.h"
#endif 


#ifdef _AudioDAC
  #include "AudioOutputI2SDAC.h"
#endif
#ifdef _AudioNoDAC
  #include "AudioOutputI2SNoDAC.h"
  #endif 


#ifdef _Audio
AudioGeneratorWAV *wav[2];
AudioFileSourceSPIFFS *file[2];
AudioOutputMixer *mixer;
AudioOutputMixerStub *stub[2];
#endif

#ifdef _AudioDAC
  AudioOutputI2SDAC *out;
#endif
 #ifdef _AudioNoDAC
  AudioOutputI2SNoDAC *out;
#endif


int ChuffDebugState;

int ChuffCycle;  
long LastChuff;
bool WavDoneMsgSent;
bool PlayingSoundEffect;
bool ChuffPlaying;
int Wavs_Per_Revolution;
int Last_Wavs_Per_Revolution;
long SteamOnStarted;
long SteamPulseDuration =50;
long Chuff_wav_period;
String LastFilePlayed="--";
//String ChuffType; //="/ch";  //String ChuffType ="/99_H1_";  //alternate chuff sound
uint8_t SoundEffect_Request[3];



extern bool POWERON;
extern void DebugSprintfMsgSend(int CX);
extern char DebugMsg[127];
extern uint8_t NodeMCUPinD[12];
extern uint8_t CV[256];
extern uint8_t Last_Speed_demand;
bool ChuffsOn(void) {
  bool ISON;
  ISON=bitRead(SoundEffect_Request[2],0);
  return ISON;
}

void SetChuffPeriod(long Setting, int WavPerRPM ){
  Chuff_wav_period=Setting/WavPerRPM;  // setting is period of one revolution in ms calcs assume a 4 cycle sound effect. New code allows other cyclles
             #ifdef _SERIAL_Audio_DEBUG 
               DebugSprintfMsgSend( sprintf ( DebugMsg, "Chuff_wav_period set %d ms", Chuff_wav_period));
             #endif

}


void SetChuffPeriodFromSpeed(uint16_t value){
  uint16_t Speed;
  uint16_t inv_RPM;

 //if we have a change to motor speed, change chuff inv_RPM!:
            Speed=value; //to uint 16t
            inv_RPM=10360;  // period in ms of a "stopped" just to cover div by zero case its not covered later. 
            if (Speed<=0){inv_RPM=10360; }
            else{     
                 inv_RPM=10360/Speed;}      ///Proper calcs below, but you will probably need to play with the value to fit your wheel etc.
            
             if (inv_RPM<=50){inv_RPM=50;} //sets a minimum chuff inv_RPM
                 SetChuffPeriod(inv_RPM,Wavs_Per_Revolution);
                                                                    //typically 10mph=259ms quarter chuff rate at 10MPH 
                                                                    //typically 10mph=2590 inv_RPM 
                                                                    //e.g. We have 1609*10 m/hr = 16090/3600 m per second = 4.46 m per second
                                                                    //wheel of 1.4m dia is 4.4 circumference, so we have ~ 1 rotation per second
                                                                    //so with 4 chuffs per rev we will get ~250ms "wav Chuff_wav_period" at 10MPH
            #ifdef _SERIAL_Audio_DEBUG 
               DebugSprintfMsgSend( sprintf ( DebugMsg, "Using Inv_RPM %d ms for %d phase sounds at speed %d mph", inv_RPM,Wavs_Per_Revolution,value));
             #endif
}

void SetSoundEffect(uint8_t Data1,uint8_t Data2,uint8_t Data3){
  SoundEffect_Request[1]=Data1;
  SoundEffect_Request[2]=Data2;
  SoundEffect_Request[3]=Data3;
  PlayingSoundEffect=false;   // requesting new play overwrites any playing bool so it will always start a new play
  #ifdef _SERIAL_Audio_DEBUG
           DebugSprintfMsgSend( sprintf ( DebugMsg, " SFX %x %x %x  sounds<%x> ",SoundEffect_Request[1],SoundEffect_Request[2],SoundEffect_Request[3],ChuffsOn()));
  #endif
}
void SetUpAudio(uint32_t TimeNow){ 
#ifdef _Audio
  Serial.printf("-- Sound System Initiating -- \n");
 #ifdef _AudioDAC
  out = new AudioOutputI2SDAC();
   Serial.printf("-- Using I2S DAC -- \n");
  #endif
 #ifdef _AudioNoDAC
  out = new AudioOutputI2SNoDAC(); Serial.printf("-- Using I2S No DAC -- \n");
#endif

  mixer = new AudioOutputMixer(128, out);

  delay(100);
  SteamPulseDuration=5;  //5 for use as strobe
  SteamOnStarted=TimeNow;
  Wavs_Per_Revolution=4; // assume 4 wavs per rpm to start
  Last_Wavs_Per_Revolution=4;
  WavDoneMsgSent=false;
  ChuffCycle=0;
  LastChuff=TimeNow+4000;
  
 
  PlayingSoundEffect=false;   
  ChuffPlaying=false;
  Chuff_wav_period=4000;
 //delay(2000); //allow time for setups..?
  LastFilePlayed="--";
  SoundEffect_Request[1]=0;
  SoundEffect_Request[2]=1;
  SoundEffect_Request[3]=0;
/*//Temporary override sound volumes 
CV[100]=127; //Overall volume control
CV[101]=127; //volume for F1 
CV[102]=127;
CV[103]=127;
CV[104]=127;
CV[105]=127;
CV[106]=127;
CV[107]=127;
CV[108]=127; //Volume for F8

CV[110]=127; //volume for chuffs
CV[111]=127; //volume for Brake Squeal
//
*/  
 bitWrite(SoundEffect_Request[2],0,1); //set F9 is chuffs on initially
 BeginPlayND(0,"/initiated.wav",100);//this wav file will play before anything else, but does not do the file, stub,wav deletes, because nothing should be open yet.
 BeginPlayND(1,"/F3.wav",64);//this wav file will play before anything else.
    Serial.printf("-- Sound System Setup Completed -- \n");
 
    
#endif //_Audio 
}

void BeginPlay(int Channel,const char *wavfilename, uint8_t CVVolume){
#ifdef _Audio
 File TestObj;
  if (!(TestObj= SPIFFS.open(wavfilename,"r"))){ 
        DebugSprintfMsgSend( sprintf ( DebugMsg, " SFX File not found %s",wavfilename));
        malloc(TestObj);  // is this needed 
        ChuffDebugState=9;
        return; 
        }
  malloc(TestObj);

 if (wav[Channel]->isRunning()) {   wav[Channel]->stop();  delay(1);
                      #ifdef _SERIAL_Audio_DEBUG
                       Serial.print(" Truncated to restart");
                      #endif
                     }//truncate 

  
  float Volume;
    Volume=(float)CVVolume*CV[100]/16384;
    
  delete stub[Channel]; //housekeeping ?   
    stub[Channel] = mixer->NewInput();
    stub[Channel]->SetGain(Volume);
                             
  delete file[Channel]; //housekeeping ?   
    file[Channel]= new AudioFileSourceSPIFFS(wavfilename);
   
  delete wav[Channel]; //housekeeping ?   
    wav[Channel] = new AudioGeneratorWAV();
    wav[Channel]->begin(file[Channel], stub[Channel]); 
  
  ChuffDebugState=1; 
  if (Channel==1){PlayingSoundEffect=true;  //if ch1 (SFX) works ch 0 (Chuffs) will, but we do not need lots of debug messages for chuffs
                  Volume=Volume*100; // convert to % just for message
                  DebugSprintfMsgSend( sprintf ( DebugMsg, " Playing SFX file <%s> at %.0f%% volume",wavfilename,Volume));
                 }
#endif
}

void BeginPlayND(int Channel,const char *wavfilename, uint8_t CVVolume){ //no deletes version used at start of playing in startup
#ifdef _Audio
 File TestObj;
  if (!(TestObj= SPIFFS.open(wavfilename,"r"))){ 
        DebugSprintfMsgSend( sprintf ( DebugMsg, " SFX File not found %s",wavfilename));
        malloc(TestObj);  // is this needed ?
        return; 
        }
  malloc(TestObj);



  uint32_t NOW;
  NOW=micros();
  float Volume;
  Volume=(float)CVVolume*CV[100]/16384;
 
  //delete stub[Channel];
  stub[Channel] = mixer->NewInput();
  stub[Channel]->SetGain(Volume);

 //if (wav[Channel]->isRunning()) {wav[Channel]->stop();
 //Serial.printf("*audio previous wav stopped\n");
   //                      }
                        
  //delete file[Channel]; //housekeeping ?
  file[Channel]= new AudioFileSourceSPIFFS(wavfilename);
  
  //delete wav[Channel];
  wav[Channel] = new AudioGeneratorWAV();
  wav[Channel]->begin(file[Channel], stub[Channel]);  
  PlayingSoundEffect=true;
 
  Serial.printf(" Setting up First SFX play CH:");
  Serial.print(Channel);
  Serial.printf("  Playing <");
  Serial.print(wavfilename);  
  Serial.printf("> at volume :");
  Serial.println(Volume);
#endif
}


bool TimeToChuff(uint32_t TimeNow){
   if ((Chuff_wav_period*Wavs_Per_Revolution)>=4000){return false;} //switches off chuff at very low or stopped (2000ms )speeds
   if (TimeNow<=(LastChuff+(Chuff_wav_period))){return false;}
    else {LastChuff=TimeNow; return true;}
    }
    

void Chuff(String ChuffChoice, String ChuffChoiceFast,long ChuffSwitchRPMPeriod){
#if defined (_Audio) && defined (_LOCO_SERVO_Driven_Port)
  String Chuff;
  int INVRPM;
  INVRPM=Chuff_wav_period*Wavs_Per_Revolution;
 if((ChuffsOn())&& (POWERON)){ //F9 is chuffs on
   if (wav[0]->isRunning()) {wav[0]->stop();  delay(1);
                      #ifdef _SERIAL_Audio_DEBUG
                        Serial.print("Chuff -Trunc- ");
                      #endif
                     }//truncate play
   Last_Wavs_Per_Revolution=Wavs_Per_Revolution;
   
   #ifdef SteamOutputPin  //steamoutputpin stuff  here for one puff per wav send 
      SteamOnStarted=millis(); digitalWrite (NodeMCUPinD[SteamOutputPin],HIGH); //steamoutputpin stuff  here for one puff per chuff 
   #endif

   if ((INVRPM)>=ChuffSwitchRPMPeriod){ 
                 Wavs_Per_Revolution=4;
                   if(Last_Wavs_Per_Revolution != Wavs_Per_Revolution){
                        SetChuffPeriodFromSpeed(abs(Last_Speed_demand));   // revise chuff timing
                                            }
                 
                 switch (ChuffCycle){
                              case 0:Chuff=ChuffChoice+"1.wav";BeginPlay(0,Chuff.c_str(),CV[110]);ChuffCycle=1;
                              //Stuff here only for strobe use, one per rev to help set chuff rate
                                  //SteamOnStarted=millis(); digitalWrite (NodeMCUPinD[SteamOutputPin],HIGH);
                              break;
                              case 1:Chuff=ChuffChoice+"2.wav";BeginPlay(0,Chuff.c_str(),CV[110]);ChuffCycle=2;break;
                              case 2:Chuff=ChuffChoice+"3.wav";BeginPlay(0,Chuff.c_str(),CV[110]);ChuffCycle=3;break;
                              case 3:Chuff=ChuffChoice+"4.wav";BeginPlay(0,Chuff.c_str(),CV[110]);ChuffCycle=0;break;
                        }
                }else{
                  Wavs_Per_Revolution=1;
                  if(Last_Wavs_Per_Revolution != Wavs_Per_Revolution){
                        SetChuffPeriodFromSpeed(abs(Last_Speed_demand));   // revise chuff timing
                                            }
                  switch (ChuffCycle){ 
                              case 0:Chuff=ChuffChoiceFast+"4.wav";BeginPlay(0,Chuff.c_str(),CV[110]);ChuffCycle=0; // select which wav phase sound best when running fast, or use a completely separate fast wav file
                              //Stuff here only for strobe use, one per rev to help set chuff rate
                                  //SteamOnStarted=millis(); digitalWrite (NodeMCUPinD[SteamOutputPin],HIGH);
                              break;
                              case 1:Chuff=ChuffChoiceFast+"2.wav";BeginPlay(0,Chuff.c_str(),CV[110]);ChuffCycle=2;break;
                              case 2:Chuff=ChuffChoiceFast+"3.wav";BeginPlay(0,Chuff.c_str(),CV[110]);ChuffCycle=3;break;
                              case 3:Chuff=ChuffChoiceFast+"4.wav";BeginPlay(0,Chuff.c_str(),CV[110]);ChuffCycle=0;break;
                                          }
                      }
                      } // chuffs on

#endif   
}//chuff void

void AudioLoop(int32_t TimeNow){
#ifdef _Audio
   
 #ifdef SteamOutputPin
              if ((SteamOnStarted+SteamPulseDuration)<=TimeNow){digitalWrite (NodeMCUPinD[SteamOutputPin],LOW);}
 #endif 
   
   if (wav[0]->isRunning()) { //ch 0 is chuffs
    if (!wav[0]->loop()) { wav[0]->stop(); stub[0]->stop();//Running[0]=false;Serial.printf("stopping 0\n"); }
                          #ifdef _SERIAL_Audio_DEBUG 
                              Serial.printf("S0\n");
                          #endif
                         }
                        }

  if (wav[1]->isRunning()) {ChuffDebugState=2;
      if (!wav[1]->loop()) { ChuffDebugState=3;
                            wav[1]->stop(); stub[1]->stop();
                            PlayingSoundEffect=false;//Running[1]=false;Serial.printf("stopping 1\n");}
                            #ifdef _SERIAL_Audio_DEBUG
                              Serial.printf("S1\n");
                            #endif
                            }
                           }else {ChuffDebugState=4;
                                 if (PlayingSoundEffect) {PlayingSoundEffect=false;ChuffDebugState=5;
                           #ifdef _SERIAL_Audio_DEBUG
                              Serial.printf("S3\n");
                            #endif
                           }
                            }
 #endif
 }
             
  bool SoundEffectPlaying(void){
    return PlayingSoundEffect;
    }
  void SoundEffects(void) {
 
    if (!PlayingSoundEffect){
          if(bitRead(SoundEffect_Request[1],0)==1){
            BeginPlay(1,"/F1.wav",CV[101]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F1"));}
                                       
          if(bitRead(SoundEffect_Request[1],1)==1){
           BeginPlay(1,"/F2.wav",CV[102]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F2"));
                                       }
           if(bitRead(SoundEffect_Request[1],2)==1){
           BeginPlay(1,"/F3.wav",CV[103]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F3"));
                                       }
          if(bitRead(SoundEffect_Request[1],3)==1){
           BeginPlay(1,"/F4.wav",CV[104]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F4"));
                                       }
           if(bitRead(SoundEffect_Request[1],4)==1){
           BeginPlay(1,"/F5.wav",CV[105]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F5"));
                                       }
           if(bitRead(SoundEffect_Request[1],5)==1){
           BeginPlay(1,"/F6.wav",CV[106]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F6"));
                                       }
           if(bitRead(SoundEffect_Request[1],6)==1){
           BeginPlay(1,"/F7.wav",CV[107]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F7"));
                                       }
           if(bitRead(SoundEffect_Request[1],7)==1){  //this is "F8" on DCC sounds 
           BeginPlay(1,"/F8.wav",CV[108]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F8"));
                                       }                            
    }     
  }  


 

