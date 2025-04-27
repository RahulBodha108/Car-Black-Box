#include "imp.h"
void set_time(unsigned char key,unsigned char t)
{
    static int tc_flag=0;
    if(tc_flag==1)
    {
        clcd_print("Time changed",LINE1(0));
        clcd_print("successfully",LINE2(0));
        in_flag=0;
        if(timeout==0)
        {
            CLEAR_DISP_SCREEN;
            main_f=MENU;
            tc_flag=0;
             store_event();
        }
        return;
    }
    else if(tc_flag==2)
    {
        clcd_print("Time not",LINE1(0));
        clcd_print("changed",LINE2(0));
        in_flag=0;
        if(timeout==0)
        {
            CLEAR_DISP_SCREEN;
            main_f=MENU;
            tc_flag=0;
        }
        return;
    }
    clcd_print("HH:MM:SS",LINE1(3));
    if(in_flag==0)
    {
        hr=(time[0]-48)*10 + time[1]-48;
        min=(time[3]-48)*10 + time[4]-48;
        secs=(time[6]-48)*10 + time[7]-48;
        in_flag=1;
    }
    if(field==0)
    {
        clcd_putch(hr%10+48,LINE2(4));
        clcd_putch(hr/10+48,LINE2(3));
        clcd_putch(':',LINE2(5));
        clcd_putch(min%10+48,LINE2(7));
        clcd_putch(min/10+48,LINE2(6));
        clcd_putch(':',LINE2(8));
        if(blink)
        {
            clcd_putch(secs%10+48,LINE2(10));
            clcd_putch(secs/10+48,LINE2(9));
        }
        else
        {
            clcd_print("  ",LINE2(9));
        }
    }
    else if(field==1)
    {
        clcd_putch(hr%10+48,LINE2(4));
        clcd_putch(hr/10+48,LINE2(3));
        clcd_putch(':',LINE2(5));
        clcd_putch(secs%10+48,LINE2(10));
        clcd_putch(secs/10+48,LINE2(9));
        
        clcd_putch(':',LINE2(8));
        if(blink)
        {
            clcd_putch(min%10+48,LINE2(7));
            clcd_putch(min/10+48,LINE2(6));
        }
        else
        {
            clcd_print("  ",LINE2(6));
        }
    }
    else if(field==2)
    {
        clcd_putch(secs%10+48,LINE2(10));
        clcd_putch(secs/10+48,LINE2(9));
        clcd_putch(':',LINE2(5));
        clcd_putch(min%10+48,LINE2(7));
        clcd_putch(min/10+48,LINE2(6));
        clcd_putch(':',LINE2(8));
        if(blink)
        {
            clcd_putch(hr%10+48,LINE2(4));
            clcd_putch(hr/10+48,LINE2(3));
        }
        else
        {
            clcd_print("  ",LINE2(3));
        }
    }
    if(key==11)
    {
        if(t==0)
        {
            if(field==0)
                secs=(secs+1)%60;
            else if(field==1)
                min=(min+1)%60;
            else if(field==2)
                hr=(hr+1)%24;
        }
        else if(t==1)
        {
            unsigned char hr_reg = ((hr/10)&0xF)<<4 | (hr%10)&0xF;
            unsigned char min_reg = ((min/10)&0xF)<<4 | (min%10)&0xF;
            unsigned char sec_reg = ((secs/10)&0xF)<<4 | (secs%10)&0xF;

            write_ds1307(HOUR_ADDR, hr_reg);
            write_ds1307(MIN_ADDR, min_reg);
            write_ds1307(SEC_ADDR, sec_reg);
            timeout=2;
            tc_flag=1;
            CLEAR_DISP_SCREEN;
            return;
        }
    }
    else if(key==12)
    {
        if(t==0)
        {
            field=(field+1)%3;
        }
        else if(t==1)
        {
            timeout=2;
            tc_flag=2;
            CLEAR_DISP_SCREEN;
        }
    }
}
