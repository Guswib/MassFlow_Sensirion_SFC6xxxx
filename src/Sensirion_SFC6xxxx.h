
#ifndef _Sensor_SFC6000_H_
#define _Sensor_SFC6000_H_


#include <stdint.h>
#include <Arduino.h>


//#define _SFC_com_setpoint 0x00
//#define _SFC_com_measuredValue 0x08
#define _SFC_com_controller_Configuration 0x22
#define _SFC_com_Advanced_Measurements 0x30
#define _SFC_com_Calibration_Information                0x40
#define _SFC_com_Get_Current_Calibration_Information    0x44
#define _SFC_com_Calibration                            0x45
#define _SFC_com_Device_Address                         0x90
#define _SFC_com_Device_Address                         0x91
#define _SFC_com_DeviceInfo                             0xD0

//subcommands
#define _SFC_subCom_setpoint 0x01
#define _SFC_subCom_getMeasuredValue 0x01


#define _SFC_com_setpoint                                       0x0001
#define _SFC_com_ProcessValue                                   0x0801
#define _SFC_com_controller_Configuration_GAIN                  0x2200
#define _SFC_com_controller_Configuration_Init_Step             0x2203
#define _SFC_com_Advanced_Measurements_Raw_Flow                 0x3000
#define _SFC_com_Advanced_Measurements_Raw_Thermal_Conductivity 0x3002
#define _SFC_com_Advanced_Measurements_Temperature              0x3010

#define _SFC_com_Calibration_Information                        0x4000
#define _SFC_com_Calibration_Information_Calibration_Validity   0x4010
#define _SFC_com_Calibration_Information_Get_Calibration_Gas_Id 0x4012

#define _SFC_com_Current_Calibration_Information_Get_Gas_Id     0x4412


#define _SFC_com_DeviceInfo_Product_Type                        0xD000
#define _SFC_com_DeviceInfo_Product_Name                        0xD001
#define _SFC_com_DeviceInfo_Article_Code                        0xD002
#define _SFC_com_DeviceInfo_Serial_Number                       0xD003



enum class measure_commands_t : uint16_t
{
    SetValue                    = _SFC_com_setpoint,
    ProcessValue                = _SFC_com_ProcessValue,
    Gain                        = _SFC_com_controller_Configuration_GAIN,
    Init_Step                   = _SFC_com_controller_Configuration_Init_Step,
    Raw_Flow                    = _SFC_com_Advanced_Measurements_Raw_Flow,
    Raw_Thermal_Conductivity    = _SFC_com_Advanced_Measurements_Raw_Thermal_Conductivity,
    Temperature                 = _SFC_com_Advanced_Measurements_Temperature
};

enum class set_command_float_t : uint16_t
{
    SetValue                    = 0x0001,
    Gain                        = 0x2200,
    Init_Step                   = 0x2203,
};

enum set_command_int_t : uint16_t
{
    aSetValue                    = 0x0001,
};


enum deviceInfo_commands_t : uint16_t
{
    Product_Type                    = _SFC_com_DeviceInfo_Product_Type,
    Product_Name                    = _SFC_com_DeviceInfo_Product_Name,
    Article_Code                    = _SFC_com_DeviceInfo_Article_Code,
    Serial_Number                   = _SFC_com_DeviceInfo_Serial_Number,
};


class Sensor_SFC6000  
{
    public:
    float pv =0.0;
    float setValue =0.0;
    float gain =0.0;
    float  init_step=0.0;
     float  temperature=0.0;
    uint8_t gas_id =0;
    uint16_t last_command=0;
    uint8_t last_subcommand=0;
    uint16_t raw_flow=0;
    uint16_t raw_thermal_conductivity=0;
    //Sensor_SFC6000();
    uint16_t request(measure_commands_t command);
    uint16_t read (uint8_t * buff = nullptr, size_t maxBytes = 0);
    uint16_t set(set_command_float_t command, float value);
    uint16_t set(set_command_int_t command, uint32_t value);

    uint16_t pull_devInfo(deviceInfo_commands_t command, Stream & serCom);

    uint16_t _request(uint16_t com);
   
};

#endif