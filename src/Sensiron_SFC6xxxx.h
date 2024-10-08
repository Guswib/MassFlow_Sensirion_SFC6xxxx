
#ifndef _Sensor_SFC6000_H_
#define _Sensor_SFC6000_H_


#include <stdint.h>
#include <Arduino.h>


#define _SFC_com_setpoint 0x00
#define _SFC_com_measuredValue 0x08
#define _SFC_com_controller_Configuration 0x22
#define _SFC_com_Advanced_Measurements 0x30
#define _SFC_com_Calibration_Information                0x40
#define _SFC_com_Get_Current_Calibration_Information    0x44
#define _SFC_com_Calibration                            0x45
#define _SFC_com_Device_Address                         0x90
#define _SFC_com_Device_Address                         0x91


enum measure_commands_t : uint16_t
{
    SetValue                    = 0x0001,
    ProcessValue                = 0x0801,
    Gain                        = 0x2200,
    Init_Step                   = 0x2203,
    Raw_Flow                    = 0x3000,
    Raw_Thermal_Conductivity    = 0x3002,
    Temperature                 = 0x3010
};

enum set_command_float_t : uint16_t
{
    wSetValue                    = 0x0001,
    wGain                        = 0x2200,
    wInit_Step                   = 0x2203,
};

enum set_command_int_t : uint16_t
{
    aSetValue                    = 0x0001,
};


enum deviceInfo_commands_t : uint16_t
{
    Product_Type                    = 0xD000+1,
    Product_Name                    = 0xD001,
    Article_Code                    = 0xD002,
    Serial_Number                   = 0xD003,
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
    uint8_t last_command=0;
    uint8_t last_subcommand=0;
    uint16_t raw_flow=0;
    uint16_t raw_thermal_conductivity=0;
    //Sensor_SFC6000();
    uint16_t request(measure_commands_t command);
    uint16_t read();
    uint16_t set(set_command_float_t command, float value);
    uint16_t set(set_command_int_t command, uint32_t value);

    uint16_t pull_devInfo(deviceInfo_commands_t command, Stream & serCom);
};

#endif