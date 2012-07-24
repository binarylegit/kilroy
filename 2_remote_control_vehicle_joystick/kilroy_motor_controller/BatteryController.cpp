/*
 * Copyright (c) 2012 Daniel Fowler
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef BatteryController_H
#define BatteryController_H

#include <Arduino.h>
#include "Constants.h"

class BatteryController {
  private:
    const int _battery_pin;
    const int _charging_pin;
    bool _charging_enabled;
    void enable_charging();
    void disable_charging();
  public:
   BatteryController (int, int);
   ~BatteryController ();
   
   int read_voltage();
   bool is_battery_flat();
   bool is_charging_enabled();
   void charge_battery_synchronously();
};

#endif

inline BatteryController::BatteryController(int battery_pin, int charging_pin)
  : _battery_pin(battery_pin),
  _charging_pin(charging_pin){
  pinMode (_charging_pin, OUTPUT);                                   // change Charger pin to output
  disable_charging();
}

inline BatteryController::~BatteryController() {}

inline int BatteryController::read_voltage() {
  return analogRead(_battery_pin);                          
}

inline bool BatteryController::is_battery_flat() {
  return read_voltage() < LOW_BATTERY_VOLTAGE;
}

/* only charge synchronously to prevent malfunction while at a low voltage */
inline void BatteryController::charge_battery_synchronously() {
  int current_voltage;
  int highest_voltage_reading;
  unsigned long highest_voltage_read_time;
  
  if (is_battery_flat() && !_charging_enabled) {
    highest_voltage_reading = read_voltage();
    highest_voltage_read_time = millis();

    enable_charging();
  } else {
    // this is a safegaurd to prevent accidental operation while charging.
    disable_charging();
  }
  
  while(_charging_enabled) {
    current_voltage = read_voltage();
    if(current_voltage > highest_voltage_reading) { // if voltage has increased set the current_voltage
      highest_voltage_reading = current_voltage;
      highest_voltage_read_time = millis();
    }
    
    if(highest_voltage_reading > MINIMUM_BATTERY_VOLTAGE) {
      if((highest_voltage_reading - current_voltage) > 5 || (millis() - highest_voltage_read_time) > CHARGING_TIMEOUT) {
        disable_charging();
      }
    } 
  }
}
  
inline bool BatteryController::is_charging_enabled() {
  return _charging_enabled;
}

inline void BatteryController::enable_charging() {
  if(_charging_enabled) {
    return;
  } else {
    _charging_enabled = true;
    digitalWrite(_charging_pin, 0); // turn on current regulator
  }
}

inline void BatteryController::disable_charging() {
  if(_charging_enabled) {
    _charging_enabled = false;
    digitalWrite(_charging_pin, 1); // turn off current regulator
  }
}
