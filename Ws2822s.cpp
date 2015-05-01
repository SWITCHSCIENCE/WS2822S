//*****************************************************************
// WS2822S
// 2015/01/29 ver 0.1
// 2015/02/12 ver 0.2 アドレス設定関数追加
//
// 色情報の設定　setColor(LEDの番号、赤、緑、青)
// 色情報の送信 send()
// アドレス設定  setAddress(LEDの先頭番号、LEDの末尾番号)
//******************************************************************

#include "arduino.h"
#include "Ws2822s.h"

Ws2822s::Ws2822s(uint8_t dai,int pixel_num)
{
  uint8_t bit_dai = digitalPinToBitMask(dai);
  uint8_t port_dai = digitalPinToPort(dai);

  if (port_dai == NOT_A_PIN)
    return;

  reg_dai = portModeRegister(port_dai);
  out_dai = portOutputRegister(port_dai);

  //uint8_t oldSREG = SREG;
  //cli();
  *reg_dai |= bit_dai;
  //SREG = oldSREG;
  //sei();
  bit = bit_dai;
  pixel = new uint8_t*[pixel_num];
  for (int i = 0; i < pixel_num; ++i) {
    pixel[i] = new uint8_t[3];
  }
  max_pixel = pixel_num;
}

Ws2822s::Ws2822s(uint8_t dai, uint8_t adri, int pixel_num)
{
  uint8_t bit_dai = digitalPinToBitMask(dai);
  uint8_t bit_adri = digitalPinToBitMask(adri);
  uint8_t port_dai = digitalPinToPort(dai);
  uint8_t port_adri = digitalPinToPort(adri);

  if (port_dai == NOT_A_PIN)
    return;
  if (port_adri == NOT_A_PIN)
    return;

  reg_dai = portModeRegister(port_dai);
  out_dai = portOutputRegister(port_dai);
  reg_adri = portModeRegister(port_adri);
  out_adri = portOutputRegister(port_adri);

  uint8_t oldSREG = SREG;
  cli();
  *reg_dai |= bit_dai;
  *reg_adri |= bit_adri;
  SREG = oldSREG;
  sei();
  bit = bit_dai;
  bit_address = bit_adri;
  pixel = new uint8_t*[pixel_num];
  for (int i = 0; i < pixel_num; ++i) {
    pixel[i] = new uint8_t[3];
  }
  max_pixel = pixel_num;
}

void Ws2822s::setColor(int ch, uint8_t r, uint8_t g, uint8_t b)
{
  if(ch >= max_pixel || ch < 0)
    return;

  pixel[ch][0] = b;
  pixel[ch][1] = g;
  pixel[ch][2] = r;
}

void Ws2822s::sendByte(volatile uint8_t value, volatile uint8_t *out_port, volatile uint8_t out_bit)
{
  uint8_t bitCount, delCount;

  __asm__ volatile (
    "cli\n"
    "ld __tmp_reg__,%a[out_port]\n"
    "and __tmp_reg__,%[outMask]\n"
    "st %a[out_port],__tmp_reg__\n"
    "ldi %[bitCount],11\n"
    "rjmp bitLoop%=\n"
    "bitLoop%=:\n"
    "ldi %[delCount],%[delCountVal]\n"
    "delLoop%=:\n"
    "nop\n"
    "dec %[delCount]\n"
    "brne delLoop%=\n"
    "ld __tmp_reg__,%a[out_port]\n"
    "and __tmp_reg__,%[outMask]\n"
    "sec\n"
    "ror %[value]\n"
    "brcc sendzero%=\n"
    "or __tmp_reg__,%[outBit]\n"
    "sendzero%=:\n"
    "st %a[out_port],__tmp_reg__\n"
    "dec %[bitCount]\n"
    "brne bitLoop%=\n"
    "sei\n"
    :
      [bitCount] "=&d" (bitCount),
      [delCount] "=&d" (delCount)
    :
      [out_port] "e" (out_port),
      [outMask] "r" (~out_bit),
      [outBit] "r" (out_bit),
      [delCountVal] "M" (F_CPU/1000000-3),
      [value] "r" (value)
  );
}

void Ws2822s::setAddress(int start_pixel, int end_pixel)
{
  if (start_pixel < 0 || end_pixel >= 1024)
    return;
  if (start_pixel > end_pixel)
    return;

  *out_adri |= bit_address;
  delayMicroseconds(10);
  *out_adri &= ~bit_address;
  delayMicroseconds(5000);
  uint8_t oldSREG = SREG;
  cli();
  *out_adri |= bit_address;
  delayMicroseconds(12);
  sendByte(0, out_adri, bit_address);
  *out_adri |= bit_address;

  for (int i = start_pixel; i <= end_pixel; ++i) {
    channel = i * 3 + 1;
    channel_rv = channel;
    channel_rv = ((channel_rv & 0x55) << 1) | ((channel_rv & 0xAA) >>1);
    channel_rv = ((channel_rv & 0x33) << 2) | ((channel_rv & 0xCC) >>2);
    channel_rv = ((channel_rv << 4) | (channel_rv >> 4));

    sendByte((channel_rv & 0x00FF), out_adri, bit_address);
    if (channel >= 0 && channel < 256)
      temp = 0x0F;
    else if (channel >= 256 && channel < 512)
      temp = 0x87;
    else if (channel >= 512 && channel < 768)
      temp = 0x4B;
    else if (channel >= 768 && channel < 1024)
      temp = 0xC3;
    else if (channel >= 1024 && channel < 1280)
      temp = 0x2D;
    else if (channel >= 1280 && channel < 1536)
      temp = 0xA5;
    else if (channel >= 1536 && channel < 1792)
      temp = 0x69;
    else if (channel >= 1792 && channel < 2048)
      temp = 0xE1;
    else if (channel >= 2048 && channel < 2304)
      temp = 0x1E;
    else if (channel >= 2304 && channel < 2560)
      temp = 0x96;
    else if (channel >= 2560 && channel < 2816)
      temp = 0x5A;
    else if (channel >= 2816 && channel < 3072)
      temp = 0xD2;
    sendByte(temp, out_adri, bit_address);
    temp = 0x4B;
    sendByte(temp, out_adri, bit_address);
  }
  SREG = oldSREG;
  sei();
}

void Ws2822s::send()
{
  *out_dai |= bit; // MTBP
  delayMicroseconds(100);
  *out_dai &= ~bit; // BREAK
  delayMicroseconds(100);
  uint8_t oldSREG = SREG;
  cli();
  *out_dai |= bit; // MAB
  delayMicroseconds(8);
  sendByte(0, out_dai, bit); // SC

  for (int i = 0; i < max_pixel; ++i) {
    for(int j = 0; j < 3; ++j)
      sendByte(pixel[i][j], out_dai, bit);
    delayMicroseconds(8);
  }

  SREG = oldSREG;
  sei();
}
