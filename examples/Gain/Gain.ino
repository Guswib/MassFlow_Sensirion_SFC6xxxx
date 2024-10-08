#include <SensirionCore.h>
#include <stdint.h>

#include "Device_info.h"
#include "Calibration.h"
#include "temperature.h"
#include "flow.h"
uint8_t txBuffer[256];
uint8_t rxBuffer[256];

//SensirionShdlcTxFrame txFrame(txBuffer, 256);
//SensirionShdlcRxFrame rxFrame(rxBuffer, 256);

char errorMessage[50];

void get_Flow3(){
  Serial.print("\nFlow:/");
   SensirionShdlcTxFrame txFrame(txBuffer, 256);
  int command=0x08;
  uint16_t error = txFrame.begin(0x08, 0, 1);
  error |= txFrame.addUInt8(0x01);
  error |= txFrame.finish();
  error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
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

void get_Baudrate(){
   Serial.print("\nBAUD:");
   SensirionShdlcTxFrame txFrame(txBuffer, 256);
uint16_t error = txFrame.begin(0x91, 0, 0);
    error |= txFrame.finish();
    error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
    SensirionShdlcRxFrame rxFrame1(rxBuffer, 256);
   error = SensirionShdlcCommunication::receiveFrame(rxFrame1, Serial1, 1000000);
 //  for(int i=0;i<12;i++){
 //  Serial.print(", 0x");
 //   Serial.print(rxBuffer[i]);
 //   }
    Serial.println();
    Serial.print("Part2: ");
   SensirionShdlcRxFrame rxFrame2(rxBuffer, 256);
 error = SensirionShdlcCommunication::receiveFrame(rxFrame2, Serial1, 1000000);
  //  for(int i=0;i<12;i++){
  // Serial.print(", 0x");
  //  Serial.print(rxBuffer[i]);
  //  }
  uint32_t data;
  rxFrame2.getUInt32(data);
  Serial.print("\n\tBUAD:");Serial.println(data);
}

void get_Gain(){
  Serial.print("\nGAIN:");
  Serial.println(Serial1.available());
   while(Serial1.available()>0){
      uint8_t c = Serial1.read();
      Serial.print(",0x");
      Serial.print(c,HEX);
    }Serial.println("");
    uint8_t txBuffer1[30];
    SensirionShdlcTxFrame txFrame1(txBuffer1, 30);
    uint16_t error = txFrame1.begin(0x22, 0, 1);
    uint8_t mockUInt8 = 0x00;
    error |= txFrame1.addUInt8(mockUInt8);
    error |= txFrame1.finish();
    error |= SensirionShdlcCommunication::sendFrame(txFrame1, Serial1);
    Serial.print("TXERROR");
    Serial.println(error);

    delay(200);
     Serial.println(Serial1.available());
    
    
     int nr =Serial1.available();
    
    while(Serial1.available()>0){
      uint8_t c = Serial1.read();
      Serial.print(",0x");
      Serial.print(c,HEX);
    }Serial.println("");
    Serial.print(Serial1.available());
    nr =Serial1.available();
    for(int i=0; i<nr;i++){
      uint8_t c = Serial1.read();
      Serial.print(",0x");
      Serial.print(c,HEX);
    }Serial.println("");
     Serial.println(Serial1.available());
    
    
    //SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
    for(int i=0; i<2;i++){
        Serial.print("PART"); Serial.println(i);Serial.println(Serial1.available());
   SensirionShdlcRxFrame rxFrame2(rxBuffer, 256);
 error = SensirionShdlcCommunication::receiveFrame(rxFrame2, Serial1, 1000000);
  Serial.print("\nGAIN:");
  if(error){
          Serial.print("error 0x");
        Serial.print(error,HEX);Serial.print(": ");
        errorToString(error, errorMessage,50);
          Serial.println(errorMessage);  }
      else{
  float data;
  rxFrame2.getFloat(data);
   Serial.println(data);
  }
  }
}


void get_Gain2(){
  Serial.print("\nGAIN:");
  Serial.println(Serial1.available());
    SensirionShdlcTxFrame txFrame1(txBuffer, 30);
    uint16_t error = txFrame1.begin(0x22, 0, 1);
    uint8_t mockUInt8 = 0x00;
    error |= txFrame1.addUInt8(mockUInt8);
    error |= txFrame1.finish();
    error |= SensirionShdlcCommunication::sendFrame(txFrame1, Serial1);
    Serial.print("TXERROR");
    Serial.println(error);

    delay(200);

    
    
    for(int i=0; i<2;i++){
    Serial.print("PART"); Serial.print(i);Serial.print("--");Serial.println(Serial1.available());
  SensirionShdlcRxFrame rxFrame2(rxBuffer, 256);
  error = SensirionShdlcCommunication::receiveFrame(rxFrame2, Serial1, 1000000);
  
  if(error){
          Serial.print("Gerror 0x");
        Serial.print(error,HEX);Serial.print(": ");
        errorToString(error, errorMessage,50);
          Serial.println(errorMessage);  }
      else{
        Serial.print("\tGAINvalue:");
  float data;
  rxFrame2.getFloat(data);
   Serial.println(data);
  }
  }
}
  
void setup() {
    Serial.begin(115200);
     Serial1.begin(115200);
   
     delay(2000);
 Serial.println("START");
 get_Baudrate();
 delay(100);
 get_Gain();
}
void loop(){
  Serial.println("START/////////////////////////////////////////////////////");
get_Gain2();
delay(1000);
get_Baudrate();
get_Flow();
get_Temperature();
get_nr_of_calibration();
get_current_calibration_GasID();
get_current_calibration_GasUNIT();
get_current_calibration_GasFullScale();
get_DeviceInfo_ProductType();
get_DeviceInfo_ProductName();
}