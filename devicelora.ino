#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Callbacks
void RecvCallback(SERVICE_LORA_RECEIVE_T *data) {
  Serial.println("[RECV] Recebido:");

  for (int i = 0; i < data->BufferSize; i++) {
    Serial.printf("%x", data->Buffer[i]);
  }

  Serial.print("\r\n");
}

void SendCallback(int32_t status) {
  Serial.printf("Status do Send: %d\r\n", status);
}

void JoinCallback(int32_t status) {
  Serial.printf("Status do Join: %d\r\n", status);
}

DeviceLoraABP abp("02a57a8d", "827ca0c81799cb9bb4f99f87a754cbf1", "67e6d402c83a85939d937801317d2a22", "AC1F09FFFE090B61", 'C');

void setup()
{
  Serial.begin(115200);

  api.lorawan.registerRecvCallback(RecvCallback);
  api.lorawan.registerSendCallback(SendCallback);
  api.lorawan.registerJoinCallback(JoinCallback);

  delay(5000);

  abp.Setup();

}

void loop()
{
  delay(4000);
  Serial.println("Teste Lib");
  Serial.println(abp.GetAppskey());

  delay(4000);

  abp.SendData(8, "Teste123", 7);
}