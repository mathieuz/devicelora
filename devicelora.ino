#include "DeviceLoraABP.h"

//Callbacks
void SendCallback(int32_t status) {
  Serial.printf("Status do Send: %d\r\n", status);
}

void JoinCallback(int32_t status) {
  Serial.printf("Status do Join: %d\r\n", status);
}

void setup()
{
  Serial.begin(115200);
  api.lorawan.registerSendCallback(SendCallback);
  api.lorawan.registerJoinCallback(JoinCallback);
}

void loop()
{
  delay(5000); //!!!

  DeviceLoraABP abp("020d7a66", "83652f53f69a54fe23fe2ee699c5d491", "83c92b78a26802bca3d8a4ecf3d717f9", "AC1F09FFFE090B61");

  delay(2000);

  Serial.println(abp.GetDeviceEUI());
}