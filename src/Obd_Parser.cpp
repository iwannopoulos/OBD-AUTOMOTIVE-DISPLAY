//
// Created by User on 23/6/2026.
//


#include "Obd_Parser.h"
    Obd_Parser::Obd_Parser() {}
    Obd_Parser::~Obd_Parser() {}
    float Obd_Parser::parseRpm(const uint8_t A,const uint8_t B) {
        return (A*256+B)/4.0f;
    }
     float Obd_Parser::parseSpeed(const uint8_t A) {
        return static_cast<float>(A);
    }
    float Obd_Parser::parseTemperature(const uint8_t A) {
        return static_cast<float>(A-40);
    }
    float Obd_Parser::parseEngineLoad(const uint8_t A) {
        return (A/255.0f)*100.0f;
    }
    float Obd_Parser::parseThrottle(const uint8_t A) {
        return (A/255.0f)*100.0f;
    }
    float Obd_Parser::parseMafFlowRate(const uint8_t A,const uint8_t B) {
        return (A*256.0f+B)/100.0f;
    }
    float Obd_Parser::parseIgnition(const uint8_t A) {
        return  (A/2.0f)-64.0f;
    }
