#include "imp.h"
void view_log(unsigned char key,unsigned char t)
{
    static int vl_flag=0;
    if(vl_flag==1)
    {
        clcd_print("LOG EMPTY",LINE1(0));
        if(timeout==0)
        {
            main_f=MENU;
            vl_flag=0;
            CLEAR_DISP_SCREEN;
        }
        return;
    }
    if(log_count==0)
    {
        vl_flag=1;
        timeout=2;
        CLEAR_DISP_SCREEN;
        return;
    }
    if(in_flag==0)
    {
        CLEAR_DISP_SCREEN;
        view_index=0;
        in_flag=1;
    }
    clcd_print("# TIME     EV SP",LINE1(0));
    int i;
    for(i=0;i<8;i++)
        view_event[i]=read_external_eeprom((unsigned char)(i+(((log_index+9-view_index)%10)*12)%0x78));
    view_event[i]=' ';
    i++;
    view_event[i]=read_external_eeprom((unsigned char)(i-1+(((log_index+9-view_index)%10)*12)%0x78));
    i++;
    view_event[i]=read_external_eeprom((unsigned char)(i-1+(((log_index+9-view_index)%10)*12)%0x78));
    i++;
    view_event[i]=' ';
    i++;
    view_event[i]=read_external_eeprom((unsigned char)(i-2+(((log_index+9-view_index)%10)*12)%0x78));
    i++;
    view_event[i]=read_external_eeprom((unsigned char)(i-2+(((log_index+9-view_index)%10)*12)%0x78));
    view_event[14]='\0';
    clcd_putch(view_index+48,LINE2(0));
    clcd_print(view_event,LINE2(2));
    if(key==11 && view_index<log_count-1)
    {
        view_index++;
    }
    else if(key==12)
    {
        if(t==0 && view_index>0)
        {
            view_index--;
        }
        else if(t==1)
        {
            in_flag=0;
            CLEAR_DISP_SCREEN;
            main_f=MENU;
        }
    }
}

void clear_log()
{
    if(in_flag==0)
    {
        in_flag=1;
        CLEAR_DISP_SCREEN;
        log_count = 0;
        timeout = 3;
    }
    if (timeout>0) 
    {
        clcd_print("Log cleared", LINE1(0));
    } 
    else if (timeout == 0) 
    {  
        CLEAR_DISP_SCREEN;
        main_f = MENU;
        in_flag=0;
    }
}

void download_log()
{
    if(in_flag==0)
    {
        int i;
        puts("# TIME     EV SP\n\r");
        for(int j=0;j<log_count;j++)
        {
            for(i=0;i<8;i++)
                view_event[i]=read_external_eeprom((unsigned char)(i+(((log_index+9-j)%10)*12)%0x78));
            view_event[i]=' ';
            i++;
            view_event[i]=read_external_eeprom((unsigned char)(i-1+(((log_index+9-j)%10)*12)%0x78));
            i++;
            view_event[i]=read_external_eeprom((unsigned char)(i-1+(((log_index+9-j)%10)*12)%0x78));
            i++;
            view_event[i]=' ';
            i++;
            view_event[i]=read_external_eeprom((unsigned char)(i-2+(((log_index+9-j)%10)*12)%0x78));
            i++;
            view_event[i]=read_external_eeprom((unsigned char)(i-2+(((log_index+9-j)%10)*12)%0x78));
            view_event[14]='\0';
            puts(view_event);
            puts("\n\r");
        }
        in_flag=1;
        timeout=4;
        CLEAR_DISP_SCREEN;
    }
    if(timeout>0)
    {
        clcd_print("Downloading...",LINE1(0));
        clcd_print("All Events",LINE2(0));
    }
    else
    {
        CLEAR_DISP_SCREEN;
        in_flag=0;
        main_f=MENU;
    }
}
