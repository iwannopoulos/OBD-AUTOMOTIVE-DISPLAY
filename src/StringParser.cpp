//
// Created by User on 23/6/2026.
//

#include "StringParser.h"

#include <cstdint>
#include <cstdlib>

#include "PID_Manager.h"
//safety net in case hardware fail
bool StringParser::isValid(const char* answer){
    if (answer==nullptr)return false;
    return (answer[0]==4);
}
void StringParser::processArray(const char* answer) {
    const uint8_t pid=static_cast<uint8_t>(strtoul(answer+3,nullptr,16));
    const uint8_t A=static_cast<uint8_t>(strtoul(answer+6,nullptr,16));
    const uint8_t B=static_cast<uint8_t>(strtoul(answer+9,nullptr,16));
    PID_Manager::processData(pid,A,B);
}