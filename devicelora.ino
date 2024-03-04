#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

//Timer handlers
/*
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
*/

void setup() {
    delay(4000);

    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    abp.SetupFlash();

    //Definindo estado lógico dos IOs na memória flash.
                            //PA15  //PA1  //PA8  //PA9  //PA0  //PB5  //PB4  //PB3  //PA2  //PB12
    uint8_t iosMode[10]  = {0x00,   0x00,  0x00,  0x01,  0x01,  0x01,  0x02,  0x02,  0x02,  0x00};

    //Definindo zonas/timers dos IOs na memória flash.
                            //PA15  //PA1  //PA8  //PA9  //PA0  //PB5  //PB4  //PB3  //PA2  //PB12
    uint8_t iosZones[10] = {0x00,   0x01,  0x02,  0x03,  0x04,  0x03,  0x02,  0x01,  0x00,  0x00};

    //Gravando informações na flash.
    abp.SetupIosModeFlash(iosMode);
    abp.SetupIosZonesFlash(iosZones);

    //Registrando os timer handlers.
    /*
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
    */

}

void loop() {
    abp.GetIosModes();
    delay(2000);
} 