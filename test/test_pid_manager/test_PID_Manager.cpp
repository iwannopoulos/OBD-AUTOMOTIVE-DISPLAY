#include <unity.h>

#include "DataStorage.h"
#include "PidManager.h"
#include "ScreenPidConfig.h"


void setUp(void) {}
void tearDown(void) {}

void test_RPM(void) {
    PidManager::processData(Rpm, 0x0B, 0xB8);
    float result=DataStorage::getRpm();
    TEST_ASSERT_EQUAL_FLOAT(750.0f, result);
}

void test_Speed(void) {
    PidManager::processData(Speed, 0x64, 0x00);
    float result = DataStorage::getSpeed();
    TEST_ASSERT_EQUAL_FLOAT(100.0f, result);
}

void test_Temperature(void) {
    PidManager::processData(CoolantTemp, 0x64, 0x00);
    float result = DataStorage::getCoolantTemp();
    TEST_ASSERT_EQUAL_FLOAT(60.0f, result);
}

void test_EngineLoad(void) {
    PidManager::processData(EngineLoad, 0xFF, 0x00);
    float result =DataStorage::getEngineLoad();
    TEST_ASSERT_EQUAL_FLOAT(100.0f, result);
}

void test_Throttle(void) {
    PidManager::processData(Throttle, 0xFF, 0x00);
     float result =DataStorage::getThrottle();
    TEST_ASSERT_EQUAL_FLOAT(100.0f, result);
}

void test_Ignition(void) {
    PidManager::processData(Ignition, 0x8C, 0x00);
    float result =DataStorage::getIgnition();
    TEST_ASSERT_EQUAL_FLOAT(6.0f, result);
}

void test_IntakeAirTemp(void) {
    PidManager::processData(IntakeAirTemp, 0x3C, 0x00);
    float result =DataStorage::getIntakeAirTemp();
    TEST_ASSERT_EQUAL_FLOAT(20.0f, result);
}

void test_MapSensor(void) {
    PidManager::processData(MapSensor, 0x69, 0x00);
    float result=DataStorage::getMapSensor();
    TEST_ASSERT_EQUAL_FLOAT(105.0f, result);
}

void test_ModuleVoltage(void) {
    PidManager::processData(ModuleVoltage, 0x34, 0x58);
    float result = DataStorage::getModuleVoltage();
    TEST_ASSERT_EQUAL_FLOAT(13.4f, result);
}

void test_ShortFuelTrim(void) {
    PidManager::processData(ShortFuelTrim, 0x80, 0x00);
    float result = DataStorage::getShortFuelTrim();
    TEST_ASSERT_EQUAL_FLOAT(0.0f, result);
}

void test_MafFlowRate(void) {
    PidManager::processData(MafFlowRate, 0x0A, 0x20);
    float result = DataStorage::getMafFlowRate();
    TEST_ASSERT_EQUAL_FLOAT(25.92f, result);
}

void test_CatalystTemp(void) {
    PidManager::processData(CatalystTemp, 0x1F, 0x40);
    float result = DataStorage::getCatalystTemp();
    TEST_ASSERT_EQUAL_FLOAT(760.0f, result);
}

void test_LongFuelTrim(void) {
    PidManager::processData(LongFuelTrim, 0x80, 0x00);
    float result =DataStorage::getLongFuelTrim();
    TEST_ASSERT_EQUAL_FLOAT(0.0f, result);
}

void test_BarometricPres(void) {
    PidManager::processData(BarometricPres, 0x64, 0x00);
    float result =DataStorage::getBarometricPres();
    TEST_ASSERT_EQUAL_FLOAT(100.0f, result);
}

void test_EngineRunTime(void) {
    PidManager::processData(EngineRunTime, 0x01, 0x3C);
    float result =DataStorage::getEngineRunTime();
    TEST_ASSERT_EQUAL_FLOAT(316.0f, result);
}

void test_DistanceWithMalfunction(void) {
    PidManager::processData(DistanceWithMalfunction, 0x04, 0x00);
    float result =DataStorage::getDistanceWithMalfunction();
    TEST_ASSERT_EQUAL_FLOAT(1024.0f, result);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_RPM);
    RUN_TEST(test_Speed);
    RUN_TEST(test_Temperature);
    RUN_TEST(test_EngineLoad);
    RUN_TEST(test_Throttle);
    RUN_TEST(test_Ignition);
    RUN_TEST(test_IntakeAirTemp);
    RUN_TEST(test_MapSensor);
    RUN_TEST(test_ModuleVoltage);
    RUN_TEST(test_ShortFuelTrim);
    RUN_TEST(test_MafFlowRate);
    RUN_TEST(test_CatalystTemp);
    RUN_TEST(test_LongFuelTrim);
    RUN_TEST(test_BarometricPres);
    RUN_TEST(test_EngineRunTime);
    RUN_TEST(test_DistanceWithMalfunction);
    return UNITY_END();
}