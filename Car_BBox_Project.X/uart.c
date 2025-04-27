#include "imp.h"

void init_uart()
{
    TRISC7=1; 
    TRISC6=0; 
    
    TX9=0;
    TXEN=1;
    SYNC=0;
    BRGH=1;
    
    SPEN=1;
    CREN=1;
    RX9=0;
    
    BRG16=0;
    
    SPBRG=129;
    
    TXIE=1;
    TXIF=0;
    RCIE=1;
    RCIF=0;
}

unsigned char getch()
{
    while(!RCIF);
    RCIF=0;
    return RCREG;
}

void putch(unsigned char data)
{
    while(!TXIF);
    TXIF=0;
    TXREG=data;
}

void puts(unsigned char *data)
{
    while(*data)
        putch(*data++);
}