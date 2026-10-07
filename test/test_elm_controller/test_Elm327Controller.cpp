//
// Created by User on 29/7/2026.
//
#include "BluetoothHandler.h"
#include <cstring>
#include <unity.h>
#include "Elm327Controller.h"
#include "CommunicationStates.h"
#include "ScreenPidConfig.h"

bool mock_connected = false;

// global variables for receive
char mock_receive_buffer[50] = "";
int mock_receive_index = 0;
int mock_receive_length = 0;

// global variables for send
char mock_send_buffer[50] = "";

/**
 *  mock BluetoothHandler
 *  we replace the real functions of BluetoothHandler with mocks to test only Elm327Controller logic so even
 *  if BluetoothHandler has some flaws it doesn't affect ELM327Controller tests
 */
bool BluetoothHandler::connect() {
    return mock_connected;
}

bool BluetoothHandler::connected() {
    return mock_connected;
}

void BluetoothHandler::print(const char* str) {
    strncpy(mock_send_buffer, str, sizeof(mock_send_buffer) - 1);
    mock_send_buffer[sizeof(mock_send_buffer) - 1] = '\0';
}

int BluetoothHandler::available() {
    return mock_receive_length - mock_receive_index;
}

char BluetoothHandler::read() {
    if (mock_receive_index < mock_receive_length) {
        return mock_receive_buffer[mock_receive_index++];
    }
    return '\0';
}

void setUp(void) {
    mock_connected = false;
    memset(mock_receive_buffer, 0, sizeof(mock_receive_buffer));
    mock_receive_index = 0;
    mock_receive_length = 0;
    memset(mock_send_buffer, 0, sizeof(mock_send_buffer));
    Elm327Controller::getReply();//to reset buffer
}

void tearDown(void) {}
void test_Elm327_Connect_Success(void) {
    mock_connected = true;
    State result = Elm327Controller::Connect();
    TEST_ASSERT_EQUAL(State::IDLE, result);
}
void test_Elm327_Connect_Fail(void) {
    mock_connected = false;
    State result = Elm327Controller::Connect();
    TEST_ASSERT_EQUAL(State::CONNECTING, result);
}
void test_Elm327_IsConnected(void) {
    mock_connected = true;
    TEST_ASSERT_TRUE(Elm327Controller::isConnected());

    mock_connected = false;
    TEST_ASSERT_FALSE(Elm327Controller::isConnected());
}
void test_Elm327_RequestPid_Disconnected(void) {
    mock_connected = false;
    State result = Elm327Controller::RequestPid(0x0C);
    TEST_ASSERT_EQUAL(State::DISCONNECTED, result);
}

void test_Elm327_RequestPid_Formats_Correctly_Numeric(void) {
    mock_connected = true;
    State result = Elm327Controller::RequestPid(0x0C);

    TEST_ASSERT_EQUAL(State::WAIT_REPLY, result);
    TEST_ASSERT_EQUAL_STRING("010C\r", mock_send_buffer);
}

void test_Elm327_RequestPid_Formats_Correctly_HexLetters(void) {
    mock_connected = true;
    State result = Elm327Controller::RequestPid(0x1A);

    TEST_ASSERT_EQUAL(State::WAIT_REPLY, result);
    TEST_ASSERT_EQUAL_STRING("011A\r", mock_send_buffer);
}

void test_Elm327_SetUp_Command_ATZ(void) {
    mock_connected = true;
    State result = Elm327Controller::setUp(InitATZ);

    TEST_ASSERT_EQUAL(State::WAIT_REPLY, result);
    TEST_ASSERT_EQUAL_STRING("ATZ\r", mock_send_buffer);
}


void test_Elm327_getReply_Disconnected(void) {
    mock_connected = false;
    State result = Elm327Controller::getReply();
    TEST_ASSERT_EQUAL(State::DISCONNECTED, result);
}

void test_Elm327_getReply_Incomplete_Wait(void) {
    mock_connected = true;
    strcpy(mock_receive_buffer, "41 0C 1A ");
    mock_receive_length = strlen(mock_receive_buffer);
    State result = Elm327Controller::getReply();
    TEST_ASSERT_EQUAL(State::WAIT_REPLY, result);
}

void test_Elm327_getReply_Strips_Spaces_And_Completes(void) {
    mock_connected = true;
    strcpy(mock_receive_buffer, "41 0C 1A 2B \r\n>");
    mock_receive_length = strlen(mock_receive_buffer);
    State result = Elm327Controller::getReply();
    TEST_ASSERT_EQUAL(State::PARSE_REPLY, result);
    TEST_ASSERT_EQUAL_STRING("410C1A2B", Elm327Controller::getBuffer());
}

void test_Elm327_getReply_Buffer_Overflow_Protection(void) {
    mock_connected = true;
    strcpy(mock_receive_buffer, "41 0C AABBCCDDEEFF00112233445566778899");
    mock_receive_length = strlen(mock_receive_buffer);
    State result = Elm327Controller::getReply();
    TEST_ASSERT_EQUAL(State::ERROR, result);
}
void test_Elm327_getReply_Split_Response(void) {
    mock_connected = true;
    strcpy(mock_receive_buffer, "41 0D ");
    mock_receive_length = strlen(mock_receive_buffer);
    mock_receive_index = 0;
    State result1 = Elm327Controller::getReply();
    TEST_ASSERT_EQUAL(State::WAIT_REPLY, result1);
    strcpy(mock_receive_buffer, "1A \r\n>");
    mock_receive_length = strlen(mock_receive_buffer);
    mock_receive_index = 0;
    State result2 = Elm327Controller::getReply();
    TEST_ASSERT_EQUAL(State::PARSE_REPLY, result2);
    TEST_ASSERT_EQUAL_STRING("410D1A", Elm327Controller::getBuffer());
}

void test_Elm327_getReply_Glued_Replies(void) {
    mock_connected = true;
    strcpy(mock_receive_buffer, "41 0C 1A>41 0D 2B \r\n>");
    mock_receive_length = strlen(mock_receive_buffer);
    mock_receive_index = 0;
    State result1 = Elm327Controller::getReply();
    TEST_ASSERT_EQUAL(State::PARSE_REPLY, result1);
    TEST_ASSERT_EQUAL_STRING("410C1A", Elm327Controller::getBuffer());
    State result2 = Elm327Controller::getReply();
    TEST_ASSERT_EQUAL(State::PARSE_REPLY, result2);
    TEST_ASSERT_EQUAL_STRING("410D2B", Elm327Controller::getBuffer());
}
void test_Elm327_getReply_Garbage_Data(void) {
    mock_connected = true;
    strcpy(mock_receive_buffer, "NO DATA\r\n>");
    mock_receive_length = strlen(mock_receive_buffer);
    mock_receive_index = 0;

    State result = Elm327Controller::getReply();
    TEST_ASSERT_EQUAL(State::PARSE_REPLY, result);
    TEST_ASSERT_EQUAL_STRING("NODATA", Elm327Controller::getBuffer());
}
void test_Elm327_getReply_Only_Prompt(void) {
    mock_connected = true;
    strcpy(mock_receive_buffer, ">");
    mock_receive_length = strlen(mock_receive_buffer);
    mock_receive_index = 0;
    State result = Elm327Controller::getReply();
    TEST_ASSERT_EQUAL(State::PARSE_REPLY, result);
    TEST_ASSERT_EQUAL_STRING("", Elm327Controller::getBuffer());
}

void test_Elm327_getReply_Recovery_After_Overflow(void) {
    mock_connected = true;
    strcpy(mock_receive_buffer, "AABBCCDDEEFF00112233445566");
    mock_receive_length = strlen(mock_receive_buffer);
    mock_receive_index = 0;
    State result_overflow = Elm327Controller::getReply();
    TEST_ASSERT_EQUAL(State::ERROR, result_overflow);
    strcpy(mock_receive_buffer, "41 0C 1A\r\n>");
    mock_receive_length = strlen(mock_receive_buffer);
    mock_receive_index = 0;
    State result_recovery = Elm327Controller::getReply();
    TEST_ASSERT_EQUAL(State::PARSE_REPLY, result_recovery);
    TEST_ASSERT_EQUAL_STRING("410C1A", Elm327Controller::getBuffer());
}


int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_Elm327_Connect_Success);
    RUN_TEST(test_Elm327_Connect_Fail);
    RUN_TEST(test_Elm327_IsConnected);

    RUN_TEST(test_Elm327_RequestPid_Disconnected);
    RUN_TEST(test_Elm327_RequestPid_Formats_Correctly_Numeric);
    RUN_TEST(test_Elm327_RequestPid_Formats_Correctly_HexLetters);
    RUN_TEST(test_Elm327_SetUp_Command_ATZ);

    RUN_TEST(test_Elm327_getReply_Disconnected);
    RUN_TEST(test_Elm327_getReply_Incomplete_Wait);
    RUN_TEST(test_Elm327_getReply_Strips_Spaces_And_Completes);
    RUN_TEST(test_Elm327_getReply_Buffer_Overflow_Protection);

    RUN_TEST(test_Elm327_getReply_Split_Response);
    RUN_TEST(test_Elm327_getReply_Glued_Replies);

    RUN_TEST(test_Elm327_getReply_Garbage_Data);
    RUN_TEST(test_Elm327_getReply_Only_Prompt);
    RUN_TEST(test_Elm327_getReply_Recovery_After_Overflow);
    return UNITY_END();
}