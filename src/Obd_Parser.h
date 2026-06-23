//
// Created by User on 23/6/2026.
//

#ifndef OBD_AUTOMOTIVE_DISPLAY_OBD_PARSER_H
#define OBD_AUTOMOTIVE_DISPLAY_OBD_PARSER_H
#include <cstdint>
class Obd_Parser {
    public:
    Obd_Parser();
    ~Obd_Parser();
    static float parseRpm(uint8_t A,uint8_t B);
    static float parseSpeed(uint8_t A);
    static float parseTemperature(uint8_t A);
    static float parseEngineLoad(uint8_t A);
    static float parseThrottle(uint8_t A);
    static float parseMafFlowRate(uint8_t A,uint8_t B);
    static float parseIgnition(uint8_t A);
};

#endif //OBD_AUTOMOTIVE_DISPLAY_OBD_PARSER_H
