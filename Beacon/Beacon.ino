#include "Udp.h"

void setup() {
  Serial.begin(115200);

  UdpInit();
}

void loop() {
  delay(1000);
  UdpRun();
}
