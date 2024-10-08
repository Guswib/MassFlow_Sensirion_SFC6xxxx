#include <stdint.h>
#include <Arduino.h>

#include <SensirionCore.h>


/////////////////////////////////////////////////////////////////////////////
void get_DeviceInfo_ProductType(){
    uint8_t txBuffer1[20];
  Serial.println("\nget_DeviceInfo_ProductType:////////////////////////////////");
   SensirionShdlcTxFrame txFrame(txBuffer1, 20);
  int command=0xD0;
  uint16_t error = txFrame.begin(command, 0, 1);
  error |= txFrame.addUInt8(0x00);
  error |= txFrame.finish();
  error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);

  uint8_t rxBuffer2[50];
  SensirionShdlcRxFrame rxFrame(rxBuffer2, 50);
  //error = SensirionShdlcCommunication::receiveFrame(rxFrame, Serial1, 1000000);
  delay(200);
  for(int i=0; i<2;i++)
    {
    Serial.print("PART"); Serial.print(i);Serial.print("--");Serial.println(Serial1.available());
    error = SensirionShdlcCommunication::receiveFrame(rxFrame, Serial1, 1000000);
    if(rxFrame.getCommand()== command)
    {
      if(error){
        char errorMessage[50];
        Serial.print("error 0x");
        Serial.print(error,HEX);Serial.print(": ");
        errorToString(error, errorMessage,50);
        Serial.println(errorMessage);  }
      else{
        Serial.print("\tProductType:");
        uint8_t Message[50];
         //Message[49]='\00';
        rxFrame.getBytes(Message,50);
        for(int i=0;i<49;i++){
          char c = Message[i];
          if (c == 0) break;
          Serial.print(c);
        }
         Serial.println();
      }
    }
  }
  Serial.println();
}



/////////////////////////////////////////////////////////////////////////////
void get_DeviceInfo_ProductName(){
    uint8_t txBuffer1[20];
  Serial.println("\nget_DeviceInfo_ProductName:////////////////////////////////");
   SensirionShdlcTxFrame txFrame(txBuffer1, 20);
  int command=0xD0;
  uint16_t error = txFrame.begin(command, 0, 1);
  error |= txFrame.addUInt8(0x01);
  error |= txFrame.finish();
  error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);

  uint8_t rxBuffer3[50];
  SensirionShdlcRxFrame rxFrame(rxBuffer3, 50);
  //error = SensirionShdlcCommunication::receiveFrame(rxFrame, Serial1, 1000000);
  delay(200);
  for(int i=0; i<2;i++)
    {
    Serial.print("PART"); Serial.print(i);Serial.print("--");Serial.println(Serial1.available());
    error = SensirionShdlcCommunication::receiveFrame(rxFrame, Serial1, 1000000);
    if(rxFrame.getCommand()== command)
    {if(error){
        char errorMessage[50];
          Serial.print("error 0x");
          Serial.print(error,HEX);Serial.print(": ");
          errorToString(error, errorMessage,50);
          Serial.println(errorMessage);  }
        else{
          Serial.print("\tProductType:");
    
    uint8_t Message[50];
    //Message[49]='\00';
    rxFrame.getBytes(Message,50);
    //String a = String(Message);
    //Serial.print(Message);
    // Serial.println();
    for(int i=0;i<49;i++){
      char c = Message[i];
      if (c == 0) break;
      Serial.print(c);
    //Serial.print(Message[i]);
    }
    }
    }
  }
  Serial.println();
}