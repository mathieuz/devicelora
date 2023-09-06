#ifndef DeviceLoraOTAA_h
#define DeviceLoraOTAA_h

#include "DeviceLora.h"

class DeviceLoraOTAA : public DeviceLora
{

private:
    String appkey;

public:

    DeviceLoraOTAA(String appkey, String deviceEui, char classMode) {
        this->JoinMode(RAK_LORA_OTAA);

        this->appkey = appkey;
        this->deviceEui = deviceEui;
        this->classMode = classMode;
        this->bandRegion = this->bandRegion;

        this->SetAppkey(this->appkey);
        this->SetDeviceEUI(this->deviceEui);
        this->SetClass(this->classMode);
        this->SetActiveRegion(this->bandRegion);

        if (this->GetNetworkJoinStatus() == 0) {
            this->Join();
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