#include "imp.h"
void change_pass(unsigned char key)
{
    static unsigned char n_password[5], c_password[5];
    static int success_flag = 0;
    
    if (success_flag == 1)
    {
        clcd_print("Password does", LINE1(0));
        clcd_print("not match", LINE2(0));
        if (timeout == 0)
        {
            CLEAR_DISP_SCREEN;
            main_f = MENU;
            p_flag = 0;
            pass_index = 0;
            success_flag = 0;
        return;
        }
    }
    else if (success_flag == 2)
    {
        clcd_print("Password changed", LINE1(0));
        clcd_print("Successfully", LINE2(0));
        if (timeout == 0)
        {
            CLEAR_DISP_SCREEN;
            main_f = MENU;
            p_flag = 0;
            pass_index = 0;
            success_flag = 0;
        
        return;
    }
    }
    
    if (p_flag == 0)
    {
        if (pass_index < 4)
        {
            clcd_print("ENTER NEW PWD", LINE1(0));
            if (sec % 2 == 0)
                clcd_putch('_', LINE2(pass_index));
            else
                clcd_putch(' ', LINE2(pass_index));
            if (key == 11)
            {
                clcd_putch('*', LINE2(pass_index));
                n_password[pass_index++] = '1';
            }
            else if (key == 12)
            {
                clcd_putch('*', LINE2(pass_index));
                n_password[pass_index++] = '0';
            }
        }
        else if (pass_index == 4)
        {
            CLEAR_DISP_SCREEN;
            n_password[pass_index] = '\0';
            pass_index = 0;
            p_flag = 1;
        }
    }
    else if (p_flag == 1)
    {
        if (pass_index < 4)
        {
            clcd_print("CONFIRM PWD", LINE1(0));
            if (sec % 2 == 0)
                clcd_putch('_', LINE2(pass_index));
            else
                clcd_putch(' ', LINE2(pass_index));
            if (key == 11)
            {
                clcd_putch('*', LINE2(pass_index));
                c_password[pass_index++] = '1';
            }
            else if (key == 12)
            {
                clcd_putch('*', LINE2(pass_index));
                c_password[pass_index++] = '0';
            }
        }
        else if (pass_index == 4)
        {
//            CLEAR_DISP_SCREEN;
            c_password[pass_index] = '\0';
            pass_index = 0;
            p_flag = 2;
        }
    }
    else if (p_flag == 2)
    {
        for (int j = 0; j < 4; j++)
        {
            if (n_password[j] != c_password[j])
            {
//                CLEAR_DISP_SCREEN;
                success_flag = 1;
                timeout = 2;
                return;
            }
        }
        for (int j = 0; j < 4; j++)
        {
            m_password[j] = c_password[j];
        }
        write_external_eeprom(0x80, n_password[0]);
        write_external_eeprom(0x81, n_password[1]);
        write_external_eeprom(0x82, n_password[2]);
        write_external_eeprom(0x83, n_password[3]);
        write_external_eeprom(0x84, 'z');
        success_flag = 2;
        timeout = 2;
//        CLEAR_DISP_SCREEN;
    }
}


void init_password()
{
    if (read_external_eeprom(0x84) == 'z')
    {
        m_password[0] = read_external_eeprom(0x80);
        m_password[1] = read_external_eeprom(0x81);
        m_password[2] = read_external_eeprom(0x82);
        m_password[3] = read_external_eeprom(0x83);
        m_password[4] = '\0';
    }
}
