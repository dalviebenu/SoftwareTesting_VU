#include "mbed.h"
#include "board_freedom.h"
#include "adc.h"
#include "oled_ssd1322.h"
#include <cstdint>
#include <cstdio>


#define MESSAGE_MAX_SIZE 50
 
 /*Libraries to add:::
Select ‘master’ for u8g2 and ‘main’ for libboxzoo in the next window. Hit finish and add the other library.
https://github.com/valuta1995/bugzoo-u8g2.git
https://github.com/valuta1995/libboxzoo.git


*/
  //smart-home
// main() runs in its own thread in the OS
int main()
{
   board_init();


    // SMART HOME NR 5 ZIGGY GLITTERDUST - 23-04-2024

    DigitalIn Green_Button(PTB5);
    DigitalIn Blue_Button(PTB6);
    DigitalIn Black_Button(PTC16);// switch button
    DigitalIn Red_Button(PTB7); // switch button
    bool greenIsPressed = false;



    DigitalOut Garden_Lamp(PTB18); // on the schema it is IN_lamp_laterna
    DigitalOut Garage_Door (PTB11); //in_servo_garage
    DigitalIn  Car_Sensor(PTE25); // 
    DigitalOut Front_Door(PTE24); 
    DigitalOut Fan(PTC12);
    DigitalOut Curtains(PTC7);

    DigitalOut MuxB(PTA9);
    DigitalOut MuxA(PTA8);

    // uint16_t analog_in_value = adc_read(0);// temp sensor at runtime
    // uint16_t analog_in_value = adc_read(1);// light sensor OUTDOOR at runtime
    // uint16_t analog_in_value = adc_read(2);// AN Spare/blue at runtime
    // uint16_t analog_in_value = adc_read(3);// IO/AN Spare/purple at runtime
    
    // unsigned int pwm_min=580;    
    pwm0.write (0.5); //indoor lamp
    pwm0.period_ms(10);
    pwm1.write (0.5); //front door lamp
    pwm1.period_ms(10);  
    pwm2.write (0.5); //lamp garage
    pwm2.period_ms(10);
    Garden_Lamp = 0;


    // Setting the multiplexor to the indoor temp sensor.
    MuxB = 0;
    MuxA = 0;

    char message[MESSAGE_MAX_SIZE + 1];
    message[MESSAGE_MAX_SIZE] = '\0';

    u8g2_ClearBuffer(&oled);
    u8g2_SetFont(&oled, u8g2_font_6x12_mr);
    u8g2_SendBuffer(&oled);

    bool openDoor = false;
    while (true)
    {

        if(!Blue_Button && !openDoor){
            Front_Door = 1;
            openDoor = true;
            ThisThread::sleep_for(1000ms);
        }
        else if (!Blue_Button && openDoor){
            Front_Door = 0;
            openDoor = false;
            ThisThread::sleep_for(1000ms);
        }
        // pwm3.write(0.5); //heater on
        // pwm3.period_ms(10);
        // ThisThread::sleep_for(5s);
        // Fan = 1;
        // Front_Door = 0;
        // Garage_Door = 0;
        
        // ThisThread::sleep_for(1s);

        // uint16_t analog_in_value = adc_read(0);
        // float voltage = ((float)analog_in_value  / 65535.0) * 3.0;
        // float temperature = (voltage * 1000 - 400) / 19.5;
        // snprintf(message, MESSAGE_MAX_SIZE, "Value is %-5d, temperature is %5.02f \n", analog_in_value , temperature);


        // // Clear screen and write a message.
        // u8g2_ClearBuffer(&oled);
        // u8g2_DrawUTF8(&oled, 10, 10, message);
        // u8g2_SendBuffer(&oled);
        
        // // Also write the message over USB to the serial monitor
        // printf("Value is %-5d, temperature is %5.02f \n", analog_in_value , temperature);
        

        // if (Car_Sensor == 0) {
        //     ThisThread::sleep_for(1s);
        //     Curtains = 1;
        //     // Front_Door = 1;
        //     // Garage_Door = 1;
        //     ThisThread::sleep_for(5s);
        //     Curtains = 0;
        //     // Front_Door = 0;
        //     // Garage_Door = 0; 
        // }
    }
 




}
