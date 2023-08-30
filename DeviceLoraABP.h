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
    /*
    DeviceLoraABP(String deviceAddress, String appskey, String nwkskey, String deveui) {
        api.lorawan.njm.set(RAK_LORA_ABP);
        
        this->appskey = appskey;
        this->nwkskey = nwkskey;
        this->deviceAddress = deviceAddress;
        this->deviceEui = deveui;
        this->bandRegion = this->bandRegion;

        this->SetAppskey(this->appskey);
        this->SetNwkskey(this->nwkskey);
        this->SetDeviceAddress(this->deviceAddress);
        this->SetDeviceEUI(this->deviceEui);
        this->SetActiveRegion(this->bandRegion);

        this->SetConfirmMode(1);
        this->SetNumberOfRetransmissions(7);

    }
    */

    DeviceLoraABP(String appskey) {
        this->appskey = appskey;

        api.lorawan.njm.set(RAK_LORA_ABP);
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

        uint8_t arrayAppskey[16];
        int indiceArray = 0;

        for (int i = 0; i < 32; i += 2) {
            uint8_t digitoHex1 = 0x00;
            uint8_t digitoHex2 = 0x00;
            
            if (appskey[i] >= 'a' && appskey[i] <= 'f') {
                digitoHex1 = appskey[i] - 87;

            } else if (appskey[i] >= '0' && appskey[i] <= '9') {
                digitoHex1 = appskey[i] - 48;
            }

            if (appskey[i + 1] >= 'a' && appskey[i + 1] <= 'f') {
                digitoHex2 = appskey[i + 1] - 87;

            } else if (appskey[i + 1] >= '0' && appskey[i + 1] <= '9') {
                digitoHex2 = appskey[i + 1] - 48;
            }

            arrayAppskey[indiceArray] = (digitoHex1 << 4) + digitoHex2;
            indiceArray++;
        }
        
        if (api.lorawan.appskey.set(arrayAppskey, 16) == true) {
            Serial.println("Appskey enviado!");

        } else {
            Serial.println("Erro!");
        }
       
    }

    String GetNwkskey() {

    }

    void SetNwkskey(String nwkskey) {

    }

    String GetDeviceAddress() {

    }

    void SetDeviceAddress(String deviceAddress) {

    }
};


#endif