#include "imp.h"

void store_event()
{
    int i;
     
    for(i=0;i<8;i++)
    {
        write_external_eeprom((unsigned char)(i+(log_index*12)%0x78),time[i]);
    }
    write_external_eeprom((unsigned char)(i+(log_index*12)%0x78),events[event_index][0]);
    i++;
    write_external_eeprom((unsigned char)(i+(log_index*12)%0x78),events[event_index][1]);
    i++;
    write_external_eeprom((unsigned char)(i+(log_index*12)%0x78),(speed/10)+48);
    i++;
    write_external_eeprom((unsigned char)(i+(log_index*12)%0x78),(speed%10)+48);
    
    log_index=(log_index+1)%10;
    
    if(log_count<10)
        log_count++;
}