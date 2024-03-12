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

        //Lê os valores de timer da flash e atribui nas propriedades de timer da classe.
        this->SetTimersProperty();

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