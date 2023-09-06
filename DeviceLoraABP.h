#ifndef DeviceLoraABP_h
#define DeviceLoraABP_h

#include "DeviceLora.h"

class DeviceLoraABP : public DeviceLora
{

private:
    String appskey;
    String nwkskey;
    String deviceAddress;

public:

    DeviceLoraABP(String deviceAddress, String appskey, String nwkskey, String deviceEui, char classMode) {
        this->JoinMode(RAK_LORA_ABP);

        this->deviceAddress = deviceAddress;
        this->appskey = appskey;
        this->nwkskey = nwkskey;
        this->deviceEui = deviceEui;
        this->classMode = classMode;
        this->bandRegion = this->bandRegion;

        this->SetDeviceAddress(this->deviceAddress);
        this->SetAppskey(this->appskey);
        this->SetNwkskey(this->nwkskey);
        this->SetDeviceEUI(this->deviceEui);
        this->SetClass(this->classMode);
        this->SetActiveRegion(this->bandRegion);
    }

    String GetAppskey() {
        return this->GetActivationKey(APPSKEY, 16);
    }

    void SetAppskey(String appskey) {
        this->SetActivationKey(APPSKEY, appskey, appskey.length());
    }

    String GetNwkskey() {
        return this->GetActivationKey(NWKSKEY, 16);
    }

    void SetNwkskey(String nwkskey) {
        this->SetActivationKey(NWKSKEY, nwkskey, nwkskey.length());
    }

    String GetDeviceAddress() {
        return this->GetActivationKey(DEVICE_ADDRESS, 4);
    }

    void SetDeviceAddress(String deviceAddress) {
        this->SetActivationKey(DEVICE_ADDRESS, deviceAddress, deviceAddress.length());
    }
};


#endif