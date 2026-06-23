//
// Created by User on 23/6/2026.
//

#include "PID_Manager.h"

#include "Obd_Parser.h"

    float PID_Manager::processData(uint8_t pid,uint8_t A,uint8_t B) {
        switch (pid) {
            case 0x0C:return Obd_Parser::parseRpm(A,B);
            case 0x0E:return Obd_Parser::parseIgnition(A);
            case 0x0D:return Obd_Parser::parseSpeed(A);
            case 0x04:return Obd_Parser::parseEngineLoad(A);
            case 0x05:return Obd_Parser::parseTemperature(A);
            case 0x10:return Obd_Parser::parseMafFlowRate(A,B);
            case 0x11:return Obd_Parser::parseThrottle(A);

            default:return 0.0f;
        }
    }