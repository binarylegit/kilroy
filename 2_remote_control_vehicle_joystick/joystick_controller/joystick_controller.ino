/*
 * Copyright (c) 2012 Daniel Fowler
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

int BaudRate = 9600;     // Baud rate for serial communications
int fiveSeconds = 5000;

int verticalIn = 1;
int horizontalIn = 0;

int horizontal_mid = 499;
int vertical_mid = 513;

int verifyLED = 13;

int ascii_L = 76;
int ascii_R = 82;
int ascii_V = 86;
int ascii_f = 102;
int ascii_b = 98;
int ascii_r = 114;

int max_velocity = 200;

void setup() {
  Serial.begin(BaudRate);
  Serial.flush();

  analogReference(DEFAULT);

  pinMode(verifyLED, OUTPUT);
  
  delay(1000);
  
  vertical_mid = analogRead(verticalIn);
  horizontal_mid = analogRead(horizontalIn);
}

void loop() {

  int verticalVal = analogRead(verticalIn);
  int horizontalVal = analogRead(horizontalIn);

  int equalized_vertical = equalize_joystick_reading(verticalVal, vertical_mid);
  int equalized_horizontal = equalize_joystick_reading(horizontalVal, vertical_mid);
  
//  int right_velocity = (equalized_vertical/max_velocity)*(equalized_horizontal + equalized_vertical);
//  int left_velocity = (equalized_vertical/max_velocity)*(equalized_vertical - equalized_horizontal);

  int right_velocity = max_min_two_hundred(equalized_horizontal + equalized_vertical);
  int left_velocity = max_min_two_hundred(equalized_vertical - equalized_horizontal);
  
/*  Serial.print("R: ");
  Serial.println(right_velocity, DEC);
  Serial.print("L: ");
  Serial.println(left_velocity, DEC);
  delay(5000);*/
    
  Serial.write(ascii_V);
  
  Serial.write(ascii_R);
  if(right_velocity > 0) {
    Serial.write(ascii_f);
  } else if(right_velocity < 0) {
    Serial.write(ascii_r);
  } else {
    Serial.write(ascii_b);
  }
  Serial.write(abs(right_velocity));
  
  Serial.write(ascii_L);
  if(left_velocity > 0) {
    Serial.write(ascii_f);
  } else if(left_velocity < 0) {
    Serial.write(ascii_r);
  } else {
    Serial.write(ascii_b);
  }
  Serial.write(abs(left_velocity));
 
  delay(250);
  
  Serial.flush();
}

int equalize_joystick_reading(int reading, int midpoint) {
  // TODO: this could be more clear
  if(reading > (midpoint - 10) && reading < (midpoint + 10)) {
      // if withing +- 5 of midpoint assume mid
    return 0;
  }
  
  reading = (reading - midpoint) / 2;
  
  return max_min_two_hundred(reading);  
}

int max_min_two_hundred(int reading) {
  // set to max/min if over
  if (reading > 200) {
    reading = 200;
  } else if (reading < -200) {
    reading = -200;
  }
  return reading;
}
