#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//DeviceLoraABP abp("023627b5", "3004bc20bb1d1b0b61affd70163af673", "564d90f6e3757c5dc211a27fae00b287", "AC1F09FFFE090B61", 'C');
DeviceLoraOTAA otaa("354966473fc1bcf2bcc4c6ab997ba5d2", "AC1F09FFFE090B61", 'C');

void setup()
{
  Serial.begin(115200);
  otaa.Setup();
}

void loop()
{
  delay(5000);
  otaa.SendData(8, "TesteCallback321", 7);
}