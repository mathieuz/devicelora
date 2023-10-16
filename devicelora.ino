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

DeviceLoraOTAA otaa("354966473fc1bcf2bcc4c6ab997ba5d2", "ac1f09fffe090b61", 'C');

void setup()
{
  Serial.begin(115200);

  api.lorawan.registerRecvCallback(RecvCallback);
  api.lorawan.registerSendCallback(SendCallback);
  api.lorawan.registerJoinCallback(JoinCallback);

  delay(5000);

  otaa.Setup();
}

void loop()
{
  delay(4000);
  Serial.println("Teste Lib");
  Serial.println(otaa.GetAppskey());

  delay(4000);

  otaa.SendData(8, "TesteOTAA!", 7);
}