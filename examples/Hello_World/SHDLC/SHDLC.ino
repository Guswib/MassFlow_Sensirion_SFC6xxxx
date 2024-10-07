#include <SensirionCore.h>
#include <stdint.h>

uint8_t txBuffer[256];
uint8_t rxBuffer[256];

SensirionShdlcTxFrame txFrame(txBuffer, 256);
SensirionShdlcRxFrame rxFrame(rxBuffer, 256);

char errorMessage[50];


void set_setpoint(){
uint16_t error = txFrame.begin(0, 0, 5);
    uint8_t mockUInt8 = 0x01;
    error |= txFrame.addUInt8(mockUInt8);
    error |= txFrame.addFloat(200.0);
    error |= txFrame.finish();
    error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
}

void get_Baudrate(){
uint16_t error = txFrame.begin(0x91, 0, 0);
    error |= txFrame.finish();
    error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
    SensirionShdlcRxFrame rxFrame1(rxBuffer, 256);
   error = SensirionShdlcCommunication::receiveFrame(rxFrame1, Serial1, 1000000);
   SensirionShdlcRxFrame rxFrame2(rxBuffer, 256);
 error = SensirionShdlcCommunication::receiveFrame(rxFrame2, Serial1, 1000000);
  uint32_t data;
  rxFrame2.getUInt32(data);
  Serial.print("\nBUAD:");Serial.println(data);
}

void get_Flow(){
uint16_t error = txFrame.begin(0x08, 0, 1);
        uint8_t mockUInt8 = 0x01;
    error |= txFrame.addUInt8(mockUInt8);
    error |= txFrame.finish();
    error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
    SensirionShdlcRxFrame rxFrame1(rxBuffer, 256);
   error = SensirionShdlcCommunication::receiveFrame(rxFrame1, Serial1, 1000000);
   SensirionShdlcRxFrame rxFrame2(rxBuffer, 256);
 error = SensirionShdlcCommunication::receiveFrame(rxFrame2, Serial1, 1000000);
  float data;
  rxFrame2.getFloat(data);
  Serial.print("\nFlow:");Serial.println(data);
}

void get_Gain(){
uint16_t error = txFrame.begin(0x22, 0, 1);
        uint8_t mockUInt8 = 0x00;
    error |= txFrame.addUInt8(mockUInt8);
    error |= txFrame.finish();
    error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
    delay(400);
    SensirionShdlcRxFrame rxFrame1(rxBuffer, 256);
   error = SensirionShdlcCommunication::receiveFrame(rxFrame1, Serial1, 1000000);
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

void get_Temp(){
uint16_t error = txFrame.begin(0x30, 0, 1);
        uint8_t mockUInt8 = 0x10;
    error |= txFrame.addUInt8(mockUInt8);
    error |= txFrame.finish();
    error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
    delay(400);
    SensirionShdlcRxFrame rxFrame1(rxBuffer, 256);
  Serial.print("\nTemp: ");
   error = SensirionShdlcCommunication::receiveFrame(rxFrame1, Serial1, 1000000);
    if(error){
          Serial.print("error 0x");
        Serial.print(error,HEX);Serial.print(": ");
        errorToString(error, errorMessage,50);
          Serial.println(errorMessage);  }
   SensirionShdlcRxFrame rxFrame2(rxBuffer, 256);
 error = SensirionShdlcCommunication::receiveFrame(rxFrame2, Serial1, 1000000);
  Serial.print("\nTemp: ");
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

void read()
{
  for(int i=0;i<5;i++){
    delay(100); 
    int nr=Serial1.available();
    Serial.print("qqvail:"); Serial.print(i); Serial.print(":");Serial.println(nr);


      for(int i=0;i<0;i++)
      { Serial.print(", 0x");
        uint8_t data = Serial1.read();
        Serial.print( data,HEX);
      }
          
          SensirionShdlcRxFrame rxFrame1(rxBuffer, 256);
      uint16_t error;
      error = SensirionShdlcCommunication::receiveFrame(rxFrame1, Serial1, 1000000);
      
      if(error){
          Serial.print("error 0x");
        Serial.print(error,HEX);Serial.print(": ");
        errorToString(error, errorMessage,50);
          Serial.println(errorMessage);  }
      else{

        Serial.print("SUCCCESS ");
        float f=-1.0;
        //rxFrame.getFloat(f);
        uint8_t datas[50];
        rxFrame.getBytes(datas, 50);
        Serial.write(datas,50);
        Serial.println(f);
      }
    }
     int nr=Serial1.available();
    Serial.print("\tEND:"); Serial.println(nr);
    for(int i=0;i<nr;i++)
    { Serial.print(", 0x");
      uint8_t data = Serial1.read();
      Serial.print( data,HEX);
    }
}

void setup() {
    Serial.begin(115200);
     Serial1.begin(115200);
   
     delay(2000);
 Serial.println("START");
 get_Baudrate();
 set_setpoint();
      uint8_t mockCommand = 0x00;
    uint8_t mockAddress = 0;
    uint8_t mockDataLength = 1;
    uint16_t error = txFrame.begin(mockCommand, mockAddress, mockDataLength);
    uint8_t mockUInt8 = 0x00;
    error |= txFrame.addUInt8(mockUInt8);
    //error |= txFrame.addFloat(2.0);
      error |= txFrame.finish();
    while(Serial1.available())Serial1.read();
      error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
      errorToString(error, errorMessage,50);
     Serial.println(errorMessage);
     Serial1.write(txBuffer,7); 
      Serial1.write(0x7E);    Serial1.write(0x7E);     
for(int i=0;i<7;i++)
{ Serial.print(", 0x");
  Serial.print(txBuffer[i],HEX);
}
Serial.println();
 Serial.println("///////////////////////////"); 
 while(Serial1.available()==0);
for(int i=0;i<3;i++){
        delay(500); 
//while(Serial1.available()==0);
 Serial.print("Avail;");Serial.println(Serial1.available());
 for(int i=0;i<16;i++)
{ Serial.print(", 0x");
  uint8_t data = Serial1.read();
  Serial.print( data,HEX);
}
  uint16_t error = 0;
//  error = SensirionShdlcCommunication::receiveFrame(rxFrame, Serial1, 1000000);
  delay(500);
 
  Serial.print("error 0x");
  Serial.println(error,HEX);
  
  errorToString(error, errorMessage,50);
     Serial.println(errorMessage);              
  
        mockCommand = rxFrame.getCommand();
    mockAddress = rxFrame.getAddress();
    mockDataLength = rxFrame.getDataLength();
       mockDataLength = rxFrame.getDataLength();
       uint8_t    state = rxFrame.getState();
  Serial.print("cm:");
   Serial.print( mockCommand);
    Serial.print("\tadd:");
    Serial.print(mockAddress);
      Serial.print("\tState:");
     
     Serial.print(state);
      Serial.print("\tlength:");
       Serial.print(mockDataLength);
    Serial.println();
    }
}

void loop(){
    Serial.print("\n////////////////WRITE:");
    int nr=Serial1.available();
    for(int i=0;i<nr;i++)
    { Serial.print(", 0x");
      uint8_t data = Serial1.read();
      Serial.print( data,HEX);
    }
    Serial.print("Avail:");Serial.println(nr);
     Serial.print("SETPOINT:");
    set_setpoint();
    read();
    while(Serial1.available()>0){Serial1.read();}
    Serial.print("Avail:");Serial.println(nr);
    Serial.println("dddd");
    //SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
    uint16_t error = 0;
    read();
 while(Serial1.available()>0)Serial1.read();
 get_Flow();
 while(Serial1.available()>0)Serial1.read();
 get_Gain();
 while(Serial1.available()>0)Serial1.read();
 get_Temp();
}