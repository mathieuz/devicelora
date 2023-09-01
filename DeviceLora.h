#ifndef DeviceLora_h
#define DeviceLora_h

class DeviceLora
{

protected:
    int joinMode;
    char classMode;
    String deviceEui;
    int bandRegion = RAK_REGION_AU915;

    enum ActivationKey{DEVICE_ADDRESS, APPSKEY, NWKSKEY, DEVICE_EUI};

    void SetActivationKey(ActivationKey activationKey, String key, uint length) {
        length = length / 2;

        uint8_t arrayKey[length];
        int indexArray = 0;

        key.toLowerCase();

        for (int i = 0; i < length * 2; i += 2) {
            uint8_t hex1 = 0x00;
            uint8_t hex2 = 0x00;
            
            if (key[i] >= 'a' && key[i] <= 'f') {
                hex1 = key[i] - 87;

            } else if (key[i] >= '0' && key[i] <= '9') {
                hex1 = key[i] - 48;
            }

            if (key[i + 1] >= 'a' && key[i + 1] <= 'f') {
                hex2 = key[i + 1] - 87;

            } else if (key[i + 1] >= '0' && key[i + 1] <= '9') {
                hex2 = key[i + 1] - 48;
            }

            arrayKey[indexArray] = (hex1 << 4) + hex2;
            indexArray++;
        }

        switch (activationKey) {

            case DEVICE_ADDRESS:
                api.lorawan.daddr.set(arrayKey, length);
            break;

            case APPSKEY:
                api.lorawan.appskey.set(arrayKey, length);
            break;

            case NWKSKEY:
                api.lorawan.nwkskey.set(arrayKey, length);
            break;

            case DEVICE_EUI:
                api.lorawan.deui.set(arrayKey, length);
            break;

        }
    }

    String GetActivationKey(ActivationKey activationKey, int length) {
        uint8_t arrayKey[length];

        switch (activationKey) {
            case DEVICE_ADDRESS:
                api.lorawan.daddr.get(arrayKey, length);
            break;

            case APPSKEY:
                api.lorawan.appskey.get(arrayKey, length);
            break;

            case NWKSKEY:
                api.lorawan.nwkskey.get(arrayKey, length);
            break;

            case DEVICE_EUI:
                api.lorawan.deui.get(arrayKey, length);
            break;
        }

        int dec = 0;
        int res = 0;
        String hex = "";
        String finalhex = "";

        for (int i = 0; i < length; i++) {
            int dec = arrayKey[i];

            while (dec != 0) {
                res = dec % 16;
                dec = dec / 16;

                if (res >= 0 && res <= 9) {
                    res = res + 48;

                } else if (res >= 10 && res <= 15) {
                    res = res + 55;

                }

                hex += (char) res;
                
            }

            for (int i = hex.length() - 1; i != -1; i--) {
                finalhex += hex[i];
            }

            hex = "";
        }

        return finalhex;
    }

public:
    void JoinMode(int mode) {
        api.lorawan.njm.set(mode);
    }

    String GetJoinMode() {
        return api.lorawan.njm.get() ? "OTAA" : "ABP";
    }

    int GetNetworkJoinStatus() {
        return api.lorawan.njs.get();
    }

    void SendData(int port, String data) {

        uint8_t payload[data.length()];

        for (int i = 0; i < data.length(); i++) {
            payload[i] = data[i];
        }

        if (api.lorawan.send(sizeof(payload), payload, port)) {
            Serial.println(data + " enviado na porta " + port + ".");
        } else {
            Serial.println("Erro ao enviar.");
        }
    }

    void SendData(int port, String data, int numRetries) {
        uint8_t payload[data.length()];

        for (int i = 0; i < data.length(); i++) {
            payload[i] = data[i];
        }

        if (api.lorawan.send(sizeof(payload), payload, port, true, numRetries)) {
            Serial.println(data + " enviado na porta " + port + ".");
        } else {
            Serial.println("Erro ao enviar.");
        }
    }

    void SendLongPacketData(int port, bool ack, String data) {

    }

    String GetLastReceivedTextData() {

    }

    int GetRSSIOnReception() {

    }

    String GetAllChannelRSSI() {

    }

    int GetSignalNoiseRatio() {

    }

    bool GetConfirmMode() {

    }

    void SetConfirmMode(bool mode) {
        api.lorawan.cfm.set(mode);
    }

    int GetNumberOfRetransmissions() {

    }

    void SetNumberOfRetransmissions(int val) {
        api.lorawan.rety.set(val);
    }

    int GetActiveRegion() {

    }

    void SetActiveRegion(int bandRegion) {
        api.lorawan.band.set(bandRegion);
    }

    String GetNetworkId() {

    }

    void SetNetworkId(String networkId) {

    }

    String GetMCRootKey() {

    }

    //

    String GetDeviceEUI() {
        this->GetActivationKey(DEVICE_EUI, 8);
    }

    void SetDeviceEUI(String deviceEui) {
        this->SetActivationKey(DEVICE_EUI, deviceEui, deviceEui.length());
    }

    int GetAdaptiveRate() {

    }

    void SetAdaptiveRate(int adaptativeRate) {

    }

    char GetClass() {

    }

    void SetClass(char classMode) {

    }

    int GetDataRate() {

    }

    void SetDataRate(int dataRate) {

    }

    int GetTransmitPower() {

    }

    void SetTransmitPower(int transmitPower) {

    }

    bool GetDutyCycleSettings() {

    }

    void SetDutyCycleSettings(bool dutyCycle) {

    }

    int GetRX1JoinDelay() {

    }

    void SetRX1JoinDelay(int joinDelay) {

    }

    int GetRX2JoinDelay() {

    }

    void SetRX2JoinDelay(int joinDelay) {

    }

    bool GetPublicNetworkMode() {

    }

    void SetPublicNetworkMode(bool mode) {

    }

    int GetDelayWindow1() {

    }

    void SetDelayWindow1(int delayWindow) {
        
    }

    int GetDelayWindow2() {

    }

    void SetDelayWindow2(int delayWindow) {
        
    }

    int GetDataRateWindow2() {

    }

    void SetDataRateWindow2(int dataRate) {

    }

    long GetFrequencyWindow2() {

    }

    int GetNetworkLinkStatus() {

    }

    void SetNetworkLinkStatus(int val) {
        
    }

    //

    int GetPingSlot() {

    }

    void SetPingSlot(int pingSlot) {

    }

    String GetBeaconFrequency() {

    }

    String GetBeaconTime() {

    }

    String GetGWGPSCoordinate() {

    }

    String GetLocalTime() {

    }

};

#endif