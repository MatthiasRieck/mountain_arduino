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
const uint16_t TIME_STEP = 50;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PIXEL_COUNT, PIXEL_PIN);

HslColor pixels_curr[PIXEL_COUNT];
HslColor pixels_target[PIXEL_COUNT];
HslColor pixels_start[PIXEL_COUNT];
int blend_start[PIXEL_COUNT];
int blend_curr[PIXEL_COUNT];
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

HslColor linearBlendHslColor(HslColor c_start, HslColor c_target, int start, int curr, int target) {
  float alpha_start = (float)(curr-start)/(float)(target-start);
  float alpha_target = 1-alpha_start;

  return HslColor(
    c_start.H*alpha_start + c_target.H*alpha_target,
    c_start.S*alpha_start + c_target.S*alpha_target,
    c_start.L*alpha_start + c_target.L*alpha_target
  );
}

void processTargetBlending() {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    HslColor curr_color = linearBlendHslColor(pixels_start[i], pixels_target[i], blend_start[i], blend_curr[i], blend_in[i]);

  }
}


void setup() {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    pixels_curr[i] = HslColor(0, 0, 0);
    pixels_start[i] = HslColor(0, 0, 0);
    pixels_target[i] = HslColor(0, 0, 0);
  }
}

void calculate_flames() {
    
}


void loop()
{
    float l_gain = 0.5;
    delay(50);

    calculate_flames();

    for (int i=0; i< PIXEL_COUNT; i++) {
      HslColor col = pixels_curr[i];
      strip.SetPixelColor(i, HslColor(col.H, col.S, col.L*l_gain));
    }
    strip.Show();






}
