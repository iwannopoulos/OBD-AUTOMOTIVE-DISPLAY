//
// Created by User on 23/6/2026.
//

#ifndef OBD_AUTOMOTIVE_DISPLAY_OBD_PARSER_H
#define OBD_AUTOMOTIVE_DISPLAY_OBD_PARSER_H
#include <cstdint>
class Obd_Parser {
    public:
    static float parseRpm(uint8_t A,uint8_t B);
    static float parseSpeed(uint8_t A);
    static float parseTemperature(uint8_t A);
    static float parseEngineLoad(uint8_t A);
    static float parseThrottle(uint8_t A);
    static float parseMafFlowRate(uint8_t A,uint8_t B);
    static float parseIgnition(uint8_t A);
    static float parseIntakeAirTemp(uint8_t A);
    static float parseMapSensor(uint8_t A);
    static float parseModuleVoltage(uint8_t A,uint8_t B);
    static float parseShortFuelTrim(uint8_t A);
    static float parseLongFuelTrim(uint8_t A);
    static float parseDistanceWithMalfunction(uint8_t A,uint8_t B);
    static float parseCatalystTemp(uint8_t A,uint8_t B);
    static float parseBarometricPres(uint8_t A);
    static float parseEngineRunTime(uint8_t A,uint8_t B);
};

#endif //OBD_AUTOMOTIVE_DISPLAY_OBD_PARSER_H
