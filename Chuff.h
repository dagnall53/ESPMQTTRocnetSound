#ifndef Chuff_h 
 #define Chuff_h
 

  #include <Arduino.h> //needed 
  #define _AudioDebug
//  #include "Globals.h";
  

void SetChuffPeriod(long Setting);
void SetChuffPeriodFromSpeed(uint16_t value);
//void SetChuffPeriodFromServoPos(uint16_t value);
void SetSoundEffect(uint8_t Data1,uint8_t Data2,uint8_t Data3);
void SetUpAudio(uint32_t TimeNow);
void BeginPlay(int Channel,const char *wavfilename, uint8_t CVVolume);
void BeginPlayND(int Channel,const char *wavfilename, uint8_t CVVolume); // no deletes version
bool TimeToChuff(uint32_t TimeNow);
void Chuff (String ChuffChoice);
void AudioLoop(int32_t TimeNow);
bool SoundEffectPlaying(void);
void SoundEffects(void); 
 

 


/*/ uses RX/d9, D8, and D4 pins.

  static const uint8_t D4   = 2;  and Blue Led on SP8266
  static const uint8_t D5   = 14; for chuff output
  static const uint8_t D8   = 15;
*/
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

#endif
