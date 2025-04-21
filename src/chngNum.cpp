#include <header.h>

chngNum::chngNum(long Max, long Dl)
{
    max = Max;
    dl = Dl;
    ltime = millis();
    num = 0;
}

void chngNum::Max(long MAX){
    max = MAX;
    num = 0;

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