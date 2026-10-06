//
// Created by User on 16/7/2026.
//

#include "BluetoothHandler.h"
#include "BluetoothSerial.h"
#include <cstdint>
BluetoothSerial serialHandler;
// TODO: Change this to your ELM327 PIN
const char* pin = "1234";
//TODO: Change this to the real Mac address of your ELM327 device 
uint8_t targetMac[6] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
bool BluetoothHandler::connect() {
    serialHandler.begin("ESP32_DASHBOARD", true);
    serialHandler.setPin(pin);

    return serialHandler.connect(targetMac);
}

bool BluetoothHandler::connected() {
    return serialHandler.connected();
}
int BluetoothHandler::available() {
    return serialHandler.available();
}
char BluetoothHandler::read() {
    return serialHandler.read();
}
void BluetoothHandler::print(const char* message) {
    serialHandler.print(message);
}
