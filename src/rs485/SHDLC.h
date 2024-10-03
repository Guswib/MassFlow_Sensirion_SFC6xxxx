#ifndef _Sensor_SHDLC_H_
#define _Sensor_SHDLC_H_

#include <stdint.h>
#include <arduino.h>


constexpr uint8_t SHDLC_start = (uint8_t)0x7E


class shdlc_bus
{
    uint8_t device_address = 0;
    stream & serCom;

    shdlc_bus(stream & Serial_Com, uint8_t address){serCom(Serial_Com)}
    
    {device_address=address;};

    void begin()
    {
        serCom.begin(115200);
    }

    void push(stream & sercom, uint8_t command, uint16_t const TXdataSize, uint8_t const * TXdata )
    {
        //Start
        error=0;
        uint8_t Frame[TXdataSize+5];
        //Header
        Frame[0] = device_address;
        Frame[1] = command;
        Frame[2] = device_address;
        if(TXdataSize > 0)
            memcopy(Frame[3], TXdata,TXdataSize);
        checkSum_index = TXdataSize + 3;
        Frame[checkSum_index] = calc_checkSum(Frame, checkSum_index);
        int length = checkSum_index+1;
        sercom.write(SHDL_start);
        for(int i=0; i < length;i++)
            send_single_with_stuffing(stream & serCom, Frame[i]);
        sercom.write(SHDL_start); 
    };

    uint8_t pull(stream & sercom, uint8_t const * RXdata, uint8_t const RXdataSize)
        {
        error=0;
        unsigned long start = millis();
        timeout=200;
        //waith for start
        uint8_t data =0;
        while(millis()-start < timeout)
        {
            data = 0
            if(sercom.available()>0){
                data = sercom.read();
                if(data == SHDLC_start) break;
            }else{
                delay(1);
            }
        }
        //read the message:
        uint8_t const FrameSize = 50;
        uint8_t Frame[FrameSize];
        uint8_t index = 0;
        while(millis()-start < timeout){
            data=0;
            if(sercom.available()){
                data = sercom.read()
                if(data == SHDLC_start) break;
                else{
                    read_single_with_stuffing(serCom, data);
                    Frame[index] = data;
                    index++;
                    if(index>=FrameSize) {error=1; break;}
                }
            }else{
                delay(1);
            }
            
        }
        uint8_t Checksum_calc = calc_checkSum(Frame,index-2);
        uint8_t Checksum_expected = Frame[index-1];
        if(Checksum_calc != Checksum_expected && error == 0) error =2;
        if(error == 0 && RXdataSize>0)
        {
            memcopy(RXdata, Frame, RXdataSize);
        }
        return error;
    };

    void send_single_with_stuffing(stream & serCom, uint8_t data)
    {
        uint8_t a = 0x7D;
        uint8_t b = 0;
        switch (data)
        {
            case 0x11:
                b = 0x31;
                break;
            case 0x13:
                b = 0x33;
                break;
            case 0x7D:
                b = 0x5D;
                break;
            case 0x7E:
                b = 0x5E;
                break;
            
            default:
                a= data[i]
                break;
        }
        serCom.write(a);
        if (a == 0x7D){
            serCom.write(b);
        }
    };

    uint8_t read_single_with_stuffing(stream & serCom, uint8_t & data)
    {
        unsigned long start = millis();
        unsigned long timeout = 100;
        uint8_t c_extra = 0;
        uint8_t error = 0;

        if(data == 0x7D){
            while(millis()-start < timeout && serCom.available()==0)
            c_extra= serCom.read()
            switch (c_extra)
            {
                case 0x31:
                    data = 0x11;
                    break;
                case 0x33:
                    data = 0x13;
                    break;
                case 0x5D:
                    data = 0x7D;
                    break;
                case 0x5E:
                    data = 0x7E;
                    break;
                
                default:
                    error = 1;
                    break;
            }
        }
        return error;
    };

    uint8_t calc_checkSum(uint8_t * Frame, uint16_t end_index)
    {
        uint32_t sum = 0;
        for(int i=0;i<end_index;i++){
            sum += Frame[i];
            }
        uint8_t Checksum = ! lowByte(sum);
        return Checksum;
    }
    
};



#endif