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


const int maxnum = 148;

const uint16_t PixelCount = maxnum; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 2;  // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 128

// three element pixels, in different order and speeds
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
//NeoPixelBus<NeoRgbFeature, Neo400KbpsMethod> strip(PixelCount, PixelPin);

// For Esp8266, the Pin is omitted and it uses GPIO3 due to DMA hardware use.  
// There are other Esp8266 alternative methods that provide more pin options, but also have
// other side effects.
// For details see wiki linked here https://github.com/Makuna/NeoPixelBus/wiki/ESP8266-NeoMethods.

// You can also use one of these for Esp8266, 
// each having their own restrictions.
//
// These two are the same as above as the DMA method is the default.
// NOTE: These will ignore the PIN and use GPI03 pin.
//NeoPixelBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> strip(PixelCount, PixelPin);
//NeoPixelBus<NeoRgbFeature, NeoEsp8266Dma400KbpsMethod> strip(PixelCount, PixelPin);

// Uart method is good for the Esp-01 or other pin restricted modules.
// for details see wiki linked here https://github.com/Makuna/NeoPixelBus/wiki/ESP8266-NeoMethods.
// NOTE: These will ignore the PIN and use GPI02 pin.
//NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart1800KbpsMethod> strip(PixelCount, PixelPin);
//NeoPixelBus<NeoRgbFeature, NeoEsp8266Uart1400KbpsMethod> strip(PixelCount, PixelPin);

// The bitbang method is really only good if you are not using WiFi features of the ESP.
// It works with all but pin 16.
//NeoPixelBus<NeoGrbFeature, NeoEsp8266BitBang800KbpsMethod> strip(PixelCount, PixelPin);
//NeoPixelBus<NeoRgbFeature, NeoEsp8266BitBang400KbpsMethod> strip(PixelCount, PixelPin);

// four element pixels, RGBW
//NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

RgbColor red(226, 88, 34);
RgbColor green(230, 41, 44);
RgbColor blue(255, 165, 0);


void setup()
{
    Serial.begin(115200);
    while (!Serial); // wait for serial attach

    Serial.println();
    Serial.println("Initializing...");
    Serial.flush();

    // this resets all the neopixels to an off state
    strip.Begin();
    strip.Show();


    Serial.println();
    Serial.println("Running...");
}


void loop()
{
    delay(50);

    for (int i=0; i< maxnum; i++) {
      strip.SetPixelColor(i, RgbColor(random(255), random(255), random(255)));
    }
    strip.Show();






}
