//
// Created by User on 23/6/2026.
//

#include "PID_Manager.h"

#include "Obd_Parser.h"
#include "Screen_pid_Config.h"

float PID_Manager::processData(uint8_t pid,uint8_t A,uint8_t B) {
        switch (pid) {
            case Rpm:return Obd_Parser::parseRpm(A,B);
            case Ignition:return Obd_Parser::parseIgnition(A);
            case Speed:return Obd_Parser::parseSpeed(A);
            case EngineLoad:return Obd_Parser::parseEngineLoad(A);
            case CoolantTemp:return Obd_Parser::parseTemperature(A);
            case MafFlowRate:return Obd_Parser::parseMafFlowRate(A,B);
            case Throttle:return Obd_Parser::parseThrottle(A);
            case IntakeAirTemp:return Obd_Parser::parseIntakeAirTemp(A);
            case MapSensor:return Obd_Parser::parseMapSensor(A);
            case ModuleVoltage:return Obd_Parser::parseModuleVoltage(A,B);
            case ShortFuelTrim:return Obd_Parser::parseShortFuelTrim(A);
            case LongFuelTrim:return Obd_Parser::parseLongFuelTrim(A);
            case DistanceWithMalfunction:return Obd_Parser::parseDistanceWithMalfunction(A,B);
            case CatalystTemp:return Obd_Parser::parseCatalystTemp(A,B);
            case BarometricPres:return Obd_Parser::parseBarometricPres(A);
            case EngineRunTime:return Obd_Parser::parseEngineRunTime(A,B);

            default:return 0.0f;
        }
    }
