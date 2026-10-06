//
// Created by User on 16/7/2026.
//

#ifndef OBD_AUTOMOTIVE_DISPLAY_BLUETOOTHHANDLER_H
#define OBD_AUTOMOTIVE_DISPLAY_BLUETOOTHHANDLER_H
class BluetoothHandler {
public:
    bool connect(); //connects to bluetooth
    bool connected();// checks if is connected
    int available();// checks how many characters are ready to read
    char read();//reads a byte (an ascii character) per time
    void print(const char* str); // to send command
};
#endif //OBD_AUTOMOTIVE_DISPLAY_BLUETOOTHHANDLER_H
