//*****************************************************************
// WS2822S
//
// アドレス設定  setAddress(LEDの先頭番号、LEDの末尾番号)
//******************************************************************

#include "Ws2822s.h"
#define NUM_PIXELS 10 // 使用するWS2822Sの数
#define LED_PIN 13 // WS2822SのDAIピンにつなげるArduinoのピン番号
#define ADR_PIN 12 // WS2822SのADRIピンにつなげるArduinoのピン番号

Ws2822s LED(LED_PIN, ADR_PIN, NUM_PIXELS);

void setup()
{
}

void loop()
{
  LED.setAddress(0,9); // 先頭から0,1,2... 8,9とアドレスを書き込み
		       // 一度アドレスを書き込んだらLEDの電源をOFFに
  delay(5000);
}
