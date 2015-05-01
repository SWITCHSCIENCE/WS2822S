//*****************************************************************
// WS2822S
// 2015/01/29
//
// 色情報の設定　setColor(LEDの番号、赤、緑、青)
// 色情報の送信  send()
//
//******************************************************************

#include "Ws2822s.h"
#define NUM_PIXELS 10 // 使用するWS2822Sの数
#define LED_PIN 13 // WS2822SのDAIピンにつなげるArduinoのピン番号

Ws2822s LED(LED_PIN, NUM_PIXELS);

void setup()
{
}

void loop()
{
  for (int i = 0; i < NUM_PIXELS; ++i) {
    LED.setColor(i, 0xFF, 0x00, 0x00);
    LED.setColor((i + 1) % NUM_PIXELS, 0xFF, 0xFF, 0x00);
    LED.setColor((i + 2) % NUM_PIXELS, 0x00, 0xFF, 0x00);
    LED.setColor((i + 3) % NUM_PIXELS, 0x00, 0xFF, 0xFF);
    LED.setColor((i + 4) % NUM_PIXELS, 0x00, 0x00, 0xFF);
    LED.setColor((i + 5) % NUM_PIXELS, 0xFF, 0x00, 0xFF);
    LED.setColor((i + 6) % NUM_PIXELS, 0x00, 0x00, 0x00);
    LED.setColor((i + 7) % NUM_PIXELS, 0x00, 0x00, 0x00);
    LED.setColor((i + 8) % NUM_PIXELS, 0x00, 0x00, 0x00);
    LED.setColor((i + 9) % NUM_PIXELS, 0x00, 0x00, 0x00);
    LED.send();
    delay(300);
  }
}
