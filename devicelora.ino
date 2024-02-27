#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C');

void setup() {
    delay(2000);
    Serial.begin(115200);
    abp.Setup();
}

void loop() {
    Serial.println(abp.GetClass());
}