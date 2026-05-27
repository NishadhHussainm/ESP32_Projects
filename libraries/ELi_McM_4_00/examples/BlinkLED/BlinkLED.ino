#include <ELi_McM_4_00.h>

void setup() {
  // put your setup code here, to run once:
 pinMode(McM_4_00_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(McM_4_00_LED, HIGH);
  delay(100);
  digitalWrite(McM_4_00_LED, LOW);
  delay(100);
}
