//
// Created by User on 28/6/2026.
//

#ifndef OBD_AUTOMOTIVE_DISPLAY_ELM327CONTROLLER_H
#define OBD_AUTOMOTIVE_DISPLAY_ELM327CONTROLLER_H
#include <cstdint>

class Elm327Controller {
    public:
     static bool init();
     static void sendCommand(const  char *command);
     static void getReply(char* buffer, uint8_t bufferSize, int timeout_ms = 2000);

};
#endif //OBD_AUTOMOTIVE_DISPLAY_ELM327CONTROLLER_H
