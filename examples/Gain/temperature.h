#include <Arduino.h>

#include <SensirionCore.h>

void get_Temperature(){
    uint8_t txBuffer1[20];
  Serial.println("\nTemp:////////////////////////////////");
   SensirionShdlcTxFrame txFrame(txBuffer1, 20);
  int command=0x30;
  uint16_t error = txFrame.begin(command, 0, 1);
  error |= txFrame.addUInt8(0x10);
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
    {if(error){
        char errorMessage[50];
          Serial.print("error 0x");
          Serial.print(error,HEX);Serial.print(": ");
          errorToString(error, errorMessage,50);
          Serial.println(errorMessage);  }
        else{
          Serial.print("\tTemp_value:");
    float data;
    rxFrame.getFloat(data);
    Serial.println(data);
    }
    }
  }
}