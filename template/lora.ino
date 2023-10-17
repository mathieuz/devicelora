#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

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

void setup()
{
  Serial.begin(115200);

  api.lorawan.registerRecvCallback(RecvCallback);
  api.lorawan.registerSendCallback(SendCallback);
  api.lorawan.registerJoinCallback(JoinCallback);
}

void loop()
{

}