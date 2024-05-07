#include "mbed.h"
#include "adc.h"
#include <cstdint>
#include <cstdio>
#include "oled_ssd1322.h"
#include "home.cpp"
#include <iostream>
#include <string>
using namespace std;

#define MESSAGE_MAX_SIZE 50

class FreedomController {
    public:
        Home& SmartHome;
        DigitalIn Green_Button;
        DigitalIn Blue_Button;
        DigitalIn Black_Button;// switch button
        DigitalIn Red_Button; // switch button

        DigitalOut Red_Led;
        DigitalOut Green_Led;
        FreedomController(
            PinName green_button_pin,
            PinName blue_button_pin,
            PinName black_button_pin,
            PinName red_button_pin,
            PinName red_led_pin,
            PinName green_led_pin,
            Home& homeRef
            ) : 
            Green_Button(green_button_pin),
            Blue_Button(blue_button_pin),
            Black_Button(black_button_pin),
            Red_Button(red_button_pin),
            Red_Led(red_led_pin),
            Green_Led(green_led_pin),
            SmartHome(homeRef) {}

        void init() {
            InitScreen();
            // SmartHome.SetHeaterOn();
            SmartHome.Front_Door = 1;
            while (true)
            {
                // Smarthome actions:
                    // UC_Too_Warm // DONE
                    // When it’s above 30 degrees celsius (inside-sensor), make sure the heater. 
                    // The red light of the freedom controller will turn red if it is above 30 degrees.

                    // UC_Sunset // done
                    // When the light sensor detects that it is dark (< 10'000), turn on all the lights in- and outside the house.
                    // 
                    // UC_Sunrise //  done
                    // When the light sensor detects that it is daylight (>10'000), turn off all the lights in- and outside the house.
                    
                    // UC_HomeComing //done?
                    // When the car is at the garage door(car sensor), open the garage and turn on the heater if the inside temperature sensor is below 25 degrees.
                    // Also we turn on the inside light when this occurs.
                    
                    // UC_DeliverPackage //done 
                    // When the green button on the freedom controller is pressed, the door is opened for 5 seconds, “so a package can be delivered while you’re not at home”.


                if (IsItTooWarm()) {
                    SmartHome.SetHeaterOff();
                    Red_Led = 1;
                } else {
                    Red_Led = 0;
                }

                if (IsCarOnDriveway()) {
                    ThisThread::sleep_for(1s);
                    SmartHome.Garage_Door = 1;
                    SmartHome.Curtains = 0; // bug, should not open because of this event.
                    ThisThread::sleep_for(5s);
                    SmartHome.Garage_Door = 0; 
                    SmartHome.SetIndoorLampOn();
                    

                    if (IsItBelowDegrees(25.0)) {
                        SmartHome.SetHeaterOn();
                    }
                }

                if (!Green_Button) {
                    SmartHome.Front_Door = 0;
                    ThisThread::sleep_for(5s);
                    SmartHome.Front_Door = 1;
                }

                // bug timeeee
                if (!Blue_Button) {
                    while (true) {
                        SmartHome.Garage_Door = 1;
                        SmartHome.Garden_Lamp = 1;
                        SmartHome.SetFrontDoorLampOn();
                        ThisThread::sleep_for(100ms);
                        SmartHome.Garden_Lamp = 0;
                        SmartHome.SetFrontDoorLampOff();
                        ThisThread::sleep_for(100ms);
                    }
                }

                if (SmartHome.Sensors.IsDarkOutside()) {
                    SmartHome.Garden_Lamp = 1;
                     SmartHome.Curtains = 0;
                } else {
                    SmartHome.Garden_Lamp = 0;
                    SmartHome.Curtains = 1;
                }

                UpdateDashboard();
                ThisThread::sleep_for(500ms);
            }
        }

        void InitScreen() {
            u8g2_ClearBuffer(&oled);
            u8g2_SetFont(&oled, u8g2_font_6x12_mr);
            u8g2_SendBuffer(&oled);
        }

        void UpdateDashboard() {
            u8g2_ClearBuffer(&oled);
            // info
            int light_val_outside = SmartHome.Sensors.GetAnalogValueOfOutdoorLight();
            float temperature = SmartHome.Sensors.getInsideTemperature();

            char message1[MESSAGE_MAX_SIZE + 1];
            message1[MESSAGE_MAX_SIZE] = '\0';
            snprintf(message1, MESSAGE_MAX_SIZE, "========SMART HOME========\n");

            char message2[MESSAGE_MAX_SIZE + 1];
            message2[MESSAGE_MAX_SIZE] = '\0';
            snprintf(message2, MESSAGE_MAX_SIZE, "Temperature inside: %5.02f\n" , temperature);
            
            char message3[MESSAGE_MAX_SIZE +1];
            message3[MESSAGE_MAX_SIZE] = '\0';
            snprintf(message3, MESSAGE_MAX_SIZE,  "Light-value outside:  %d \n" ,light_val_outside);

            SetMessage(message1, 10, 10);
            SetMessage(message2, 10, 20);
            SetMessage(message3, 10, 30);
            u8g2_SendBuffer(&oled);
        }


        void SetMessage(char* msg_string, int x, int y) {
            // u8g2_ClearBuffer(&oled);
            u8g2_DrawUTF8(&oled, x, y, msg_string);
        }

        bool IsItTooWarm() {
            return SmartHome.Sensors.getInsideTemperature() > 30.0;
        }

        bool IsItBelowDegrees(float degrees) {
            return SmartHome.Sensors.getInsideTemperature() < degrees;
        }

        bool IsCarOnDriveway() {
            return SmartHome.Sensors.Car_Sensor == 0;
        }
};
