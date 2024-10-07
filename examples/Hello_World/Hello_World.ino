//Simple Test of a Sensiron


#define startChar 0x7E
#define endChar 0x7E
#define dev_adr 0x00
#define dev_adr 0x00
#define baudrate 115200

// a MOSI FRAME : DEV_adr, CMD, Length, TX_Data... , CHK
//a  MISO FRAME : DEV_adr,CMD,STATE, Length, RX_Data..., CHK,
uint8_t Get_SetPointFrame[] = {dev_adr, 0x08, 0x01, 0x01} ;

#define bufferSize 50

uint8_t rx_buffer[bufferSize];




uint8_t chechNum_calc(const uint8_t * buffer, size_t size)
{
    uint32_t sum = 0;
    
    for(int i=0;i<size; i++){
        sum += buffer[i];
    }
    Serial.print("\tsm(");
    Serial.print(size);
    Serial.print(") ");
    Serial.print(sum);
    Serial.print(" ");
    uint8_t ret = ((uint8_t)(sum & (0xff)));
    //lowByte(w)
    //Serial.print(~ret & (0xff),BIN);Serial.print(" ");
    return ~ret;
}
void send(const uint8_t * buffer, size_t size){
    
    Serial1.write(startChar);
    Serial1.write(buffer,size);
    Serial1.write(chechNum_calc(buffer, size));
    Serial1.write(endChar);
    Serial.print("\nSEND: ");
    
    Serial.print(startChar,HEX);
    Serial.print("\t");
    for(int i=0;i<size;i++){
      Serial.print(", 0x");
      Serial.print(buffer[i],HEX);
      
    }
    Serial.print("\tCheck:");
    Serial.print(chechNum_calc(buffer, size),BIN);
    Serial.print("\tend:");
    Serial.print(endChar,HEX);
    Serial.println();

}

int16_t read_until(){
  unsigned long start = millis();
  for(uint8_t i=0;i<bufferSize ;i++){
      while(Serial1.available()== 0 && (millis()-start)<1000);
      if(Serial1.available()== 0) {return -1;
      }else{
      uint8_t cChar = Serial1.read();
      if(cChar == (uint8_t)startChar){return i;}
      else{rx_buffer[i]= cChar;}
      }
  }
  return bufferSize;
}

void RX(){
  unsigned long start = millis();
  //while(Serial1.available()== 0 && start-millis<1000)
    int16_t nr_bytes = read_until(); 
    // Serial1.readBytesUntil(startChar, rx_buffer,bufferSize);
    Serial.print("1.Bytes: ");
    Serial.print(nr_bytes);
    if(nr_bytes<0){
      Serial.println("Timed out");
    }else{
      if(nr_bytes>0)
      {
        Serial.print("StrangeStart: ");
        for(uint8_t i=0;i<nr_bytes ;i++){
          uint8_t data = rx_buffer[i];
          Serial.print(",0x");
                  
                  Serial.print(data, HEX);
                }
        Serial.println("");
      }else{
        nr_bytes = read_until(); 
        // Serial1.readBytesUntil(endChar, rx_buffer, bufferSize); 
        if(nr_bytes>0){
          
            Serial.print(" 2.Bytes: ");
            Serial.print(nr_bytes);
          
            Serial.print("\tDevAdr:0x");
            Serial.print(rx_buffer[0],HEX);
            Serial.print("\tCMD:0x");
            Serial.print(rx_buffer[1],HEX);
            Serial.print("\tSTATE:0x"); 
            Serial.print(rx_buffer[2],HEX);
            Serial.print("\tLength: ");
            Serial.print(rx_buffer[3]);
            uint8_t length = rx_buffer[3];
            if(length>bufferSize) length = bufferSize;
            if(rx_buffer[2]==0){
              Serial.print("\tRXData:");
              for(uint8_t i=4;i<length+4 ;i++){
                uint8_t data = rx_buffer[i];
                  Serial.print(",0x");
                  
                  Serial.print(data, HEX);
                }
            }
            Serial.print("\tCRC: ");
            Serial.print(rx_buffer[nr_bytes-1],HEX);
            Serial.print("\tCRC: ");
            Serial.print((uint8_t)(chechNum_calc(rx_buffer, nr_bytes-1))& (0xff),HEX);
            Serial.println();
            
        }else{
            Serial.println("no end to message");
        }
      }
    }
    //Serial.println(" ");Serial.print("CLEAN:");Serial.println(Serial1.available());
    //while(Serial1.available()) {Serial.print(" ");Serial.print(Serial1.read(),HEX);}
}


void read_raw()
{
  for(uint8_t i=0;i<10 ;i++){
        delay(100);
        if(Serial1.available()>0) break;
      }
      while(Serial1.available()) {Serial.print(" ");Serial.print(Serial1.read(),HEX);}
      delay(200);
          while(Serial1.available()) {Serial.print(" ");Serial.print(Serial1.read(),HEX);}

}

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
     
    Serial1.begin(baudrate);
    Serial1.setTimeout(1000);
    while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
    }
    delay(2000);
    Serial.println("Hello World--------------");

    send(Get_SetPointFrame,4);
    RX();
    RX();
    
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println("\nHello World");
    delay(2000);
    Serial.println(" ");Serial.print("CLEAN:");Serial.println(Serial1.available());
    while(Serial1.available()) {Serial.print(" ");Serial.print(Serial1.read(),HEX);}
    send(Get_SetPointFrame,4);
    
    //read_raw();
/*
    for(uint8_t i=0;i<10 ;i++){
      delay(100);
      int nr_bytes = Serial1.readBytesUntil(endChar, rx_buffer, bufferSize); 
      Serial.print("\n");
      Serial.print(i);
      Serial.print(": ");
      for(uint8_t j=0;j<nr_bytes ;j++){
        Serial.print(",");Serial.print(rx_buffer[j],HEX);
        }
    }*/
    RX();RX();RX();
}








