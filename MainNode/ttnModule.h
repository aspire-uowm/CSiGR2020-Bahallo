#include <TheThingsNetwork.h>

#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868

static TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void ttnDeviceInit();
void ttnDevice_get();
