/*
 * Copyright (c) 2012 Daniel Fowler
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 
#include "Constants.h"
#include "BatteryController.cpp"
#include "Motor.cpp"

unsigned long chargeTimer;
unsigned long left_overload_time;
unsigned long right_overload_time;
const int REVERSE_MODE = 0;
const int BRAKE_MODE = 1;
const int FORWARD_MODE = 2;
int left_mode=1;  
int right_mode=1; 
int left_velocity;
int right_velocity;
BatteryController *battery_controller;
Motor *left_motor;
Motor *right_motor;

void setup()
{

  battery_controller = new BatteryController(BATTERY_PIN, CHARGING_PIN);
  
  Serial.begin(SERIAL_BAUD);                                      // enable serial communications if Cmode=1
  Serial.flush();                                           // flush buffer
  left_motor = new Motor(LEFT_MOTOR_A, LEFT_MOTOR_B, LEFT_MOTOR_CURRENT, LEFT_MAX_AMPS);;
  right_motor = new Motor(RIGHT_MOTOR_A, RIGHT_MOTOR_B, RIGHT_MOTOR_CURRENT, RIGHT_MAX_AMPS);
  
}


void loop() {

  if (left_motor->is_motor_over_amp_limit()) {
    left_motor->turn_off();
    left_overload_time=millis();                                    // record time of overload
  }

  if (right_motor->is_motor_over_amp_limit()) {
    right_motor->turn_off();
    right_overload_time=millis();                                   // record time of overload
  }

  if (battery_controller->is_battery_flat() || battery_controller->is_charging_enabled()) {  
    left_motor->turn_off();
    right_motor->turn_off();
    battery_controller->charge_battery_synchronously();
  } else {
    read_serial();
    if ((millis()-left_overload_time)>OVERLOAD_DELAY_MS) {
      switch (left_mode) {                                   
      case FORWARD_MODE:                                               
        left_motor->forward(left_velocity);
        break;
      case BRAKE_MODE: 
        left_motor->brake(left_velocity);
        break;
      case REVERSE_MODE: 
        left_motor->reverse(left_velocity);
        break;
      }
    } 
    
    if ((millis()-right_overload_time)>OVERLOAD_DELAY_MS) {
      switch (right_mode) {                        
      case FORWARD_MODE:                                     
        right_motor->forward(right_velocity);
        break;
      case BRAKE_MODE:
        right_motor->brake(right_velocity);
        break;
      case REVERSE_MODE:
        right_motor->reverse(right_velocity);
        break;
      }
    } 
  }
}


void read_serial() {
      // first byte: [V] - velocity continue reading below [O] - turn off motors, stop reading.
      // serial package: [R,L][f,b,r][0-225] x 2
  
  if (Serial.available() >= 1) {
    int serial_data = Serial.read();
    Serial.write(serial_data);
    
    if(serial_data == 86) { // V
      // read velocity values
      int wheel_side_1 = blocking_serial_read();
      int wheel_direction_1 = blocking_serial_read();
      int wheel_velocity_1 = blocking_serial_read();
      int wheel_side_2 = blocking_serial_read();
      int wheel_direction_2 = blocking_serial_read();
      int wheel_velocity_2 = blocking_serial_read();

      if(wheel_side_1 == 82/*R*/ && wheel_side_2 == 76/*L*/) {
        right_mode = get_mode_value(wheel_direction_1);
        right_velocity = wheel_velocity_1;
        left_mode = get_mode_value(wheel_direction_2);
        left_velocity = wheel_velocity_2;
      } else if(wheel_side_1 == 76/*L*/ && wheel_side_2 == 82/*R*/) {
        right_mode = get_mode_value(wheel_direction_2);
        right_velocity = wheel_velocity_2;
        left_mode = get_mode_value(wheel_direction_1);
        left_velocity = wheel_velocity_1;
      }
    } else if(serial_data == 79) { // O
      // TODO
    } else {
      Serial.flush();
    }
  }
}

int get_mode_value(int letter_value) {
  if(letter_value == 102) { //f
  return FORWARD_MODE;
  } else if (letter_value == 98) { // b
  return BRAKE_MODE;
  } else if(letter_value == 114) { //r
  return REVERSE_MODE;
  } else {
    return -1;
  }
}

int blocking_serial_read() { // blocking serial read 
  int data = -1;
  do {
    data=Serial.read();
  } while (data<0);
  return data;
}

