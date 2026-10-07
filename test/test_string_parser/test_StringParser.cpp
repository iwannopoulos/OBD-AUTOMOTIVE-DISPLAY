#include <cstdint>
#include <unity.h>

#include "StringParser.h"
//
// Created by User on 12/7/2026.
//
uint8_t LastPid = 0;
uint8_t LastA = 0;
uint8_t LastB = 0;

    void mockProcessData(uint8_t Pid,uint8_t A,uint8_t B ) {
        LastPid=Pid;
        LastA=A;
        LastB=B;
    }

void setUp(void) {
    LastPid=0;
    LastA=0;
    LastB=0;
    StringParser::processData = mockProcessData;
}

void tearDown(void) {}
void test_StringParser(void) {
    StringParser::processArray("410C1A2B");
    TEST_ASSERT_EQUAL_HEX8(0x0C, LastPid);
    TEST_ASSERT_EQUAL_HEX8(0x1A, LastA);
    TEST_ASSERT_EQUAL_HEX8(0x2B, LastB);

}
void test_StringParser_InvalidMode(void) {
    StringParser::processArray("990C1A2B");
    TEST_ASSERT_EQUAL_HEX8(0,LastPid);
    TEST_ASSERT_EQUAL_HEX8(0,LastA);
    TEST_ASSERT_EQUAL_HEX8(0,LastB);
}
void test_StringParser_OnlyA(void) {
    StringParser::processArray("410C1A");
    TEST_ASSERT_EQUAL_HEX8(0x0C, LastPid);
    TEST_ASSERT_EQUAL_HEX8(0x1A, LastA);
    TEST_ASSERT_EQUAL_HEX8(0, LastB);
}
void test_StringParser_Lowercase(void) {
    StringParser::processArray("410c1a2b");
    TEST_ASSERT_EQUAL_HEX8(0x0C, LastPid);
    TEST_ASSERT_EQUAL_HEX8(0x1A, LastA);
    TEST_ASSERT_EQUAL_HEX8(0x2B, LastB);
}
void test_StringParser_Pid00(void) {
    StringParser::processArray("4100FF00");
    TEST_ASSERT_EQUAL_HEX8(0x00,LastPid);
    TEST_ASSERT_EQUAL_HEX8(0xFF,LastA);
    TEST_ASSERT_EQUAL_HEX8(0x00, LastB);
}
void test_StringParser_ExtraLongString(void) {
    StringParser::processArray("410C1A2B33");
    TEST_ASSERT_EQUAL_HEX8(0x0C, LastPid);
    TEST_ASSERT_EQUAL_HEX8(0x1A, LastA);
    TEST_ASSERT_EQUAL_HEX8(0x2B, LastB);
}
void test_StringParser_EmptyString(void) {
    StringParser::processArray("");
    TEST_ASSERT_EQUAL_HEX8(0, LastPid);
    TEST_ASSERT_EQUAL_HEX8(0, LastA);
    TEST_ASSERT_EQUAL_HEX8(0, LastB);
}
void test_StringParser_InvalidCharacter(void) {
    StringParser::processArray("410G1A2B");
    TEST_ASSERT_EQUAL_HEX8(0, LastPid);
    TEST_ASSERT_EQUAL_HEX8(0, LastA);
    TEST_ASSERT_EQUAL_HEX8(0, LastB);
}
void test_StringParser_Nullptr(void) {
    StringParser::processArray(nullptr);
    TEST_ASSERT_EQUAL_HEX8(0, LastPid);
}
void test_StringParser_OnlyMode(void) {
    StringParser::processArray("41");
    TEST_ASSERT_EQUAL_HEX8(0, LastPid);
}
void test_StringParser_OddLength(void) {
    StringParser::processArray("410C1");
    TEST_ASSERT_EQUAL_HEX8(0, LastPid);
}
int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_StringParser);
    RUN_TEST(test_StringParser_InvalidMode);
    RUN_TEST(test_StringParser_OnlyA);
    RUN_TEST(test_StringParser_Lowercase);
    RUN_TEST(test_StringParser_Pid00);
    RUN_TEST(test_StringParser_ExtraLongString);
    RUN_TEST(test_StringParser_EmptyString);
    RUN_TEST(test_StringParser_InvalidCharacter);
    RUN_TEST(test_StringParser_Nullptr);
    RUN_TEST(test_StringParser_OnlyMode);
    RUN_TEST(test_StringParser_OddLength);
    return UNITY_END();
}