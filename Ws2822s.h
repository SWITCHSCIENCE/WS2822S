//*****************************************************************
// WS2822S
// 2015/01/29 ver 0.1
// 2015/02/12 ver 0.2 アドレス設定関数追加
//
// 色情報の設定　setColor(LEDの番号、赤、緑、青)
// 色情報の送信 send()
// アドレス設定  setAddress(LEDの先頭番号、LEDの末尾番号)
//******************************************************************

#ifndef Ws2822s_h
#define Ws2822s_h
#include "Arduino.h"

class Ws2822s
{
public:
  Ws2822s(uint8_t dai,int pixel_num);
  Ws2822s(uint8_t dai, uint8_t adri, int pixel_num);

  void setColor(int ch, uint8_t r, uint8_t g, uint8_t b);
  void setAddress(int start_pixel, int end_pixel);
  void send();
  void test();

private:
  volatile uint8_t *reg_dai, *reg_adri, *out_dai, *out_adri;
  volatile uint8_t bit, bit_address;
  volatile int max_pixel;
  uint8_t **pixel;
  volatile uint8_t channel_rv, temp;
  volatile int channel;
  void sendByte(volatile uint8_t value, volatile uint8_t *out_port, volatile uint8_t out_bit);
};

#endif
