/*
 * File: main.c
 * Author: Rahul Bodha
 * reg id: 24008_014
 * project: Car Black Box Project
 *Created on 4 October, 2024, 8:27 AM
 */

#include "imp.h"


static void init_config(void)
{
    init_clcd(); 
    init_matrix_keypad();
    init_adc();
	init_i2c();
	init_ds1307();
    init_password();
    init_uart();
}

void main(void) 
{
    
    init_config();
    unsigned char key,t=0;
    unsigned int wait=0;
    while (1)
    {
        
        if(wait++==1000)
        {
            wait=0;
            blink=~blink;
            sec--;
            timeout--;
        }
        if(main_f!=MENU && main_f!=MENU_ENTER)
            key=read_switches(1);
        else
            key=long_short_press(&t);
        if(main_f == DASHBOARD)
        {
            dashboard(key);
        }
        else if(main_f == PASSWORD)
        {
            password(key);
        }
        else if(main_f == MENU)
        {
            menu(key,t);
        }
        else if(main_f == MENU_ENTER)
        {
            if(menu_f == VIEWLOG)
            {
                view_log(key,t);
                
      
            }
            else if(menu_f == DOWNLOADLOG)
            {
                download_log();
            }
            else if(menu_f == CLEARLOG)
            {
                clear_log();         
        store_event();
            }
            else if(menu_f == SETTIME)
            {
                set_time(key,t);

            }
            else if(menu_f == CHANGEPASS)
            {
                change_pass(key);

            }
        }    
    }
}
