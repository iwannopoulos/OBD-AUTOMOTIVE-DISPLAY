//
// Created by User on 23/6/2026.
//

#ifndef OBD_AUTOMOTIVE_DISPLAY_STRINGPARSER_H
#define OBD_AUTOMOTIVE_DISPLAY_STRINGPARSER_H
#include <cstdint>
static constexpr uint8_t INVALID_BYTE = 0xFF;
class StringParser {

     static uint8_t ConvertCharToHex(char c) {
        if (c>='0'&& c<='9') return c-'0';
        if (c>='A'&& c<='F') return c-'A'+10;
        if (c>='a'&& c<='f') return c-'a'+10;
        return INVALID_BYTE; //Error Flag
    }

   static uint8_t ConsumeNextByte(const char* &c,bool &success) {

        const uint8_t first=ConvertCharToHex(*c++);
        const  uint8_t second=ConvertCharToHex(*c++);
        if (first==INVALID_BYTE || second==INVALID_BYTE) {
            success=false;
            return 0xFF;
        }
        return (first<<4) | second;
    }
public:
    template <typename Manager>
    static void processArray(const char *answer) {
        if (answer==nullptr || *answer=='\0') return;
        const char* ptr=answer;
        bool success = true;
        const uint8_t mode=ConsumeNextByte(ptr,success); //we are at mode 1 so answer should always be 0x41
        if (mode==0x41) {
            const uint8_t pid=ConsumeNextByte(ptr,success);
            const uint8_t A=ConsumeNextByte(ptr,success);
            uint8_t B=0;
            if (*ptr!='\0') {
                B=ConsumeNextByte(ptr,success);

            }
            if (success) {
                Manager::processData(pid, A, B);
            }


        }
    }

};
#endif
