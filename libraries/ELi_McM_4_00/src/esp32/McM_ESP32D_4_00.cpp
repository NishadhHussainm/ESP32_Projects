#include <ELi_McM_4_00.h>
int MCM_ESP32D_4_00_Setmux(uint8_t m)
{
  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
  pinMode(MUX_S3, OUTPUT);
  
  delayMicroseconds(10);

  digitalWrite(MUX_S0,(m&B00000001));
  digitalWrite(MUX_S1,(m&B00000010)>>1);
  digitalWrite(MUX_S2,(m&B00000100)>>2);
  digitalWrite(MUX_S3,(m&B00001000)>>3);
  return(0);
}
