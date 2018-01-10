#ifndef Chuff_h 
 #define Chuff_h
  #include <Arduino.h> //needed 
  #define _AudioDebug
  #include "AudioFileSourceSPIFFS.h"
  #include "AudioGeneratorWAV.h"
  #include "AudioOutputI2SDAC.h"
 
int ChuffCycle;  
long LastChuff;
bool WavDoneMsgSent;
bool PlayingSoundEffect;
bool ChuffPlaying;

String LastFilePlayed="--";
String ChuffType ="/ch";

//String ChuffType ="/99_H1_";  //alternate chuff sound
AudioGeneratorWAV *wav;
AudioFileSourceSPIFFS *file;
AudioOutputI2SDAC *out;



void SetChuffPeriod(long Setting);
void SetSoundEffect(uint8_t Data1,uint8_t Data2,uint8_t Data3);
void SetUpChuff(void);
void BeginPlay(const char *wavfilename);
bool TimeToChuff(void);
void Chuff (void);
void AudioLoop(int x);
bool SoundEffectPlaying(void);
void SoundEffects(void); 
 

 


/*/ uses RX/d9, D8, and D4 pins.

  static const uint8_t D4   = 2;  and Blue Led on SP8266
  static const uint8_t D5   = 14; for chuff output
  static const uint8_t D8   = 15;
*/

/*expected wav files are:
 Initiate sound:
   /initiated.wav
 
 CHUFFS:
  /ch1.wav
  /ch2.wav
  /ch3.wav
  /ch4.wav
Whistle:
  /whistle.wav
Brake Squeal
  /brakes.wav

*/
void SetChuffPeriod(long Setting){
  ChuffPeriod=Setting;
}
void SetSoundEffect(uint8_t Data1,uint8_t Data2,uint8_t Data3){
  SoundEffect_Request[1]=Data1;
  SoundEffect_Request[2]=Data2;
  SoundEffect_Request[3]=Data3;
}
void SetUpChuff(void){ 
  out = new AudioOutputI2SDAC();out->SetGain(0.5);
  wav = new AudioGeneratorWAV();
  WavDoneMsgSent=false;
  ChuffCycle=0;
  LastChuff=millis()+1000;
  Serial.printf("-- Sound System Initiating -- \n");
  BeginPlay("/initiated.wav");// this wav file will play before anything else.
  //BeginPlay("/Class 4 Guard's Whistle.wav");
  PlayingSoundEffect=true;   
  ChuffPlaying=false;
  ChuffPeriod=1000;
  delay(1); // allow time for setups..
}
/*
Serial.println();
Serial.print("Begin play <");
Serial.print(Filename.substring(0,3));
Serial.print ("> is equal to <");
Serial.print (ChuffType.substring(0,3));
Serial.println(">");
*/

void BeginPlay(const char *wavfilename){
  String Filename;
  Filename=wavfilename;
  WavDoneMsgSent=false;
  if (Filename.substring(0,3)== ChuffType.substring(0,3)){  // playing chuffs 
            PlayingSoundEffect=false;
            ChuffPlaying=true;
            #ifdef _AudioDebug
            //Serial.printf("Chuff");
            #endif
           }
       else {   // need to truncate previous ?? 
        PlayingSoundEffect=true; 
        if (wav->isRunning()) {
                           wav->stop();
                           #ifdef _AudioDebug
                              Serial.printf("*audio previous wav stopped\n");
                           #endif
                  }
        #ifdef _AudioDebug 
       // Serial.println("");
       // Serial.printf("*Audio  last file was:");
       // Serial.print(LastFilePlayed);
        Serial.printf(" Now Playing wav...");
        Serial.println(wavfilename);
        #endif
            }      
            if (LastFilePlayed!="--"){  delete file;    }//housekeeping.. delete last file  
     LastFilePlayed=wavfilename;      
     out->SetGain(0.5); 
     file = new AudioFileSourceSPIFFS(wavfilename);
     wav->begin(file, out);
  }


bool TimeToChuff(void){
  
   if (ChuffPeriod>=2000){return false;} // switches off chuff at very low or stopped speeds
   if (SoundEffectPlaying()){return false;}
   if (millis()<=(LastChuff+ChuffPeriod)){return false;}
    else {LastChuff=millis(); return true;}
    }
    

void Chuff (void){
  String Chuff;
  if (!PlayingSoundEffect){
   if (wav->isRunning()) {wav->stop();  delay(1);
                           #ifdef _AudioDebug
                             // Serial.print-wav -Truncated\n");
                              #endif
                          }// truncate play
   switch (ChuffCycle){ LastChuff=millis();
                              case 0:Chuff=ChuffType+"1.wav";BeginPlay(Chuff.c_str());ChuffCycle=1;break;
                              case 1:Chuff=ChuffType+"2.wav";BeginPlay(Chuff.c_str());ChuffCycle=2;break;
                              case 2:Chuff=ChuffType+"3.wav";BeginPlay(Chuff.c_str());ChuffCycle=3;break;
                              case 3:Chuff=ChuffType+"4.wav";BeginPlay(Chuff.c_str());ChuffCycle=0;break;
}}
}
void AudioLoop(int x){
  if (wav->isRunning()) { if (!wav->loop()) {wav->stop();}//
                        } 
           else {delay(10);PlayingSoundEffect=false;
                  if (!WavDoneMsgSent){
                    //wav->stop();
                     WavDoneMsgSent=true;  
                     #ifdef _AudioDebug
                      Serial.printf(" -WAV done\n"); 
                     #endif
                     }
                 }
                
}
  bool SoundEffectPlaying(void){
    return PlayingSoundEffect;
    }
  void SoundEffects(void) {
          if(bitRead(SoundEffect_Request[1],0)==1){
            if (!PlayingSoundEffect){BeginPlay("/F1.wav");
            DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "sfx-F1"));}
                                       }
          if(bitRead(SoundEffect_Request[1],1)==1){
            if (!PlayingSoundEffect){BeginPlay("/F2.wav");
            DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "sfx-F2"));}
                                       }
           if(bitRead(SoundEffect_Request[1],2)==1){
           if (!PlayingSoundEffect){BeginPlay("/F3.wav");
            DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "sfx-F3"));}
                                       }
          if(bitRead(SoundEffect_Request[1],3)==1){
           if (!PlayingSoundEffect){BeginPlay("/F4.wav");
            DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "sfx-F4"));}
                                       }
           if(bitRead(SoundEffect_Request[1],4)==1){
           if (!PlayingSoundEffect){BeginPlay("/F5.wav");
            DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "sfx-F5"));}
                                       }
           if(bitRead(SoundEffect_Request[1],5)==1){
           if (!PlayingSoundEffect){BeginPlay("/F6.wav");
            DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "sfx-F6"));}
                                       }
           if(bitRead(SoundEffect_Request[1],6)==1){
           if (!PlayingSoundEffect){BeginPlay("/F7.wav");
            DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "sfx-F7"));}
                                       }
           if(bitRead(SoundEffect_Request[1],7)==1){  // this is "F8" on DCC sounds 
           if (!PlayingSoundEffect){BeginPlay("/F8.wav");
            DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "sfx-F8"));}
                                       }                            
        
  }  
 

 
#endif
