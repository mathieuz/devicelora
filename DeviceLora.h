#ifndef DeviceLora_h
#define DeviceLora_h

class DeviceLora
{

protected:

    //String com as IOs. Essa é ordem de configuração dos modos e zonas dos IOs na memória flash do device.
    String iosString[10] = {"PA15", "PA1", "PA8", "PA9", "PA0", "PB5", "PB4", "PB3", "PA2", "PB12"};

    //Propriedade com o valor dos timers.
    uint16_t timer0;
    uint16_t timer1;
    uint16_t timer2;
    uint16_t timer3;
    uint16_t timer4;

    //Chaves de conexão e definições gerais do dispositivo
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

    /// @brief Inicializa modos, zonas e timers dos IOs na memória flash. Offsets do 10000 ao 10030 (seguindo a ordem dos IOs).
    /// @param iosConfig 
    void SetupIosConfig(uint8_t iosConfig[30]) {
        api.system.flash.set(10000, iosConfig, 30);
    }

    /// @brief Inicializa as propriedades de zona com os valores dos timers.
    void SetTimersProperty() {
        
        //Array que vai receber os valores de timer.
        uint16_t timers[5];

        //Buffer que vai ser preenchido com os bytes dos valores de timer.
        uint8_t bufferTimers[10];

        if (api.system.flash.get(10020, bufferTimers, 10)) {

            //Preenchendo o array com os valores de timer + atribuindo os valores nas propriedades.
            uint indexCount = 0;
            for (uint i = 0; i < 10; i += 2) {
                uint8_t byteHigh = bufferTimers[i];
                uint8_t byteLow = bufferTimers[i + 1];

                timers[indexCount] = (uint16_t)((byteHigh << 8) + byteLow);
                indexCount++;
            }

            this->timer0 = timers[0];
            this->timer1 = timers[1];
            this->timer2 = timers[2];
            this->timer3 = timers[3];
            this->timer4 = timers[4];
        }
    }

    uint16_t CalcCRC(uint8_t buffer[], uint8_t length) {
        uint16_t crc = 0xFFFF;

        for (uint pos = 0; pos < length; pos++) {

            crc ^= (uint16_t)buffer[pos];
            
            for (uint16_t i = 8; i != 0; i--) {

                if ((crc & 0x0001) != 0) {
                    crc >>= 1;
                    crc ^= 0xA001;

                } else {
                    crc >>= 1;

                }
            }
        }

        return crc;

    }

    uint8_t GetCRCHigh(uint8_t buffer[], uint8_t length)
    {
        uint16_t crc = this->CalcCRC(buffer, length);
        return (uint8_t)(crc >> 8);
    }

    uint8_t GetCRCLow(uint8_t buffer[], uint8_t length)
    {
        uint16_t crc = this->CalcCRC(buffer, length);
        return (uint8_t)(crc & 0x00FF);
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

    /// @brief Aguarda os bytes de configuração dos IOs para registrar na memória flash.
    void SetupFlash() {
        uint tempoResposta = millis();

        while ((millis() - tempoResposta) < 5000) {
            if (Serial.available() > 0) {

                //São 10 IOs no total. Cada IO, em ordem, recebe uma configuração de modo, zona e valor de timer. 30 bytes
                //devem ser recebidos + 2 bytes referentes ao CRC. Total de 32 bytes.
                uint8_t bufferIosConfig[32];
                Serial.readBytes(bufferIosConfig, 32);

                //Recebe apenas as configurações dos IOs.
                uint8_t iosConfig[30];
                for (uint i = 0; i < 30; i++) {
                    iosConfig[i] = bufferIosConfig[i];
                }

                //Recuperando o CRC recebido do buffer.
                uint8_t crcResHigh = bufferIosConfig[30];
                uint8_t crcResLow = bufferIosConfig[31];
                uint16_t crcRecebido = (uint16_t)((crcResHigh << 8) + crcResLow);

                //Recalculando o CRC.
                uint16_t crcCalculado = this->CalcCRC(iosConfig, 30);

                //Comparando se o CRC recalculado e o CRC recebido do buffer são iguais.
                if (crcCalculado == crcRecebido) {

                    //Atualizando as propriedades de timers do objeto com os novos valores da flash.
                    this->SetTimersProperty();

                    //Gravando modos, zonas dos IOs e tempo dos timers na flash.
                    this->SetupIosConfig(iosConfig);

                    break;

                } else {
                    Serial.println("O CRC calculado não condiz com o CRC recebido.");

                }
            }
        }
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

    void GetIoConfig(uint32_t zone) {

        String res = "";
        uint8_t bufferData[30] = {0};

        //Separando os valores de configuração em duas arrays diferentes (modos, zonas e timers das zonas).
        uint8_t iosModes[10];
        uint8_t iosZones[10];
        uint16_t timerZones[5];

        //Lendo os 30 endereços da memória (modos e zonas dos IOs e timers das zonas).
        if (api.system.flash.get(10000, bufferData, 30)) {

            uint8_t indexCount = 0;
            for (uint i = 0; i < 10; i++)
            {
                iosModes[indexCount] = bufferData[i];
                indexCount++;
            }

            indexCount = 0;

            for (uint i = 10; i < 20; i++)
            {
                iosZones[indexCount] = bufferData[i];
                indexCount++;
            }

            indexCount = 0;

            for (uint i = 20; i < 30; i += 2)
            {
                uint8_t byteHigh = bufferData[i];
                uint8_t byteLow = bufferData[i + 1];

                timerZones[indexCount] = (uint16_t)((byteHigh << 8) + byteLow);
                indexCount++;
            }

            //Verificando se a zona definida no espaço da memória e o modo é referente ao IO. Se sim, retorna essas informações no handler.
            for (uint i = 0; i < 10; i++) {
                if (iosZones[i] == zone) {
                    res += this->iosString[i];

                    if (iosModes[i] == 0) {
                        res += " (Entrada Digital)";

                    } else if (iosModes[i] == 1) {
                        res += " (Saida Digital)";

                    } else {
                        res += " (Entrada Analogica)";

                    }

                    res += "\n";
                }
            }
        }

        Serial.print("\nIOs associados a zona/timer ID ");
        Serial.print(zone);
        Serial.print(" (tempo do timer definido: ");
        Serial.print(timerZones[zone]);
        Serial.print(")\n");
        Serial.print(res);
    }

    uint16_t GetTimer0() {
        return this->timer0;
    }

    uint16_t GetTimer1() {
        return this->timer1;
    }

    uint16_t GetTimer2() {
        return this->timer2;
    }

    uint16_t GetTimer3() {
        return this->timer3;
    }

    uint16_t GetTimer4() {
        return this->timer4;
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