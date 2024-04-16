#include "mbed.h"

// main() runs in its own thread in the OS
int main()
{

    DigitalOut signalOut(PTC12);

    for (double i = 0.1; i <= 0.9; i += 0.1) {
        auto now = std::chrono::system_clock::now();
        std::chrono::seconds durationToAdd(2);

        // Add the duration to the current time point
        auto time_to_stop = now + durationToAdd;
        while (time_to_stop > std::chrono::system_clock::now()) {
            signalOut = 1;
            wait_us(1000000 * i);
            signalOut = 0;
            wait_us(1000000 - (1000000 * i));
        }
    }
}