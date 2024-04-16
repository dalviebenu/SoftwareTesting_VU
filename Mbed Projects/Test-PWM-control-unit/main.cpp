#include "board_freedom.h"
#include "mbed.h"

int main() {
  unsigned int pwm_min = 775;
  board_init();
  pwm0.period_ms(20);
  while (true) {
    pwm0.pulsewidth_us(pwm_min);
    ThisThread::sleep_for(1s);

    for (int i = 0; i < 100; i++) {
      pwm0.pulsewidth_us(pwm_min + i * 900 / 100);
      ThisThread::sleep_for(40ms);
    }
    ThisThread::sleep_for(1s);
  }
}