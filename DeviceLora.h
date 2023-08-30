#ifndef DeviceLora_h
#define DeviceLora_h

class DeviceLora
{

protected:
    int joinMode;
    char classMode;
    String deviceEui;
    int adaptiveRate;
    int dataRate;
    int transmitPower;
    int bandRegion = 6;

public:
    void JoinMode(int mode) {

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
        };
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

    }

    int GetNumberOfRetransmissions() {

    }

    void SetNumberOfRetransmissions(int val) {

    }

    int GetActiveRegion() {

    }

    void SetActiveRegion(int bandRegion) {

    }

    String GetNetworkId() {

    }

    void SetNetworkId(String networkId) {

    }

    String GetMCRootKey() {

    }

    //

    String GetDeviceEUI() {

    }

    void SetDeviceEUI(String deviceEui) {

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