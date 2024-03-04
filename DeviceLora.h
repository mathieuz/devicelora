#ifndef DeviceLora_h
#define DeviceLora_h

class DeviceLora
{

protected:

    //Matriz com os IOs e os endereços na memória onde serão salvos.
                              //PA15  //PA1  //PA8  //PA9  //PA0  //PB5  //PB4  //PB3  //PA2  //PB12
    uint32_t iosOffsets[10] = {10000, 10010, 10020, 10030, 10040, 10050, 10060, 10070, 10080, 10090};

    //Matriz com os valores de zonas/timers e os endereços na memória onde serão salvos.
                                    //PA15  //PA1  //PA8  //PA9  //PA0  //PB5  //PB4  //PB3  //PA2  //PB12
    uint32_t timersIosOffsets[10] = {10100, 10110, 10120, 10130, 10140, 10150, 10160, 10170, 10180, 10190};

    String iosString[10] = {"PA15", "PA1", "PA8", "PA9", "PA0", "PB5", "PB4", "PB3", "PA2", "PB12"};

    int joinMode;
    String appskey;
    String nwkskey;
    String deviceAddress;
    String deviceEui;
    char classMode;
    int bandRegion = RAK_REGION_AU915;
    uint16_t channelMask;

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
    String GetActivationKey(ActivationKey activationKey, uint length) {
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

    void GetHexMulticastKeys(uint8_t mcKeyAddress[4], uint8_t mcKeyNwkskey[16], uint8_t mcKeyAppskey[16], String mcKeyStrAddress, String mcKeyStrNwkskey, String mcKeyStrAppskey){
        mcKeyStrAddress.toLowerCase();
        mcKeyStrNwkskey.toLowerCase();
        mcKeyStrAppskey.toLowerCase();

        uint8_t hex1 = 0x00;
        uint8_t hex2 = 0x00;

        uint indexArray = 0;

        //Preenchendo mc_arr_address (Multicast Device Address)
        for (int i = 0; i < mcKeyStrAddress.length(); i += 2) {

            if (mcKeyStrAddress[i] >= 'a' && mcKeyStrAddress[i] <= 'f') {
                hex1 = mcKeyStrAddress[i] - 87;

            } else if (mcKeyStrAddress[i] >= '0' && mcKeyStrAddress[i] <= '9') {
                hex1 = mcKeyStrAddress[i] - 48;

            }

            if (mcKeyStrAddress[i + 1] >= 'a' && mcKeyStrAddress[i + 1] <= 'f') {
                hex2 = mcKeyStrAddress[i + 1] - 87;

            } else if (mcKeyStrAddress[i + 1] >= '0' && mcKeyStrAddress[i + 1] <= '9') {
                hex2 = mcKeyStrAddress[i + 1] - 48;

            }

            mcKeyAddress[indexArray] = (hex1 << 4) + hex2;
            indexArray++;

        }

        indexArray = 0;

        //Preenchendo mc_arr_nwkskey (Multicast Nwkskey)
        for (int i = 0; i < mcKeyStrNwkskey.length(); i += 2) {

            if (mcKeyStrNwkskey[i] >= 'a' && mcKeyStrNwkskey[i] <= 'f') {
                hex1 = mcKeyStrNwkskey[i] - 87;

            } else if (mcKeyStrNwkskey[i] >= '0' && mcKeyStrNwkskey[i] <= '9') {
                hex1 = mcKeyStrNwkskey[i] - 48;

            }

            if (mcKeyStrNwkskey[i + 1] >= 'a' && mcKeyStrNwkskey[i + 1] <= 'f') {
                hex2 = mcKeyStrNwkskey[i + 1] - 87;

            } else if (mcKeyStrNwkskey[i + 1] >= '0' && mcKeyStrNwkskey[i + 1] <= '9') {
                hex2 = mcKeyStrNwkskey[i + 1] - 48;

            }

            mcKeyNwkskey[indexArray] = (hex1 << 4) + hex2;
            indexArray++;

        }

        indexArray = 0;

        //Preenchendo mc_arr_appskey (Multicast Appskey)
        for (int i = 0; i < mcKeyStrAppskey.length(); i += 2) {

            if (mcKeyStrAppskey[i] >= 'a' && mcKeyStrAppskey[i] <= 'f') {
                hex1 = mcKeyStrAppskey[i] - 87;

            } else if (mcKeyStrAppskey[i] >= '0' && mcKeyStrAppskey[i] <= '9') {
                hex1 = mcKeyStrAppskey[i] - 48;

            }

            if (mcKeyStrAppskey[i + 1] >= 'a' && mcKeyStrAppskey[i + 1] <= 'f') {
                hex2 = mcKeyStrAppskey[i + 1] - 87;

            } else if (mcKeyStrAppskey[i + 1] >= '0' && mcKeyStrAppskey[i + 1] <= '9') {
                hex2 = mcKeyStrAppskey[i + 1] - 48;

            }

            mcKeyAppskey[indexArray] = (hex1 << 4) + hex2;
            indexArray++;
        }

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

    void AddMulticastGroup(char mcDeviceClass, String mcAddress, String mcNwkskey, String mcAppskey, uint mcFrequency, uint mcDatarate, uint mcPeriodicity, uint mcGroupID, uint mcEntry){
        uint mcClass;

        switch (mcDeviceClass) {
            case 'A':
            case 'a':
                mcClass = 0;
            break;

            case 'B':
            case 'b':
                mcClass = 1;
            break;

            case 'C':
            case 'c':
                mcClass = 2;
            break;
        }

        uint8_t mc_arr_address[4];
        uint8_t mc_arr_nwkskey[16];
        uint8_t mc_arr_appskey[16];

        GetHexMulticastKeys(mc_arr_address, mc_arr_nwkskey, mc_arr_appskey, mcAddress, mcNwkskey, mcAppskey);

        RAK_LORA_McSession session = {
            .McDevclass = mcClass,
            .McAddress = mc_arr_address[0]<<24 | mc_arr_address[1]<<16 | mc_arr_address[2]<<8 | mc_arr_address[3],
            .McFrequency = mcFrequency,
            .McDatarate = mcDatarate,
            .McPeriodicity = mcPeriodicity,
            .McGroupID = mcGroupID,
            .entry = mcEntry,
        };

        memcpy(session.McAppSKey, mc_arr_appskey, 16);
        memcpy(session.McNwkSKey, mc_arr_nwkskey, 16);

        if(api.lorawan.addmulc(session) == true) {
          Serial.println("Grupo de multicast adicionado com sucesso!");

        } else {
          Serial.println("Erro ao adicionar grupo de multicast.");

        }
    }

    void RemoveMulticastGroup(String mcAddress) {
        mcAddress.toLowerCase();

        uint8_t mcKeyAddress[4];

        uint8_t hex1 = 0x00;
        uint8_t hex2 = 0x00;

        uint indexArray = 0;

        //Preenchendo mc_arr_address (Multicast Device Address)
        for (int i = 0; i < mcAddress.length(); i += 2) {

            if (mcAddress[i] >= 'a' && mcAddress[i] <= 'f') {
                hex1 = mcAddress[i] - 87;

            } else if (mcAddress[i] >= '0' && mcAddress[i] <= '9') {
                hex1 = mcAddress[i] - 48;

            }

            if (mcAddress[i + 1] >= 'a' && mcAddress[i + 1] <= 'f') {
                hex2 = mcAddress[i + 1] - 87;

            } else if (mcAddress[i + 1] >= '0' && mcAddress[i + 1] <= '9') {
                hex2 = mcAddress[i + 1] - 48;

            }

            mcKeyAddress[indexArray] = (hex1 << 4) + hex2;
            indexArray++;

        }

        api.lorawan.rmvmulc(mcKeyAddress[0] << 24 | mcKeyAddress[1] << 16 | mcKeyAddress[2] << 8 | mcKeyAddress[3]);
    
        Serial.println("Grupo de multicast removido com sucesso!");
    }

    void ListMulticastGroups() {
        RAK_LORA_McSession multicast_list;

        while (api.lorawan.lstmulc(&multicast_list) == true) {

            if (multicast_list.McDevclass != 0) {
                Serial.printf("Multicast Device Class = %d\r\n", multicast_list.McDevclass);
                Serial.printf("Multicast Device Address = %08X\r\n", multicast_list.McAddress);

                Serial.print("Multicast APPSKEY = ");

                for (int i=0; i<16; i++) {
                    Serial.printf("%02X", multicast_list.McAppSKey[i]);
                }

                Serial.println("");

                Serial.print("Multicast NWKSKEY = ");
                for (int i=0; i<16; i++) {
                    Serial.printf("%02X", multicast_list.McNwkSKey[i]);
                }

                Serial.println("");

                Serial.printf("Frequencia = %d\r\n", multicast_list.McFrequency);
                Serial.printf("Data Rate = %d\r\n", multicast_list.McDatarate);
                Serial.printf("Periodicidade = %d\r\n", multicast_list.McPeriodicity);
                //Serial.printf("Group ID = %d\r\n", multicast_list.McGroupID);
                Serial.printf("Entry = %d\r\n", multicast_list.entry);

                Serial.println("");
            }
        }
    }

    /// @brief Aguarda comando serial para registrar informações na memória flash.
    void SetupFlash() {
        uint tempoResposta = millis();

        while ((millis() - tempoResposta) < 5000) {
            if (Serial.available() > 0) {

                uint8_t buff[3];
                Serial.readBytes(buff, 3);

                Serial.println("Recebido da Serial:");
                for (uint i = 0; i < 3; i++) {
                    Serial.println((char)buff[i]);
                }

                Serial.println();
            }
        }
    }

    /// @brief Inicializa estado lógico das IOs na memória flash. Offsets do 10000 ao 10009 (seguindo a ordem dos IOs).
    void SetupIosModeFlash(uint8_t iosMode[10]) {
        api.system.flash.set(10000, iosMode, 10);
    }

    /// @brief Inicializa timers/zonas na memória flash. Offsets do 1000A ao 10013 (seguindo a ordem dos IOs).
    void SetupIosZonesFlash(uint8_t ioZones[10]) {
        api.system.flash.set(10010, ioZones, 10);
    }

    /// @brief Exibe os estados lógicos dos pinos IOs.
    void GetIosModes() {
        String res = "";
        uint8_t bufferData[10] = {0};

        if (api.system.flash.get(10000, bufferData, 10)) {
            for (uint i = 0; i < 10; i++) {
                res += iosString[i];
                res += ": ";
                res += (String)bufferData[i];
                res += "\n";
            }
        }

        Serial.println("\nEstado lógico dos IOs:");
        Serial.print(res);
    }

    /// @brief Exibe as zonas definidas dos pinos IOs.
    void GetIosZones() {
        String res = "";
        uint8_t bufferData[10] = {0};

        if (api.system.flash.get(10010, bufferData, 10)) {
            for (uint i = 0; i < 10; i++) {
                res += iosString[i];
                res += ": ";
                res += (String)bufferData[i];
                res += "\n";
            }
        }

        Serial.println("\nZonas definidas nos IOs:");
        Serial.print(res);
    }

    void GetIoConfig(uint32_t timerId) {

        String res = "";
        uint8_t bufferData[4] = {0};
        uint32_t data = 0;

        //Recuperando o timer id de cada offset de zona.
        for (uint i = 0; i < 10; i++) {
            if (api.system.flash.get(this->timersIosOffsets[i], bufferData, 4)) {
                data |= bufferData[0] << 0;
                data |= bufferData[1] << 8;
                data |= bufferData[2] << 16;
                data |= bufferData[3] << 24;

                //Se o timerid recuperado da flash for igual ao timerid da função do handler,
                //retorna a string da IO associada ao timerid na mesma posição dentro do array.
                if (data == timerId) {
                    res += this->iosString[i];
                    res += '\n';
                }

                data = 0;
            }
        }

        Serial.printf("\nIOs associados ao Timer ID %d:\n", timerId);
        Serial.print(res);
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
        return api.lorawan.cfm.get();
    }

    void SetConfirmMode(bool mode) {
        api.lorawan.cfm.set(mode);
    }

    int GetNumberOfRetransmissions() {
        return api.lorawan.rety.get();
    }

    void SetNumberOfRetransmissions(int val) {
        api.lorawan.rety.set(val);
    }

    int GetActiveRegion() {
        return api.lorawan.band.get();
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

    /// @brief Retorna o nível de bateria atual do dispositivo.
    /// @return float
    float GetBatteryLevel(){
        return api.system.bat.get();
    }

    /// @brief Habilita o modo sleep do dispositivo e todos seus componentes durante um período de tempo (em milissegundos).
    /// @param time Tempo em milissegundos.
    void SleepAll(int time){
        api.system.sleep.all(time);
    }

    /// @brief Habilita o modo sleep do dispositivo por tempo indeterminado.
    void SleepAll(){
        api.system.sleep.all();
    }

    /// @brief Habilita o modo sleep do CPU do dispositivo durante um período de tempo (em milissegundos).
    /// @param time Tempo em milissegundos.
    void SleepCPU(int time){
        api.system.sleep.cpu(time);
    }

    /// @brief Habilita o modo sleep do CPU do dispositivo por tempo indeterminado.
    void SleepCPU(){
        api.system.sleep.cpu();
    }

    /// @brief Habilita o modo sleep do dispositivo LoRa durante um período de tempo (em milissegundos).
    /// @param time Tempo em milissegundos.
    void SleepLoRa(int time){
        api.system.sleep.lora(time);
    }

    void SetChannelMask(uint16_t mask) {
        api.lorawan.mask.set(&mask);
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

    //

};

#endif