#include "imp.h"

unsigned char long_short_press(unsigned char *t)
{
    unsigned int l=0;
    unsigned char key;
    key = scan_key();
    l=0;
    if(key!=0xFF)
    {
        while(key==scan_key())
        {
            if(l++ > 16000)
            {
                *t = 1;
            }
        }
    }
    if(l > 0 && l < 16000)
    {
        l = 0;
        *t=0;
    }
    else
    {
        l = 0;
    }
    return key;
}