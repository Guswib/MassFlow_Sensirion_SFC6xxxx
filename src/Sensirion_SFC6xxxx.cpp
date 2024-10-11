
#include "Sensirion_SFC6xxxx.h"


#include <Arduino.h>

#include <SensirionCore.h>


uint16_t Sensor_SFC6000::set(set_command_float_t command, float value){
    uint16_t com = static_cast<uint16_t> (command);
    uint8_t main_command=highByte(com);
    uint8_t subcommad=lowByte(com);
    uint8_t txBuf[20];
    SensirionShdlcTxFrame txFrame(txBuf, 20);
    bool subcom = (last_subcommand != 0xFF);
    uint16_t error = txFrame.begin(main_command, 0, subcom+4);
    if(subcom)
      {error |= txFrame.addUInt8(subcommad);}
    txFrame.addFloat(value);
    error |= txFrame.finish();
     for(int i=0;i<20;i++){
            Serial.print(", 0x");
            Serial.print(txBuf[i],HEX);
            }
             Serial.println();
    error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
    if(error==0){
        last_command = com;
    }
    return error;
}
 
uint16_t Sensor_SFC6000::set(set_command_int_t command, uint32_t value)
{   
    uint8_t main_command=highByte(command);
    uint8_t subcommad=lowByte(command);
    uint8_t txBuffer[20];
    for(int i=0;i<20;i++) txBuffer[i]=0;
    SensirionShdlcTxFrame txFrame(txBuffer, 20);
    bool subcom = (last_subcommand != 0xFF);
    uint16_t error = txFrame.begin(last_command, 0, subcom+4);
    if(subcom)
      {error |= txFrame.addUInt8(subcommad);}
    txFrame.addFloat(value);
    error |= txFrame.finish();
    error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
}

uint16_t Sensor_SFC6000::request(measure_commands_t command){
    uint16_t com = static_cast<uint16_t> (command);
    return _request(com);
}

uint16_t Sensor_SFC6000::_request(uint16_t com){
    uint8_t main_command=highByte(com);
    uint8_t subcommand=lowByte(com);
    uint8_t txBuffer[50];
    for(int i=0;i<20;i++) txBuffer[i]=0;
    SensirionShdlcTxFrame txFrame(txBuffer, 50);
    bool subcom = (subcommand != 0xFF);
    uint16_t error = txFrame.begin(main_command, 0, subcom);
    if(subcom)
      {error |= txFrame.addUInt8(subcommand);}
    error |= txFrame.finish();
     for(int i=0;i<20;i++){
            Serial.print(", 0x");
            Serial.print(txBuffer[i],HEX);
            }
             Serial.println();
    error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
    if(error==0){
        last_command = com;
        last_subcommand = subcommand;
    }
    return error;
}

uint16_t Sensor_SFC6000::read(uint8_t * buff, size_t maxBytes)
{
    uint8_t rxBuffer2[50];
    uint16_t error =0;
    SensirionShdlcRxFrame rxFrame(rxBuffer2, 50);
    error = SensirionShdlcCommunication::receiveFrame(rxFrame, Serial1, 1000000);
    
    //Serial.print("READ-----------state:");
    //        Serial.print(rxFrame.getState(),HEX);
    //         Serial.print("\tCMD:");
    //         Serial.print(last_command,HEX);
    //         Serial.print("\t");
    //         Serial.print(last_subcommand,HEX);
    if(error)
    {
      //  for(int i=0;i<20;i++){
      //      Serial.print(", 0x");
      //      Serial.print(rxBuffer2[i],HEX);
      //      }
      //       Serial.println();
      ;
    }
    else{
         //    Serial.print("\t");
         //    Serial.print(rxFrame.getCommand(),HEX);
        //     Serial.println();
        if(rxFrame.getDataLength()==0){
            uint8_t main_command=highByte(last_command);
            if(rxFrame.getCommand() == main_command)
                Serial.println("Command Arrived");
        }else{

        
        switch (last_command){
            case _SFC_com_setpoint:
                rxFrame.getFloat(setValue);
                Serial.println("-----------SETVALUE ");
                break;
            case _SFC_com_ProcessValue:
                rxFrame.getFloat(pv);
                 Serial.println("-----------ProcessValueE ");
            break;
            /////////////Ctrl

            case _SFC_com_controller_Configuration_GAIN:
                rxFrame.getFloat(gain);
                  Serial.println("-----------Gain ");
                break;
            case _SFC_com_controller_Configuration_Init_Step:
                rxFrame.getFloat(init_step);
                 Serial.println("-----------Init ");
                break;
            /////////////Advanced_Measurement

            case _SFC_com_Advanced_Measurements_Raw_Flow:
                rxFrame.getUInt16(raw_flow);
            case _SFC_com_Advanced_Measurements_Raw_Thermal_Conductivity:
                rxFrame.getUInt16(raw_thermal_conductivity);
                break;
            case _SFC_com_Advanced_Measurements_Temperature:
                rxFrame.getFloat(temperature);
                Serial.print("-----------TEMP ");Serial.println(temperature);
            break;

            case _SFC_com_DeviceInfo_Product_Type:
            case _SFC_com_DeviceInfo_Product_Name:
            case _SFC_com_DeviceInfo_Article_Code:
            case _SFC_com_DeviceInfo_Serial_Number:
                rxFrame.getBytes(buff,maxBytes);
                break;
             default:
            break;
        }
       } 
        
       
   
    }
    return error;
}

uint16_t Sensor_SFC6000::pull_devInfo(deviceInfo_commands_t command, Stream & serCom)
  {
    uint16_t com = static_cast<uint16_t> (command);
    uint16_t error = _request(com);
    uint8_t data[20];
    for(int i=0; i<2; i++){
        error = read(data, 20);
        if(error ==0 ) 
            {serCom.print(reinterpret_cast<char*>(data));
            serCom.println();
            break;}
         if(error ==0x0203 ) break;
    }

  }

