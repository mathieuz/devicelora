#ifndef DeviceLoraOTAA_h
#define DeviceLoraOTAA_h

#include "DeviceLora.h"

class DeviceLoraOTAA : public DeviceLora
{

private:
    String appkey;

    //Callbacks
    /*
    static void RecvCallback(SERVICE_LORA_RECEIVE_T *data) {
        String recvData = "";

        for (int i = 0; i < data->BufferSize; i++) {
            recvData += (char)data->Buffer[i];

        }

        Serial.println("recvData:\n");
        Serial.println(recvData);
    }

    static void SendCallback(int32_t status) {
        Serial.printf("Status do Send: %d\r\n", status);
    }

    static void JoinCallback(int32_t status) {
        Serial.printf("Status do Join: %d\r\n", status);
    }
    */

public:

    DeviceLoraOTAA(String appkey, String deviceEui, char classMode, uint16_t channelMask) {
        this->appkey = appkey;
        this->deviceEui = deviceEui;
        this->classMode = classMode;
        this->bandRegion = this->bandRegion;
        this->channelMask = channelMask;
    }

    void Setup() {

        //Lê os valores de timer da flash e atribui nas propriedades de timer da classe.
        this->SetTimersProperty();

        //Enviando chaves + configuração do device.
        this->JoinMode(RAK_LORA_OTAA);
        
        this->SetAppkey(this->appkey);
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

        //Conectando.
        while (this->GetNetworkJoinStatus() == 0) {
            this->Join();
            delay(5000);
        }
    }

    /// @brief Conecta a uma rede LoRaWAN (modo OTAA).
    void Join() {
        api.lorawan.join();
    }

    /// @brief Retorna Appkey definido.
    /// @return String
    String GetAppkey() {
        return this->GetActivationKey(APPKEY, 16);
    }

    /// @brief Define Appkey.
    /// @param appkey 
    void SetAppkey(String appkey) {
        this->SetActivationKey(APPKEY, appkey, appkey.length());
    }

    String GetApplicationIdentifier() {
        return this->GetActivationKey(APPEUI, 8);
    }

    void SetApplicationIdentifier(String appeui) {
        this->SetActivationKey(APPEUI, appeui, appeui.length());
    }
};

#endif