//
// Created by User on 28/7/2026.
//

#include "DataStorage.h"

float DataStorage::rpm = 0.0f;
float DataStorage::speed = 0.0f;
float DataStorage::coolantTemp = 0.0f;
float DataStorage::engineLoad = 0.0f;
float DataStorage::throttle = 0.0f;
float DataStorage::mafFlowRate = 0.0f;
float DataStorage::ignition = 0.0f;
float DataStorage::intakeAirTemp = 0.0f;
float DataStorage::mapSensor = 0.0f;
float DataStorage::moduleVoltage = 0.0f;
float DataStorage::shortFuelTrim = 0.0f;
float DataStorage::longFuelTrim = 0.0f;
float DataStorage::distanceWithMalfunction = 0.0f;
float DataStorage::catalystTemp = 0.0f;
float DataStorage::barometricPres = 0.0f;
float DataStorage::engineRunTime = 0.0f;

void DataStorage::setRpm(float val) { rpm = val; }
void DataStorage::setSpeed(float val) { speed = val; }
void DataStorage::setCoolantTemp(float val) { coolantTemp = val; }
void DataStorage::setEngineLoad(float val) { engineLoad = val; }
void DataStorage::setThrottle(float val) { throttle = val; }
void DataStorage::setMafFlowRate(float val) { mafFlowRate = val; }
void DataStorage::setIgnition(float val) { ignition = val; }
void DataStorage::setIntakeAirTemp(float val) { intakeAirTemp = val; }
void DataStorage::setMapSensor(float val) { mapSensor = val; }
void DataStorage::setModuleVoltage(float val) { moduleVoltage = val; }
void DataStorage::setShortFuelTrim(float val) { shortFuelTrim = val; }
void DataStorage::setLongFuelTrim(float val) { longFuelTrim = val; }
void DataStorage::setDistanceWithMalfunction(float val) { distanceWithMalfunction = val; }
void DataStorage::setCatalystTemp(float val) { catalystTemp = val; }
void DataStorage::setBarometricPres(float val) { barometricPres = val; }
void DataStorage::setEngineRunTime(float val) { engineRunTime = val; }

float DataStorage::getRpm() { return rpm; }
float DataStorage::getSpeed() { return speed; }
float DataStorage::getCoolantTemp() { return coolantTemp; }
float DataStorage::getEngineLoad() { return engineLoad; }
float DataStorage::getThrottle() { return throttle; }
float DataStorage::getMafFlowRate() { return mafFlowRate; }
float DataStorage::getIgnition() { return ignition; }
float DataStorage::getIntakeAirTemp() { return intakeAirTemp; }
float DataStorage::getMapSensor() { return mapSensor; }
float DataStorage::getModuleVoltage() { return moduleVoltage; }
float DataStorage::getShortFuelTrim() { return shortFuelTrim; }
float DataStorage::getLongFuelTrim() { return longFuelTrim; }
float DataStorage::getDistanceWithMalfunction() { return distanceWithMalfunction; }
float DataStorage::getCatalystTemp() { return catalystTemp; }
float DataStorage::getBarometricPres() { return barometricPres; }
float DataStorage::getEngineRunTime() { return engineRunTime; }