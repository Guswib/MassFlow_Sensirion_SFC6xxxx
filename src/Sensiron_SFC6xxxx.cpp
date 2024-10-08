
#include "Sensiron_SFC6xxxx.h"


#include <Arduino.h>

#include <SensirionCore.h>


uint16_t Sensor_SFC6000::set(set_command_float_t command, float value){
    uint8_t main_command=highByte(command);
    uint8_t subcommad=lowByte(command);
    uint8_t txBuf[20];
    SensirionShdlcTxFrame txFrame(txBuf, 20);
    bool subcom = (last_subcommand != 0xFF);
    uint16_t error = txFrame.begin(main_command, 0, subcom+4);
    if(subcom)
      {error |= txFrame.addUInt8(0x00);}
    txFrame.addFloat(value);
    error |= txFrame.finish();
     for(int i=0;i<20;i++){
            Serial.print(", 0x");
            Serial.print(txBuf[i],HEX);
            }
             Serial.println();
    error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
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
      {error |= txFrame.addUInt8(0x00);}
    txFrame.addFloat(value);
    error |= txFrame.finish();
    error |= SensirionShdlcCommunication::sendFrame(txFrame, Serial1);
}


uint16_t Sensor_SFC6000::request(measure_commands_t command){

    uint8_t main_command=highByte(command);
    uint8_t subcommand=lowByte(command);
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
        last_command = main_command;
        last_subcommand = subcommand;
    }
    return error;
}

uint16_t Sensor_SFC6000::read()
{
    uint8_t rxBuffer2[50];
    uint16_t error =0;
    SensirionShdlcRxFrame rxFrame(rxBuffer2, 50);
    error = SensirionShdlcCommunication::receiveFrame(rxFrame, Serial1, 1000000);
     Serial.print("READ-----------state:");
            Serial.print(rxFrame.getState());
             Serial.print("\tCMD:");
             Serial.print(last_command,HEX);
             Serial.print("\t");
             Serial.print(last_subcommand,HEX);
    if(error)
    {
        for(int i=0;i<20;i++){
            Serial.print(", 0x");
            Serial.print(rxBuffer2[i]);
            }
             Serial.println();
    }
    else{
             Serial.print("\t");
             Serial.print(rxFrame.getCommand(),HEX);
             Serial.println();
    switch (rxFrame.getCommand())
    {
    case _SFC_com_setpoint:
        if(last_subcommand == 0) {rxFrame.getFloat(setValue);
            Serial.println("-----------SETVALUE");
            }
            
        break;
    case _SFC_com_measuredValue:
        if(last_subcommand == 0) rxFrame.getFloat(pv);
        
        break;
    case _SFC_com_controller_Configuration:
        if(last_subcommand == 0x00) rxFrame.getFloat(gain);
        if(last_subcommand == 0x03) rxFrame.getFloat(init_step);
        /* code */
        break;
    
    case _SFC_com_Advanced_Measurements:
        if(last_subcommand == 0x00) rxFrame.getUInt16(raw_flow);
        if(last_subcommand == 0x02) rxFrame.getUInt16(raw_thermal_conductivity);
        if(last_subcommand == 0x10) {
            rxFrame.getFloat(temperature);
            Serial.print("-----------TEMP");Serial.println(temperature);}


    default:
        break;
    }
    }
    return error;
}

  uint16_t pull_devInfo(deviceInfo_commands_t command, Stream & serCom)
  {
    ;
  }

