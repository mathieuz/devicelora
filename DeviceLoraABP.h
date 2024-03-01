#ifndef DeviceLoraABP_h
#define DeviceLoraABP_h

#include "DeviceLora.h"

class DeviceLoraABP : public DeviceLora
{

private:
    //Callbacks
    /*
    static void RecvCallback(SERVICE_LORA_RECEIVE_T *data) {
        Serial.println("[RECV] Recebido:");

    for (int i = 0; i < data->BufferSize; i++) {
        Serial.printf("%x", data->Buffer[i]);
    }
        Serial.print("\r\n");
    }
    */

    /*
    static void RecvCallback(SERVICE_LORA_RECEIVE_T *data) {
        String recvData = "";

        for (int i = 0; i < data->BufferSize; i++) {
            recvData += (char)data->Buffer[i];

        }

        //Serial.println(recvData);
    }

    static void SendCallback(int32_t status) {
        Serial.printf("Status do Send: %d\r\n", status);
    }

    static void JoinCallback(int32_t status) {
        Serial.printf("Status do Join: %d\r\n", status);
    }
    */


public:

    DeviceLoraABP(String deviceAddress, String appskey, String nwkskey, String deviceEui, char classMode, uint16_t channelMask) {
        this->deviceAddress = deviceAddress;
        this->appskey = appskey;
        this->nwkskey = nwkskey;
        this->deviceEui = deviceEui;
        this->classMode = classMode;
        this->bandRegion = this->bandRegion;
        this->channelMask = channelMask;

    }

    /// @brief Inicializa instância de conexão.
    void Setup() {

        //Enviando chaves + configurações do device
        this->JoinMode(RAK_LORA_ABP);

        this->SetDeviceAddress(this->deviceAddress);
        this->SetAppskey(this->appskey);
        this->SetNwkskey(this->nwkskey);
        this->SetDeviceEUI(this->deviceEui);
        this->SetClass(this->classMode);
        this->SetActiveRegion(this->bandRegion);
        this->SetChannelMask(this->channelMask);

        //Registrando callbacks
        /*
        api.lorawan.registerRecvCallback(RecvCallback);
        api.lorawan.registerSendCallback(SendCallback);
        api.lorawan.registerJoinCallback(JoinCallback);
        */
    }

    /// @brief Inicializa timers/zonas na memória flash.
    void SetupZoneFlash(uint32_t timersIos[10]) {

        //Registrando IOs e timers na memória flash do dispositivo.
        uint8_t arrData32bit[4];

        //Definindo todas as zonas/timers na memória flash
        for (uint32_t i = 0; i < 10; i++) {
            uint32_t data = timersIos[i]; //Recebe os valores de timer.

            arrData32bit[0] = (uint8_t)(data >> 0);
            arrData32bit[1] = (uint8_t)(data >> 8);
            arrData32bit[2] = (uint8_t)(data >> 16);
            arrData32bit[3] = (uint8_t)(data >> 24);

            api.system.flash.set(this->timersIosOffsets[i], arrData32bit, 4); //Armazena no offset definido para o valor de timer.
        }
    }

    /// @brief Define Appskey.
    /// @param appskey 
    void SetAppskey(String appskey) {
        this->SetActivationKey(APPSKEY, appskey, appskey.length());
    }

    /// @brief Define Nwkskey.
    /// @param nwkskey
    void SetNwkskey(String nwkskey) {
        this->SetActivationKey(NWKSKEY, nwkskey, nwkskey.length());
    }

    /// @brief Define Device Address.
    /// @param deviceAddress 
    void SetDeviceAddress(String deviceAddress) {
        this->SetActivationKey(DEVICE_ADDRESS, deviceAddress, deviceAddress.length());
    }
};


#endif