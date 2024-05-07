#include "adc.h"
#include "board_freedom.h"
#include "freedom.cpp"
#include "mbed.h"
#include <cstdint>
#include <cstdio>



//  /*Libraries to add:::
// Select ‘master’ for u8g2 and ‘main’ for libboxzoo in the next window. Hit
// finish and add the other library.
// https://github.com/valuta1995/bugzoo-u8g2.git
// https://github.com/valuta1995/libboxzoo.git

int main() {
  board_init();

  HomeSensors Smart_Home_Sensors(PTE25, PTA8, PTA9, 0, 1);
  Home Smart_Home(PTB18, PTB11, PTE24, PTC12, PTC7, Smart_Home_Sensors);
  FreedomController Freedom(PTB5, PTB6, PTC16, PTB7, PTB2, PTB3, Smart_Home);

  Freedom.init();

  // SMART HOME NR 5 ZIGGY GLITTERDUST - 23-04-2024

  // NOT Implemented yet:
  // uint16_t analog_in_value = adc_read(2);// AN Spare/blue at runtime
  // uint16_t analog_in_value = adc_read(3);// IO/AN Spare/purple at runtime

  // char message[MESSAGE_MAX_SIZE + 1];
  // message[MESSAGE_MAX_SIZE] = '\0';

  // u8g2_ClearBuffer(&oled);
  // u8g2_SetFont(&oled, u8g2_font_6x12_mr);
  // u8g2_SendBuffer(&oled);

  // snprintf(message, MESSAGE_MAX_SIZE, "Value is %-5d, temperature is %5.02f
  // \n", analog_in_value , temperature);

  // Clear screen and write a message.
  // u8g2_ClearBuffer(&oled);
  // u8g2_DrawUTF8(&oled, 10, 10, message);
  // u8g2_SendBuffer(&oled);

  // Also write the message over USB to the serial monitor
  // printf("Value is %-5d, temperature is %5.02f \n", analog_in_value ,
  // temperature);
}