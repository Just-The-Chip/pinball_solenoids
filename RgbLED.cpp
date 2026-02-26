#include "Arduino.h"
#include "RgbLED.h"
 
#define	PINVAL(x) 	(type == COMMON_CATHODE ? (x) : (255 - (x)))

RgbLED::RgbLED(
  int _pinred, int _pingreen, int _pinblue , bool _type
) {
  pinred = _pinred;
  pinblue = _pinblue;
  pingreen = _pingreen;
  type = _type;
  currentAngle = 0;
  rainbowStepTime = 0;

  pinMode(_pinred, OUTPUT);
  pinMode(_pingreen, OUTPUT);
  pinMode(_pinblue, OUTPUT);
  setRGB(0, 0, 0);
}

void RgbLED::setRGB(uint8_t red, uint8_t green, uint8_t blue) {
  analogWrite(pinred, PINVAL(red));	
  analogWrite(pingreen, PINVAL(green));
  analogWrite(pinblue, PINVAL(blue));
}

void RgbLED::initRainbow(unsigned int angle) {
  rainbowStepTime = millis();
  setCurrentAngle(angle);
  stepRainbow();
}

void RgbLED::rainbow(int wait) {
  unsigned long currentTime = millis();

  // Serial.print(currentTime);
  // Serial.print(" ");
  // Serial.println(rainbowStepTime);
  if (currentTime >= rainbowStepTime + wait) {
    rainbowStepTime = currentTime;
    setCurrentAngle(++currentAngle);
    // Serial.println(currentAngle);
    stepRainbow();
  }
}

void RgbLED::setCurrentAngle(unsigned int angle) {
  currentAngle = angle % 360;
}

// HSV algorithm: https://www.instructables.com/How-to-Make-Proper-Rainbow-and-Random-Colors-With-/
void RgbLED::stepRainbow() {
  uint8_t red, green, blue;

  if (currentAngle<60) {red = 255; green = HSVlights[currentAngle]; blue = 0;} else
  if (currentAngle<120) {red = HSVlights[120-currentAngle]; green = 255; blue = 0;} else 
  if (currentAngle<180) {red = 0, green = 255; blue = HSVlights[currentAngle-120];} else 
  if (currentAngle<240) {red = 0, green = HSVlights[240-currentAngle]; blue = 255;} else 
  if (currentAngle<300) {red = HSVlights[currentAngle-240], green = 0; blue = 255;} else 
                 {red = 255, green = 0; blue = HSVlights[360-currentAngle];} 

  setRGB(red, green, blue);
}
