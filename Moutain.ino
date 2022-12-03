// NeoPixelTest
// This example will cycle between showing four pixels as Red, Green, Blue, White
// and then showing those pixels as Black.
//
// Included but commented out are examples of configuring a NeoPixelBus for
// different color order including an extra white channel, different data speeds, and
// for Esp8266 different methods to send the data.
// NOTE: You will need to make sure to pick the one for your platform 
//
//
// There is serial output of the current state so you can confirm and follow along.
//

#include <NeoPixelBus.h>

const uint16_t PIXEL_COUNT = 148; 
const uint8_t PIXEL_PIN = 2;
const uint16_t TIME_STEP = 10;

HslColor fire_on(10.0/360.0, 1, 50.0/100.0);

HslColor pixel_off(10.0/360.0, 1, 0);

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PIXEL_COUNT, PIXEL_PIN);

HslColor pixels_curr[PIXEL_COUNT];
HslColor pixels_target[PIXEL_COUNT];
HslColor pixels_start[PIXEL_COUNT];
int blend_start[PIXEL_COUNT];
int blend_in[PIXEL_COUNT];
int blend_out[PIXEL_COUNT];

HslColor addBlendHslColors(HslColor colors[], float alphas[]) {
  float h = 0;
  float s = 0;
  float l = 0;
  float alpha = 0;

  for (int i = 0; i < PIXEL_COUNT; i++) {
    h += colors[i].H;
    s += colors[i].S;
    l += colors[i].L;
    alpha += alphas[i];
  }

  return HslColor(h/alpha, s/alpha, l/alpha);
}

HslColor linearBlendHslColor(HslColor c_start, HslColor c_target, int start, int target) {
  float alpha_target = (float)(-start)/(float)(target-start);

  if (alpha_target < 0) alpha_target = 0;
  if (alpha_target > 1) alpha_target = 1;

  float alpha_start = 1-alpha_target;

  return HslColor(
    c_start.H*alpha_start + c_target.H*alpha_target,
    c_start.S*alpha_start + c_target.S*alpha_target,
    c_start.L*alpha_start + c_target.L*alpha_target
  );
}

void processTargetBlending() {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    if (blend_in[i] <= 0) continue;

    pixels_curr[i] = linearBlendHslColor(pixels_start[i], pixels_target[i], blend_start[i], blend_in[i]);

    blend_start[i] -= TIME_STEP;
    blend_in[i] -= TIME_STEP;
    blend_out[i] -= TIME_STEP;

    if (blend_in[i] <= 0) {
      if (blend_out[i] > 0) {
        blend_start[i] = blend_in[i];
        blend_in[i] = blend_out[i];
        blend_out[i] = 0;
        pixels_start[i] = pixels_target[i];
        pixels_target[i] = pixel_off;
      } else {
        blend_start[i] = 0;
        blend_in[i] = 0;
        blend_out[i] = 0;
        pixels_start[i] = pixel_off;
        pixels_target[i] = pixel_off;
        pixels_curr[i] = pixel_off;
      }
    }
  }
}


void setup() {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    pixels_curr[i] = HslColor(0, 0, 0);
    pixels_start[i] = HslColor(0, 0, 0);
    pixels_target[i] = HslColor(0, 0, 0);
    blend_in[i] = 0;
    blend_out[i] = 0;
  }
  strip.Begin();
  for (int i=0; i< PIXEL_COUNT; i++) {
      strip.SetPixelColor(i, pixels_curr[i]);
    }
  strip.Show();
}

void calculate_flames() {
    uint16_t index = random(PIXEL_COUNT);
     if (pixels_curr[index].L > 0)
       pixels_start[index] = pixels_curr[index];
     else
      pixels_start[index] = pixel_off;
    pixels_target[index] = fire_on;
    blend_start[index] = 0.0;
    int intime = random(300)+200;
    blend_in[index] = intime;
    blend_out[index] = intime+random(300)+200;

    processTargetBlending();    
}

float offset = 0;

void loop()
{
    float l_gain = 1;
    delay(TIME_STEP);

    calculate_flames();

    for (int i=0; i< PIXEL_COUNT; i++) {
      HslColor col = pixels_curr[i];
      strip.SetPixelColor(i, HslColor(col.H, col.S, col.L*l_gain));
    }
    strip.Show();
}
