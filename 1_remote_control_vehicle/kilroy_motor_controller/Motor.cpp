/*
 * Copyright (c) 2012 Daniel Fowler
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef Motor_H
#define Motor_H

#include <Arduino.h>

class Motor {
  private:
    const int _hbridge_input_a;
    const int _hbridge_input_b;
    const int _current_draw_pin;
    const int _max_amps;
    
    static const int max_allowed_power = 255;
    
    int validate_velocity(int);
  public:
   Motor (int, int, int, int);
   ~Motor ();
   
   bool is_motor_over_amp_limit();
   void forward(int);
   void reverse(int);
   void brake(int);
   void turn_off();
};

#endif

inline Motor::Motor(int hbridge_input_a, 
                    int hbridge_input_b, 
                    int current_draw_pin, 
                    int max_amps) 
  : _hbridge_input_a(hbridge_input_a), 
    _hbridge_input_b(hbridge_input_b),
    _current_draw_pin(current_draw_pin),
    _max_amps(max_amps) {
}

inline Motor::~Motor() {}

inline bool Motor::is_motor_over_amp_limit() {
  return analogRead(_current_draw_pin) > _max_amps; 
}

inline void Motor::forward(int velocity) {
  velocity = validate_velocity(velocity);
  analogWrite(_hbridge_input_a,0);
  analogWrite(_hbridge_input_b,velocity);
}

inline void Motor::reverse(int velocity) {
  velocity = validate_velocity(velocity);
  analogWrite(_hbridge_input_a,velocity);
  analogWrite(_hbridge_input_b,0);
}

inline void Motor::brake(int power) {
  power = validate_velocity(power);
  analogWrite(_hbridge_input_a,power);
  analogWrite(_hbridge_input_b,power);
}

inline void Motor::turn_off() {
  analogWrite(_hbridge_input_a,0);
  analogWrite(_hbridge_input_b,0);
}

inline int Motor::validate_velocity(int velocity) {
  if( velocity > max_allowed_power) {
    velocity = max_allowed_power;
  } else if (velocity < 0) {
    velocity = 0;
  }
  return velocity;
}

