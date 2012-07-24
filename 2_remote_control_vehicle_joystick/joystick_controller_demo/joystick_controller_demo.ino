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
int zero = 0;
int fiveSeconds = 5000;

int verticalIn = 1;
int horizontalIn = 0;

int horizontalMid = 499;
int verticalMid = 526;

int verifyLED = 13;

int ascii_L = 76;
int ascii_R = 82;
int ascii_V = 86;
int ascii_f = 102;
int ascii_b = 98;
int ascii_r = 114;

void setup() {
  Serial.begin(BaudRate);
  Serial.flush();

  analogReference(DEFAULT);

  pinMode(verifyLED, OUTPUT);
}

void loop() {

  //int verticalVal = analogRead(verticalIn);
  //int horizontalVal = analogRead(horizontalIn);

  //Serial.print("V: ");
  //Serial.println(verticalVal, DEC);
  //Serial.print("H: ");
  //Serial.println(horizontalVal, DEC);
  //delay(250);
  
  Serial.write(ascii_V);
  
  Serial.write(ascii_R);
  Serial.write(ascii_f);
  Serial.write(200);
  
  Serial.write(ascii_L);
  Serial.write(ascii_f);
  Serial.write(200);
  
  delay(2000);
  
  Serial.flush();

  Serial.write(ascii_V);
  
  Serial.write(ascii_R);
  Serial.write(ascii_b);
  Serial.write(200);
  
  Serial.write(ascii_L);
  Serial.write(ascii_b);
  Serial.write(200);
  
  delay(1000);
  
  Serial.flush();
  
  Serial.write(ascii_V);
  
  Serial.write(ascii_R);
  Serial.write(ascii_r);
  Serial.write(200);
  
  Serial.write(ascii_L);
  Serial.write(ascii_r);
  Serial.write(200);
  
  delay(2000);
  
  Serial.flush();
  
}

