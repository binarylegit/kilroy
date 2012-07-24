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

int forwardButton = 8;
int backwardButton = 9;
int leftButton = 10;
int rightButton = 11;

int verifyLED = 13;

int asciiF = 70;
int asciiB = 66;
int asciiS = 83;
int asciiL = 76;
int asciiR = 82;

void setup() {
  Serial.begin(BaudRate);
  //delay(fiveSeconds);
  Serial.flush();

  pinMode(forwardButton, INPUT);
  pinMode(backwardButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(verifyLED, OUTPUT);
}

void loop() {

  int forwardVal = digitalDebounceRead(forwardButton);
  int backwardVal = digitalDebounceRead(backwardButton);
  int rightVal = digitalDebounceRead(rightButton);
  int leftVal = digitalDebounceRead(leftButton);

  if(forwardVal == HIGH) {
    Serial.write(asciiF);
    validateFeedback(asciiF, Serial.read());
  } 
  else if(backwardVal == HIGH) {
    Serial.write(asciiB);
    validateFeedback(asciiB, Serial.read());
  }
  else if(rightVal == HIGH) {
    Serial.write(asciiR);
    validateFeedback(asciiR, Serial.read());
  }
  else if(leftVal == HIGH) {
    Serial.write(asciiL);
    validateFeedback(asciiL, Serial.read());
  } 
  else {
    Serial.write(asciiS);
    validateFeedback(asciiS, Serial.read());
  }
  Serial.flush();
}

void validateFeedback(int writtenVal, int readVal) {
  if(writtenVal != readVal) {
    digitalWrite(verifyLED, HIGH);
  } 
  else {
    digitalWrite(verifyLED, LOW);
  }
}

int digitalDebounceRead(int pinToRead) {
  int initialState = digitalRead(pinToRead);
  delay(50); // delay 50 milliseconds
  int laterState = digitalRead(pinToRead);
  if(initialState == laterState) {
    return initialState;
  } 
  return LOW;
}









