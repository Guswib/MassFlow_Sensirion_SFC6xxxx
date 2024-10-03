

#ifndef _Sensor_SFC6000x_H_
#define _Sensor_SFC6000x_H_

#include <stdint.h>
#include <string.h>
#include <Arduino.h>


#include "SHDLC.h"


#define _SFC_com_setpoint 0x00
#define _SFC_com_measuredValue 0x08
#define _SFC_com_controller_Configuration 0x22
#define _SFC_com_Advanced_Measurements 0x30
#define _SFC_com_Calibration_Information                0x40
#define _SFC_com_Get_Current_Calibration_Information    0x44
#define _SFC_com_Calibration                            0x45
#define _SFC_com_Device_Address                         0x90
#define _SFC_com_Device_Address                         0x91



enum currentCalibrationInfo
{
    Gas_Id = 0x12,
    Gas_Unit = 0x13,
    Full_Scale = 0x14


};


Calibration Information
class Sensor_SFC6000x  
 { 
    dev = shdlc();
    Stream & serCom;
    public: 
      //Sensor_HMM105(); 
      uint8_t begin(Stream & Serial_Port_for_RS485,uint8_t Server_Address = 0); 
      void debug_ini(Stream & Serial_Port); 

    float pull_SetPoint();
    uint8_t push_SetPoint(float const value);

    float pull_PV();


    push_ControllerGain(float const value);
    

    push_User_Init_Step(float const value){
        //subcommand 0x01
        _send_float(_SFC_com_controller_Configuration,0x03, value);

    }

    uint8_t push_DevAddress(uint8_t Address);
    uint8_t pull_DevAddress();
    uint8_t push_DevBaudRate(uint32_t Baud);
    uint8_t pull_DevBaudRate();

    pull_Calibration(uint32_t value){
        _send_uint32(uint8_t const Command,uint8_t const subCommand, value);
    }




    pull_currentCalibrationInfo()


    pull_Calibration(){
        dev.push(_serCom, _SFC_com_Calibration, 0, nullptr );
        ///
    }
////////////////////////////////////////////////////////
    uint8_t _send_float(uint8_t const Command,uint8_t const subCommand, float const value);
    uint8_t _send_uint32(uint8_t const Command,uint8_t const subCommand, uint32_t const value);
    uint8_t _request(uint8_t const Command,uint8_t const subCommand);
  
 };



#endif





