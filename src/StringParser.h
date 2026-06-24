//
// Created by User on 23/6/2026.
//

#ifndef OBD_AUTOMOTIVE_DISPLAY_STRINGPARSER_H
#define OBD_AUTOMOTIVE_DISPLAY_STRINGPARSER_H
class StringParser {
    public:
    static bool isValid(const char* answer);
    static void processArray(const char* answer);
};
#endif
