#include <cstdint>
#include <unity.h>

#include "StringParser.h"
//
// Created by User on 12/7/2026.
//
struct mock_Pid_Manager{
    static uint8_t LastPid;
    static uint8_t LastA;
    static uint8_t LastB;

    static void processData(uint8_t Pid,uint8_t A,uint8_t B ) {
        LastPid=Pid;
        LastA=A;
        LastB=B;
    }
};
uint8_t mock_Pid_Manager::LastPid = 0;
uint8_t mock_Pid_Manager::LastA = 0;
uint8_t mock_Pid_Manager::LastB = 0;
void setUp(void) {
    mock_Pid_Manager::LastPid=0;
    mock_Pid_Manager::LastA=0;
    mock_Pid_Manager::LastB=0;
}

void tearDown(void) {}
void test_StringParser(void) {
    StringParser::processArray<mock_Pid_Manager>("410C1A2B");
    TEST_ASSERT_EQUAL_HEX8(0x0C, mock_Pid_Manager::LastPid);
    TEST_ASSERT_EQUAL_HEX8(0x1A, mock_Pid_Manager::LastA);
    TEST_ASSERT_EQUAL_HEX8(0x2B, mock_Pid_Manager::LastB);

}
void test_StringParser_InvalidMode(void) {
    StringParser::processArray<mock_Pid_Manager>("990C1A2B");
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastPid);
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastA);
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastB);
}
void test_StringParser_OnlyA(void) {
    StringParser::processArray<mock_Pid_Manager>("410C1A");
    TEST_ASSERT_EQUAL_HEX8(0x0C, mock_Pid_Manager::LastPid);
    TEST_ASSERT_EQUAL_HEX8(0x1A, mock_Pid_Manager::LastA);
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastB);
}
void test_StringParser_Lowercase(void) {
    StringParser::processArray<mock_Pid_Manager>("410c1a2b");
    TEST_ASSERT_EQUAL_HEX8(0x0C, mock_Pid_Manager::LastPid);
    TEST_ASSERT_EQUAL_HEX8(0x1A, mock_Pid_Manager::LastA);
    TEST_ASSERT_EQUAL_HEX8(0x2B, mock_Pid_Manager::LastB);
}
void test_StringParser_Pid00(void) {
    StringParser::processArray<mock_Pid_Manager>("4100FF00");
    TEST_ASSERT_EQUAL_HEX8(0x00, mock_Pid_Manager::LastPid);
    TEST_ASSERT_EQUAL_HEX8(0xFF, mock_Pid_Manager::LastA);
    TEST_ASSERT_EQUAL_HEX8(0x00, mock_Pid_Manager::LastB);
}
void test_StringParser_ExtraLongString(void) {
    StringParser::processArray<mock_Pid_Manager>("410C1A2B33");
    TEST_ASSERT_EQUAL_HEX8(0x0C, mock_Pid_Manager::LastPid);
    TEST_ASSERT_EQUAL_HEX8(0x1A, mock_Pid_Manager::LastA);
    TEST_ASSERT_EQUAL_HEX8(0x2B, mock_Pid_Manager::LastB);
}
void test_StringParser_EmptyString(void) {
    StringParser::processArray<mock_Pid_Manager>("");
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastPid);
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastA);
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastB);
}
void test_StringParser_InvalidCharacter(void) {
    StringParser::processArray<mock_Pid_Manager>("410G1A2B");
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastPid);
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastA);
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastB);
}
void test_StringParser_Nullptr(void) {
    StringParser::processArray<mock_Pid_Manager>(nullptr);
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastPid);
}
void test_StringParser_OnlyMode(void) {
    StringParser::processArray<mock_Pid_Manager>("41");
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastPid);
}
void test_StringParser_OddLength(void) {
    StringParser::processArray<mock_Pid_Manager>("410C1");
    TEST_ASSERT_EQUAL_HEX8(0, mock_Pid_Manager::LastPid);
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