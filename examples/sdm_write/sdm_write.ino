#include <SoftwareSerial.h>                                                     //import SoftwareSerial library
#include <SDM_mod.h>                                                                //import SDM library

#define NODE_ID  5

SoftwareSerial swSerSDM(10, 11);                                                //config SoftwareSerial (rx->pin10 / tx->pin11)

SDM sdm(swSerSDM, 9600, 4);                                                     //config SDM (serial port, baurd rat->2400, control pin rs485->4)

void setup() {
  
  Serial.begin(9600);                                                         //initialize serial
  sdm.begin();  
  
  delay(1000);
  
  byte reData[SDM::RESPONSE_FRAME_SIZE] = {};
  
  SDM::RCommand rcmd; 
  SDM::WCommand wcmd;
  
  sdm.setNodeId(5);  /////////////////////////////////////// Select Node ID
  
  byte hexArrIeee754[sizeof(float)] = {};
  float fBaud = 2.0f;

  Serial.print("Write to Node ID Register Command {"); //< Command to change Node ID (1-274)
  floatToBytes(hexArrIeee754, NODE_ID); /////////////////////////////////////////////////////////< Change Node ID to 3
  wcmd = sdm._setWriteCommand(SDM::NODE_ID_HI_BYTE, SDM::NODE_ID_LO_BYTE,
                                      hexArrIeee754[0], hexArrIeee754[1],
                                      hexArrIeee754[2], hexArrIeee754[3]);
  if (sdm.getRawData(reData, wcmd.cmd, wcmd.size) == SDM::ERR_READ_RS485) {
       return ;
  }
  sdm._debugViewCommand(wcmd);
  Serial.println("}");
  Serial.print("Response: { ");
  for (byte i = 0; i < SDM::RESPONSE_FRAME_SIZE; i++) {
      Serial.print(reData[i], HEX);
      Serial.print(" ");
  }
  Serial.println("}");
  delay(1000);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  sdm.setNodeId(NODE_ID);
  Serial.print("Write to Baudrate Register Command {"); //< Command to change baudrate
    // 2400 bps -> 0.0f
    // 4800 bps -> 1.0f
    // 9600 bps -> 2.0f
    // 19200 bps -> 3.0f
  floatToBytes(hexArrIeee754, 2.0f); //< 9600 bps
  wcmd = sdm._setWriteCommand(SDM::BAUDRATE_HI_BYTE, SDM::BAUDRATE_LO_BYTE,
                                      hexArrIeee754[0], hexArrIeee754[1],
                                      hexArrIeee754[2], hexArrIeee754[3]);
  if (sdm.getRawData(reData, wcmd.cmd, wcmd.size) == SDM::ERR_READ_RS485) {
      return ;
  }
  sdm._debugViewCommand(wcmd);
  Serial.println("}");

  Serial.print("Response: { ");
  for (byte i = 0; i < SDM::RESPONSE_FRAME_SIZE; i++) {
      Serial.print(reData[i], HEX);
      Serial.print(" ");
  }
  Serial.println("}");
  Serial.println();
}
void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
}
