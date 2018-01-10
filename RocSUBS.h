void SetDefaultSVs(){

 

//rocnode
  //port and channel defaults
  for (int i=1; i<=NumberOfPorts; i++) {
    NodePortValue[i]=1;

    
NodePortType[i]=0; //0= out 1= in
NodePortDelay[i]=0;//10ms units, max. 255 * 10.
NodePortConfig[i]=1;
NodePortEvent[i]=0;
NodePortidH[i]=0;  // idh
NodePortidL[i]=0;  //idl
NodePortport[i]=0;
NodeChanneloffposH[i]=0; 
NodeChanneloffposL[i]=160; 
NodeChannelonposH[i]=2;  
NodeChannelonposL[i]=88;  
NodeChanneloffsteps[i]=1;  
NodeChannelonsteps[i]=1; 
NodeChanneloptions[i]=0;
NodeChannelLastUpdated[i]=0;
  }

  
#ifndef _LOCO_SERVO_Driven_Port {  
 // a set of defaults derived from a saved emprom set...for a station
 // This set sets 1-4 as pwm outputs 
 //     ( BUT use only 1 and 2 with the motor board for lights (to gnd) on outputs 2 and 4 due to strange DebugMsg logic in motor driver)
 // 5 AND 6 are sensor inputs for using with hall switches
 // 7 and 8 are servo outputs for points.
 
 NodePortValue[1]=0;
 NodePortType[1]=0;
 NodePortDelay[1]=0;
 NodePortConfig[1]=1;
 NodePortEvent[1]=0;
 NodePortidH[1]=0;
 NodePortidL[1]=0;
 NodePortport[1]=0;
 NodeChanneloffposH[1]=0;
 NodeChanneloffposL[1]=0;
 NodeChannelonposH[1]=9;
 NodeChannelonposL[1]=227;
 NodeChanneloffsteps[1]=1;
 NodeChannelonsteps[1]=1;
 NodeChanneloptions[1]=128;
 NodeChannelLastUpdated[1]=6184;
 NodePortValue[2]=0;
 NodePortType[2]=0;
 NodePortDelay[2]=0;
 NodePortConfig[2]=1;
 NodePortEvent[2]=0;
 NodePortidH[2]=0;
 NodePortidL[2]=0;
 NodePortport[2]=0;
 NodeChanneloffposH[2]=0;
 NodeChanneloffposL[2]=0;
 NodeChannelonposH[2]=7;
 NodeChannelonposL[2]=181;
 NodeChanneloffsteps[2]=1;
 NodeChannelonsteps[2]=1;
 NodeChanneloptions[2]=128;
 NodeChannelLastUpdated[2]=6184;
 NodePortValue[3]=0;
 NodePortType[3]=0;
 NodePortDelay[3]=0;
 NodePortConfig[3]=1;
 NodePortEvent[3]=0;
 NodePortidH[3]=0;
 NodePortidL[3]=0;
 NodePortport[3]=0;
 NodeChanneloffposH[3]=0;
 NodeChanneloffposL[3]=0;
 NodeChannelonposH[3]=15;
 NodeChannelonposL[3]=255;
 NodeChanneloffsteps[3]=1;
 NodeChannelonsteps[3]=1;
 NodeChanneloptions[3]=128;
 NodeChannelLastUpdated[3]=6184;
 NodePortValue[4]=0;
 NodePortType[4]=0;
 NodePortDelay[4]=0;
 NodePortConfig[4]=1;
 NodePortEvent[4]=0;
 NodePortidH[4]=0;
 NodePortidL[4]=0;
 NodePortport[4]=0;
 NodeChanneloffposH[4]=0;
 NodeChanneloffposL[4]=0;
 NodeChannelonposH[4]=15;
 NodeChannelonposL[4]=255;
 NodeChanneloffsteps[4]=1;
 NodeChannelonsteps[4]=1;
 NodeChanneloptions[4]=128;
 NodeChannelLastUpdated[4]=6184;
 NodePortValue[5]=0;
 NodePortType[5]=65;
 NodePortDelay[5]=0;
 NodePortConfig[5]=1;
 NodePortEvent[5]=0;
 NodePortidH[5]=0;
 NodePortidL[5]=0;
 NodePortport[5]=0;
 NodeChanneloffposH[5]=0;
 NodeChanneloffposL[5]=160;
 NodeChannelonposH[5]=2;
 NodeChannelonposL[5]=88;
 NodeChanneloffsteps[5]=1;
 NodeChannelonsteps[5]=1;
 NodeChanneloptions[5]=0;
 NodeChannelLastUpdated[5]=6184;
 NodePortValue[6]=0;
 NodePortType[6]=65;
 NodePortDelay[6]=0;
 NodePortConfig[6]=1;
 NodePortEvent[6]=0;
 NodePortidH[6]=0;
 NodePortidL[6]=0;
 NodePortport[6]=0;
 NodeChanneloffposH[6]=0;
 NodeChanneloffposL[6]=160;
 NodeChannelonposH[6]=2;
 NodeChannelonposL[6]=88;
 NodeChanneloffsteps[6]=1;
 NodeChannelonsteps[6]=1;
 NodeChanneloptions[6]=0;
 NodeChannelLastUpdated[6]=6184;
 NodePortValue[7]=0;
 NodePortType[7]=0;
 NodePortDelay[7]=0;
 NodePortConfig[7]=1;
 NodePortEvent[7]=0;
 NodePortidH[7]=0;
 NodePortidL[7]=0;
 NodePortport[7]=0;
 NodeChanneloffposH[7]=1;
 NodeChanneloffposL[7]=4;
 NodeChannelonposH[7]=1;
 NodeChannelonposL[7]=197;
 NodeChanneloffsteps[7]=1;
 NodeChannelonsteps[7]=1;
 NodeChanneloptions[7]=34;
 NodeChannelLastUpdated[7]=8131;
 NodePortValue[8]=0;
 NodePortType[8]=0;
 NodePortDelay[8]=0;
 NodePortConfig[8]=1;
 NodePortEvent[8]=0;
 NodePortidH[8]=0;
 NodePortidL[8]=0;
 NodePortport[8]=0;
 NodeChanneloffposH[8]=0;
 NodeChanneloffposL[8]=236;
 NodeChannelonposH[8]=1;
 NodeChannelonposL[8]=201;
 NodeChanneloffsteps[8]=1;
 NodeChannelonsteps[8]=1;
 NodeChanneloptions[8]=34;
 NodeChannelLastUpdated[8]=6184;

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
 NodePortValue[1]=0;
 NodePortType[1]=0;
 NodePortDelay[1]=0;
 NodePortConfig[1]=1;
 NodePortEvent[1]=0;
 NodePortidH[1]=0;
 NodePortidL[1]=0;
 NodePortport[1]=0;
 NodeChanneloffposH[1]=1;
 NodeChanneloffposL[1]=145;
 NodeChannelonposH[1]=1;
 NodeChannelonposL[1]=145;
 NodeChanneloffsteps[1]=0;
 NodeChannelonsteps[1]=0;
 NodeChanneloptions[1]=42;
 NodeChannelLastUpdated[1]=18054;
 NodePortValue[2]=0;
 NodePortType[2]=0;
 NodePortDelay[2]=0;
 NodePortConfig[2]=1;
 NodePortEvent[2]=0;
 NodePortidH[2]=0;
 NodePortidL[2]=0;
 NodePortport[2]=0;
 NodeChanneloffposH[2]=0;
 NodeChanneloffposL[2]=0;
 NodeChannelonposH[2]=7;
 NodeChannelonposL[2]=181;
 NodeChanneloffsteps[2]=1;
 NodeChannelonsteps[2]=1;
 NodeChanneloptions[2]=0;
 NodeChannelLastUpdated[2]=18054;
 NodePortValue[3]=0;
 NodePortType[3]=0;
 NodePortDelay[3]=0;
 NodePortConfig[3]=1;
 NodePortEvent[3]=0;
 NodePortidH[3]=0;
 NodePortidL[3]=0;
 NodePortport[3]=0;
 NodeChanneloffposH[3]=0;
 NodeChanneloffposL[3]=0;
 NodeChannelonposH[3]=15;
 NodeChannelonposL[3]=255;
 NodeChanneloffsteps[3]=1;
 NodeChannelonsteps[3]=1;
 NodeChanneloptions[3]=0;
 NodeChannelLastUpdated[3]=18054;
 NodePortValue[4]=0;
 NodePortType[4]=0;
 NodePortDelay[4]=0;
 NodePortConfig[4]=1;
 NodePortEvent[4]=0;
 NodePortidH[4]=0;
 NodePortidL[4]=0;
 NodePortport[4]=0;
 NodeChanneloffposH[4]=0;
 NodeChanneloffposL[4]=0;
 NodeChannelonposH[4]=15;
 NodeChannelonposL[4]=255;
 NodeChanneloffsteps[4]=1;
 NodeChannelonsteps[4]=1;
 NodeChanneloptions[4]=0;
 NodeChannelLastUpdated[4]=18054;
 NodePortValue[5]=0;
 NodePortType[5]=0;
 NodePortDelay[5]=0;
 NodePortConfig[5]=1;
 NodePortEvent[5]=0;
 NodePortidH[5]=0;
 NodePortidL[5]=0;
 NodePortport[5]=0;
 NodeChanneloffposH[5]=0;
 NodeChanneloffposL[5]=160;
 NodeChannelonposH[5]=2;
 NodeChannelonposL[5]=88;
 NodeChanneloffsteps[5]=1;
 NodeChannelonsteps[5]=1;
 NodeChanneloptions[5]=0;
 NodeChannelLastUpdated[5]=18054;
 NodePortValue[6]=0;
 NodePortType[6]=0;
 NodePortDelay[6]=10;
 NodePortConfig[6]=1;
 NodePortEvent[6]=0;
 NodePortidH[6]=0;
 NodePortidL[6]=0;
 NodePortport[6]=0;
 NodeChanneloffposH[6]=0;
 NodeChanneloffposL[6]=160;
 NodeChannelonposH[6]=3;
 NodeChannelonposL[6]=232;
 NodeChanneloffsteps[6]=1;
 NodeChannelonsteps[6]=1;
 NodeChanneloptions[6]=128;
 NodeChannelLastUpdated[6]=18054;
 NodePortValue[7]=0;
 NodePortType[7]=0;
 NodePortDelay[7]=0;
 NodePortConfig[7]=1;
 NodePortEvent[7]=0;
 NodePortidH[7]=0;
 NodePortidL[7]=0;
 NodePortport[7]=0;
 NodeChanneloffposH[7]=1;
 NodeChanneloffposL[7]=4;
 NodeChannelonposH[7]=14;
 NodeChannelonposL[7]=176;
 NodeChanneloffsteps[7]=1;
 NodeChannelonsteps[7]=1;
 NodeChanneloptions[7]=128;
 NodeChannelLastUpdated[7]=18054;
 NodePortValue[8]=0;
 NodePortType[8]=0;
 NodePortDelay[8]=0;
 NodePortConfig[8]=1;
 NodePortEvent[8]=0;
 NodePortidH[8]=0;
 NodePortidL[8]=0;
 NodePortport[8]=0;
 NodeChanneloffposH[8]=0;
 NodeChanneloffposL[8]=236;
 NodeChannelonposH[8]=1;
 NodeChannelonposL[8]=201;
 NodeChanneloffsteps[8]=1;
 NodeChannelonsteps[8]=1;
 NodeChanneloptions[8]=0;
 NodeChannelLastUpdated[8]=18054;
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
 CV[100]=0;
 RN[101]=1;
 CV[101]=0;
 RN[102]=0;
 CV[102]=0;
 RN[103]=0;
 CV[103]=0;
 RN[104]=0;
 CV[104]=0;
 RN[105]=0;
 CV[105]=0;
 RN[106]=0;
 CV[106]=0;
 RN[107]=1;
 CV[107]=0;
 RN[108]=0;
 CV[108]=0;
 RN[109]=0;
 CV[109]=0;
 RN[110]=0;
 CV[110]=0;
 RN[111]=145;
 CV[111]=0;
 RN[112]=0;
 CV[112]=0;
 RN[113]=0;
 CV[113]=0;
 RN[114]=0;
 CV[114]=0;
 RN[115]=160;
 CV[115]=0;
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

 uint16_t ROCNodeID(){
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
     
    
Serial.print(" NodePortValue[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodePortValue[i]);Serial.println(";");
Serial.print(" NodePortType[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodePortType[i]);Serial.println(";");
Serial.print(" NodePortDelay[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodePortDelay[i]);  Serial.println(";");  
Serial.print(" NodePortConfig[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodePortConfig[i]);Serial.println(";");
Serial.print(" NodePortEvent[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodePortEvent[i]);Serial.println(";");
Serial.print(" NodePortidH[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodePortidH[i]);Serial.println(";");
Serial.print(" NodePortidL[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodePortidL[i]);Serial.println(";");
Serial.print(" NodePortport[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodePortport[i]);Serial.println(";");
Serial.print(" NodeChanneloffposH[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodeChanneloffposH[i]);Serial.println(";");
Serial.print(" NodeChanneloffposL[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodeChanneloffposL[i]);Serial.println(";");
Serial.print(" NodeChannelonposH[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodeChannelonposH[i]);Serial.println(";");
Serial.print(" NodeChannelonposL[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodeChannelonposL[i]);Serial.println(";");
Serial.print(" NodeChanneloffsteps[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodeChanneloffsteps[i]);Serial.println(";");
Serial.print(" NodeChannelonsteps[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodeChannelonsteps[i]);Serial.println(";");
Serial.print(" NodeChanneloptions[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodeChanneloptions[i]);Serial.println(";");
Serial.print(" NodeChannelLastUpdated[");
Serial.print(i);
Serial.print("]=");
Serial.print(NodeChannelLastUpdated[i]);Serial.println(";");
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
    RN[20 + i] = NodePortValue[i];
    RN[30 + i] = NodePortType[i];
    RN[40 + i] = NodePortDelay[i];
    RN[50 + i] = NodePortConfig[i];
    RN[60 + i] = NodePortEvent[i];
    RN[70 + i] = NodePortidH[i]; // idh
    RN[80 + i] = NodePortidL[i]; //idl
    RN[90 + i] = NodePortport[i];

    RN[100 + i] = NodeChanneloffposH[i];
    RN[110 + i] = NodeChanneloffposL[i];
    RN[120 + i] = NodeChannelonposH[i];
    RN[130 + i] = NodeChannelonposL[i];
    RN[140 + i] = NodeChanneloffsteps[i];
    RN[150 + i] = NodeChannelonsteps[i];
    RN[160 + i] = NodeChanneloptions[i];
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
  for (int i = 1; i <= NumberOfPorts; i++) {
    NodePortValue[i] = RN[20 + i];
    NodePortType[i] = RN[30 + i];
    NodePortDelay[i] = RN[40 + i];
    NodePortConfig[i] = RN[50 + i];
    NodePortEvent[i] = RN[60 + i];
    NodePortidH[i] = RN[70 + i]; // idh
    NodePortidL[i] = RN[80 + i]; //idl
    NodePortport[i] = RN[90 + i];

    NodeChanneloffposH[i] = RN[100 + i];
    NodeChanneloffposL[i] = RN[110 + i];
    NodeChannelonposH[i] = RN[120 + i];
    NodeChannelonposL[i] = RN[130 + i];
    NodeChanneloffsteps[i] = RN[140 + i];
    NodeChannelonsteps[i] = RN[150 + i];
    NodeChanneloptions[i] = RN[160 + i];
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

void MQTTSendQ1 (char* topic, uint8_t * payload) { //QoS1 version
  uint8_t Length;
  digitalWrite (NodeMcuPortD[SignalLed], HIGH) ;  /// turn On
  Length = payload[7] + 8;
  MsgSendTime = millis();
  MSGReflected = false;
  copyUid(SentMessage, payload, 128); // nb  dest, source,
  SentMessage_Length = Length;
  strncpy(SentTopic, topic, 20);     // nb dest, source
  if ((CV[47] & 0x04) == 0x04) {
    Serial.print("*QOS 0 POST with check for 'reflection'[");
    Serial.print(topic);
    Serial.print("] ");
    dump_byte_array(payload, Length);
    Serial.println();
  }
  client.publish(topic, payload, Length); //send as qos 0..for now
}
void testConnection  (int Number) {
  digitalWrite (NodeMcuPortD[SignalLed], HIGH) ;  /// turn On
  PingSendTime = millis();
  PingReflected = false;
  byte id[2];
  id[0] = Number >> 8;
  id[1] = Number & 0xFF;
  client.publish("PiNg", id, 2); //,strlen(payload));//send as qos 0..
}

void MQTTSend (char* topic, uint8_t * payload) { //replaces rocsend
  uint8_t Length;
  digitalWrite (NodeMcuPortD[SignalLed], HIGH) ;  /// turn On
  Length = payload[7] + 8;

  if ((CV[47] & 0x10) == 0x10) {
    Serial.println();
    Serial.print("*MQTT POST [");
    Serial.print(topic);
    Serial.print("] ");
    dump_byte_array(payload, Length);
    Serial.println();
  }

  client.publish(topic, payload, Length);

}

void MQTTFetch (char* topic, byte* payload, unsigned int Length) { //replaces rocfetch
  // do a check on length matching payload[7] ??

  if ((strncmp("PiNg", topic, 4) == 0)) {
    Message_Length = 0; Message_Decoded = true;         // do not bother to do work on this, its a copy of what I sent
    if (RocNodeID == ((payload[0] << 8) + payload[1])) {
      PingReflected = true;
    }
    return;
  }
  if ((strncmp("rocnet/ht", topic, 9) == 0)) {
    Message_Length = 0;
    Message_Decoded = true;
    return;
  }

  Message_Length = Length;
  if (Message_Length >= 1) {

    digitalWrite (NodeMcuPortD[SignalLed], HIGH) ;  /// turn On
    ROC_netid = payload[0];
    ROC_recipient = IntFromPacket_at_Addr(payload, Recipient_Addr);
    ROC_sender = IntFromPacket_at_Addr(payload, Sender_Addr);
    ROC_group = payload[5];
    ROC_code = payload[6];
    ROC_len = payload[7];
    for (byte i = 1; i <= ROC_len; i++) {
      ROC_Data[i] = payload[7 + i];
    }
    Message_Decoded = false;
    if ((CV[47] & 0x08) == 0x08) {
      Serial.print("*MQTT Received [");
      Serial.print(topic);
      Serial.print("] ");
      dump_byte_array(payload, Message_Length);
    }

    if ((strncmp(SentTopic, topic, 20) == 0) && (compareUid(SentMessage, payload, Message_Length))) {
      MSGReflected = true;
    
      cx = sprintf ( DebugMsg, "*Sensor Confirmed Address:%d state:%d", ROC_Data[4], ROC_Data[3]);
      DebugMsgSend("debug", DebugMsg);
    }
  }
}                                                 //*Sensor Seen Node:%d Address:%d state:%d


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
         cx = sprintf ( DebugMsg, "Set CV[%d]=%d",CVNum,ROC_Data[5]);
           DebugMsgSend("debug", DebugMsg);
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
           cx = sprintf ( DebugMsg, "Get CV[%d]=%d",CVNum,CV[CVNum]);
           DebugMsgSend("debug", DebugMsg);
           Serial.println(DebugMsg);
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



void ROC_MOBILE() { // group 2
  switch (ROC_code) {
    case 0:  {}    // NOP
      break;
    case 1:  {}    // setup
      break;
    case 2:  {
        int revoffset;
        int servodemand;
        revoffset = (CV[48] - 100); // else computed as unsigned and so cannot go negative!

        //      Serial.print("Local:");
        //      Serial.print(CV[1]);
        //      Serial.print(" MSG for:");
        //      Serial.print(ROC_recipient);
        Message_Decoded = true; // we understand these even if they are not for us
#ifdef _LOCO_SERVO_Driven_Port
        if (ROC_recipient == CV[1]) { //for me, do it!
          Serial.print (" Set Speed ");
          Serial.print( ROC_Data[1]);
          SPEED = ROC_Data[1];
          LastSetSpeed = SPEED;
          bitWrite(DIRF, 5, ROC_Data[2]);
          bitWrite(DIRF, 4, ROC_Data[3]);
          if  (!(bitRead(DIRF, 4))) {
            digitalWrite (NodeMcuPortD[FRONTLight], 1);
            digitalWrite (NodeMcuPortD[BACKLight], 1);
          }

          //---------Direction Lights and Servo settings---------------
          if (bitRead(CV[29], 0)) {         // need to account for the  cv29 bit 0....
            if (bitRead(DIRF, 5 )) {
              servodemand = 90 + (CV[2] + (SPEED * CV[5]) / 100);
              if  (bitRead(DIRF, 4)) {
                digitalWrite (NodeMcuPortD[FRONTLight], 0);
                digitalWrite (NodeMcuPortD[BACKLight], 1);
              }
            }
            else {
              servodemand = 90 - (CV[2] + (SPEED * CV[5]) / 100);// - revoffset; 
              if  (bitRead(DIRF, 4)) {
                digitalWrite (NodeMcuPortD[BACKLight], 0);
                digitalWrite (NodeMcuPortD[FRONTLight], 1);
              }
            }
          }
          else {   // cv29 =1
            if (!bitRead(DIRF, 5 )) {
              servodemand =  90 + (CV[2] + (SPEED * CV[5]) / 100);
              if  (bitRead(DIRF, 4)) {
                digitalWrite (NodeMcuPortD[BACKLight], 0);
                digitalWrite (NodeMcuPortD[FRONTLight], 1);
              }
            }
            else {
              servodemand = 90 - (CV[2] + (SPEED * CV[5]) / 100) ; // revoffset?
              if  (bitRead(DIRF, 4)) {
                digitalWrite (NodeMcuPortD[FRONTLight], 0);
                digitalWrite (NodeMcuPortD[BACKLight], 1);
              }
            }
          }

          if ((SPEED == 00) || (SPEED == 0x01)) {
            servodemand = 90;
          }
          ButtonState[_LOCO_SERVO_Driven_Port] = false;
          if (SPEED >= OLDSPEED) ( ButtonState[_LOCO_SERVO_Driven_Port] = true); // use button state to differentiate acc and decc needed to select between acc and decc
          OLDSPEED = SPEED;
          if (servodemand >= 180) {
            servodemand = 180;
          }
          if ((servodemand) <= 1  ) {
            servodemand = 0; // range for servo is 0-180
          }
          Loco_motor_servo_demand =    servodemand; //allows use of signed before this point
          Serial.print (" updated motor demand: ");
          Serial.print( Loco_motor_servo_demand);
          Serial.print ("deg  Dirn:");
          Serial.print (bitRead(DIRF, 5));
          Serial.print (" Lights:");
          Serial.print (bitRead(DIRF, 4));      Serial.println();

         
          DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "Speed set to:%d Dir:%d Lights:%d", ROC_Data[1], (bitRead(DIRF, 5 )),(bitRead(DIRF, 4)) ));
        } 
        #endif
        Message_Decoded = true;

      }    // Velocity, direction , lights
      break;
    case 3:  {
        //Serial.println();

        Message_Decoded = true; // we understand these 
        if (ROC_recipient == CV[1]) {     //for me, do it!
          //Serial.print(" Function change for :");  
          //Serial.print(ROC_recipient); Serial.print(" data :"); 
#ifdef _Audio          
          DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "SFX-F changed <%X>h <%X>h <%X>h",ROC_Data[1],ROC_Data[2],ROC_Data[3]));  //X is hex d is decimal
          delay(1); // make sure its sent!
         
         // SetSoundEffect(ROC_Data[1],ROC_Data[2],ROC_Data[3]); //if i could get it to compile!!
          SoundEffect_Request[1]=ROC_Data[1];
          SoundEffect_Request[2]=ROC_Data[2];
          SoundEffect_Request[3]=ROC_Data[3];
/*               //ROC_Data[1];    // F1-F8   
                 //ROC_Data[2];    // F9-F16
                 //ROC_Data[3];    // F17-F24
*/        
#endif
        
        }
        Serial.println("  ");
        Message_Decoded = true;
      }    // case 3 functions
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
  PrintTime("Time synch");
  //DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "Time Synchronised  Connects<%s>  ",connects));
  
    Message_Decoded = true;
  //set / synch clock
}

void ROC_NODE() { // stationary decoders GROUP 3
  uint8_t TEMP;

  switch (ROC_code) {
    case 8:  {  //dentify         class manuID  versionH  versionL  nr I/O  subipH  subipL
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {   //Serial.println();
          Serial.print("IDENTIFY. This node is:");
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

          MQTTSend("rocnet/dc", sendMessage);
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
            sendMessage[7 + i + 1] = NodePortValue[port]; // value=
            sendMessage[7 + i + 2] = NodePortType[port]; //type = switch
            sendMessage[7 + i + 3] = NodePortDelay[port]; //delay
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
            NodePortValue[ROC_Data[i]] = ROC_Data[i + 1]; // value=
            NodePortType[ROC_Data[i]] = ROC_Data[i + 2]; //type =
            NodePortDelay[ROC_Data[i]] = ROC_Data[i + 3]; //delay
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
            sendMessage[7 + i + 1] = NodePortidH[port]; // idh
            sendMessage[7 + i + 2] = NodePortidL[port]; //idl
            sendMessage[7 + i + 3] = NodePortport[port]; //port
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
            NodePortidH[ROC_Data[i]] = ROC_Data[i + 1]; // value=
            NodePortidL[ROC_Data[i]] = ROC_Data[i + 2]; //type =
            NodePortport[ROC_Data[i]] = ROC_Data[i + 3]; //delay
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
            sendMessage[7 + i + 1] = NodeChanneloffposH[port];
            sendMessage[7 + i + 2] = NodeChanneloffposL[port];
            sendMessage[7 + i + 3] = NodeChannelonposH[port];
            sendMessage[7 + i + 4] = NodeChannelonposL[port];
            sendMessage[7 + i + 5] = NodeChanneloffsteps[port];
            sendMessage[7 + i + 6] = NodeChannelonsteps[port];
            sendMessage[7 + i + 7] = NodeChanneloptions[port];
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
            NodeChanneloffposH[ROC_Data[i]] = ROC_Data[i + 1];
            NodeChanneloffposL[ROC_Data[i]] = ROC_Data[i + 2];
            NodeChannelonposH[ROC_Data[i]] = ROC_Data[i + 3];
            NodeChannelonposL[ROC_Data[i]] = ROC_Data[i + 4];
            NodeChanneloffsteps[ROC_Data[i]] = ROC_Data[i + 5];
            NodeChannelonsteps[ROC_Data[i]] = ROC_Data[i + 6];
            NodeChanneloptions[ROC_Data[i]] = ROC_Data[i + 7];


          }
          WriteEEPROM();
          Data_Updated = true;
          EPROM_Write_Delay = millis() + 500; // not ten sec, as we have all the data now..
        }
        Message_Decoded = true;
      }

      break;
    case 18: { //set channel#  valueH  valueL
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) || (    ROC_recipient ==   0)) {
          uint16_t DesiredPos;

          PrintTime( " Single Channel WRITE Ch:"); //channel# valueH  valueL
          Serial.print(ROC_Data[1]);
          
          if (ROC_Data[4] == 0) {
            Serial.print(" updating Left position");
            NodeChanneloffposH[ROC_Data[1]] = ROC_Data[1 + 1];
            NodeChanneloffposL[ROC_Data[1]] = ROC_Data[1 + 2];
          }    // uses 150-600 so need to change it before using with servo
          if (ROC_Data[4] == 1) {
            Serial.print(" updating Right position");
            NodeChannelonposH[ROC_Data[1]] = ROC_Data[1 + 1];
            NodeChannelonposL[ROC_Data[1]] = ROC_Data[1 + 2];
          }      

          
   // ROCRAIL DesiredPos uses 150-600 so need to change it before using with servo 
          if ((NodeChanneloptions[ROC_Data[1]] & 32) == 32) { ///SERVO....To address a channel instead of a port the port type servo must be set on the interface tab of switches and outputs
             DesiredPos = (ROC_Data[1 + 1] * 256) + ROC_Data[1 + 2];
             SDemand[ROC_Data[1]] = ((DesiredPos - 150) * 2) / 5;  // why??  // set demand set servo position for test

             DebugSprintfMsgSend("debug", sprintf ( DebugMsg, "Servo[%d] to:%d degrees",ROC_Data[1],(((DesiredPos - 150) * 2) / 5)));

              SERVOS();} // set the servo immediately range 150-600 (rocrail limmits) = 0 to 180

          // if PWM output   //  ROCRAIL DesiredPos sets 0-4095 range,,   Arduino PWM range is 0-1023, 
           if ((NodeChanneloptions[ROC_Data[1]] & 128) == 128) { // set pwm immediately, arduino range is 0-1023, rocrail has 0-4095 range
            Serial.print(" PWM to :");
            Serial.println(DesiredPos/4);
            analogWrite( NodeMcuPortD[ROC_Data[1]], DesiredPos/4);   
            }
         // WriteEEPROM();// not ten sec, as we have all the data now..
          Data_Updated = true;
          EPROM_Write_Delay = millis() + 20000; // not ten sec, as we have all the data now..
        }
        Message_Decoded = true;
      }
      break;

  }// end code switch
}// end group 5


void ROC_Outputs() { //group 9

  switch (ROC_code) {
    case 1: {
        Message_Decoded = true; // we understand these even if they are not for us
        if ( (ROC_recipient ==   RocNodeID) ) {
          boolean STATE; 
          STATE = ROC_Data[1];
          
         
 if ((NodePortType[ROC_Data[4]] & 0x01) == 0) {      // Setting an output first make sure its an output!
            ButtonState[ROC_Data[4]] = STATE;
      if ((NodePortType[ROC_Data[4]] & 64) == 64)   {  // invert ?
              STATE = !STATE;   // invert state
                                                    }   
          if ((NodeChanneloptions[ROC_Data[4]] & 32) == 32) {   //SERVO....To address a channel instead of a port the port type servo must be set on the interface tab of switches and outputs
          // cx = sprintf ( DebugMsg, "Setting Output %d (SERVO) to %d", ROC_Data[4], STATE); 
          // DebugMsgSend("debug", DebugMsg);
           
            ButtonState[ROC_Data[4]] = STATE;
            SDemand[ROC_Data[4]] = servoLR(STATE, ROC_Data[4]);// just setting sdemand allows "servos" to drive the servo to the desired position 
            if (SDemand[ROC_Data[4]] >= 180) {  //set limits 
              SDemand[ROC_Data[4]] = 180;
            }
            if (SDemand[ROC_Data[4]] <= 0) {    // set limit
              SDemand[ROC_Data[4]] = 0;
            }
            NodeChannelLastUpdated[ROC_Data[4]] = millis();  
           cx = sprintf ( DebugMsg, "Setting Output %d (SERVO) to State(%d) = Position:%d ", ROC_Data[4],STATE,SDemand[ROC_Data[4]]); 
           DebugMsgSend("debug", DebugMsg);
          /*PrintTime("Setting servo:");
            Serial.print (ROC_Data[4]);
            Serial.print (" to  ");//D1=on off  D4= Port
            Serial.println (SDemand[ROC_Data[4]]);  // the demand, can be 0,1 or pwm 
          */
          }   //        End of servo                                         
          else {   // not servo
            if ((NodeChanneloptions[ROC_Data[4]] & 128) == 128) {// is channel blink set, if so, use PWM outputs as settings for on and off channel positions
           //PrintTime("SET PWM OUTPUT D");Serial.print (ROC_Data[4]);
           //   if((NodePortType[ROC_Data[4]] & 129) == 128){Serial.print(" flashing ");}
             
           //   Serial.print (" PWM set by rocrail  ");
           //   Serial.println (FlashHL(STATE, ROC_Data[4]));// STATE will record on or off, so we can turn flashing on and off
              PortTimingDelay[ROC_Data[4]] = millis() + (NodePortDelay[ROC_Data[4]] * 10);
              analogWrite( NodeMcuPortD[ROC_Data[4]], FlashHL(STATE, ROC_Data[4]));   // set pwm, arduino range is 0-1023, rocrail has 0-4095 range
              SDemand[ROC_Data[4]] = FlashHL(STATE, ROC_Data[4]); // save  what we have set for flashing 
              
              cx = sprintf ( DebugMsg, "Setting Output %d (PWM) to %d", ROC_Data[4], SDemand[ROC_Data[4]]); 
              if((NodePortType[ROC_Data[4]] & 129) == 128){cx = sprintf ( DebugMsg, "%s and Flashing",DebugMsg);}
              DebugMsgSend("debug", DebugMsg);
            }
            else {                                                // this is a pure digital output
            // PrintTime(" (1251) OUTPUT D");Serial.print (ROC_Data[4]);   
            //  if((NodePortType[ROC_Data[4]] & 129) == 128){Serial.print(" flashing ");}
              
              cx = sprintf ( DebugMsg, "Setting Output %d (Digital) to %d", ROC_Data[4], STATE); 
              if((NodePortType[ROC_Data[4]] & 129) == 128){cx = sprintf ( DebugMsg, "%s and Flashing",DebugMsg);}
              DebugMsgSend("debug", DebugMsg); Serial.print (" set by rocrail  ");
             
              //Serial.println (STATE);// record on or off, so we can turn flashing on and off
              
              digitalWrite(NodeMcuPortD[ROC_Data[4]], STATE); 
              PortTimingDelay[ROC_Data[4]] = millis() + (NodePortDelay[ROC_Data[4]] * 10);
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

