
#include "Sensirion_SFC6xxxx.h"
#include <SensirionCore.h>
   char errorMessage[50];
Sensor_SFC6000 sen;

void printBuf(){
   Serial.println();
   while(Serial1.available()){Serial.print(", 0x");Serial.print(Serial1.read(),HEX);} 
   Serial.println();
}

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

    Serial.println("\n\n\n\n\n////////////////////////////////\nHello World------------------------------------");

   while(Serial1.available())Serial1.read();
   sen.device_reset();
  Serial.print("SetValue:  ");
    sen.set(set_command_float_t::SetValue, 15.4);
     error = sen.read();
      error = sen.read();
    printBuf();
    // sen.read();
    //sen.read();
      Serial.print("Gain:  ");
    sen.set(set_command_float_t::Gain, 1.523);
     error = sen.read();
      error = sen.read();
 printBuf();
   Serial.print("ProductType:  ");
    sen.pull_devInfo(deviceInfo_commands_t::Product_Type,Serial);
    Serial.print("Product_Name:  ");
    sen.pull_devInfo(deviceInfo_commands_t::Product_Name,Serial);
    sen.pull_devInfo(deviceInfo_commands_t::Article_Code,Serial);
    sen.pull_devInfo(deviceInfo_commands_t::Serial_Number,Serial);

    Serial.print("SetValue:  ");
    sen.set(set_command_float_t::SetValue, 1.25);
    sen.request(measure_commands_t::SetValue);
    error = sen.read();
    Serial.print("\nSetValue:  ");
    Serial.println(sen.setValue);
    sen.set(set_command_float_t::Gain, 2.5);
    sen.set(set_command_float_t::Init_Step, 1.2);
    //sen.set(set_command_int_t::Init_Step, 1.2);

        Serial.println("\n\nDONE INI------------------------------------");

}

measure_commands_t m[] ={
  measure_commands_t::Gain,
  measure_commands_t::Init_Step,
  measure_commands_t::Init_Step,
  measure_commands_t::Temperature,  
  measure_commands_t::ProcessValue,
  measure_commands_t::SetValue,
  measure_commands_t::Raw_Flow,
  measure_commands_t::Raw_Thermal_Conductivity


  
  
        };

void loop() {
     while(Serial1.available())Serial1.read();
   //sen.set(set_command_float_t::wSetValue, 4);
   Serial.println("NEW");
   uint16_t error =0; 
  // put your main code here, to run repeatedly:
   // Serial.println("\nHello World");
    delay(2000);
    for(int i=0; i<7;i++)
    { delay(1000);
      while(Serial1.available())Serial1.read();
      Serial.print("loop:"); Serial.print(i);
      Serial.print(" com:");Serial.print(static_cast<uint16_t>(m[i]),HEX);
      Serial.println();
      //Serial1.write(0x7E);
      //Serial1.write(0x7E);
      for(int k=0;k<2;k++){
        error = sen.request(m[i]);
        //Serial1.write(0x7E);
        error_check(error);
        //if(error == 0x206) break;
        //if(error == 0) break;
        delay(400);
        int a = Serial1.available();
        
        if(a>0) {Serial.print(a);break;}
      }
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