/*
 * Tune RGB LED based on HSV model
 * This code is derived from "Adafruit Arduino - Lesson 3. RGB LED"
 * https://learn.adafruit.com/adafruit-arduino-lesson-3-rgb-leds/overview
 */
// #define DEBUG

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE

void setColorHSV(float h, float s, float v);
void setup()
{
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  // Fading hue
  for(int hue=0;hue<360;++hue){
    setColorHSV(hue,1.0,0.2);
    delay(100);
  }
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

/**
* @brief Tune a rgb led based on HSV model
* HSV色空間に基づいて,RGBLEDを光らせる
* @param H Hue(色相), 0.0--360.0
* @param S Saturation(彩度), 0.0--1.0
* @param V Value(Brightness, 明度), 0.0--1.0
*/
void setColorHSV(float h, float s, float v)
{
  int r,g,b;
  int hi;
  float f, p, q, t;

  hi = ((int)(h / 60)) % 6;
  f = h / 60 - hi;
  p = v * (1 - s);
  q = v * (1 - f * s);
  t = v * (1 - (1 - f) * s);

  // convert to 256 levels
	v *= 255;
	p *= 255;
	q *= 255;
	t *= 255;
  switch (hi) {
  case 0: r = v; g = t; b = p; break;
  case 1: r = q; g = v; b = p; break;
  case 2: r = p; g = v; b = t; break;
  case 3: r = p; g = q; b = v; break;
  case 4: r = t; g = p; b = v; break;
  case 5: r = v; g = p; b = q; break;
  }
  #ifdef DEBUG
  Serial.print(r);
  Serial.print(",");
  Serial.print(g);
  Serial.print(",");
  Serial.println(b);
  #endif
  setColor(r,g,b);
}
