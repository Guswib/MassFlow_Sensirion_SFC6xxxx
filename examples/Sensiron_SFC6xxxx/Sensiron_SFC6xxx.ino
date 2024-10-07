
#include "Sensiron_SFC6xxxx.h"


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