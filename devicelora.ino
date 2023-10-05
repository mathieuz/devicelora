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

  delay(5000);

  DeviceLoraABP abp("0271a1ca", "fea60afdd4cfec1ae34dc92c135ea228", "8b989d48cca9f7a1a929330b9ae2ca35", "AC1F09FFFE090B61", 'C');
  abp.AddMulticastGroup('C', "aabbccdd", "31bb0739b191b43663e141664ce706e2", "5f2fb2119333ce6c3b0482f85c9d1f46", 923300000, 8, 0, 4, 0);
  
  delay(2000);
  
  abp.RemoveMulticastGroup("aabbccdd");

}

void loop()
{
  
}