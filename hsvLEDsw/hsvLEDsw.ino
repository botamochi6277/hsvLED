/*
 * light RGB LED based on HSV model and change color with switch
 * This code is derived from "Adafruit Arduino - Lesson 3. RGB LED"
 * https://learn.adafruit.com/adafruit-arduino-lesson-3-rgb-leds/overview
 */
// #define DEBUG

const int swPin = 2;

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

int flag = 0;
bool isPush = false;
int cnt = 0;
float color[6] = {0,60,120,180,240,300};

//uncomment this line if using a Common Anode LED
#define COMMON_ANODE

void setColorHSV(float h, float s, float v);
void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(swPin, INPUT_PULLUP);
}

void loop()
{
  if(digitalRead(swPin) == LOW){
    // unPushing
    ++flag;
    if(flag > 3){
      flag = 3;
      isPush = false;
    }
  }else{
    // Pushing
    --flag;
    if(flag < -3){
      flag = -3;
      isPush = true;
    }
  }
  if(flag==0 && !isPush){
    // Push!!!
    ++cnt;
    if(cnt > 5){
      cnt = 0;
    }
  }

  setColorHSV(color[cnt],(float)analogRead(A0)/1024,0.2);
  delay(10);
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
* @brief HSV色空間に基づいて,RGBLEDを光らせる
* @param H 色相(Hue), 0.0--360.0
* @param S 彩度(Saturation), 0.0--1.0
* @param V 明度(Value), 0.0--1.0
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

  // 256階調に戻す
	v = v*255;
	p = p*255;
	q = q*255;
	t = t*255;
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
