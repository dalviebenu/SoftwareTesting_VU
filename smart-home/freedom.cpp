#include "mbed.h"
#include "adc.h"
#include <cstdint>
#include <cstdio>
#include "home.cpp"

class FreedomController {
    public:
        Home& SmartHome;
        DigitalIn Green_Button;
        DigitalIn Blue_Button;
        DigitalIn Black_Button;// switch button
        DigitalIn Red_Button; // switch button
        FreedomController(
            PinName green_button_pin,
            PinName blue_button_pin,
            PinName black_button_pin,
            PinName red_button_pin,
            Home& homeRef
            ) : 
            Green_Button(green_button_pin),
            Blue_Button(blue_button_pin),
            Black_Button(black_button_pin),
            Red_Button(red_button_pin),
            SmartHome(homeRef) {}

        void init() {
            while (true)
            {
                bool openDoor = false;
                if(!Blue_Button && !openDoor){
                    SmartHome.Curtains = 1;
                    openDoor = true;
                    ThisThread::sleep_for(1000ms);
                }
                else if (!Blue_Button && openDoor){
                    SmartHome.Curtains = 0;
                    openDoor = false;
                    ThisThread::sleep_for(1000ms);
                }

                if (SmartHome.Sensors.Car_Sensor == 0) {
                    ThisThread::sleep_for(1s);
                    // SmartHome.Curtains = 1;
                    SmartHome.Garage_Door = 1; // does not work?
                    ThisThread::sleep_for(5s);
                    // SmartHome.Curtains = 0;
                    SmartHome.Garage_Door = 0; 
                }
            }
        }
};
