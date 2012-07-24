/*
 * Copyright (c) 2012 Daniel Fowler
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#define SERIAL_BAUD            9600     // Baud rate for serial communications

/***************************** BATTERY CHARGER SETTINGS *****************************/

#define MINIMUM_BATTERY_VOLTAGE           487     // This is the nominal battery voltage reading. Peak charge can only occur above this voltage.
#define LOW_BATTERY_VOLTAGE          410     // This is the voltage at which the speed controller goes into recharge mode.
#define CHARGING_TIMEOUT   300000     // If the battery voltage does not change in this number of milliseconds then stop charging.



/***************************** H BRIDGE SETTINGS *****************************/

#define LEFT_MAX_AMPS       800     // set overload current for left motor 
#define RIGHT_MAX_AMPS       800     // set overload current for right motor 
#define OVERLOAD_DELAY_MS       100     // time in mS before motor is re-enabled after overload occurs

/***************************** IO Pins *****************************/

#define LEFT_MOTOR_A             3  // Left  motor H bridge, input A
#define LEFT_MOTOR_B            11  // Left  motor H bridge, input B
#define RIGHT_MOTOR_A             5  // Right motor H bridge, input A
#define RIGHT_MOTOR_B             6  // Right motor H bridge, input B


#define BATTERY_PIN             0  // Analog input 00
#define RIGHT_MOTOR_CURRENT             6  // Analog input 06
#define LEFT_MOTOR_CURRENT             7  // Analog input 07
#define CHARGING_PIN            13  // Low=ON High=OFF


