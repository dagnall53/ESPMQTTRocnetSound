

#include "Chuff.h"

  #include "AudioFileSourceSPIFFS.h"
  #include "AudioGeneratorWAV.h"
  #include "AudioOutputMixer.h"
  
#include "Directives.h";
#ifdef _AudioDAC
  #include "AudioOutputI2SDAC.h"
#endif
#ifdef _AudioNoDAC
  #include "AudioOutputI2SNoDAC.h"
  #endif 



AudioGeneratorWAV *wav[2];
AudioFileSourceSPIFFS *file[2];
#ifdef _AudioDAC
  AudioOutputI2SDAC *out;
#endif
 #ifdef _AudioNoDAC
  AudioOutputI2SNoDAC *out;
#endif

AudioOutputMixer *mixer;
AudioOutputMixerStub *stub[2];


int ChuffCycle;  
long LastChuff;
bool WavDoneMsgSent;
bool PlayingSoundEffect;
bool ChuffPlaying;

long SteamOnStarted;
long SteamPulseDuration =50;
long ChuffPeriod;
String LastFilePlayed="--";
String ChuffType; // ="/ch";  //String ChuffType ="/99_H1_";  //alternate chuff sound
uint8_t SoundEffect_Request[3];




extern void DebugSprintfMsgSend(int CX);
extern char DebugMsg[127];
extern uint8_t NodeMCUPinD[12];

extern uint8_t  CV[256];
void SetChuffPeriod(long Setting){
  ChuffPeriod=Setting;
}


void SetChuffPeriodFromSpeed(uint16_t value){
  uint16_t SavedValue;
  uint16_t ChuffPeriod;
 // if changes to motor speed, change chuff period:
            SavedValue=value; // to uint 16t
            ChuffPeriod=4000;  // just to cover div by zero case if not covered later. 
            if (SavedValue<=0){ChuffPeriod=4000;}                 
            else{ChuffPeriod=2590/SavedValue;}      /// Proper calcs below, but you will probably need to play with the value to fit your motor speed settings etc.
            
            SetChuffPeriod(ChuffPeriod);
                                                                    //typically 10mph=259ms quarter chuff rate at 10MPH 
                                                                    // e.g. We have 1609*10 m/hr = 16090/3600 m per second = 4.46 m per second
                                                                    // wheel of 1.4m dia is 4.4 circumference, so we have ~ 1 rotation per second
                                                                    // so with 4 chuffs per rev we get ~250ms "chuffperiod" at 10MPH
DebugSprintfMsgSend( sprintf ( DebugMsg, "Chuff rate set at %d ms for speed %d", ChuffPeriod,value));
  
}

void SetSoundEffect(uint8_t Data1,uint8_t Data2,uint8_t Data3){
  SoundEffect_Request[1]=Data1;
  SoundEffect_Request[2]=Data2;
  SoundEffect_Request[3]=Data3;
}
void SetUpAudio(uint32_t TimeNow){ 
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
  

  WavDoneMsgSent=false;
  ChuffCycle=0;
  LastChuff=TimeNow+4000;
  
 
  PlayingSoundEffect=false;   
  ChuffPlaying=false;
  ChuffPeriod=3000;
 // delay(2000); // allow time for setups..?
  LastFilePlayed="--";
  SoundEffect_Request[1]=0;
  SoundEffect_Request[2]=0;
  SoundEffect_Request[3]=0;
/*//Temporary override sound volumes 
CV[100]=127; // Overall volume control
CV[101]=127; //volume for F1 
CV[102]=127;
CV[103]=127;
CV[104]=127;
CV[105]=127;
CV[106]=127;
CV[107]=127;
CV[108]=127; // Volume for F8

CV[110]=127; // volume for chuffs
CV[111]=127; // volume for Brake Squeal
//
*/  
 bitWrite(SoundEffect_Request[2],0,1); //set F9 is chuffs on initially
 BeginPlayND(0,"/initiated.wav",64);// this wav file will play before anything else, but does not do the file, stub,wav deletes.
 BeginPlayND(1,"/initiated.wav",64);// this wav file will play before anything else.
    Serial.printf("-- Sound System Setup Completed -- \n");
}

void BeginPlay(int Channel,const char *wavfilename, uint8_t CVVolume){
 float Volume;
 Volume=(float)CVVolume*CV[100]/16384;
 
  delete stub[Channel];
  stub[Channel] = mixer->NewInput();
  stub[Channel]->SetGain(Volume);
  
 // if (wav[Channel]->isRunning()) {wav[Channel]->stop();
 //Serial.printf("*audio previous wav stopped\n");
   //                           }
                             
  delete file[Channel]; // housekeeping ?
  file[Channel]= new AudioFileSourceSPIFFS(wavfilename);
   
  delete wav[Channel];
  wav[Channel] = new AudioGeneratorWAV();
  wav[Channel]->begin(file[Channel], stub[Channel]);  
  if (Channel==1){PlayingSoundEffect=true;  // if ch1 works ch 0 will, but we d not need lots of messages for chuffs

  Serial.printf(" CH:");
  Serial.print(Channel);
  Serial.printf("  Playing <");
  Serial.print(wavfilename);  
  Serial.printf("> at volume :");
  Serial.println(Volume);}
}
void BeginPlayND(int Channel,const char *wavfilename, uint8_t CVVolume){ // no deletes version
  uint32_t NOW;
  NOW=micros();
  float Volume;
 Volume=(float)CVVolume*CV[100]/16384;
 
  //delete stub[Channel];
  stub[Channel] = mixer->NewInput();
  stub[Channel]->SetGain(Volume);

 // if (wav[Channel]->isRunning()) {wav[Channel]->stop();
 //Serial.printf("*audio previous wav stopped\n");
   //                           }
                        
  //delete file[Channel]; // housekeeping ?
  file[Channel]= new AudioFileSourceSPIFFS(wavfilename);
  
  //delete wav[Channel];
  wav[Channel] = new AudioGeneratorWAV();
  wav[Channel]->begin(file[Channel], stub[Channel]);  
  PlayingSoundEffect=true;
 
  Serial.printf(" Setting up first play CH:");
  Serial.print(Channel);
  Serial.printf("  Playing <");
  Serial.print(wavfilename);  
  Serial.printf("> at volume :");
  Serial.println(Volume);

}


bool TimeToChuff(uint32_t TimeNow){
  
   if (ChuffPeriod>=2000){return false;} // switches off chuff at very low or stopped speeds
   if (TimeNow<=(LastChuff+ChuffPeriod)){return false;}
    else {LastChuff=TimeNow; return true;}
    }
    

void Chuff (String ChuffChoice){
  String Chuff;
 // if (ChuffPeriod>=60){ChuffChoice="/ch";} // test for switching sound effects with speed this works, but my fast sound clips need work 
 // else{ChuffChoice="/CHF_";} 
  
  ChuffType=ChuffChoice;

  
 //  if (wav[0]>isRunning()) {wav[0]->stop();  delay(1);
 //                          #ifdef _AudioDebug
 //                            // Serial.print-wav -Truncated\n");
 //                             #endif
 //                         }// truncate play
   LastChuff=millis();
  
   #ifdef _LOCO_SERVO_Driven_Port
   #ifdef SteamOutputPin  //steamoutputpin stuff  here for one puff per chuff 
   SteamOnStarted=millis(); digitalWrite (NodeMCUPinD[SteamOutputPin],HIGH); //steamoutputpin stuff  here for one puff per chuff 
   #endif
    if(bitRead(SoundEffect_Request[2],0)==1){ //F9 is chuffs on
   switch (ChuffCycle){ 
                              case 0:Chuff=ChuffType+"1.wav";BeginPlay(0,Chuff.c_str(),CV[110]);ChuffCycle=1;
                              //Stuff here only for strobe use, one per rev to help set chuff rate
                                  //SteamOnStarted=millis(); digitalWrite (NodeMCUPinD[SteamOutputPin],HIGH);
                              break;
                              case 1:Chuff=ChuffType+"2.wav";BeginPlay(0,Chuff.c_str(),CV[110]);ChuffCycle=2;break;
                              case 2:Chuff=ChuffType+"3.wav";BeginPlay(0,Chuff.c_str(),CV[110]);ChuffCycle=3;break;
                              case 3:Chuff=ChuffType+"4.wav";BeginPlay(0,Chuff.c_str(),CV[110]);ChuffCycle=0;break;
}}
#endif
}

void AudioLoop(int32_t TimeNow){
   
 #ifdef SteamOutputPin
              if ((SteamOnStarted+SteamPulseDuration)<=TimeNow){digitalWrite (NodeMCUPinD[SteamOutputPin],LOW);}
 #endif 
   
   if (wav[0]->isRunning()) { 
    if (!wav[0]->loop()) {  Serial.printf("S0\n");wav[0]->stop(); stub[0]->stop();}//    Running[0]=false;Serial.printf("stopping 0\n"); }
  }

  if (wav[1]->isRunning()) {
      if (!wav[1]->loop()) { Serial.printf("S1\n");wav[1]->stop(); stub[1]->stop();PlayingSoundEffect=false;}// Running[1]=false;Serial.printf("stopping 1\n");}
                           }
 }
             
  bool SoundEffectPlaying(void){
    return PlayingSoundEffect;
    }
  void SoundEffects(void) {
          if(bitRead(SoundEffect_Request[1],0)==1){
            if (!PlayingSoundEffect){BeginPlay(1,"/F1.wav",CV[101]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F1"));}
                                       }
          if(bitRead(SoundEffect_Request[1],1)==1){
            if (!PlayingSoundEffect){BeginPlay(1,"/F2.wav",CV[102]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F2"));}
                                       }
           if(bitRead(SoundEffect_Request[1],2)==1){
           if (!PlayingSoundEffect){BeginPlay(1,"/F3.wav",CV[103]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F3"));}
                                       }
          if(bitRead(SoundEffect_Request[1],3)==1){
           if (!PlayingSoundEffect){BeginPlay(1,"/F4.wav",CV[104]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F4"));}
                                       }
           if(bitRead(SoundEffect_Request[1],4)==1){
           if (!PlayingSoundEffect){BeginPlay(1,"/F5.wav",CV[105]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F5"));}
                                       }
           if(bitRead(SoundEffect_Request[1],5)==1){
           if (!PlayingSoundEffect){BeginPlay(1,"/F6.wav",CV[106]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F6"));}
                                       }
           if(bitRead(SoundEffect_Request[1],6)==1){
           if (!PlayingSoundEffect){BeginPlay(1,"/F7.wav",CV[107]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F7"));}
                                       }
           if(bitRead(SoundEffect_Request[1],7)==1){  // this is "F8" on DCC sounds 
           if (!PlayingSoundEffect){BeginPlay(1,"/F8.wav",CV[108]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F8"));}
                                       }                            
        
  }  
 

 

