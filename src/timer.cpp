#include <header.h>

timer::timer(long time, byte mode = 2){
    Time = time;
    Mode = mode;
    trigger = false;
    if (mode == 3) StartTime = millis();
}

bool timer::status(){
    bool flag = false;
    if (!trigger)
    {
    if (millis() - StartTime >= Time)
    {
    flag = true;
    if (Mode >= 2) start();
    }
    if (Mode == 0 && flag == true) trigger = true;
    }
    return flag;
}

void timer::start(){
    StartTime = millis();
    trigger = false;   
}


