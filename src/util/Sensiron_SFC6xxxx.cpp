

#include <stdint.h>
#include <string.h>
#include <Arduino.h>


#include "Sensiron_SFC6xxxx.h"




float Sensor_SFC6000x::pull_Measure_Temperature(float & value)
{
    _request(_SFC_com_Advanced_Measurements,Advanced_Measurments_t::Measure_Temperature);
    return _receive_float(value);
}


float Sensor_SFC6000x::push_ControllerGain(float const value){
        //subcommand 0x01
        _send_float(_SFC_com_controller_Configuration,0x00, value);
    }
float Sensor_SFC6000x::pull_ControllerGain(){
        //subcommand 0x01
        _send_float(_SFC_com_controller_Configuration,0x00, value);
    }



pull_Calibration(){
        dev.push(_serCom, _SFC_com_Calibration, 0, nullptr );
        ///
    }    

float Sensor_SFC6000x::pull_PV(){
        _request(_SFC_com_Advanced_Measurements,0x10);
        //pull;
        //This function returns a float
        uint8_t RXdata[4];    
        uint8_t pull(stream & sercom, RXdata, 4)
        return atof(RXdata);

    }

float Sensor_SFC6000x::push_SetPoint(float const value){
        //subcommand 0x01
        _send_float(_SFC_com_setpoint,0x01, value);
    }

float Sensor_SFC6000x::pull_SetPoint()
    {
        _request(uint8_t const Command,uint8_t const subCommand)
        uint8_t RXdata[4];    
        uint8_t _bus.pull(stream & sercom, RXdata, 4)
        return atof(RXdata);
        
    }

uint8_t Sensor_SFC6000x::push_DevAddress(uint8_t Address){
        const uint8_t buf_length=1;
        uint8_t buf[buf_length];
        buf[0]=Address;
        _bus.push(_serCom, _SFC_com_Device_Address, buf_length, buf );
        return 0;
    }

/////////////////////////////////////////////////////

uint8_t Sensor_SFC6000x::_send_float(uint8_t const Command,uint8_t const subCommand, float const value){
        const uint8_t buf_length=5;
        uint8_t buf[buf_length];
        buf[0]=subCommand;
        memcpy(xbuf, & value,sizeof(value));
        _bus.push(_serCom, Command, buf_length, buf );
        return 0;
    }
uint8_t Sensor_SFC6000x::_send_uint32(uint8_t const Command,uint8_t const subCommand, uint32_t const value){
        const uint8_t buf_length=5;
        uint8_t buf[buf_length];
        buf[0]=subCommand;
        memcpy(xbuf, & value,sizeof(value));
        _bus.push(_serCom, Command, buf_length, buf );
        return 0;
    }
    
uint8_t Sensor_SFC6000x::_request(uint8_t const Command,uint8_t const subCommand){
        const uint8_t buf_length=1;
        uint8_t buf[buf_length];
        buf[0]=subCommand;
        _bus.push(_serCom, Command, buf_length, buf );
        return 0;
    }
uint8_t Sensor_SFC6000x::_receive_float(float & value)
    {
        uint8_t RXdata[4];    
        uint8_t error = _bus.pull(stream & sercom, RXdata, 4)
        value =  atof(RXdata);
        return error;
    }


 