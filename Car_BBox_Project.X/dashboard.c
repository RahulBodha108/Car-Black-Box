#include "imp.h"


void dashboard(unsigned char key)
{
    unsigned short adc_val;
    static int c_flag;   
     
    
     
    
    if(key==2)
    {
        if(c_flag==1)
        {
            event_index=1;
            c_flag=0;
            store_event();
        }
        else if(event_index<7)
        {
            event_index++;
            store_event();
        }
    }
    else if(key==3)
    {
         if(c_flag==1)
        {
            event_index=1;
            c_flag=0;
            store_event();
        }
         else if(event_index>1 && c_flag!=1)
        {
            event_index--;
            store_event();
        }
    }
    else if(key==1)
    {
        c_flag=1;
        if(event_index!=8)
        {
            event_index=8;
            store_event();
        }
    }
    clcd_print("Tme    Gear  SP", LINE1(0));
    
    get_time();
    display_time();
    
    clcd_putch(events[event_index][0], LINE2(10));
    clcd_putch(events[event_index][1], LINE2(11));
    adc_val=read_adc(4);
    speed=adc_val/10.33;
    clcd_putch(speed/10+48, LINE2(14));
    clcd_putch(speed%10+48, LINE2(15));
    clear_dis=1;
    timeout=9;
    if(key==11)
        main_f=PASSWORD;
}