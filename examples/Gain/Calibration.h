#include <stdint.h>
#include <Arduino.h>

#include <SensirionCore.h>

void get_nr_of_calibration(){
    uint8_t txBuffer1[20];
  Serial.println("\nget_nr_of_calibration:////////////////////////////////");
   SensirionShdlcTxFrame txFrame(txBuffer1, 20);
  int command=0x40;
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
    {if(error){
        char errorMessage[50];
          Serial.print("error 0x");
          Serial.print(error,HEX);Serial.print(": ");
          errorToString(error, errorMessage,50);
          Serial.println(errorMessage);  }
        else{
          Serial.print("\tCalibration_nr_of_value:");
    uint32_t data;
    rxFrame.getUInt32(data);
    Serial.println(data);
    }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
void get_current_calibration_GasID(){
    uint8_t txBuffer1[20];
  Serial.println("\nget_current_calibration_GasID:////////////////////////////////");
   SensirionShdlcTxFrame txFrame(txBuffer1, 20);
  int command=0x44;
  uint16_t error = txFrame.begin(command, 0, 1);
  error |= txFrame.addUInt8(0x12);
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
          Serial.print("\tGAS_ID:");
    uint32_t data;
    rxFrame.getUInt32(data);
    Serial.println(data);
    }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
void get_current_calibration_GasUNIT(){
    uint8_t txBuffer1[20];
  Serial.println("\nget_current_calibration_GasUNIT:////////////////////////////////");
   SensirionShdlcTxFrame txFrame(txBuffer1, 20);
  int command=0x44;
  uint16_t error = txFrame.begin(command, 0, 1);
  error |= txFrame.addUInt8(0x13);
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
          Serial.print("\tGAS_UNIT:");
    int8_t data0;
    rxFrame.getInt8(data0);
     Serial.print("\tprefix:");
    Serial.print(data0);
    uint8_t data1;
    rxFrame.getUInt8(data1);
     Serial.print("\tMediumUnit:");
    Serial.print(data1);
    uint8_t data2;
    rxFrame.getUInt8(data2);
    Serial.print("\tTimebase:");
    Serial.println(data2);
    }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
void get_current_calibration_GasFullScale(){
    uint8_t txBuffer1[20];
  Serial.println("\nget_current_calibration_GasFullScale:////////////////////////////////");
   SensirionShdlcTxFrame txFrame(txBuffer1, 20);
  int command=0x44;
  uint16_t error = txFrame.begin(command, 0, 1);
  error |= txFrame.addUInt8(0x14);
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
          Serial.print("\tFull_Scale:");
    float data;
    rxFrame.getFloat(data);
    Serial.println(data);
    
    }
    }
  }
}