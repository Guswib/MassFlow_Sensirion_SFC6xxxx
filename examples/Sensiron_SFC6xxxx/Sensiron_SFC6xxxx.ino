
#include "Sensiron_SFC6xxxx.h"
#include <SensirionCore.h>
   char errorMessage[50];
Sensor_SFC6000 sen;


void error_check(uint16_t error){
 if(error){
          Serial.print("error 0x");
          Serial.print(error,HEX);Serial.print(": ");
          errorToString(error, errorMessage,50);
          Serial.println(errorMessage);  }

}

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
     
    Serial1.begin(115200);
    Serial1.setTimeout(1000);
    while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
    }
    delay(2000);   
     uint16_t error =0; 

    Serial.println("Hello World--------------");

   while(Serial1.available())Serial1.read();

    sen.set(set_command_float_t::wSetValue, 15.4);
    sen.set(set_command_float_t::wGain, 1.523);
}

measure_commands_t m[] ={
   measure_commands_t::Gain,
   measure_commands_t::Init_Step,
    measure_commands_t::Temperature,  
  measure_commands_t::ProcessValue,
  measure_commands_t::SetValue
  
  
        };

void loop() {
     while(Serial1.available())Serial1.read();
   //sen.set(set_command_float_t::wSetValue, 4);
   Serial.println("NEW");
   uint16_t error =0; 
  // put your main code here, to run repeatedly:
   // Serial.println("\nHello World");
    delay(2000);
    for(int i=0; i<5;i++)
    { delay(1000);
       while(Serial1.available())Serial1.read();
      Serial.print("loop:");
       Serial.print(i);
       Serial.print(" com:");
       Serial.print(m[i],HEX);
        Serial.println();
 error = sen.request(m[i]);
    error_check(error);
    delay(200);
    Serial.print(Serial1.available());
    
    Serial.print("\tr1 :");
    error = sen.read();
    error_check(error);
    Serial.print(Serial1.available());
    Serial.print("\tr2 :");
    
    error = sen.read();
   error_check(error);
     Serial.println();
}
    Serial.print("SV:");
     Serial.print(sen.setValue);
     Serial.print("\tPV:");
          Serial.print(sen.pv);
     Serial.print("\tGAIN:");
     Serial.print(sen.gain);
          Serial.print("\tTemp:");
     Serial.print(sen.temperature);
       Serial.println("");
    
}