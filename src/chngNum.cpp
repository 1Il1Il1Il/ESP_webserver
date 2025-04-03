#include <header.h>

chngNum::chngNum(long Max, long Dl)
{
    max = Max;
    dl = Dl;
    ltime = millis();
}

long chngNum::value()
{
    if (millis() - ltime >= dl)
    {
        ltime = millis();
        num++;
        if (num >= max) num = 0; 
    }
    return num;
}