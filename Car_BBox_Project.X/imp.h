#ifndef imp
#define	imp

#include <xc.h>
#include"matrix_keypad.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "ext_eeprom.h"

#define DASHBOARD               0
#define PASSWORD                1
#define MENU                    2
#define MENU_ENTER              3
#define VIEWLOG                 0
#define DOWNLOADLOG             1
#define CLEARLOG                2
#define SETTIME                 3
#define CHANGEPASS              4

unsigned int main_f = 0, menu_f = 0,sec=0;

void init_matrix_keypad();
unsigned char read_switches(unsigned char detection);
unsigned char scan_key();

void init_adc();
unsigned short read_adc(unsigned char channel);

void dashboard(unsigned char key);
unsigned int event_index=0,speed;
unsigned char clock_reg[3];
unsigned char time[9];
unsigned char events[9][2]={"ON","GN","GR","G1","G2","G3","G4","G5","C "};

void display_time(void);
void get_time(void);

void password(unsigned char key);
unsigned int timeout=0, clear_dis=0, pass_index=0,attempts=3,success,login_flag=0;
unsigned char m_password[5] = "1100";

void menu(unsigned char key,unsigned char t);
unsigned int L=0,sel=0;

void store_event();
unsigned int log_index=0,log_count=0;

unsigned char long_short_press(unsigned char *t);

void change_pass(unsigned char key);
void init_password();
unsigned int p_flag=0;

void set_time(unsigned char key,unsigned char t);
unsigned int in_flag=0,field=0,blink=0,min,secs,hr;

void view_log(unsigned char key,unsigned char t);
unsigned char view_event[15];
unsigned int view_index=0;

void clear_log(); 

void download_log();
void init_uart();
unsigned char getch();
void putch(unsigned char data);
void puts(unsigned char *data);

#endif

