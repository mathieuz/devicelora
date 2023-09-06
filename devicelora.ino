#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

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

  DeviceLoraABP abp("026a42dc", "0813fa6348559dc537034fe9e08f380f", "446ebbf49a04bc2811ba07dc877a2c6e", "AC1F09FFFE090B61", 'A');

  delay(2000);

  Serial.println();

}