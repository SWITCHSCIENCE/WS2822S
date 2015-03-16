//*****************************************************************
// WS2822S
// 2015/01/29
//
// 色情報の設定　setColor(LEDの番号、赤、緑、青)
// 色情報の送信  send()
//
//******************************************************************

#include "Ws2822s.h"
#define PIXEL_NUM 10    //使用するWS2822Sの数
#define LED_PIN 13      //WS2822SのDAIピンにつなげるArduinoのピン番号

Ws2822s LED(LED_PIN , PIXEL_NUM);

void setup()
{
    
}
void loop()
{     
  for(int i=0;i<PIXEL_NUM;i++){
      LED.setColor(i              ,0xFF,0x00,0x00);
      LED.setColor((i+1)%PIXEL_NUM,0xFF,0xFF,0x00);
      LED.setColor((i+2)%PIXEL_NUM,0x00,0xFF,0x00);
      LED.setColor((i+3)%PIXEL_NUM,0x00,0xFF,0xFF);
      LED.setColor((i+4)%PIXEL_NUM,0x00,0x00,0xFF);
      LED.setColor((i+5)%PIXEL_NUM,0xFF,0x00,0xFF);
      LED.setColor((i+6)%PIXEL_NUM,0x00,0x00,0x00);
      LED.setColor((i+7)%PIXEL_NUM,0x00,0x00,0x00);
      LED.setColor((i+8)%PIXEL_NUM,0x00,0x00,0x00);
      LED.setColor((i+9)%PIXEL_NUM,0x00,0x00,0x00);
      LED.send();
      delay(300);
  }
  
}

