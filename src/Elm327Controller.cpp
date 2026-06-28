//
// Created by User on 28/6/2026.
//

#include "Elm327Controller.h"

#include <esp32-hal.h>
static BluetoothSerial SerialBT;
constexpr  char ELM_PIN[]="1234";
constexpr uint8_t TARGET_MAC[6] = {
    0x00,0x1D,0xA5,0x02,0xC3,0x22
}; ///switch to real mac adress
constexpr uint8_t MAX_RETRIES = 3;
constexpr int RESET_TIMEOUT = 2000;
constexpr int COMMAND_TIMEOUT = 500;
constexpr int CONNECT_DELAY = 1000;





inline bool connectWithMaxRetries() {
    for(int i = 0; i < MAX_RETRIES; i++) {
        if (SerialBT.connect(TARGET_MAC)) return true;
        vTaskDelay(pdMS_TO_TICKS(CONNECT_DELAY)); //lets esp32to Operate Other Task instead of freezing with delay
    }
    return false;
}

inline bool connect() {
    SerialBT.begin("ESP32_DASHBOARD",true);
    SerialBT.setPin(ELM_PIN);
    SerialBT.println("Trying to Connect");
    return connectWithMaxRetries();
}

void Elm327Controller::getReply(char *buffer, uint8_t bufferSize, int timeout_ms) {
    const unsigned long startTime = millis();
    char* ptr=buffer;
    const char* end = (buffer != nullptr) ? (buffer + bufferSize - 1) : nullptr;
    while (millis()-startTime <static_cast<unsigned long>(timeout_ms)) {
        if (SerialBT.available()) {
            char c=SerialBT.read();
            if (c == '>') break;
            if (ptr != nullptr && ptr < end) {
                *ptr++=c;
            }
            }
        }
    if (ptr != nullptr) *ptr = '\0';
    }

void Elm327Controller::sendCommand(const char *command) {
    while(SerialBT.available()) SerialBT.read();
    SerialBT.print(command);
    SerialBT.print('\r');
}
bool Elm327Controller::init() {
    if (!connect()) return false;
    sendCommand("ATZ"); //RESET
    while (SerialBT.available()) SerialBT.read();//empty what remains from reset
    sendCommand("ATE0");//ECHO OFF
    getReply(nullptr,0,RESET_TIMEOUT);
    sendCommand("ATH0");//HEADERS OFF
    getReply(nullptr,0,COMMAND_TIMEOUT);
    sendCommand("ATSP0");//AUTO PROTOCOL
    getReply(nullptr,0,COMMAND_TIMEOUT);
    sendCommand("ATL1");//LINEFEEDS ON
    getReply(nullptr,0,COMMAND_TIMEOUT);
    SerialBT.println("ELM327 CALIBRATED");
    return true;

}

