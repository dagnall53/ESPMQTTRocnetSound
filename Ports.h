// Stuff to work the ports on the ESP


void READ_PORT( int i) {
  boolean STATE;
  uint8_t TEMP;
  uint16_t senderADDR;
  if (((NodePortType[i] & 0x01) == 1) && ((NodeChanneloptions[i] & 32) != 32))  { // only do this if this port is an "INPUT" and not a "SERVO"
    if (Debounce(i)) { // debounce is true if switch changed

      if (((NodePortType[i] & 32) == 32)  && (digitalRead(NodeMcuPortD[i]) == 1)) {
        ButtonState[i] = !ButtonState[i]; // only change on one state..
      }
      if ((NodePortType[i] & 32) == 32)   {
        STATE = ButtonState[i];
      }
      else {
        STATE = digitalRead(NodeMcuPortD[i]);
      }
      if ((NodePortType[i] & 64) == 64)   {
        STATE = !STATE;
      }
#if _SERIAL_DEBUG
      Serial.print ("Change on IO port : ");
      Serial.print(i);
      Serial.print(" State");
      Serial.println(STATE);
#endif
      SendPortChange(RocNodeID, STATE, i);

      if (STATE && (NodePortDelay[i] >= 1)) {
        PortTimingDelay[i] = millis() + (NodePortDelay[i] * 10);
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
                      Serial.print (" used as LOCO MOTOR ");
                      NodePortType[i] = 0;
                      NodeChanneloptions[i] = 42;
                      hardset =true;
                      break;
  case SignalLed:  
                      Serial.print (" is SignalLED  Output ");
                      pinMode(NodeMcuPortD[SignalLed], OUTPUT);
                      NodePortType[i] = NodePortType[i] & 0xFE;  
                      hardset =true;
                      break;
  case FRONTLight:
                      Serial.print (" is FRONTLight  Output ");
                      pinMode(NodeMcuPortD[FRONTLight], OUTPUT);
                      NodePortType[i] = NodePortType[i] & 0xFE; 
                      hardset =true;
                      break;
  case BACKLight:
                      Serial.print (" is BACKLight  Output ");
                      pinMode(NodeMcuPortD[BACKLight], OUTPUT);
                      NodePortType[i] = NodePortType[i] & 0xFE; 
                      hardset =true;
                      break;
                      #ifdef _Audio
  case AudioRX:Serial.print (" is used by Audio");
                      NodePortType[i] = 0; NodeChanneloptions[i] = 0;
                             hardset =true;
                      break;
  case AudioD4:Serial.print (" is used by Audio");
                      NodePortType[i] = 0; NodeChanneloptions[i] = 0;
                             hardset =true;
                      break;
  case AudioD8:Serial.print (" is used by Audio");
                      NodePortType[i] = 0; NodeChanneloptions[i] = 0;
                             hardset =true;
                      break;
                      #endif
  default:
    
    //in 1 out 0
    if ((NodeChanneloptions[i] & 32) == 32) {
      Serial.print (" is Servo");
      pinMode(NodeMcuPortD[i], OUTPUT);
      NodePortType[i] = bitClear (NodePortType[i], 0 );
                    }
    else {
      if ((NodePortType[i] & 0x01) == 1) {
        pinMode(NodeMcuPortD[i], INPUT_PULLUP);
        Serial.print (" is input with pullup");
      }
      if ((NodePortType[i] & 0x01) == 0) {
        pinMode(NodeMcuPortD[i], OUTPUT);
        Serial.print (" is output");
      }
    }
    break;           
  }//end of switch
    
    // TODO would be good to add more explicit identification of what ports are set to with different channel options etc..
    if (hardset) {Serial.print( "(FIXED)");}
    
          Serial.print (" NodePortType :");
          Serial.print (NodePortType[i]);
          Serial.print ("  NodeChanneloptions");
          Serial.println (NodeChanneloptions[i]);
    
  }


void PortSetupReport() {
  int i;

  if (!bReaderActive) {
    #ifdef  _RFID
        Serial.println("            Reader Absent ....all ports available");
        Serial.println("");
    #endif 
    for (int i = 1 ; i <= 8; i++) {   // for now, Ignore port 0 as it has drive limitations

      PortMode(i);
    }
  }
  else {
    // only port 4 is user available.
    PortMode(4);
  }
 // Serial.println("all Ports set");
}

