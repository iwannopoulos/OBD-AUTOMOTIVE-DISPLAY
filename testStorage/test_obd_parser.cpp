//
// Created by User on 11/7/2026.
//
#include <unity.h>
#include "Obd_Parser.h"
#include "../../../.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/unity/unity/src/unity.h"
// Το Unity ΑΠΑΙΤΕΙ αυτές τις δύο συναρτήσεις, έστω κι αν τις αφήσεις άδειες!
void setUp(void) {}

void tearDown(void) {}
void test_speed_calculation(void) {
    // Test: A=0x32(50) -> 50
    TEST_ASSERT_EQUAL_FLOAT(50.0f, Obd_Parser::parseSpeed(0x32));
}

void test_Temperature_calculation(void) {
    // Test: A=0x32(50) -> 50 - 40 = 10
    TEST_ASSERT_EQUAL_FLOAT(10.0f, Obd_Parser::parseTemperature(0x32));
}
void test_Temperature_edge_cases(void) {
    // 0x00 -> 0 - 40 = -40°C (Το απόλυτο χαμηλό)
    TEST_ASSERT_EQUAL_FLOAT(-40.0f, Obd_Parser::parseTemperature(0x00));

    // 0x28 -> 40 - 40 = 0°C (Το σημείο μηδενισμού)
    TEST_ASSERT_EQUAL_FLOAT(0.0f, Obd_Parser::parseTemperature(0x28));
}

void test_EngineLoad_calculation(void) {
    // Test: A=0x32(50) -> 50 * 100 / 255 = 19.60784
    TEST_ASSERT_EQUAL_FLOAT(19.60784f, Obd_Parser::parseEngineLoad(0x32));
}

void test_throttle_calculation(void) {
    // Test: A=0x32(50) -> 50 * 100 / 255 = 19.60784
    TEST_ASSERT_EQUAL_FLOAT(19.60784f, Obd_Parser::parseThrottle(0x32));
}

void test_MafFlowRate_calculation(void) {
    // Test: A=0x1A(26), B=0x2B(43) -> (26*256 + 43) / 100 = 66.99
    TEST_ASSERT_EQUAL_FLOAT(66.99f, Obd_Parser::parseMafFlowRate(0x1A, 0x2B));
}

void test_Ignition_calculation(void) {
    // Test: A=0x32(50) -> (50 / 2) - 64 = -39
    TEST_ASSERT_EQUAL_FLOAT(-39.0f, Obd_Parser::parseIgnition(0x32));
}
void test_Ignition_edge_cases(void) {
    // 0x00 -> (0 / 2) - 64 = -64 (Ακραία αρνητική τιμή)
    TEST_ASSERT_EQUAL_FLOAT(-64.0f, Obd_Parser::parseIgnition(0x00));

    // 0x80 (128) -> (128 / 2) - 64 = 0
    TEST_ASSERT_EQUAL_FLOAT(0.0f, Obd_Parser::parseIgnition(0x80));
}

void test_IntakeAirTemp_calculation(void) {
    // Test: A=0x32(50) -> 50 - 40 = 10
    TEST_ASSERT_EQUAL_FLOAT(10.0f, Obd_Parser::parseIntakeAirTemp(0x32));
}

void test_MapSensor_calculation(void) {
    // Test: A=0x32(50) -> 50
    TEST_ASSERT_EQUAL_FLOAT(50.0f, Obd_Parser::parseMapSensor(0x32));
}

void test_ModuleVoltage_calculation(void) {
    // Test: A=0x1A(26), B=0x2B(43) -> (26*256 + 43) / 1000 = 6.699
    TEST_ASSERT_EQUAL_FLOAT(6.699f, Obd_Parser::parseModuleVoltage(0x1A, 0x2B));
}

void test_ShortFuelTrim_calculation(void) {
    // Test: A=0x32(50) -> (50 - 128) * 100 / 128 = -60.9375
    TEST_ASSERT_EQUAL_FLOAT(-60.9375f, Obd_Parser::parseShortFuelTrim(0x32));
}
void test_FuelTrim_edge_cases(void) {
    // 0x00 -> (0 - 128) * 100 / 128 = -100% (Μέγιστο αρνητικό trim)
    TEST_ASSERT_EQUAL_FLOAT(-100.0f, Obd_Parser::parseShortFuelTrim(0x00));

    // 0x80 -> (128 - 128) * 100 / 128 = 0% (Ιδανικό trim)
    TEST_ASSERT_EQUAL_FLOAT(0.0f, Obd_Parser::parseShortFuelTrim(0x80));

    // 0xFF -> (255 - 128) * 100 / 128 = 99.21875% (Μέγιστο θετικό trim)
    TEST_ASSERT_EQUAL_FLOAT(99.21875f, Obd_Parser::parseShortFuelTrim(0xFF));
}
void test_LongFuelTrim_calculation(void) {
    // Test: A=0x32(50) -> (50 - 128) * 100 / 128 = -60.9375
    TEST_ASSERT_EQUAL_FLOAT(-60.9375f, Obd_Parser::parseLongFuelTrim(0x32));
}

void test_DistanceWithMalfunction_calculation(void) {
    // Test: A=0x1A(26), B=0x2B(43) -> 26*256 + 43 = 6699
    TEST_ASSERT_EQUAL_FLOAT(6699.0f, Obd_Parser::parseDistanceWithMalfunction(0x1A, 0x2B));
}

void test_CatalystTemp_calculation(void) {
    // Test: A=0x1A(26), B=0x2B(43) -> ((26*256 + 43) / 10) - 40 = 629.9
    TEST_ASSERT_EQUAL_FLOAT(629.9f, Obd_Parser::parseCatalystTemp(0x1A, 0x2B));
}

void test_BarometricPressure_calculation(void) {
    // Test: A=0x32(50) -> 50
    TEST_ASSERT_EQUAL_FLOAT(50.0f, Obd_Parser::parseBarometricPres(0x32));
}

void test_EngineRunTime(void) {
    // Test: A=0x1A(26), B=0x2B(43) -> 26*256 + 43 = 6699
    TEST_ASSERT_EQUAL_FLOAT(6699.0f, Obd_Parser::parseEngineRunTime(0x1A, 0x2B));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    // Γενικά Tests
    RUN_TEST(test_speed_calculation);
    RUN_TEST(test_Temperature_calculation);
    RUN_TEST(test_Temperature_edge_cases);
    RUN_TEST(test_EngineLoad_calculation);
    RUN_TEST(test_throttle_calculation);
    RUN_TEST(test_MafFlowRate_calculation);
    RUN_TEST(test_Ignition_calculation);
    RUN_TEST(test_Ignition_edge_cases);
    RUN_TEST(test_IntakeAirTemp_calculation);
    RUN_TEST(test_MapSensor_calculation);
    RUN_TEST(test_ModuleVoltage_calculation);
    RUN_TEST(test_ShortFuelTrim_calculation);
    RUN_TEST(test_FuelTrim_edge_cases);
    RUN_TEST(test_LongFuelTrim_calculation);
    RUN_TEST(test_DistanceWithMalfunction_calculation);
    RUN_TEST(test_CatalystTemp_calculation);
    RUN_TEST(test_BarometricPressure_calculation);
    RUN_TEST(test_EngineRunTime);

    return UNITY_END();
}