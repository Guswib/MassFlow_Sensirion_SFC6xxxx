#include <Arduino.h>

#include <SensirionCore.h>


void get_Flow(){
  Serial.println("\nFlow://///////////////////////////////////");
    uint8_t txBuffer[20];
   SensirionShdlcTxFrame txFrame(txBuffer, 256);
  int command=0x08;
  uint16_t error = txFrame.begin(0x08, 0, 1);
  error |= txFrame.addUInt8(0x01);
  error |= txFrame.finish();
  error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
   uint8_t rxBuffer[50];
  SensirionShdlcRxFrame rxFrame(rxBuffer, 256);
  //error = SensirionShdlcCommunication::receiveFrame(rxFrame, Serial1, 1000000);
  delay(200);
  for(int i=0; i<2;i++)
    {
      Serial.print("PART"); Serial.print(i);Serial.print("--");Serial.println(Serial1.available());
    error = SensirionShdlcCommunication::receiveFrame(rxFrame, Serial1, 1000000);
    if(rxFrame.getCommand()== command)
    {if(error){
            char errorMessage[50];
          Serial.print("Gerror 0x");
          Serial.print(error,HEX);Serial.print(": ");
          errorToString(error, errorMessage,50);
          Serial.println(errorMessage);  }
        else{
          Serial.print("\tFlow_value:");
    float data;
    rxFrame.getFloat(data);
    Serial.println(data);
    }
    }
  }
}