//
// Created by User on 23/6/2026.
//

#include "StringParser.h"

#include <cstdint>
#include <cstdlib>

#include "PID_Manager.h"

inline uint8_t ConverHexToByte(const char c) {
    if (c>='0'&& c<='9') return c-'0';
    if (c>='A'&& c<='F') return c-'A'+10;
    if (c>='a'&& c<='f') return c-'a'+10;
    return 0;
}

inline bool isHex(const char c) {
    return ((c>='0' && c<='9') ||
            (c>='A' && c<='F') ||
            (c>='a' && c<='f'));
}
inline uint8_t ConsumeNextByte(const char* &c) {
    while (*c && !isHex(*c)) {
        c++;
    }
    const uint8_t first=ConverHexToByte(*c++);
    //we could check also here if we get incorrect input but i think its unnecessary
    const  uint8_t second=ConverHexToByte(*c++);
    return (first<<4) | second;
}

void StringParser::processArray(const char *answer) {
    const char* ptr=answer;
    const uint8_t mode=ConsumeNextByte(ptr); //we are at mode 1 so answer should always be 0x41
    if (mode==0x41) {
        const uint8_t pid=ConsumeNextByte(ptr);
        const uint8_t A=ConsumeNextByte(ptr);
        const uint8_t B=ConsumeNextByte(ptr);
        PID_Manager::processData(pid, A, B);
    }
    return;
}
