#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);


void setup() {
    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    //Aguarda os bytes das configurações dos IOs por 5 segundos.
    abp.SetupFlash();

}

void loop() {
    abp.GetIosModes();
    delay(4000);
    abp.GetIosZones();
    delay(4000);
    abp.GetTimersZones();
    delay(4000);
} 