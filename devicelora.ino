#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

//Timer handlers
void timer0 (void* data) {
    abp.GetIoConfig(0);
}

void timer1 (void* data) {
    abp.GetIoConfig(1);
}

void timer2 (void* data) {
    abp.GetIoConfig(2);
}

void timer3 (void* data) {
    abp.GetIoConfig(3);
}

void timer4 (void* data) {
    abp.GetIoConfig(4);
}

void setup() {
    delay(4000);

    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    //Definindo estado lógico dos IOs na memória flash.
                              //PA15  //PA1  //PA8  //PA9  //PA0  //PB5  //PB4  //PB3  //PA2  //PB12
    uint32_t iosMode[10]   = {0,      1,     2,     1,     0,     1,     2,     1,     0,     1};

    //Definindo zonas/timers dos IOs na memória flash.
                              //PA15  //PA1  //PA8  //PA9  //PA0  //PB5  //PB4  //PB3  //PA2  //PB12
    uint32_t timersIos[10] = {0,      0,     1,     2,     3,     4,     1,     1,     0,     2};

    //Gravando informações na flash.
    abp.SetupIoModeFlash(iosMode);
    abp.SetupTimersFlash(timersIos);

    //Registrando os timer handlers.
    api.system.timer.create(RAK_TIMER_0, (RAK_TIMER_HANDLER)timer0, RAK_TIMER_ONESHOT);
    api.system.timer.start(RAK_TIMER_0, 2000, NULL);

    api.system.timer.create(RAK_TIMER_1, (RAK_TIMER_HANDLER)timer1, RAK_TIMER_ONESHOT);
    api.system.timer.start(RAK_TIMER_1, 4000, NULL);

    api.system.timer.create(RAK_TIMER_2, (RAK_TIMER_HANDLER)timer2, RAK_TIMER_ONESHOT);
    api.system.timer.start(RAK_TIMER_2, 6000, NULL);

    api.system.timer.create(RAK_TIMER_3, (RAK_TIMER_HANDLER)timer3, RAK_TIMER_ONESHOT);
    api.system.timer.start(RAK_TIMER_3, 8000, NULL);

    api.system.timer.create(RAK_TIMER_4, (RAK_TIMER_HANDLER)timer4, RAK_TIMER_ONESHOT);
    api.system.timer.start(RAK_TIMER_4, 10000, NULL);

}

void loop() {
    /*
    uint offset = 10060;
    Serial.printf("Valor lido do endereço %d da memória flash:\n", offset);

    uint8_t arrBufferData[4] = {0};
    uint32_t data = 0;

    if (api.system.flash.get(offset, arrBufferData, 4)) {
        data |= arrBufferData[0] << 0;
        data |= arrBufferData[1] << 8;
        data |= arrBufferData[2] << 16;
        data |= arrBufferData[3] << 24;

        Serial.println(data);

        delay(3000);

    } else {
        Serial.println("Erro ao ler informação da flash.");

    }
    */

}