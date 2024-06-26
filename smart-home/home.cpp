#include "adc.h"
#include "mbed.h"
#include <cstdint>
#include <cstdio>


class HomeSensors {
public:
  DigitalIn Car_Sensor;
  DigitalOut MuxA;
  DigitalOut MuxB;
  int Analog_Temp_Pin;
  int Analog_Light_Outdoor_Pin;
  HomeSensors(PinName car_sensor_pin, PinName muxa_pin, PinName muxb_pin,
              int analog_temp_pin, int analog_light_outdoor_pin)
      : Car_Sensor(car_sensor_pin), MuxA(muxa_pin), MuxB(muxb_pin) {
    Analog_Temp_Pin = analog_temp_pin;
    Analog_Light_Outdoor_Pin = analog_light_outdoor_pin;
  }

  uint16_t GetAnalogValueOfTempterature() { return adc_read(Analog_Temp_Pin); }

  uint16_t GetAnalogValueOfOutdoorLight() {
    return adc_read(Analog_Light_Outdoor_Pin);
  }

  float getInsideTemperature() {
    MuxA = 0;
    MuxB = 0;
    uint16_t analog_in_value = GetAnalogValueOfTempterature();
    float voltage = ((float)analog_in_value / 65535.0) * 3.0;
    return (voltage * 1000 - 400) / 19.5;
  }

  bool IsDarkOutside() {
      return GetAnalogValueOfOutdoorLight() < 10000;
  }
};

class Home {
public:
  DigitalOut Garden_Lamp;
  DigitalOut Garage_Door;
  DigitalOut Front_Door;
  DigitalOut Fan;
  DigitalOut Curtains;
  HomeSensors &Sensors;

  Home(PinName garden_lamp_pin, PinName garage_door_pin, PinName front_door_pin,
       PinName fan_pin, PinName curtains_pin, HomeSensors &sensors_ref)
      : Garden_Lamp(garden_lamp_pin), Garage_Door(garage_door_pin),
        Front_Door(front_door_pin), Fan(fan_pin), Curtains(curtains_pin),
        Sensors(sensors_ref) {}

  void SetIndoorLampOn() { 
      pwm0.write(0.5);
      pwm0.period_ms(10); 
  }

  void SetIndoorLampOff() {
      pwm0.write(0);
    //   pwm0.period_ms(0);
  }

  void SetFrontDoorLampOn() {
       pwm1.write(0.5); 
       pwm1.period_ms(10);
  }

  void SetFrontDoorLampOff() {
       pwm1.write(0); 
    //    pwm1.period_ms(0);
  }

  void SetGarageLampOn() { 
      pwm2.write(0.5); 
      pwm2.period_ms(10);
  }

  void SetGarageLampOff() { 
      pwm2.write(0); 
    //   pwm2.period_ms(0);
  }

  void SetHeaterOn() { 
      pwm3.write(1.0);
      pwm3.period_ms(10);
      Fan = 1;
  }

  void SetHeaterOff() { 
      pwm3.write(0);
    //   pwm3.period_ms(0);
      Fan = 0;
  }
};
