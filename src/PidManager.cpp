//
// Created by User on 23/6/2026.
//

#include "PidManager.h"

#include "DataStorage.h"
#include "ObdParser.h"
#include "ScreenPidConfig.h"

void PidManager::processData(uint8_t pid, uint8_t A, uint8_t B) {
    switch (pid) {
        case Rpm:DataStorage::setRpm(ObdParser::parseRpm(A, B)); break;
        case Ignition: DataStorage::setIgnition(ObdParser::parseIgnition(A));break;
        case Speed:DataStorage::setSpeed(ObdParser::parseSpeed(A));break;
        case EngineLoad:DataStorage::setEngineLoad(ObdParser::parseEngineLoad(A));break;
        case CoolantTemp:DataStorage::setCoolantTemp(ObdParser::parseTemperature(A));break;
        case MafFlowRate:DataStorage::setMafFlowRate(ObdParser::parseMafFlowRate(A, B));break;
        case Throttle:DataStorage::setThrottle(ObdParser::parseThrottle(A));break;
        case IntakeAirTemp:DataStorage::setIntakeAirTemp(ObdParser::parseIntakeAirTemp(A));break;
        case MapSensor:DataStorage::setMapSensor(ObdParser::parseMapSensor(A));break;
        case ModuleVoltage:DataStorage::setModuleVoltage(ObdParser::parseModuleVoltage(A, B));break;
        case ShortFuelTrim:DataStorage::setShortFuelTrim(ObdParser::parseShortFuelTrim(A));break;
        case LongFuelTrim:DataStorage::setLongFuelTrim(ObdParser::parseLongFuelTrim(A));break;
        case DistanceWithMalfunction:DataStorage::setDistanceWithMalfunction(ObdParser::parseDistanceWithMalfunction(A, B));break;
        case CatalystTemp:DataStorage::setCatalystTemp(ObdParser::parseCatalystTemp(A, B));break;
        case BarometricPres:DataStorage::setBarometricPres(ObdParser::parseBarometricPres(A));break;
        case EngineRunTime:DataStorage::setEngineRunTime(ObdParser::parseEngineRunTime(A, B));break;
        default: break;
    }
}
