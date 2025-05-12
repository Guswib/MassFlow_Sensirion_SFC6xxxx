#ifndef _Sensor_SHDLC_H_
#define _Sensor_SHDLC_H_

#include <stdint.h>
#include <arduino.h>


constexpr uint8_t SHDLC_start = (uint8_t)0x7E;


class shdlc_bus
{
    uint8_t device_address = 0;
    Stream & serCom;

    shdlc_bus(Stream & Serial_Com):
        serCom{Serial_Com}
        {device_address=address;};

    void begin()
    {
        serCom.begin(115200);
    }

    void push(uint8_t device_address, uint8_t command, uint16_t const TXdataSize, uint8_t const * TXdata );

    uint8_t pull(uint8_t device_address, uint8_t const * RXdata, uint8_t const RXdataSize);

    void send_single_with_stuffing( uint8_t data);

    uint8_t read_single_with_stuffing( uint8_t & data);
    
    uint8_t calc_checkSum(uint8_t * Frame, uint16_t end_index);
    
};



#endif