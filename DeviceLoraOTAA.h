#ifndef DeviceLoraOTAA_h
#define DeviceLoraOTAA_h

#include "DeviceLora.h"

class DeviceLoraOTAA : public DeviceLora
{

private:
    uint16_t appkey;
    uint8_t applicationIdentifier;

public:

/*
    DeviceLoraOTAA(uint16_t appkey, uint8_t applicationIdentifier, char classMode, int adaptiveRate, int transmitPower){
        this->appkey = appkey;
        this->applicationIdentifier = applicationIdentifier;
        this->joinMode = 1;
        this->classMode = classMode;
        this->adaptiveRate = adaptiveRate;
        this->dataRate = dataRate;
        this->transmitPower = transmitPower;
    }
*/

    DeviceLoraOTAA() {

    }

    void Join() {
        
    }

    String GetAppkey() {
        return "Teste GetAppkey";
    }

    void SetAppkey(String appkey) {

    }

    String GetApplicationIdentifier() {

    }

    void SetApplicationIdentifier(String appeui) {

    }
};

#endif