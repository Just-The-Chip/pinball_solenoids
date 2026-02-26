#include <stdint.h>
#ifndef RGB_LED_h
#define RGB_LED_h

#include	<Arduino.h>

#define	COMMON_ANODE		1
#define	COMMON_CATHODE		0

// HSV algorithm: https://www.instructables.com/How-to-Make-Proper-Rainbow-and-Random-Colors-With-/
static const uint8_t HSVlights[61] = 
{0, 4, 8, 13, 17, 21, 25, 30, 34, 38, 42, 47, 51, 55, 59, 64, 68, 72, 76,
81, 85, 89, 93, 98, 102, 106, 110, 115, 119, 123, 127, 132, 136, 140, 144,
149, 153, 157, 161, 166, 170, 174, 178, 183, 187, 191, 195, 200, 204, 208,
212, 217, 221, 225, 229, 234, 238, 242, 246, 251, 255};

class RgbLED {
  public:
    RgbLED(
      int _pinred = 3, 
      int _pingreen = 5, 
      int _pinblue = 6,
      bool _type = COMMON_ANODE
    );
    void setRGB(uint8_t red, uint8_t green, uint8_t blue);
    void initRainbow(unsigned int angle = 0);
    void rainbow(int wait);

  private:
    unsigned long rainbowStepTime;
    unsigned int currentAngle = 0;

    bool	type;
    int	pinred;
    int	pingreen;
    int	pinblue;

    void setCurrentAngle(unsigned int angle);
    void stepRainbow();
};

#endif

