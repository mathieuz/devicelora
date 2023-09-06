#ifndef DeviceLora_h
#define DeviceLora_h

class DeviceLora
{

protected:
    int joinMode;
    String appskey;
    String nwkskey;
    String deviceAddress;
    String deviceEui;
    char classMode;
    int bandRegion = RAK_REGION_AU915;

    enum ActivationKey{DEVICE_ADDRESS, APPSKEY, NWKSKEY, DEVICE_EUI, APPKEY, APPEUI};

    /// @brief Preenche e define um vetor de chave de ativação.
    /// @param activationKey Tipo de chave de ativação.
    /// @param key Chave de ativação.
    /// @param length Comprimento da chave de ativação.
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

            case APPKEY:
                api.lorawan.appkey.set(arrayKey, length);
            break;

            case APPEUI:
                api.lorawan.appeui.set(arrayKey, length);
            break;

        }
    }

    /// @brief Retorna a String de uma chave de ativação.
    /// @param activationKey Tipo de chave de ativação.
    /// @param length Comprimento do buffer/vetor do tipo de chave de ativação.
    /// @return String
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

            case APPKEY:
                api.lorawan.appkey.get(arrayKey, length);
            break;

            case APPEUI:
                api.lorawan.appeui.get(arrayKey, length);
            break;
        }

        char hex1;
        char hex2;
        String finalhex;

        for (int i = 0; i < length; i++) {
            hex1 = (arrayKey[i] & 0xF0) >> 4;
            hex2 = arrayKey[i] & 0x0F;

            if (hex1 >= 0 && hex1 <= 9) {
                hex1 += 48;

            } else if (hex1 >= 10 && hex1 <= 15) {
                hex1 += 55;

            }

            if (hex2 >= 0 && hex2 <= 9) {
                hex2 += 48;

            } else if (hex2 >= 10 && hex2 <= 15) {
                hex2 += 55;

            }

            finalhex += (char) hex1;
            finalhex += (char) hex2;
        }

        return finalhex;
    }

public:
    /// @brief Define o modo de conexão.
    /// @param mode Modo de conexão (0 = ABP, 1 = OTAA)
    void JoinMode(int mode) {
        api.lorawan.njm.set(mode);
    }

    /// @brief Join Mode - retorna o modo de conexão definido ("OTAA" ou "ABP").
    /// @return String ("OTAA" ou "ABP")
    String GetJoinMode() {
        return api.lorawan.njm.get() ? "OTAA" : "ABP";
    }

    /// @brief Join Status - retorna o status de conexão atual do dispositivo.
    /// @return bool (0 = Not Joined, 1 = Joined)
    bool GetNetworkJoinStatus() {
        return api.lorawan.njs.get();
    }

    /// @brief Envia informação para uma porta especificada.
    /// @param port Número da porta (de 1 à 233).
    /// @param data Informação à ser enviada.
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

    /// @brief Envia informação para uma porta especificada.
    /// @param port Número da porta (de 1 à 233).
    /// @param data Informação à ser enviada.
    /// @param retries Número de tentativas de envio.
    void SendData(int port, String data, int retries) {
        uint8_t payload[data.length()];

        for (int i = 0; i < data.length(); i++) {
            payload[i] = data[i];
        }

        if (api.lorawan.send(sizeof(payload), payload, port, true, retries)) {
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

    /// @brief Retorna Appskey definido.
    /// @return String
    String GetAppskey() {
        return this->GetActivationKey(APPSKEY, 16);
    }

    /// @brief Retorna Nwkskey definido.
    /// @return String
    String GetNwkskey() {
        return this->GetActivationKey(NWKSKEY, 16);
    }

    /// @brief Retorna Nwkskey definido.
    /// @return String
    String GetDeviceAddress() {
        return this->GetActivationKey(DEVICE_ADDRESS, 4);
    }

    /// @brief Retorna DeviceEUI definido.
    /// @return String
    String GetDeviceEUI() {
        return this->GetActivationKey(DEVICE_EUI, 8);
    }

    /// @brief Define DeviceEUI.
    /// @param deviceEui 
    void SetDeviceEUI(String deviceEui) {
        this->SetActivationKey(DEVICE_EUI, deviceEui, deviceEui.length());
    }

    int GetAdaptiveRate() {

    }

    void SetAdaptiveRate(int adaptativeRate) {

    }

    char GetClass() {
        char deviceClass;

        switch (api.lorawan.deviceClass.get()) {
            case 0: deviceClass = 'A'; break;
            case 1: deviceClass = 'B'; break;
            case 2: deviceClass = 'C'; break;
        }

        return deviceClass;
    }

    void SetClass(char classMode) {
        int deviceClass;

        switch (classMode) {
            case 'A':
            case 'a': 
                deviceClass = 0; 
            break;

            case 'B':
            case 'b':
                deviceClass = 1; 
            break;

            case 'C':
            case 'c':
                deviceClass = 2;
            break;
        }

        api.lorawan.deviceClass.set(deviceClass);
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