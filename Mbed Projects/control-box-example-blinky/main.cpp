#include "mbed.h"

// main() runs in its own thread in the OS
int main()
{
    DigitalOut redLed(PTB2);
    DigitalIn button(PTB3);
     
     bool isPressed = false;

    while (true) {

        if(!button && !isPressed){
            isPressed = true;
            redLed = 1;
            ThisThread::sleep_for(500ms);
        }
        else if (!button && isPressed){
            isPressed = false;
            redLed = 0;
            ThisThread::sleep_for(500ms);
        }        
    }
}
