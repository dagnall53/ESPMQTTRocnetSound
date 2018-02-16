//void MQTTFetch (char* topic, byte* payload, unsigned int Length) ;
uint8_t DIRF = 0 ;

uint8_t LastSetSpeed;
uint32_t PingSendTime;
boolean  PingReflected;

#define NumberOfPorts  8


uint8_t Value_for_PortD[NumberOfPorts + 1]; // ignore [0] so we can have 1...8
uint8_t Pi02_Port_Settings_D[NumberOfPorts + 1];
uint8_t DelaySetting_for_PortD[NumberOfPorts + 1];
uint8_t Configuration_for_PortD[NumberOfPorts + 1];
uint8_t EventMarker_for_PortD[NumberOfPorts + 1];
uint8_t ID_High_for_PortD[NumberOfPorts + 1]; // idh
uint8_t ID_Low_for_PortD[NumberOfPorts + 1]; //idl
uint8_t XRef_Port[NumberOfPorts + 1];
uint8_t Pi03_Setting_offposH[NumberOfPorts + 1];
uint8_t Pi03_Setting_offposL[NumberOfPorts + 1];
uint8_t Pi03_Setting_onposH[NumberOfPorts + 1];
uint8_t Pi03_Setting_onposL[NumberOfPorts + 1];
uint8_t Pi03_Setting_offsteps[NumberOfPorts + 1];
uint8_t Pi03_Setting_onsteps[NumberOfPorts + 1];
uint8_t Pi03_Setting_options[NumberOfPorts + 1];
uint32_t Pi03_Setting_LastUpdated[NumberOfPorts + 1];


extern void SERVOS(void);
extern uint16_t servoLR(int state, int port);
extern int FlashHL(int state, int port);
uint8_t Speed_demand ;
uint8_t Last_Speed_demand;

#define Recipient_Addr  1   //  use with SetWordIn_msg_loc_value(sendMessage,Recipient_Addr,data  , or get sender or recipient addr  
#define Sender_Addr 3       //  use with SetWordIn_msg_loc_value(sendMessage,Sender_Addr,data   
#define Code_Request 0<<5
#define Code_Event   1<<5
#define Code_Reply   2<<5


uint8_t ROC_netid;
uint16_t ROC_recipient;
uint16_t ROC_sender;
uint8_t  ROC_group;
uint8_t  ROC_code;
uint8_t ROC_len;
uint8_t ROC_Data[200];
uint8_t ROC_OUT_DATA[200];
uint16_t RocNodeID;




void SetDefaultSVs(){

 

//rocnode
  //port and channel defaults
  for (int i=1; i<=NumberOfPorts; i++) {
    Value_for_PortD[i]=1;

    
Pi02_Port_Settings_D[i]=0; //0= out 1= in
DelaySetting_for_PortD[i]=0;//10ms units, max. 255 * 10.
Configuration_for_PortD[i]=1;
EventMarker_for_PortD[i]=0;
ID_High_for_PortD[i]=0;  // idh
ID_Low_for_PortD[i]=0;  //idl
XRef_Port[i]=0;
Pi03_Setting_offposH[i]=0; 
Pi03_Setting_offposL[i]=160; 
Pi03_Setting_onposH[i]=2;  
Pi03_Setting_onposL[i]=88;  
Pi03_Setting_offsteps[i]=1;  
Pi03_Setting_onsteps[i]=1; 
Pi03_Setting_options[i]=0;
Pi03_Setting_LastUpdated[i]=0;
  }

  
#ifndef _LOCO_SERVO_Driven_Port {  
 // a set of defaults derived from a saved emprom set...for a station
 // This set sets 1-4 as pwm outputs 
 //     ( BUT use only 1 and 2 with the motor board for lights (to gnd) on outputs 2 and 4 due to strange DebugMsg logic in motor driver)
 // 5 AND 6 are sensor inputs for using with hall switches
 // 7 and 8 are servo outputs for points.
 
 Value_for_PortD[1]=0;
 Pi02_Port_Settings_D[1]=0;
 DelaySetting_for_PortD[1]=0;
 Configuration_for_PortD[1]=1;
 EventMarker_for_PortD[1]=0;
 ID_High_for_PortD[1]=0;
 ID_Low_for_PortD[1]=0;
 XRef_Port[1]=0;
 Pi03_Setting_offposH[1]=0;
 Pi03_Setting_offposL[1]=0;
 Pi03_Setting_onposH[1]=9;
 Pi03_Setting_onposL[1]=227;
 Pi03_Setting_offsteps[1]=1;
 Pi03_Setting_onsteps[1]=1;
 Pi03_Setting_options[1]=128;
 Pi03_Setting_LastUpdated[1]=6184;
 Value_for_PortD[2]=0;
 Pi02_Port_Settings_D[2]=0;
 DelaySetting_for_PortD[2]=0;
 Configuration_for_PortD[2]=1;
 EventMarker_for_PortD[2]=0;
 ID_High_for_PortD[2]=0;
 ID_Low_for_PortD[2]=0;
 XRef_Port[2]=0;
 Pi03_Setting_offposH[2]=0;
 Pi03_Setting_offposL[2]=0;
 Pi03_Setting_onposH[2]=7;
 Pi03_Setting_onposL[2]=181;
 Pi03_Setting_offsteps[2]=1;
 Pi03_Setting_onsteps[2]=1;
 Pi03_Setting_options[2]=128;
 Pi03_Setting_LastUpdated[2]=6184;
 Value_for_PortD[3]=0;
 Pi02_Port_Settings_D[3]=0;
 DelaySetting_for_PortD[3]=0;
 Configuration_for_PortD[3]=1;
 EventMarker_for_PortD[3]=0;
 ID_High_for_PortD[3]=0;
 ID_Low_for_PortD[3]=0;
 XRef_Port[3]=0;
 Pi03_Setting_offposH[3]=0;
 Pi03_Setting_offposL[3]=0;
 Pi03_Setting_onposH[3]=15;
 Pi03_Setting_onposL[3]=255;
 Pi03_Setting_offsteps[3]=1;
 Pi03_Setting_onsteps[3]=1;
 Pi03_Setting_options[3]=128;
 Pi03_Setting_LastUpdated[3]=6184;
 Value_for_PortD[4]=0;
 Pi02_Port_Settings_D[4]=0;
 DelaySetting_for_PortD[4]=0;
 Configuration_for_PortD[4]=1;
 EventMarker_for_PortD[4]=0;
 ID_High_for_PortD[4]=0;
 ID_Low_for_PortD[4]=0;
 XRef_Port[4]=0;
 Pi03_Setting_offposH[4]=0;
 Pi03_Setting_offposL[4]=0;
 Pi03_Setting_onposH[4]=15;
 Pi03_Setting_onposL[4]=255;
 Pi03_Setting_offsteps[4]=1;
 Pi03_Setting_onsteps[4]=1;
 Pi03_Setting_options[4]=128;
 Pi03_Setting_LastUpdated[4]=6184;
 Value_for_PortD[5]=0;
 Pi02_Port_Settings_D[5]=65;
 DelaySetting_for_PortD[5]=0;
 Configuration_for_PortD[5]=1;
 EventMarker_for_PortD[5]=0;
 ID_High_for_PortD[5]=0;
 ID_Low_for_PortD[5]=0;
 XRef_Port[5]=0;
 Pi03_Setting_offposH[5]=0;
 Pi03_Setting_offposL[5]=160;
 Pi03_Setting_onposH[5]=2;
 Pi03_Setting_onposL[5]=88;
 Pi03_Setting_offsteps[5]=1;
 Pi03_Setting_onsteps[5]=1;
 Pi03_Setting_options[5]=0;
 Pi03_Setting_LastUpdated[5]=6184;
 Value_for_PortD[6]=0;
 Pi02_Port_Settings_D[6]=65;
 DelaySetting_for_PortD[6]=0;
 Configuration_for_PortD[6]=1;
 EventMarker_for_PortD[6]=0;
 ID_High_for_PortD[6]=0;
 ID_Low_for_PortD[6]=0;
 XRef_Port[6]=0;
 Pi03_Setting_offposH[6]=0;
 Pi03_Setting_offposL[6]=160;
 Pi03_Setting_onposH[6]=2;
 Pi03_Setting_onposL[6]=88;
 Pi03_Setting_offsteps[6]=1;
 Pi03_Setting_onsteps[6]=1;
 Pi03_Setting_options[6]=0;
 Pi03_Setting_LastUpdated[6]=6184;
 Value_for_PortD[7]=0;
 Pi02_Port_Settings_D[7]=0;
 DelaySetting_for_PortD[7]=0;
 Configuration_for_PortD[7]=1;
 EventMarker_for_PortD[7]=0;
 ID_High_for_PortD[7]=0;
 ID_Low_for_PortD[7]=0;
 XRef_Port[7]=0;
 Pi03_Setting_offposH[7]=1;
 Pi03_Setting_offposL[7]=4;
 Pi03_Setting_onposH[7]=1;
 Pi03_Setting_onposL[7]=197;
 Pi03_Setting_offsteps[7]=1;
 Pi03_Setting_onsteps[7]=1;
 Pi03_Setting_options[7]=34;
 Pi03_Setting_LastUpdated[7]=8131;
 Value_for_PortD[8]=0;
 Pi02_Port_Settings_D[8]=0;
 DelaySetting_for_PortD[8]=0;
 Configuration_for_PortD[8]=1;
 EventMarker_for_PortD[8]=0;
 ID_High_for_PortD[8]=0;
 ID_Low_for_PortD[8]=0;
 XRef_Port[8]=0;
 Pi03_Setting_offposH[8]=0;
 Pi03_Setting_offposL[8]=236;
 Pi03_Setting_onposH[8]=1;
 Pi03_Setting_onposL[8]=201;
 Pi03_Setting_offsteps[8]=1;
 Pi03_Setting_onsteps[8]=1;
 Pi03_Setting_options[8]=34;
 Pi03_Setting_LastUpdated[8]=6184;

 CV[1]=3; //DEFAULT ADDR
 CV[47]=131; //(send serial and MQTT debug messages, have d4 flash at the loop rate (shows if something stops....)
 CV[2]=10; //V START
 CV[3]=5; //ACC
 CV[4]=5;  // DEC RATE
 CV[5]=100;  // HIGH SPEED
 CV[6]=50;  // MID but not used at the moment
#endif 
    
// end of defaults for station

#ifdef _LOCO_SERVO_Driven_Port

// This set is for a Loco (dcc address 3) with Audio
 // ------Current EEPROM Settings----------
 Value_for_PortD[1]=0;
 Pi02_Port_Settings_D[1]=0;
 DelaySetting_for_PortD[1]=0;
 Configuration_for_PortD[1]=1;
 EventMarker_for_PortD[1]=0;
 ID_High_for_PortD[1]=0;
 ID_Low_for_PortD[1]=0;
 XRef_Port[1]=0;
 Pi03_Setting_offposH[1]=1;
 Pi03_Setting_offposL[1]=145;
 Pi03_Setting_onposH[1]=1;
 Pi03_Setting_onposL[1]=145;
 Pi03_Setting_offsteps[1]=0;
 Pi03_Setting_onsteps[1]=0;
 Pi03_Setting_options[1]=42;
 Pi03_Setting_LastUpdated[1]=18054;
 Value_for_PortD[2]=0;
 Pi02_Port_Settings_D[2]=0;
 DelaySetting_for_PortD[2]=0;
 Configuration_for_PortD[2]=1;
 EventMarker_for_PortD[2]=0;
 ID_High_for_PortD[2]=0;
 ID_Low_for_PortD[2]=0;
 XRef_Port[2]=0;
 Pi03_Setting_offposH[2]=0;
 Pi03_Setting_offposL[2]=0;
 Pi03_Setting_onposH[2]=7;
 Pi03_Setting_onposL[2]=181;
 Pi03_Setting_offsteps[2]=1;
 Pi03_Setting_onsteps[2]=1;
 Pi03_Setting_options[2]=0;
 Pi03_Setting_LastUpdated[2]=18054;
 Value_for_PortD[3]=0;
 Pi02_Port_Settings_D[3]=0;
 DelaySetting_for_PortD[3]=0;
 Configuration_for_PortD[3]=1;
 EventMarker_for_PortD[3]=0;
 ID_High_for_PortD[3]=0;
 ID_Low_for_PortD[3]=0;
 XRef_Port[3]=0;
 Pi03_Setting_offposH[3]=0;
 Pi03_Setting_offposL[3]=0;
 Pi03_Setting_onposH[3]=15;
 Pi03_Setting_onposL[3]=255;
 Pi03_Setting_offsteps[3]=1;
 Pi03_Setting_onsteps[3]=1;
 Pi03_Setting_options[3]=0;
 Pi03_Setting_LastUpdated[3]=18054;
 Value_for_PortD[4]=0;
 Pi02_Port_Settings_D[4]=0;
 DelaySetting_for_PortD[4]=0;
 Configuration_for_PortD[4]=1;
 EventMarker_for_PortD[4]=0;
 ID_High_for_PortD[4]=0;
 ID_Low_for_PortD[4]=0;
 XRef_Port[4]=0;
 Pi03_Setting_offposH[4]=0;
 Pi03_Setting_offposL[4]=0;
 Pi03_Setting_onposH[4]=15;
 Pi03_Setting_onposL[4]=255;
 Pi03_Setting_offsteps[4]=1;
 Pi03_Setting_onsteps[4]=1;
 Pi03_Setting_options[4]=0;
 Pi03_Setting_LastUpdated[4]=18054;
 Value_for_PortD[5]=0;
 Pi02_Port_Settings_D[5]=0;
 DelaySetting_for_PortD[5]=0;
 Configuration_for_PortD[5]=1;
 EventMarker_for_PortD[5]=0;
 ID_High_for_PortD[5]=0;
 ID_Low_for_PortD[5]=0;
 XRef_Port[5]=0;
 Pi03_Setting_offposH[5]=0;
 Pi03_Setting_offposL[5]=160;
 Pi03_Setting_onposH[5]=2;
 Pi03_Setting_onposL[5]=88;
 Pi03_Setting_offsteps[5]=1;
 Pi03_Setting_onsteps[5]=1;
 Pi03_Setting_options[5]=0;
 Pi03_Setting_LastUpdated[5]=18054;
 Value_for_PortD[6]=0;
 Pi02_Port_Settings_D[6]=0;
 DelaySetting_for_PortD[6]=10;
 Configuration_for_PortD[6]=1;
 EventMarker_for_PortD[6]=0;
 ID_High_for_PortD[6]=0;
 ID_Low_for_PortD[6]=0;
 XRef_Port[6]=0;
 Pi03_Setting_offposH[6]=0;
 Pi03_Setting_offposL[6]=160;
 Pi03_Setting_onposH[6]=3;
 Pi03_Setting_onposL[6]=232;
 Pi03_Setting_offsteps[6]=1;
 Pi03_Setting_onsteps[6]=1;
 Pi03_Setting_options[6]=128;
 Pi03_Setting_LastUpdated[6]=18054;
 Value_for_PortD[7]=0;
 Pi02_Port_Settings_D[7]=0;
 DelaySetting_for_PortD[7]=0;
 Configuration_for_PortD[7]=1;
 EventMarker_for_PortD[7]=0;
 ID_High_for_PortD[7]=0;
 ID_Low_for_PortD[7]=0;
 XRef_Port[7]=0;
 Pi03_Setting_offposH[7]=1;
 Pi03_Setting_offposL[7]=4;
 Pi03_Setting_onposH[7]=14;
 Pi03_Setting_onposL[7]=176;
 Pi03_Setting_offsteps[7]=1;
 Pi03_Setting_onsteps[7]=1;
 Pi03_Setting_options[7]=128;
 Pi03_Setting_LastUpdated[7]=18054;
 Value_for_PortD[8]=0;
 Pi02_Port_Settings_D[8]=0;
 DelaySetting_for_PortD[8]=0;
 Configuration_for_PortD[8]=1;
 EventMarker_for_PortD[8]=0;
 ID_High_for_PortD[8]=0;
 ID_Low_for_PortD[8]=0;
 XRef_Port[8]=0;
 Pi03_Setting_offposH[8]=0;
 Pi03_Setting_offposL[8]=236;
 Pi03_Setting_onposH[8]=1;
 Pi03_Setting_onposL[8]=201;
 Pi03_Setting_offsteps[8]=1;
 Pi03_Setting_onsteps[8]=1;
 Pi03_Setting_options[8]=0;
 Pi03_Setting_LastUpdated[8]=18054;
 // RN and CV settings
 RN[0]=0;
 CV[0]=0;
 RN[1]=0;
 CV[1]=3;
 RN[2]=2;
 CV[2]=5;
 RN[3]=5;
 CV[3]=3;
 RN[4]=97;
 CV[4]=3;
 RN[5]=117;
 CV[5]=80;
 RN[6]=100;
 CV[6]=50;
 RN[7]=105;
 CV[7]=3;
 RN[8]=111;
 CV[8]=13;
 RN[9]=0;
 CV[9]=0;
 RN[10]=0;
 CV[10]=0;
 RN[11]=0;
 CV[11]=0;
 RN[12]=0;
 CV[12]=0;
 RN[13]=0;
 CV[13]=0;
 RN[14]=18;
 CV[14]=0;
 RN[15]=33;
 CV[15]=0;
 RN[16]=0;
 CV[16]=0;
 RN[17]=0;
 CV[17]=0;
 RN[18]=0;
 CV[18]=0;
 RN[19]=0;
 CV[19]=0;
 RN[20]=1;
 CV[20]=0;
 RN[21]=0;
 CV[21]=0;
 RN[22]=0;
 CV[22]=0;
 RN[23]=0;
 CV[23]=0;
 RN[24]=0;
 CV[24]=0;
 RN[25]=0;
 CV[25]=0;
 RN[26]=0;
 CV[26]=0;
 RN[27]=0;
 CV[27]=0;
 RN[28]=0;
 CV[28]=0;
 RN[29]=0;
 CV[29]=0;
 RN[30]=0;
 CV[30]=0;
 RN[31]=0;
 CV[31]=0;
 RN[32]=0;
 CV[32]=0;
 RN[33]=0;
 CV[33]=0;
 RN[34]=0;
 CV[34]=0;
 RN[35]=0;
 CV[35]=0;
 RN[36]=0;
 CV[36]=0;
 RN[37]=0;
 CV[37]=0;
 RN[38]=0;
 CV[38]=0;
 RN[39]=0;
 CV[39]=0;
 RN[40]=0;
 CV[40]=0;
 RN[41]=0;
 CV[41]=0;
 RN[42]=0;
 CV[42]=0;
 RN[43]=0;
 CV[43]=0;
 RN[44]=0;
 CV[44]=0;
 RN[45]=0;
 CV[45]=0;
 RN[46]=10;
 CV[46]=0;
 RN[47]=0;
 CV[47]=131;
 RN[48]=0;
 CV[48]=0;
 RN[49]=0;
 CV[49]=0;
 RN[50]=0;
 CV[50]=0;
 RN[51]=1;
 CV[51]=0;
 RN[52]=1;
 CV[52]=0;
 RN[53]=1;
 CV[53]=0;
 RN[54]=1;
 CV[54]=0;
 RN[55]=1;
 CV[55]=0;
 RN[56]=1;
 CV[56]=0;
 RN[57]=1;
 CV[57]=0;
 RN[58]=1;
 CV[58]=0;
 RN[59]=0;
 CV[59]=0;
 RN[60]=0;
 CV[60]=0;
 RN[61]=0;
 CV[61]=0;
 RN[62]=0;
 CV[62]=0;
 RN[63]=0;
 CV[63]=0;
 RN[64]=0;
 CV[64]=0;
 RN[65]=0;
 CV[65]=0;
 RN[66]=0;
 CV[66]=0;
 RN[67]=0;
 CV[67]=0;
 RN[68]=0;
 CV[68]=0;
 RN[69]=0;
 CV[69]=0;
 RN[70]=0;
 CV[70]=0;
 RN[71]=0;
 CV[71]=0;
 RN[72]=0;
 CV[72]=0;
 RN[73]=0;
 CV[73]=0;
 RN[74]=0;
 CV[74]=0;
 RN[75]=0;
 CV[75]=0;
 RN[76]=0;
 CV[76]=0;
 RN[77]=0;
 CV[77]=0;
 RN[78]=0;
 CV[78]=0;
 RN[79]=0;
 CV[79]=0;
 RN[80]=0;
 CV[80]=0;
 RN[81]=0;
 CV[81]=0;
 RN[82]=0;
 CV[82]=0;
 RN[83]=0;
 CV[83]=0;
 RN[84]=0;
 CV[84]=0;
 RN[85]=0;
 CV[85]=0;
 RN[86]=0;
 CV[86]=0;
 RN[87]=0;
 CV[87]=0;
 RN[88]=0;
 CV[88]=0;
 RN[89]=0;
 CV[89]=0;
 RN[90]=0;
 CV[90]=0;
 RN[91]=0;
 CV[91]=0;
 RN[92]=0;
 CV[92]=0;
 RN[93]=0;
 CV[93]=0;
 RN[94]=0;
 CV[94]=0;
 RN[95]=0;
 CV[95]=0;
 RN[96]=0;
 CV[96]=0;
 RN[97]=0;
 CV[97]=0;
 RN[98]=0;
 CV[98]=0;
 RN[99]=0;
 CV[99]=0;
 RN[100]=0;
 CV[100]=127;
 RN[101]=1;
 CV[101]=127;
 RN[102]=0;
 CV[102]=127;
 RN[103]=0;
 CV[103]=127;
 RN[104]=0;
 CV[104]=127;
 RN[105]=0;
 CV[105]=127;
 RN[106]=0;
 CV[106]=127;
 RN[107]=1;
 CV[107]=127;
 RN[108]=0;
 CV[108]=127;
 RN[109]=0;
 CV[109]=127;
 RN[110]=0;
 CV[110]=127;
 RN[111]=145;
 CV[111]=127;
 RN[112]=0;
 CV[112]=127;
 RN[113]=0;
 CV[113]=127;
 RN[114]=0;
 CV[114]=127;
 RN[115]=160;
 CV[115]=127;
 RN[116]=160;
 CV[116]=0;
 RN[117]=4;
 CV[117]=0;
 RN[118]=236;
 CV[118]=0;
 RN[119]=0;
 CV[119]=0;
 RN[120]=0;
 CV[120]=0;
 RN[121]=1;
 CV[121]=0;
 RN[122]=7;
 CV[122]=0;
 RN[123]=15;
 CV[123]=0;
 RN[124]=15;
 CV[124]=0;
 RN[125]=2;
 CV[125]=0;
 RN[126]=3;
 CV[126]=0;
 RN[127]=14;
 CV[127]=0;
 RN[128]=1;
 CV[128]=0;
 RN[129]=0;
 CV[129]=0;
 RN[130]=0;
 CV[130]=0;
 RN[131]=145;
 CV[131]=0;
 RN[132]=181;
 CV[132]=0;
 RN[133]=255;
 CV[133]=0;
 RN[134]=255;
 CV[134]=0;
 RN[135]=88;
 CV[135]=0;
 RN[136]=232;
 CV[136]=0;
 RN[137]=176;
 CV[137]=0;
 RN[138]=201;
 CV[138]=0;
 RN[139]=0;
 CV[139]=0;
 RN[140]=0;
 CV[140]=0;
 RN[141]=0;
 CV[141]=0;
 RN[142]=1;
 CV[142]=0;
 RN[143]=1;
 CV[143]=0;
 RN[144]=1;
 CV[144]=0;
 RN[145]=1;
 CV[145]=0;
 RN[146]=1;
 CV[146]=0;
 RN[147]=1;
 CV[147]=0;
 RN[148]=1;
 CV[148]=0;
 RN[149]=0;
 CV[149]=0;
 RN[150]=0;
 CV[150]=0;
 RN[151]=0;
 CV[151]=0;
 RN[152]=1;
 CV[152]=0;
 RN[153]=1;
 CV[153]=0;
 RN[154]=1;
 CV[154]=0;
 RN[155]=1;
 CV[155]=0;
 RN[156]=1;
 CV[156]=0;
 RN[157]=1;
 CV[157]=0;
 RN[158]=1;
 CV[158]=0;
 RN[159]=0;
 CV[159]=0;
 RN[160]=0;
 CV[160]=0;
 RN[161]=42;
 CV[161]=0;
 RN[162]=0;
 CV[162]=0;
 RN[163]=0;
 CV[163]=0;
 RN[164]=0;
 CV[164]=0;
 RN[165]=0;
 CV[165]=0;
 RN[166]=128;
 CV[166]=0;
 RN[167]=128;
 CV[167]=0;
 RN[168]=32;
 CV[168]=0;
 RN[169]=0;
 CV[169]=0;
 RN[170]=0;
 CV[170]=0;
 RN[171]=0;
 CV[171]=0;
 RN[172]=0;
 CV[172]=0;
 RN[173]=0;
 CV[173]=0;
 RN[174]=0;
 CV[174]=0;
 RN[175]=0;
 CV[175]=0;
 RN[176]=0;
 CV[176]=0;
 RN[177]=0;
 CV[177]=0;
 RN[178]=0;
 CV[178]=0;
 RN[179]=0;
 CV[179]=0;
 RN[180]=0;
 CV[180]=0;
 RN[181]=0;
 CV[181]=0;
 RN[182]=0;
 CV[182]=0;
 RN[183]=0;
 CV[183]=0;
 RN[184]=0;
 CV[184]=0;
 RN[185]=0;
 CV[185]=0;
 RN[186]=0;
 CV[186]=0;
 RN[187]=0;
 CV[187]=0;
 RN[188]=0;
 CV[188]=0;
 RN[189]=0;
 CV[189]=0;
 RN[190]=0;
 CV[190]=0;
 RN[191]=0;
 CV[191]=0;
 RN[192]=0;
 CV[192]=0;
 RN[193]=0;
 CV[193]=0;
 RN[194]=0;
 CV[194]=0;
 RN[195]=0;
 CV[195]=0;
 RN[196]=0;
 CV[196]=0;
 RN[197]=0;
 CV[197]=0;
 RN[198]=0;
 CV[198]=0;
 RN[199]=0;
 CV[199]=0;
 RN[200]=0;
 CV[200]=0;
 RN[201]=0;
 CV[201]=0;
 RN[202]=0;
 CV[202]=0;
 RN[203]=0;
 CV[203]=0;
 RN[204]=0;
 CV[204]=0;
 RN[205]=0;
 CV[205]=0;
 RN[206]=0;
 CV[206]=0;
 RN[207]=0;
 CV[207]=0;
 RN[208]=0;
 CV[208]=0;
 RN[209]=0;
 CV[209]=0;
 RN[210]=0;
 CV[210]=0;
 RN[211]=0;
 CV[211]=0;
 RN[212]=0;
 CV[212]=0;
 RN[213]=0;
 CV[213]=0;
 RN[214]=0;
 CV[214]=0;
 RN[215]=0;
 CV[215]=0;
 RN[216]=0;
 CV[216]=0;
 RN[217]=0;
 CV[217]=0;
 RN[218]=0;
 CV[218]=0;
 RN[219]=0;
 CV[219]=0;
 RN[220]=0;
 CV[220]=0;
 RN[221]=0;
 CV[221]=0;
 RN[222]=0;
 CV[222]=0;
 RN[223]=0;
 CV[223]=0;
 RN[224]=0;
 CV[224]=0;
 RN[225]=0;
 CV[225]=0;
 RN[226]=0;
 CV[226]=0;
 RN[227]=0;
 CV[227]=0;
 RN[228]=0;
 CV[228]=0;
 RN[229]=0;
 CV[229]=0;
 RN[230]=0;
 CV[230]=0;
 RN[231]=0;
 CV[231]=0;
 RN[232]=0;
 CV[232]=0;
 RN[233]=0;
 CV[233]=0;
 RN[234]=0;
 CV[234]=0;
 RN[235]=0;
 CV[235]=0;
 RN[236]=0;
 CV[236]=0;
 RN[237]=0;
 CV[237]=0;
 RN[238]=0;
 CV[238]=0;
 RN[239]=0;
 CV[239]=0;
 RN[240]=0;
 CV[240]=0;
 RN[241]=0;
 CV[241]=0;
 RN[242]=0;
 CV[242]=0;
 RN[243]=0;
 CV[243]=0;
 RN[244]=0;
 CV[244]=0;
 RN[245]=0;
 CV[245]=0;
 RN[246]=0;
 CV[246]=0;
 RN[247]=0;
 CV[247]=0;
 RN[248]=0;
 CV[248]=0;
 RN[249]=0;
 CV[249]=0;
 RN[250]=0;
 CV[250]=0;
 RN[251]=0;
 CV[251]=0;
 RN[252]=0;
 CV[252]=0;
 RN[253]=0;
 CV[253]=0;
 RN[254]=0;
 CV[254]=0;
 RN[255]=0;
 CV[255]=0;
// end of saved set of values 
#endif






 
}

 uint16_t Get_ROCNodeID(){
  return  RocNodeID;
 }
 
String NICKname(){
return Nickname;
}

void WriteEEPROM() {
  RN[14] = mosquitto[3];
#ifdef _DefaultPrintOut 
  // code to serial print eprom settings in a form that can be used in SetDefaultSVs() 
    
  Serial.println(" ------Current EEPROM Settings----------");
    
  for (int i = 1; i <= NumberOfPorts; i++) {
     
    
Serial.print(" Value_for_PortD[");
Serial.print(i);
Serial.print("]=");
Serial.print(Value_for_PortD[i]);Serial.println(";");
Serial.print(" Pi02_Port_Settings_D[");
Serial.print(i);
Serial.print("]=");
Serial.print(Pi02_Port_Settings_D[i]);Serial.println(";");
Serial.print(" DelaySetting_for_PortD[");
Serial.print(i);
Serial.print("]=");
Serial.print(DelaySetting_for_PortD[i]);  Serial.println(";");  
Serial.print(" Configuration_for_PortD[");
Serial.print(i);
Serial.print("]=");
Serial.print(Configuration_for_PortD[i]);Serial.println(";");
Serial.print(" EventMarker_for_PortD[");
Serial.print(i);
Serial.print("]=");
Serial.print(EventMarker_for_PortD[i]);Serial.println(";");
Serial.print(" ID_High_for_PortD[");
Serial.print(i);
Serial.print("]=");
Serial.print(ID_High_for_PortD[i]);Serial.println(";");
Serial.print(" ID_Low_for_PortD[");
Serial.print(i);
Serial.print("]=");
Serial.print(ID_Low_for_PortD[i]);Serial.println(";");
Serial.print(" XRef_Port[");
Serial.print(i);
Serial.print("]=");
Serial.print(XRef_Port[i]);Serial.println(";");
Serial.print(" Pi03_Setting_offposH[");
Serial.print(i);
Serial.print("]=");
Serial.print(Pi03_Setting_offposH[i]);Serial.println(";");
Serial.print(" Pi03_Setting_offposL[");
Serial.print(i);
Serial.print("]=");
Serial.print(Pi03_Setting_offposL[i]);Serial.println(";");
Serial.print(" Pi03_Setting_onposH[");
Serial.print(i);
Serial.print("]=");
Serial.print(Pi03_Setting_onposH[i]);Serial.println(";");
Serial.print(" Pi03_Setting_onposL[");
Serial.print(i);
Serial.print("]=");
Serial.print(Pi03_Setting_onposL[i]);Serial.println(";");
Serial.print(" Pi03_Setting_offsteps[");
Serial.print(i);
Serial.print("]=");
Serial.print(Pi03_Setting_offsteps[i]);Serial.println(";");
Serial.print(" Pi03_Setting_onsteps[");
Serial.print(i);
Serial.print("]=");
Serial.print(Pi03_Setting_onsteps[i]);Serial.println(";");
Serial.print(" Pi03_Setting_options[");
Serial.print(i);
Serial.print("]=");
Serial.print(Pi03_Setting_options[i]);Serial.println(";");
Serial.print(" Pi03_Setting_LastUpdated[");
Serial.print(i);
Serial.print("]=");
Serial.print(Pi03_Setting_LastUpdated[i]);Serial.println(";");
    }
Serial.println(" // RN and CV settings");
for (int i = 0; i <= 255 ; i++) {
  Serial.print(" RN[");
Serial.print(i);
Serial.print("]=");
Serial.print(RN[i]);Serial.println(";");
Serial.print(" CV[");
Serial.print(i);
Serial.print("]=");
Serial.print(CV[i]);Serial.println(";");
   
  }
    
Serial.println("// end of defaults ");

#endif
// need list of what RN[0 to 19 are...

//


  
  for (int i = 1; i <= NumberOfPorts; i++) {
    RN[20 + i] = Value_for_PortD[i];
    RN[30 + i] = Pi02_Port_Settings_D[i];
    RN[40 + i] = DelaySetting_for_PortD[i];
    RN[50 + i] = Configuration_for_PortD[i];
    RN[60 + i] = EventMarker_for_PortD[i];
    RN[70 + i] = ID_High_for_PortD[i]; // idh
    RN[80 + i] = ID_Low_for_PortD[i]; //idl
    RN[90 + i] = XRef_Port[i];

    RN[100 + i] = Pi03_Setting_offposH[i];
    RN[110 + i] = Pi03_Setting_offposL[i];
    RN[120 + i] = Pi03_Setting_onposH[i];
    RN[130 + i] = Pi03_Setting_onposL[i];
    RN[140 + i] = Pi03_Setting_offsteps[i];
    RN[150 + i] = Pi03_Setting_onsteps[i];
    RN[160 + i] = Pi03_Setting_options[i];
  }

  SetWordIn_msg_loc_value(RN, 1, RocNodeID);

    Serial.println("");//
    Serial.println(" EEProm writing ");//

  for (int i = 0; i <= 255 ; i++) {
    EEPROM.write(i, RN[i]);
    EEPROM.write(i + 256, CV[i]);
  }
}

void ReadEEPROM() {

  for (int i = 0; i <= 255 ; i++) {
    RN[i] = EEPROM.read(i);
    CV[i] = EEPROM.read(i + 256);
  }
  /*
    Serial.print(" EEProm Reading ");//
    for (int p=0; p <= 20 ;p++){
                                  Serial.print("RN[");// limit to 6 char
                                  Serial.print(p);
                                  Serial.print("] =:");
                                  Serial.print(RN[p]);    }
                                  Serial.println(" ");
  */

    // Nickname, length RN[3] ESP is default
       Nickname="                   ";
         
          Serial.println("--------------------------------------");
          // Serial.print(" EEPROM Read: This Node Nickname is:");
         //   Serial.print(RN[3]);
          //  Serial.print(" chars :'");   
             for (int i = 1 ;  i <= RN[3]; i++) {
                    Nickname[i-1] = char(RN[3 + i]);
                    }
                    Nickname[RN[3]]=char(0);         //  add null to end string nickname, length RN[3] ESP is default
                            // Serial.println("'");
         // Serial.print("NICKNAME BUILT IS:");
        //  Serial.println(Nickname);
          
  mosquitto[3] = RN[14];
  RocNodeID = getTwoBytesFromMessageHL(RN, 1);
#ifdef _ForceRocnetNodeID_to_subIPL
  RocNodeID =subIPL;
#endif
  for (int i = 1; i <= NumberOfPorts; i++) {
    Value_for_PortD[i] = RN[20 + i];
    Pi02_Port_Settings_D[i] = RN[30 + i];
    DelaySetting_for_PortD[i] = RN[40 + i];
    Configuration_for_PortD[i] = RN[50 + i];
    EventMarker_for_PortD[i] = RN[60 + i];
    ID_High_for_PortD[i] = RN[70 + i]; // idh
    ID_Low_for_PortD[i] = RN[80 + i]; //idl
    XRef_Port[i] = RN[90 + i];

    Pi03_Setting_offposH[i] = RN[100 + i];
    Pi03_Setting_offposL[i] = RN[110 + i];
    Pi03_Setting_onposH[i] = RN[120 + i];
    Pi03_Setting_onposL[i] = RN[130 + i];
    Pi03_Setting_offsteps[i] = RN[140 + i];
    Pi03_Setting_onsteps[i] = RN[150 + i];
    Pi03_Setting_options[i] = RN[160 + i];
  }
}


void  ROCSerialPrint(uint8_t *msg)   {
  Serial.print("NetId  RidH  RidL   SidH  SidL  Grp   Code  Len");
  for (byte i = 1; i <= (msg[7]); i++) {
    Serial.print("    D");
    Serial.print(i);
  }
  Serial.println();
  for (byte i = 0; i <= (7 + msg[7]); i++) {
    Serial.print(" ");
    dump_byte(msg[i]);
  }
  Serial.println();
}


char*  Show_ROC_MSG() {

  if (Message_Length >= 1) {
    DebugMessage[0] = 0;
    strcat(DebugMessage, " NetID:");
    snprintf(DebugMessage, sizeof(DebugMessage), "%s%d", DebugMessage, ROC_netid);
    strcat(DebugMessage, " Rec:"); snprintf(DebugMessage, sizeof(DebugMessage), "%s%d", DebugMessage, ROC_recipient);
    strcat(DebugMessage, " Sdr:"); snprintf(DebugMessage, sizeof(DebugMessage), "%s%d", DebugMessage, ROC_sender);
    strcat(DebugMessage, " Grp:"); snprintf(DebugMessage, sizeof(DebugMessage), "%s%d", DebugMessage, ROC_group);
    strcat(DebugMessage, " Code[");
    if ((ROC_code & 0x60) == 0) {
      strcat(DebugMessage, "Req]:");
    }
    if ((ROC_code & 0x60) == 0x20) {
      strcat(DebugMessage, "Evt]:");
    }
    if ((ROC_code & 0x60) == 0x40) {
      strcat(DebugMessage, "Rpy]:"); //// add request event reply then code.. (5 bits)
    }
    snprintf(DebugMessage, sizeof(DebugMessage), "%s%d", DebugMessage, (ROC_code & 0x1F));
    for (byte i = 1; i <= ROC_len; i++) {
      strcat(DebugMessage, " D"); snprintf(DebugMessage, sizeof(DebugMessage), "%s%d", DebugMessage, i);
      strcat(DebugMessage, "="); snprintf(DebugMessage, sizeof(DebugMessage), "%s%d", DebugMessage, ROC_Data[i]);
    }

    //Serial.print(DebugMessage);
  } return DebugMessage;
}

void Show_ROC_MSGS(uint8_t *payload) {
  ROC_netid = sendMessage[0];
  ROC_recipient = IntFromPacket_at_Addr(sendMessage, Recipient_Addr);
  ROC_sender = IntFromPacket_at_Addr(sendMessage, Sender_Addr);
  ROC_group = sendMessage[5];
  ROC_code = sendMessage[6];
  ROC_len = sendMessage[7];
  for (byte i = 1; i <= ROC_len; i++) {
    ROC_Data[7 + i];
  }
  Message_Length = ROC_len + 7;
  Serial.print(Show_ROC_MSG());
}


void ROC_CS() { //group 1
  uint16_t CVNum;
  uint8_t OldValue;
  switch (ROC_code) {
    case 0:  {}    // NOP
      break;
    case 2:  {
        POWERON = ROC_Data[1];
        Serial.println();
        Serial.print(" Power set to:");
        Serial.println(POWERON);
        sendMessage[8] = 0x00; // clear before doing anything later .....
        sendMessage[0] = ROC_netid;
        SetWordIn_msg_loc_value(sendMessage, Recipient_Addr, 0x00 ); // response is to host, not cs
        SetWordIn_msg_loc_value(sendMessage, Sender_Addr, RocNodeID ); // sent from the rocnode ?
        sendMessage[5] = ROC_group;
        sendMessage[6] = ROC_code | Code_Reply; // action group, response
        sendMessage[7] = 1;             // len of data coming next
        bitWrite(sendMessage[8], 1, 1); // set 'Idle' ?
        bitWrite(sendMessage[8], 0, POWERON); //set bit 0 in status to power state
        //     MQTTSend("rocnet/cs",sendMessage);        // sends status response something wrong with this
        //     ROCSerialPrint(sendMessage);
        Message_Decoded = true;
        if (POWERON == false) {
                DebugMsgSend("debug", " NODE OFF ");
                  }
        if (POWERON == true) {
                DebugMsgSend("debug", " NODE ON ");
                  }
      }
      break;
    case 8:  {
        if (((ROC_Data[2] + (ROC_Data[1] * 256)) == CV[1]) || ((ROC_Data[2] == 0) && (ROC_Data[1] == 0))) {
          if ((ROC_Data[2] + (ROC_Data[1] * 256)) == CV[1]) {
            Serial.print("Group 1, Code 8 for this Loco ");
          }
          CVNum = ((ROC_Data[3] * 256) + ROC_Data[4]);
          OldValue = CV[CVNum]; // get the old value
          Message_Decoded = true; // we understand these even if they are not for us
          if (ROC_Data[6] == 1) { // this is a SET CV

// mqtt debug message
         DebugSprintfMsgSend( sprintf ( DebugMsg, "Set CV[%d]=%d",CVNum,ROC_Data[5]));
          
        //   Serial.println(DebugMsg);
            
            if (CVNum == 8) { // set defaults when CV8=13
              if ((ROC_Data[5] == 13)) {
                Serial.print("Setting Defaults");
                DebugMsgSend("debug", "Setting EEPROM defaults");
                SetDefaultSVs();
                Data_Updated = true;
                WriteEEPROM();
              }
            }
            else {   // Setting, but not setting defaults
              CV[CVNum] = ROC_Data[5]; //set the new data
              if (OldValue != ROC_Data[5]) {
                WriteEEPROM();  // update EEPROM only if different
                Data_Updated = true;
                WriteEEPROM();
              }
            }
            EPROM_Write_Delay = millis() + Ten_Sec; // update the time so you can press the same set and get another ten seconds delay

          } //set end

          if (ROC_Data[6] == 0) { // get
            CVNum = ((ROC_Data[3] * 256) + ROC_Data[4]);
           // Serial.print(" Get  CV[");
           // Serial.print(CVNum);
           // Serial.print("] =");
           // Serial.println(CV[CVNum]);
           DebugSprintfMsgSend( sprintf ( DebugMsg, "Get CV[%d]=%d",CVNum,CV[CVNum]));
          } //get end

          //     Serial.println("    Building and sending response"); Send response for both GET and SET...
          // ----------------SEND CV Starts-----------------
          sendMessage[0] = ROC_netid;
          SetWordIn_msg_loc_value(sendMessage, Recipient_Addr, 0x00 ); // response is to host, not cs
          SetWordIn_msg_loc_value(sendMessage, Sender_Addr, CV[1] ); // ??sent from the loco not rocnodeid??
          sendMessage[5] = ROC_group;
          sendMessage[6] = ROC_code | Code_Reply; // action group, response
          sendMessage[7] = 6;   // len of data coming next
          SetWordIn_msg_loc_value(sendMessage, 8, CV[1]); // set 8 and 9 with which loco I am
          SetWordIn_msg_loc_value(sendMessage, 10, CVNum); // set 10 and 11 with the CV number
          sendMessage[12] = CV[CVNum];     // the CV value
          sendMessage[13] = 1;  //set
          if ((CV[47] & 0x20) == 0x20) {
            Serial.print("Response:");
            Show_ROC_MSGS(sendMessage);
          }
          MQTTSend("rocnet/ht", sendMessage);  // HOST not cs??
          //------------SEND CV ENDS------------
          //  Serial.println("------------ double check message content------------");
          //  ROCSerialPrint(sendMessage);
          //  Serial.println("-------------- end double check --------------");


        }  // end of if for this loco
        Message_Decoded = true;
      } // end of this case
      break;


  }
}
extern boolean ButtonState[12] ;
extern int lastButtonState[12];
extern void  SetSoundEffect(uint8_t Data1,uint8_t Data2,uint8_t Data3);
extern void BeginPlay(const char *wavfilename, uint8_t Volume);
extern void SetMotorSpeed(uint8_t SpeedDemand,uint8_t DIRF);

void ROC_MOBILE() { // group 2
  switch (ROC_code) {
    case 0:  {}    // NOP
      break;
    case 1:  {}    // setup
      break;
    case 2:  {
        //      Serial.print("Local:");  Serial.print(CV[1]); Serial.print(" MSG for:");  Serial.print(ROC_recipient);
        // set Velocity, direction , lights
        Message_Decoded = true; // we understand these even if they are not for us
#ifdef _LOCO_SERVO_Driven_Port
        if (ROC_recipient == CV[1]) { //data for me, do it!
//          Serial.print (" Set Speed ");
//          Serial.print( ROC_Data[1]);
       //   Speed_demand = ROC_Data[1];  set direction etc in DIRF 
          bitWrite(DIRF, 5, ROC_Data[2]);
          bitWrite(DIRF, 4, ROC_Data[3]);
          SetMotorSpeed(ROC_Data[1],DIRF);
// Moved all loco stuff from here to SetMotorSpeed 
                                    }
#endif
             }    // set Velocity, direction , lights
      break;
    case 3:  {
        Message_Decoded = true; // we understand these 
        if (ROC_recipient == CV[1]) {     //for me, do it!
          //Serial.print(" Function change for :");  
          //Serial.print(ROC_recipient); Serial.print(" data :"); 
#ifdef _Audio          
          DebugSprintfMsgSend( sprintf ( DebugMsg, "SFX-F changed <%X>h <%X>h <%X>h",ROC_Data[1],ROC_Data[2],ROC_Data[3]));  //X is hex d is decimal
          delay(1); // make sure its sent!
         
         SetSoundEffect(ROC_Data[1],ROC_Data[2],ROC_Data[3]); //Moved settings to SetSoundEffect
          //SoundEffect_Request[1]=ROC_Data[1];
          //SoundEffect_Request[2]=ROC_Data[2];
          //SoundEffect_Request[3]=ROC_Data[3];
/*               //ROC_Data[1];    // F1-F8   
                 //ROC_Data[2];    // F9-F16
                 //ROC_Data[3];    // F17-F24
*/        
#endif
        
        }
            }    // end case 3 functions
      break;
    case 4:  {}    // query
      break;
    case 5:  {}    // fieldcmd
      break;
  }
}
void ROC_CLOCK() {
  hrs = ROC_Data[5];
  mins = ROC_Data[6];
  secs = ROC_Data[7];
  //PrintTime("Time synch \n");
  // bad idea, to have lots of things transmitting immediately after synch.. 
  //test with delay based on subIPL  
  delay(subIPL);
  if (POWERON) {
  DebugSprintfMsgSend( sprintf ( DebugMsg, " IPaddr .%d  Time Synchronised. Power is ON",subIPL));
  }
  else{  DebugSprintfMsgSend( sprintf ( DebugMsg, " IPaddr .%d  Time Synchronised. Power is OFF",subIPL));
  }
    Message_Decoded = true;
  //set / synch clock
}

void ROC_NODE() { // stationary decoders GROUP 3
  uint8_t TEMP;

  switch (ROC_code) {
    case 8:  {  //Identify         class manuID  versionH  versionL  nr I/O  subipH  subipL
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {   //Serial.println();
          Serial.print("Responding to IDENTIFY. This node is:");
          Serial.print(RocNodeID) ;
          sendMessage[0] = ROC_netid;
          SetWordIn_msg_loc_value(sendMessage, Recipient_Addr, ROC_sender);
          SetWordIn_msg_loc_value(sendMessage, Sender_Addr, RocNodeID);
          sendMessage[5] = 3;
          sendMessage[6] = 8 + 32; // action group and code bit 6 (32) = set for REPLY
          sendMessage[7] = 7 + RN[3]; // len of data coming next + nicname length
          if (RN[3] >= 1) {
            Serial.print(" Nickname :");
            Serial.print(RN[3]);
            Serial.print(" chars :'");
          }
          // Identify... data is:  class manuID  versionH  versionL  nr I/O  subipH  subipL
          sendMessage[8] = 0x05; //class? = io?"bit 0= accessory" bit 1= dcc Bit 3=RFID
          sendMessage[9] = 13; // manuid
          SetWordIn_msg_loc_value(sendMessage, 10, SW_REV);
          sendMessage[12] = NumberOfPorts; // 8 io seems fixed in rocrail?
          sendMessage[13] = subIPH; // sub IPh
          sendMessage[14] = subIPL; // sub IPl
          for (int i = 1 ;  i <= RN[3]; i++) {
            Serial.print(char(RN[3 + i]));
            sendMessage[14 + i] = RN[3 + i];
          } // nickname, length RN[3] ESP is default
          Serial.println("'");
          //delay(subIPL*2); //prevent simultaneous responses to identify query
          MQTTSend("rocnet/dc", sendMessage);
          delay(100);
         // DebugSprintfMsgSend( sprintf ( DebugMsg, " Responded to Identify "));
          // ROCSerialPrint(sendMessage);
        }
        Message_Decoded = true;
      }    // Identify... data is:  class manuID  versionH  versionL  nr I/O  subipH  subipL
      break;
    case 9:  {
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
          PrintTime("     Node Shutdown    -- Powering off --  ");
          Serial.println();
          POWERON = false;
        }
        Message_Decoded = true;
      }    // Node Shutdown
      break;
    case 10:  {
        Message_Decoded = true; // we understand these even if they are not for us//Acknowledge
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
          Serial.print("ACKnowledging action:");       // action and port in D1, D2
          Serial.print(ROC_Data[1]);
          if (ROC_len >= 2) {
            Serial.print(" port:");
            Serial.print(ROC_Data[2]);
          }
          Serial.println(  );
          // ROCSerialPrint(recMessage);

        }
        Message_Decoded = true;
      }
      break;
    case 11:  {  //SHOW
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
          FlashMessage("   SHOW LED    ", 10, 500, 100);  // hold the LED on for 800ms, off for 800ms, 6 times!
        }

        Message_Decoded = true;
      }
      break;


  }// end of case

}// end rocnode
extern int SDemand[12];

void ROC_Programming() { // GROUP  5
  switch (ROC_code) {
    case 4:  { // read port config
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
          int TEMP;
          int port;
          PrintTime("  Multi byte READ Port# value, type delay :");


          sendMessage[0] = ROC_netid;
          SetWordIn_msg_loc_value(sendMessage, Recipient_Addr, ROC_sender );
          SetWordIn_msg_loc_value(sendMessage, Sender_Addr, RocNodeID);
          sendMessage[5] = ROC_group;
          sendMessage[6] = ROC_code | Code_Reply; // action group and code bit 6 (64) = set for REPLY
          sendMessage[7] = (((ROC_Data[2] - ROC_Data[1]) + 1) * 4); // len of data coming next from port to port..
          TEMP = 0;
          for (int i = 1 ;  i <= ((((ROC_Data[2] - ROC_Data[1]) + 1)) * 4); i = i + 4) { //  port# value type  delay
            port = ROC_Data[1] + TEMP;
            sendMessage[7 + i] = port; //port# value type  delay
            sendMessage[7 + i + 1] = Value_for_PortD[port]; // value=
            sendMessage[7 + i + 2] = Pi02_Port_Settings_D[port]; //type = switch
            sendMessage[7 + i + 3] = DelaySetting_for_PortD[port]; //delay
            //Serial.print(port);
            TEMP = TEMP + 1;
          }
          MQTTSend("rocnet/ps", sendMessage);
          //ROCSerialPrint(sendMessage);
        }      Message_Decoded = true;
      }
      break;

    case 5: {
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
          PrintTime("  Multi byte WRITE port, value type delay"); //port#  value type  delay port#  value type  delay

          for (byte i = 1; i <= ROC_len; i = i + 4) {
            //  Serial.print(" Port:");
            //  Serial.print(ROC_Data[i]);
            // Serial.print("] Value= :");
            // Serial.print(ROC_Data[i+1]);
            // Serial.print(" type= :");
            // Serial.print(ROC_Data[i+2]);
            // Serial.print(" Delay= :");
            // Serial.print(ROC_Data[i+3]);
            Value_for_PortD[ROC_Data[i]] = ROC_Data[i + 1]; // value=
            Pi02_Port_Settings_D[ROC_Data[i]] = ROC_Data[i + 2]; //type =
            DelaySetting_for_PortD[ROC_Data[i]] = ROC_Data[i + 3]; //delay
          }
          //Serial.println();
          WriteEEPROM();
          Data_Updated = true;
          EPROM_Write_Delay = millis() + Ten_Sec;
        }
        Message_Decoded = true;
      }
      break;

    case 6:  {
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
          if ((ROC_Data[3] == subIPH) && (ROC_Data[4] == subIPL)) {
            Serial.print("Programming node:  set RocNet ID to:");
            RocNodeID = ((ROC_Data[1] << 8) + ROC_Data[2]);
             RocNodeID = getTwoBytesFromMessageHL(RN, 1);
#ifdef _ForceRocnetNodeID_to_subIPL
  RocNodeID =subIPL;
  Serial.print(" Node ID forced to subIPL");
#endif
            SetWordIn_msg_loc_value(RN, 1, RocNodeID); // set RN 1 and 2
            Serial.print (RocNodeID);
            // ROCSerialPrint(recMessage);


            if ( ROC_len >= 6) { // set nickname
              Serial.print("Programming nickname ");
              Serial.print( ROC_len - 5); // new, uses rn3 as length
              Serial.print(" bytes ");
              RN[3] = ROC_len - 5;
              for (int p = 1; ((p <= RN[3]) && (p <= 7)); p++) {
                Serial.write(ROC_Data[p + 5]);
                RN[3 + p] = ROC_Data[p + 5];
              }

            }
            Serial.println(" ");
            WriteEEPROM();
            Data_Updated = true;
            EPROM_Write_Delay = millis() + Ten_Sec;
          }
        }
        Message_Decoded = true;
      }
      break;
    case 7:  {  // report addr and status
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
          PrintTime(" REPORT Node Addr and Status");
          //  ROCSerialPrint(recMessage);

/* 
 NEW: 
 Reply Data 1   2     3       4        5               6              7                8             9               10             11             12              13 
 RN[15         16    17       18        19             20             21               22            23              24             15              26              27      
 iotype       flags cstype  csdevice  I2C scan 0×20 H I2C scan 0×20 L I2C scan 0×30 H I2C scan 0×30 I2C scan 0×40 H I2C scan 0×40 L adc threshold I2C scan 0×50 H I2C scan 0×50 L
*/
RN[15]=33;  // iotype not a pi, i2c-0
RN[16]=0; // 0= no options set 
RN[17]=0; //cstype: 0=none, 1=dcc232, 2=sprog
RN[18]=0; //csdevice: 0=/dev/ttyUSB0, 1=/dev/ttyUSB1 2= /dev/ttyACMO 3 gives error in radiobox in rocview..
RN[19]=0;  //020H  //Pi o2's
RN[20]=1; //020 l
RN[21]=0; //030 H // Pi04's
RN[22]=0; //030 L
RN[23]=0; //040 H  //Pi03's
RN[24]=1; //040 l
RN[25]=0; //adc thresh
RN[26]=0; //050 H (ROC DISPLAYS)
RN[27]=0; //050 L  set 1 for "0x50" 3 for 0x50,0x51 etc..


          sendMessage[0] = ROC_netid;
          SetWordIn_msg_loc_value(sendMessage, Recipient_Addr, ROC_sender);
          SetWordIn_msg_loc_value(sendMessage, Sender_Addr, RocNodeID);
          sendMessage[5] = ROC_group;
          sendMessage[6] = ROC_code | Code_Reply; // action group and code bit 6 (64) = set for REPLY
          sendMessage[7] = 13; //  6 sends to RN20
         for (int i = 1 ;  i <= (sendMessage[7]); i = i + 1) { 
          sendMessage[7+i] = RN[14+i];
         }
      
          MQTTSend("rocnet/ps", sendMessage);
         // DebugMsgSend("debug", " sending (line 953)");
         //     ROCSerialPrint(sendMessage);

        }
        Message_Decoded = true;
      }

      break;
    case 8: {//set rocnode options etc..
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {

          //if ((recMessage[10]==subIPH) && (recMessage[11]==subIPL)){
          PrintTime(" Programming node options");
          RN[15] = ROC_Data[1];
          RN[16] = ROC_Data[2];
          RN[17] = ROC_Data[3];
          RN[18] = ROC_Data[4];
          RN[19] = ROC_Data[5]; // ROC_Data[5] is minimal length of time a sensor will report occupied.

          WriteEEPROM();
          Data_Updated = true;
          EPROM_Write_Delay = millis() + 500; // not ten sec, as we have all the data now..
        }
        Message_Decoded = true;

      }
    case 9:  { //??Shutdown
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
           //this is used by the MACRO settings... I do not  use this
        
          PrintTime("Group5 Case 9 : Node  on/off set to :");
          Serial.print("Data[1]:");
          Serial.print(ROC_Data[1]);
          Serial.print("  Data[2]:");
          Serial.println(ROC_Data[2]);
        
          //   ROCSerialPrint(recMessage);
        }
        Message_Decoded = true;
      }

      break;
    case 11: {
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
          Serial.print(" IS 'UPDATE' FROM ROCRAIL");
          if ( (ROC_Data[1] == 0) && (ROC_Data[2] == 0)) {
            Serial.println(" reset to revision 0 .. will reset SSID settings");
            ResetWiFi = true;
          }       Serial.println();
        }
        Message_Decoded = true;
      }

    case 12:  {
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
          int TEMP;
          int port;
          PrintTime(" Multi byte READ  port#  idH idL port :");


          sendMessage[0] = ROC_netid;
          SetWordIn_msg_loc_value(sendMessage, Recipient_Addr, ROC_sender );
          SetWordIn_msg_loc_value(sendMessage, Sender_Addr, RocNodeID);
          sendMessage[5] = ROC_group;
          sendMessage[6] = ROC_code | Code_Reply; // action group and code bit 6 (64) = set for REPLY
          sendMessage[7] = (((ROC_Data[2] - ROC_Data[1]) + 1) * 4); // len of data coming next
          TEMP = 0;
          for (int i = 1 ;  i <= (((ROC_Data[2] - ROC_Data[1]) + 1) * 4); i = i + 4) { //  port# value type  delay
            port = ROC_Data[1] + TEMP;
            sendMessage[7 + i] = port; //port# value type  delay
            sendMessage[7 + i + 1] = ID_High_for_PortD[port]; // idh
            sendMessage[7 + i + 2] = ID_Low_for_PortD[port]; //idl
            sendMessage[7 + i + 3] = XRef_Port[port]; //port
            //     Serial.print(port);
            TEMP = TEMP + 1;
          }
          MQTTSend("rocnet/ps", sendMessage);
          //ROCSerialPrint(sendMessage);
        } Message_Decoded = true;
      }
      break;
    case 13: {
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {

          PrintTime(" Multi byte write Event idH idL port"); //port#  idH idL port
          for (byte i = 1; i <= ROC_len; i = i + 4) {
            // Serial.print(" Port:");
            // Serial.print(ROC_Data[i]);
            // Serial.print("] Value= :");
            // Serial.print(ROC_Data[i+1]);
            // Serial.print(" type= :");
            // Serial.print(ROC_Data[i+2]);
            // Serial.print(" Delay= :");
            // Serial.print(ROC_Data[i+3]);
            ID_High_for_PortD[ROC_Data[i]] = ROC_Data[i + 1]; // value=
            ID_Low_for_PortD[ROC_Data[i]] = ROC_Data[i + 2]; //type =
            XRef_Port[ROC_Data[i]] = ROC_Data[i + 3]; //delay
          }
          // Serial.println();
          WriteEEPROM();
          Data_Updated = true;
          EPROM_Write_Delay = millis() + 500; // not ten sec, as we have all the data now..
        }
        Message_Decoded = true;
      }

      break;
    case 15:  {
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {

          int TEMP;
          int port;
          PrintTime (" Multi byte READ  Channel data sending:");


          sendMessage[0] = ROC_netid;
          SetWordIn_msg_loc_value(sendMessage, Recipient_Addr, ROC_sender);
          SetWordIn_msg_loc_value(sendMessage, Sender_Addr, RocNodeID);
          sendMessage[5] = ROC_group;
          sendMessage[6] = ROC_code | Code_Reply; // action group and code bit 6 (64) = set for REPLY
          sendMessage[7] = (((ROC_Data[2] - ROC_Data[1]) + 1) * 8); // len of data coming next
          Serial.print(sendMessage[7]);
          Serial.print(" Bytes ");
          port = ROC_Data[1];
          for (int i = 1 ;  i <= ((((ROC_Data[2] - ROC_Data[1])) + 1) * 8); i = i + 8) { //  port# value type  delay

            sendMessage[7 + i] = port; //port# value type  delay
            sendMessage[7 + i + 1] = Pi03_Setting_offposH[port];
            sendMessage[7 + i + 2] = Pi03_Setting_offposL[port];
            sendMessage[7 + i + 3] = Pi03_Setting_onposH[port];
            sendMessage[7 + i + 4] = Pi03_Setting_onposL[port];
            sendMessage[7 + i + 5] = Pi03_Setting_offsteps[port];
            sendMessage[7 + i + 6] = Pi03_Setting_onsteps[port];
            sendMessage[7 + i + 7] = Pi03_Setting_options[port];
            Serial.print(" Ch:");
            Serial.print(port);
            Serial.print(" starting at:");
            Serial.print(7 + i);
            port = port + 1;
          }
          MQTTSend("rocnet/ps", sendMessage);
          Serial.println(" end");
          // ROCSerialPrint(sendMessage);
        }   Message_Decoded = true;
      }

      break;
    case 16: {
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
          PrintTime(" Multi byte WRITE channel");  //channel# offposH offposL onposH  onposL  offsteps  onsteps options
          for (byte i = 1; i <= ROC_len; i = i + 8) {
            // Serial.print(" Port:");
            // Serial.print(ROC_Data[i]);
            // Serial.print("] Value= :");
            // Serial.print(ROC_Data[i+1]);
            // Serial.print(" type= :");
            // Serial.print(ROC_Data[i+2]);
            // Serial.print(" Delay= :");
            // Serial.print(ROC_Data[i+3]);
            Pi03_Setting_offposH[ROC_Data[i]] = ROC_Data[i + 1];
            Pi03_Setting_offposL[ROC_Data[i]] = ROC_Data[i + 2];
            Pi03_Setting_onposH[ROC_Data[i]] = ROC_Data[i + 3];
            Pi03_Setting_onposL[ROC_Data[i]] = ROC_Data[i + 4];
            Pi03_Setting_offsteps[ROC_Data[i]] = ROC_Data[i + 5];
            Pi03_Setting_onsteps[ROC_Data[i]] = ROC_Data[i + 6];
            Pi03_Setting_options[ROC_Data[i]] = ROC_Data[i + 7];


          }
          WriteEEPROM();
          Data_Updated = true;
          EPROM_Write_Delay = millis() + 500; // not ten sec, as we have all the data now..
        }
        Message_Decoded = true;
      }

      break;
    case 18: { //set channel#  valueH  valueL (Pi03 settings)
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
          uint16_t DesiredPos;

          PrintTime( " Single Channel WRITE Ch:"); //channel# valueH  valueL
          Serial.print(ROC_Data[1]);
          
          if (ROC_Data[4] == 0) {
            Serial.print(" updating Left position");
            Pi03_Setting_offposH[ROC_Data[1]] = ROC_Data[1 + 1];
            Pi03_Setting_offposL[ROC_Data[1]] = ROC_Data[1 + 2];
          }    // uses 150-600 so need to change it before using with servo
          if (ROC_Data[4] == 1) {
            Serial.print(" updating Right position");
            Pi03_Setting_onposH[ROC_Data[1]] = ROC_Data[1 + 1];
            Pi03_Setting_onposL[ROC_Data[1]] = ROC_Data[1 + 2];
          }      

          
   // ROCRAIL DesiredPos uses 150-600 so need to change it before using with servo 
          if ((Pi03_Setting_options[ROC_Data[1]] & 32) == 32) { ///SERVO....To address a channel instead of a port the port type servo must be set on the interface tab of switches and outputs
             DesiredPos = (ROC_Data[1 + 1] * 256) + ROC_Data[1 + 2];
             SDemand[ROC_Data[1]] = ((DesiredPos - 150) * 2) / 5;  // why??  because it sets "demand" to set servo position for test
             DebugSprintfMsgSend( sprintf ( DebugMsg, "Servo[%d] to:%d degrees",ROC_Data[1],(((DesiredPos - 150) * 2) / 5)));
             SERVOS();                                        } // set the servo immediately range 150-600 (rocrail limmits) = 0 to 180 so we can see the movement                                                }          
   
   
   // if PWM output   //  ROCRAIL DesiredPos sets 0-4095 range,,   Arduino PWM range is 0-1023, 
           if ((Pi03_Setting_options[ROC_Data[1]] & 128) == 128) { // set pwm immediately, arduino range is 0-1023, rocrail has 0-4095 range
            DebugSprintfMsgSend( sprintf ( DebugMsg, " PWM to :[%d]",DesiredPos/4));
            analogWrite( NodeMCUPinD[ROC_Data[1]], DesiredPos/4);   // change to the desired pwm.
                                                                 } 
         
          Data_Updated = true;
          EPROM_Write_Delay = millis() + 30000; // 30 sec, not ten sec, as we may be wanting to tweak it when we see the movement..
        }
        Message_Decoded = true;
      }
      break;

  }// end code switch
}// end group 5

extern uint32_t PortTimingDelay[12];
void ROC_Outputs() { //group 9

  switch (ROC_code) {
    case 1: {
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) ) {
          boolean STATE; 
          STATE = ROC_Data[1];
          
         
 if ((Pi02_Port_Settings_D[ROC_Data[4]] & 0x01) == 0) {      // Setting an output first make sure its an output!
            ButtonState[ROC_Data[4]] = STATE;
      if ((Pi02_Port_Settings_D[ROC_Data[4]] & 64) == 64)   {  // invert ?
              STATE = !STATE;   // invert state
                                                    }   
          if ((Pi03_Setting_options[ROC_Data[4]] & 32) == 32) {   //SERVO....To address a channel instead of a port the port type servo must be set on the interface tab of switches and outputs
          // DebugSprintfMsgSend( sprintf ( DebugMsg, "Setting Output %d (SERVO) to %d", ROC_Data[4], STATE)); 
          // DebugMsgSend("debug", DebugMsg);
           
            ButtonState[ROC_Data[4]] = STATE;
            SDemand[ROC_Data[4]] = servoLR(STATE, ROC_Data[4]);// just setting sdemand allows "servos" to drive the servo to the desired position 
            if (SDemand[ROC_Data[4]] >= 180) {  //set limits 
              SDemand[ROC_Data[4]] = 180;
            }
            if (SDemand[ROC_Data[4]] <= 0) {    // set limit
              SDemand[ROC_Data[4]] = 0;
            }
            Pi03_Setting_LastUpdated[ROC_Data[4]] = millis();  
           DebugSprintfMsgSend( sprintf ( DebugMsg, "Setting Output %d (SERVO) to State(%d) = Position:%d ", ROC_Data[4],STATE,SDemand[ROC_Data[4]])); 
         
          /*PrintTime("Setting servo:");
            Serial.print (ROC_Data[4]);
            Serial.print (" to  ");//D1=on off  D4= Port
            Serial.println (SDemand[ROC_Data[4]]);  // the demand, can be 0,1 or pwm 
          */
          }   //        End of servo                                         
          else {   // not servo
            if ((Pi03_Setting_options[ROC_Data[4]] & 128) == 128) {// is channel blink set, if so, use PWM outputs as settings for on and off channel positions
           //PrintTime("SET PWM OUTPUT D");Serial.print (ROC_Data[4]);
           //   if((Pi02_Port_Settings_D[ROC_Data[4]] & 129) == 128){Serial.print(" flashing ");}
             
           //   Serial.print (" PWM set by rocrail  ");
           //   Serial.println (FlashHL(STATE, ROC_Data[4]));// STATE will record on or off, so we can turn flashing on and off
              PortTimingDelay[ROC_Data[4]] = millis() + (DelaySetting_for_PortD[ROC_Data[4]] * 10);
              analogWrite( NodeMCUPinD[ROC_Data[4]], FlashHL(STATE, ROC_Data[4]));   // set pwm, arduino range is 0-1023, rocrail has 0-4095 range
              SDemand[ROC_Data[4]] = FlashHL(STATE, ROC_Data[4]); // save  what we have set for flashing 
              
               
              if((Pi02_Port_Settings_D[ROC_Data[4]] & 129) == 128){DebugSprintfMsgSend( sprintf ( DebugMsg, "Setting Output FLASHING %d  to %d", ROC_Data[4], SDemand[ROC_Data[4]]));}
              else {DebugSprintfMsgSend( sprintf ( DebugMsg, "Setting Output %d (PWM) to %d", ROC_Data[4], SDemand[ROC_Data[4]]));}
            }
            else {                                                // this is a pure digital output
            // PrintTime(" (1251) OUTPUT D");Serial.print (ROC_Data[4]);   
            //  if((Pi02_Port_Settings_D[ROC_Data[4]] & 129) == 128){Serial.print(" flashing ");}
              
              
              if((Pi02_Port_Settings_D[ROC_Data[4]] & 129) == 128){DebugSprintfMsgSend( sprintf ( DebugMsg, "Setting Output FLASHING %d (Digital) to %d", ROC_Data[4], STATE));}
              else{ DebugSprintfMsgSend( sprintf ( DebugMsg, "Setting Output %d (Digital) to %d", ROC_Data[4], STATE)); }
             
              //Serial.println (STATE);// record on or off, so we can turn flashing on and off
              
              digitalWrite(NodeMCUPinD[ROC_Data[4]], STATE); 
              PortTimingDelay[ROC_Data[4]] = millis() + (DelaySetting_for_PortD[ROC_Data[4]] * 10);
              SDemand[ROC_Data[4]] = servoLR(STATE, ROC_Data[4]);  // use sdemand to save state so we can flash
            } // pure digital
          } //not servo
        } // set output
      } // a node we understand
    } // end case 1
      break;


  }// end of switch code

}//end of ROC_Outputs

void SendPortChange(int RNID, boolean ST, uint8_t i) {
  Serial.print(" I/O change, Node :"); Serial.print(RNID);  Serial.print(" Sends io:");  Serial.print (i);  Serial.print(" is now:"); Serial.print(ST); Serial.println(" ");
  //new format send
  sendMessage[0] = ROC_netid;
  sendMessage[1] = 0x00;
  sendMessage[2] = 0x01; // recipient is the rocrail server
  SetWordIn_msg_loc_value(sendMessage, Sender_Addr, RNID);
  sendMessage[5] = 8;
  sendMessage[6] = 1; // action group and code
  sendMessage[7] = 4;   // len of data coming next
  sendMessage[8] = 0x00;
  sendMessage[9] = CV[1]; // reporting loco address?
  sendMessage[10] = ST;             sendMessage[11] = i; //port
  char Message[80];
  snprintf(Message, sizeof(Message), "*Sensor Seen&Sent  Address:%d state:%d", i, ST);
  DebugMsgSend("debug", Message);
  MQTTSendQ1("rocnet/sr", sendMessage);

}

void DoRocNet() {
  if (RocNodeID == IntFromPacket_at_Addr(sendMessage, Sender_Addr)){
        Message_Decoded = true;} //  this is a reflected a message we originally sent
  if (Message_Length >= 1) { // have we recieved data?
    switch (ROC_group) {
      case 0:  {}    // {Host
        break;
      case 1:  {
          ROC_CS(); // Command Station Command Station rocnet/cs
        }
        break;
      case 2:  {
          ROC_MOBILE();
        }    // Locomotives and functions rocnet/lc
        break;
      case 3:  {
          ROC_NODE(); // Stationary decoders  Multiport for inputs and outputs  rocnet/dc
        }
        break;
      case 4:  {}    // Programming mobile DCC CVs rocnet/pm
        break;
      case 5:  {
          ROC_Programming(); // Programming stationary Including command stations  rocnet/ps
        }
        break;
      case 6:  {}    // GP Data transfer  General purpose data transfer between modules
        break;
      case 7:  {
          ROC_CLOCK(); // Clock Fast clock  rocnet/ck
        }
        break;
      case 8:  {
          Message_Decoded = true; //  Position determination  rocnet/sr  // do not want to see these just now
        }
        break;
      case 9:  {
          ROC_Outputs(); // Outputs  rocnet/ot
        }
        break;
      case 10:  {}    // Input
        break;
      case 11:  {}    // Sound
        break;
      case 12:  {}    // Display
        break;
      default:  {}    // Default!!
        break;
    }
  }     // end message length decode
  
  if   ((!Message_Decoded) && (Message_Length >= 1) && ((CV[47] & 0x40) == 0x40)) {
    DebugMsgSend("debug", " Message not understood.. see serial output");
     }  // print / send things not decoded if debugs are on
   if   ((!Message_Decoded)&& (Message_Length >= 1 )) {
      Serial.print(" MSG Not Understood<"); Serial.print(Show_ROC_MSG()); Serial.println(">");
   }
  Message_Length = 0; // reset !
}

