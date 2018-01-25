#ifndef Chuff_h 
 #define Chuff_h
 
#ifdef _Audio 
  #include <Arduino.h> //needed 
  #define _AudioDebug
//  #include "Globals.h";
  

void SetChuffPeriod(long Setting);
void SetSoundEffect(uint8_t Data1,uint8_t Data2,uint8_t Data3);
void SetUpChuff(uint32_t TimeNow);
void BeginPlay(const char *wavfilename, uint8_t Volume);
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
#endif
