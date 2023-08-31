#ifndef DeviceLoraABP_h
#define DeviceLoraABP_h

#include "DeviceLora.h"

class DeviceLoraABP : public DeviceLora
{

private:
    /*uint8_t appskey;
    uint16_t nwkskey;
    uint8_t deviceAddress;*/

    String appskey;
    String nwkskey;
    String deviceAddress;

public:

    DeviceLoraABP(String deviceAddress, String appskey, String nwkskey, String deviceEui) {
        this->JoinMode(RAK_LORA_ABP);

        this->deviceAddress = deviceAddress;
        this->appskey = appskey;
        this->nwkskey = nwkskey;
        this->deviceEui = deviceEui;
        this->bandRegion = this->bandRegion;

        this->SetDeviceAddress(this->deviceAddress);
        this->SetAppskey(this->appskey);
        this->SetNwkskey(this->nwkskey);
        this->SetDeviceEUI(this->deviceEui);
        this->SetActiveRegion(this->bandRegion);

        this->SetConfirmMode(true);
        this->SetNumberOfRetransmissions(7);
    }

    String GetAppskey() {
        String resultado;

        uint8_t arrayAppskey[16];

        api.lorawan.appskey.get(arrayAppskey, 16);

        for (int i = 0; i < 32; i++) {
            resultado += arrayAppskey[i];
        }

        return resultado;
    }

    void SetAppskey(String appskey) {
        this->SetActivationKey(APPSKEY, appskey, appskey.length());
    }

    String GetNwkskey() {

    }

    void SetNwkskey(String nwkskey) {
        this->SetActivationKey(NWKSKEY, nwkskey, nwkskey.length());
    }

    String GetDeviceAddress() {

    }

    void SetDeviceAddress(String deviceAddress) {
        this->SetActivationKey(DEVICE_ADDRESS, deviceAddress, deviceAddress.length());
    }
};


#endif