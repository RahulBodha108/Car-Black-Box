#include "imp.h"

void menu(unsigned char key,unsigned char t)
{
    unsigned char menu[5][15]={"View log","Download log","Clear log","Set time","Change password"};
    clcd_print(menu[L], LINE1(1));
    clcd_print(menu[L+1], LINE2(1));
    if(sel==0)
        clcd_putch('*', LINE1(0));
    else
        clcd_putch('*', LINE2(0));
    if(key==12)
    {
        if(t==0)
        {
            if(sel==0)
                sel=1;
            else if(L<3)
                L++;
            CLEAR_DISP_SCREEN;
        }
        else if(t==1)
        {
            CLEAR_DISP_SCREEN;
            L=0;
            sel=0;
            main_f=DASHBOARD;
        }
    }
    else if(key==11)
    {
        if(t==0)
        {
            if(sel==1)
                sel=0;
            else if(L>0)
                L--;
            CLEAR_DISP_SCREEN;
        }
        else if(t==1)
        {
            CLEAR_DISP_SCREEN;
            main_f=MENU_ENTER;
            menu_f=L+sel;
            if(menu_f==3)
                in_flag=0;
            L=0;
            sel=0;
        }
    }
}