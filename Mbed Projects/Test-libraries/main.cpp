#include "mbed.h"
#include "board_freedom.h"
#include "oled_ssd1322.h"


// main() runs in its own thread in the OS
int main()
{
    // Initialize the board (and the oled screen)
    board_init();
    
    // Clear the buffer (will clear the screen when sent)
    u8g2_ClearBuffer(&oled);
    
    // Ensure a font is set (only required once)
    u8g2_SetFont(&oled, u8g2_font_nokiafc22_tr);
    
    // Draw text to the screen
    u8g2_int_t x = 30;
    u8g2_int_t y = 20;
    const char message[] = "Hello World";
    u8g2_DrawUTF8(&oled, x, y, message);


    // Put all the changes in the buffer onto the screen.
    u8g2_SendBuffer(&oled);

    }
