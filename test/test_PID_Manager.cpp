#include <unity.h>
#include "PID_Manager.h"
#include "Screen_pid_Config.h"


void setUp(void) {}
void tearDown(void) {}

void test_RPM(void) {
    float result = PID_Manager::processData(Rpm, 0x0B, 0xB8);
    TEST_ASSERT_EQUAL_FLOAT(750.0f, result);
}

void test_Speed(void) {
    float result = PID_Manager::processData(Speed, 0x64, 0x00);
    TEST_ASSERT_EQUAL_FLOAT(100.0f, result);
}

void test_Temperature(void) {
    float result = PID_Manager::processData(CoolantTemp, 0x64, 0x00);
    TEST_ASSERT_EQUAL_FLOAT(60.0f, result);
}

void test_EngineLoad(void) {
    float result = PID_Manager::processData(EngineLoad, 0xFF, 0x00);
    TEST_ASSERT_EQUAL_FLOAT(100.0f, result);
}

void test_Throttle(void) {
    float result = PID_Manager::processData(Throttle, 0xFF, 0x00);
    TEST_ASSERT_EQUAL_FLOAT(100.0f, result);
}

void test_Ignition(void) {
    float result = PID_Manager::processData(Ignition, 0x8C, 0x00);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, result);
}

void test_IntakeAirTemp(void) {
    float result = PID_Manager::processData(IntakeAirTemp, 0x3C, 0x00);
    TEST_ASSERT_EQUAL_FLOAT(20.0f, result);
}

void test_MapSensor(void) {
    float result = PID_Manager::processData(MapSensor, 0x69, 0x00);
    TEST_ASSERT_EQUAL_FLOAT(105.0f, result);
}

void test_ModuleVoltage(void) {
    float result = PID_Manager::processData(ModuleVoltage, 0x34, 0x58);
    TEST_ASSERT_EQUAL_FLOAT(13.4f, result);
}

void test_ShortFuelTrim(void) {
    float result = PID_Manager::processData(ShortFuelTrim, 0x80, 0x00);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, result);
}

void test_MafFlowRate(void) {
    float result = PID_Manager::processData(MafFlowRate, 0x0A, 0x20);
    TEST_ASSERT_EQUAL_FLOAT(25.92f, result);
}

void test_CatalystTemp(void) {
    float result = PID_Manager::processData(CatalystTemp, 0x1F, 0x40);
    TEST_ASSERT_EQUAL_FLOAT(760.0f, result);
}

void test_DefaultUnknownPID(void) {
    float result = PID_Manager::processData(0x99, 0xFF, 0xFF);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, result);
}
void test_LongFuelTrim(void) {
    float result = PID_Manager::processData(LongFuelTrim, 0x80, 0x00);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, result);
}

void test_BarometricPres(void) {
    float result = PID_Manager::processData(BarometricPres, 0x64, 0x00);
    TEST_ASSERT_EQUAL_FLOAT(100.0f, result);
}

void test_EngineRunTime(void) {
    float result = PID_Manager::processData(EngineRunTime, 0x01, 0x3C);
    TEST_ASSERT_EQUAL_FLOAT(316.0f, result);
}

void test_DistanceWithMalfunction(void) {
    float result = PID_Manager::processData(DistanceWithMalfunction, 0x04, 0x00);
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
    RUN_TEST(test_DefaultUnknownPID);
    return UNITY_END();
}