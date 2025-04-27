#include "imp.h"

void password(unsigned char key)
{
    unsigned char e_password[5];
    static int pa_flag=0;
    if(pa_flag==1)
    {
        if(success==1)
        {
            clcd_print("Access Granted", LINE1(0));
            clcd_print("****",LINE2(0));
            if(timeout==0)
            {
                CLEAR_DISP_SCREEN;
                main_f=MENU;
                pa_flag=0;
            }
            return;
        }
        else if(success==0)
        {
            clcd_print("Attempt Failed", LINE1(0));
            clcd_print("Attempt Left - ", LINE2(0));
            clcd_putch((unsigned char)attempts+48,LINE2(15));
            if(timeout==0)
            {
                pa_flag=0;
                CLEAR_DISP_SCREEN;
            }
            return;
        }
    }
    if(timeout==1)
    {
        main_f=DASHBOARD;
        pass_index=0;
        CLEAR_DISP_SCREEN;
        return;
    }
    if(attempts==0)
    {
        clcd_print("Try after...", LINE1(0));
        clcd_print("Retry in ", LINE2(0));
        clcd_putch(sec/100+48, LINE2(9));
        clcd_putch((sec%100)/10+48, LINE2(10));
        clcd_putch(sec%10+48, LINE2(11));
        clcd_print("secs", LINE2(12));
        if(sec==0)
        {
            attempts=3;
            main_f=DASHBOARD;
            CLEAR_DISP_SCREEN;
        }
        return;
    }
    if(clear_dis==1)
    {
        clear_dis=0;
        CLEAR_DISP_SCREEN;
        key=0;
    }
    if(pass_index<4)
    {
        clcd_print("ENTER PASSWORD", LINE1(0));
        if(sec%2==0)
            clcd_putch('_',LINE2(pass_index));
        else
            clcd_putch(' ',LINE2(pass_index));
        if(key==11)
        {
            clcd_putch('*',LINE2(pass_index));
            e_password[pass_index++]='1';
            timeout=9;
        }
        else if(key==12)
        {
            clcd_putch('*',LINE2(pass_index));
            e_password[pass_index++]='0';
            timeout=9;
        }
    }
    else if(pass_index>3)
    {
        pass_index=0;
        success=1;
        e_password[4]='\0';
        for(int j=0;j<4;j++)
        {
            if(m_password[j] != e_password[j])
            {
                if(--attempts==0)
                    sec=120;
                success=0;
                break;
            }
        }
        pa_flag=1;
        timeout=2;
        CLEAR_DISP_SCREEN;
    }
}
