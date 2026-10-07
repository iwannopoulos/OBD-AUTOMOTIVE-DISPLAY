#include <cstdint>
#include <unity.h>

#include "CommunicationStates.h"
#include "Elm327Controller.h"
#include "Scheduler.h"
#include "ScreenPidConfig.h"
#include <cstdlib>

#include "StringParser.h"
//
// Created by User on 13/7/2026.
//
State mock_process_task_state;
State mock_connect;
State mock_state;
bool mock_connection;
void dummyProcessData(uint8_t pid, uint8_t A, uint8_t B) {
}
State Elm327Controller::ProcessTask(uint8_t command) {return mock_process_task_state;}
State Elm327Controller::getReply() {return mock_state;}
const char* Elm327Controller::getBuffer() {return "410C1A2B";}
bool Elm327Controller::isConnected(){return mock_connection;}
State Elm327Controller::Connect(){return mock_connect;}
char Elm327Controller::buffer[16];
unsigned long fakeMillis = 0;
unsigned long myFakeMillis() {return fakeMillis;}

Task myTasks[] = { {100,0x0C, 1} };
TaskList myTaskList = { myTasks, WEIGHTED_RR, 1, false };
Task mockTimeBased[] = { {100, 0x0C, 1}, {100, 0x0D, 1} };
TaskList mockTimeList = { mockTimeBased, TIME_BASED, 2, false };
TaskList mockInitList = { myTasks, WEIGHTED_RR, 1, true };
Scheduler scheduler;
void setUp(void) {
    fakeMillis = 0;
    scheduler.getMillis = myFakeMillis;
    mock_connection=true;
    scheduler.setActiveTask(&myTaskList);
    mock_process_task_state = State::WAIT_REPLY;
    mock_state = State::PARSE_REPLY;
    mock_connect=State::IDLE;
    scheduler.setFallbackTask(&mockInitList);
    StringParser::processData=dummyProcessData;

}

void tearDown(void) {}

void test_Scheduler_WaitsForIdleTime(void) {
    // We just created Scheduler It should be Idle
    TEST_ASSERT_EQUAL(State::IDLE, scheduler.getCurrentState());

    fakeMillis = 50; //We are at 50ms Task needs 100 so we should be on Idle still
    scheduler.update();
    TEST_ASSERT_EQUAL(State::IDLE, scheduler.getCurrentState());

    fakeMillis = 101; // We pass 100ms so Scheduler State Should be SEND_REQUEST
    scheduler.update();
    TEST_ASSERT_EQUAL(State::SEND_REQUEST, scheduler.getCurrentState());
}
void test_Scheduler_Fail_SEND_REQUEST_Soft_Error(void) {
    mock_process_task_state = State::ERROR;//simulate fail SEND_REQUEST
    fakeMillis = 101;
    scheduler.update();//first update State=SEND_REQUEST
    scheduler.update();//Now should Be on Error
    TEST_ASSERT_EQUAL(State::ERROR, scheduler.getCurrentState());
    scheduler.update();
    TEST_ASSERT_EQUAL(State::IDLE, scheduler.getCurrentState());
}
void test_Scheduler_Fail_Connection_Hard_Error(void) {
    mock_connection = false;//simulate lost Connection
    mock_process_task_state = State::DISCONNECTED;
    fakeMillis = 101;
    scheduler.update();
    scheduler.update();
    TEST_ASSERT_EQUAL(State::DISCONNECTED, scheduler.getCurrentState());
    mock_connect = State::CONNECTING; //Simulate connecting wait
    scheduler.update();
    TEST_ASSERT_EQUAL(State::CONNECTING,scheduler.getCurrentState());
}
void test_scheduler_TimeOutWait(void) {
    mock_state = State::WAIT_REPLY;//Reply didnt Arrive in TIme
    fakeMillis = 101;
    scheduler.update();//IDLE->SEND_REQUEST
    scheduler.update();//SEND_REQUEST->WAIT_REPLY
    fakeMillis = 101+OBD_TIMEOUT_MS+1;
    scheduler.update();//WAIT_REPLY->ERROR
    TEST_ASSERT_EQUAL(State::ERROR, scheduler.getCurrentState());
    scheduler.update();
    TEST_ASSERT_EQUAL(State::IDLE,scheduler.getCurrentState());
}
void test_scheduler_Weighted_Round_Robin(void) {
    scheduler.setActiveTask(&PerformanceList);
    fakeMillis =126;
    //1ST CYCLE
    scheduler.update();//IDLE->SEND_REQUEST
    scheduler.update();//SEND_REQUEST->WAIT_REPLY
    scheduler.update();//WAIT_REPLY->PARSE_REPLY
    scheduler.update();//PARSE_REPLY->IDLE
    TEST_ASSERT_EQUAL(0,scheduler.getCurrentIndex()); //Index Should be 0 Because we work with WRR and the same PID MUST BE RESENT

    fakeMillis += 126;
    //2ND CYCLE
    scheduler.update();scheduler.update();scheduler.update();scheduler.update();
    TEST_ASSERT_EQUAL(0, scheduler.getCurrentIndex());
    fakeMillis += 126;
    //3RD CYCLE
    scheduler.update(); scheduler.update(); scheduler.update(); scheduler.update();
    // WEIGHT NOW IS 3=TASK.WEIGHT so We send next Pid
    TEST_ASSERT_EQUAL(1, scheduler.getCurrentIndex());
    //4TH CYCLE
    fakeMillis += 126;
    scheduler.update(); scheduler.update(); scheduler.update(); scheduler.update();
    //SPEED WEIGHT =1 SO NEXT TIME WE SENT AGAIN RPM
    TEST_ASSERT_EQUAL(0, scheduler.getCurrentIndex());
}
void test_Scheduler_Time_Based(void) {
    scheduler.setActiveTask(&mockTimeList);
    fakeMillis=101;
    //1ST CYCLE
    scheduler.update();//IDLE->SEND_REQUEST
    scheduler.update();//SEND_REQUEST->WAIT_REPLY
    scheduler.update();//WAIT_REPLY->PARSE_REPLY
    scheduler.update();//PARSE_REPLY->IDLE
    TEST_ASSERT_EQUAL(1, scheduler.getCurrentIndex());
    fakeMillis+=101;
    scheduler.update();
    scheduler.update();
    scheduler.update();
    scheduler.update();
    TEST_ASSERT_EQUAL(0, scheduler.getCurrentIndex());
}
void test_Scheduler_Switch_TaskList_While_SENDING_REQUEST(void) {
    fakeMillis =101;
    scheduler.update();
    TEST_ASSERT_EQUAL(State::SEND_REQUEST, scheduler.getCurrentState());
    scheduler.setActiveTask(&PerformanceList);
    scheduler.update();
    TEST_ASSERT_EQUAL(State::IDLE, scheduler.getCurrentState());
    fakeMillis +=126;
    scheduler.update();
    TEST_ASSERT_EQUAL(State::SEND_REQUEST, scheduler.getCurrentState());
}
void test_scheduler_Empty_TaskList_ZeroTasks(void) {
    TaskList emptyTaskList={ nullptr, TIME_BASED, 0, false };
    scheduler.setActiveTask(&emptyTaskList);
    fakeMillis=2000;
    scheduler.update();
    TEST_ASSERT_EQUAL(State::IDLE, scheduler.getCurrentState());
}
void test_scheduler_Empty_TaskList_nullptr(void) {
    scheduler.setActiveTask(nullptr);
    fakeMillis=2000;
    scheduler.update();
    TEST_ASSERT_EQUAL(State::IDLE, scheduler.getCurrentState());
}
void test_Scheduler_Disconnect_Fallback_And_Return(void) {
    // Βάζουμε την time based λίστα που έχει 2 tasks για να κοπεί στη μέση
    scheduler.setActiveTask(&mockTimeList);

    // 1. Εκτελούμε το 1ο task κανονικά
    fakeMillis = 101;
    scheduler.update();//IDLE->SEND_REQUEST
    scheduler.update();//SEND_REQUEST->WAIT_REPLY
    scheduler.update();//WAIT_REPLY->PARSE_REPLY
    scheduler.update();//PARSE_REPLY->IDLE
    TEST_ASSERT_EQUAL(1, scheduler.getCurrentIndex()); // Προχώρησε στο task 2 (index 1)

    // 2. Πάμε να εκτελέσουμε το 2ο task αλλά κόβεται η σύνδεση
    fakeMillis += 101;
    scheduler.update();//IDLE->SEND_REQUEST

    mock_process_task_state = State::DISCONNECTED; // Προσομοίωση βλάβης
    scheduler.update();//SEND_REQUEST->DISCONNECTED
    TEST_ASSERT_EQUAL(State::DISCONNECTED, scheduler.getCurrentState());

    // 3. Η handleDisconnected πρέπει να βάλει την InitList και να κάνει connect
    mock_connect = State::IDLE; // Προσομοιώνουμε άμεση επιτυχή επανασύνδεση
    scheduler.update();//DISCONNECTED -> IDLE

    // Είμαστε πλέον στην mockInitList. Το index πρέπει να έχει μηδενιστεί
    TEST_ASSERT_EQUAL(State::IDLE, scheduler.getCurrentState());
    TEST_ASSERT_EQUAL(0, scheduler.getCurrentIndex());

    // 4. Τρέχουμε το 1 task της InitList κανονικά
    fakeMillis += 101;
    mock_process_task_state = State::WAIT_REPLY; // Επαναφέρουμε την κανονική συμπεριφορά
    scheduler.update();//IDLE->SEND_REQUEST
    scheduler.update();//SEND_REQUEST->WAIT_REPLY
    scheduler.update();//WAIT_REPLY->PARSE_REPLY

    // 5. Εδώ γίνεται η μαγεία! Η handleParse τελειώνει το Init και κάνει fallback στην παλιά λίστα
    scheduler.update();//PARSE_REPLY->IDLE

    // Πρέπει να έχει επιστρέψει στην mockTimeList και να έχει ξεκινήσει από την αρχή
    TEST_ASSERT_EQUAL(State::IDLE, scheduler.getCurrentState());
    TEST_ASSERT_EQUAL(0, scheduler.getCurrentIndex());

    // 6. Για σιγουριά, τρέχουμε άλλο ένα task για να δούμε ότι όντως είναι η TimeList
    fakeMillis += 101;
    scheduler.update();//IDLE->SEND_REQUEST
    scheduler.update();//SEND_REQUEST->WAIT_REPLY
    scheduler.update();//WAIT_REPLY->PARSE_REPLY
    scheduler.update();//PARSE_REPLY->IDLE

    // Αφού είναι η TimeList, το index πρέπει να πήγε στο 1 (η InitList δεν έχει index 1)
    TEST_ASSERT_EQUAL(1, scheduler.getCurrentIndex());
}
void test_Scheduler_Stress_Test(void) {
    scheduler.setActiveTask(&mockTimeList);

    // Αρχικοποιούμε τον "σπόρο" της τυχαίας γεννήτριας
    srand(12345);

    for (int i = 0; i < 10000; i++) {
        // 1. ΤΥΧΑΙΟ ΑΛΜΑ ΧΡΟΝΟΥ: Από 1ms έως 5000ms!
        // Αυτό τεστάρει αν ο Scheduler αντέχει να χάσει κύκλους.
        fakeMillis += (rand() % 5000) + 1;

        // 2. ΤΥΧΑΙΑ ΑΠΟΣΥΝΔΕΣΗ (Flapping): 10% πιθανότητα να κοπεί ξαφνικά η σύνδεση
        if (rand() % 100 < 10) {
            mock_connection = false;
            mock_process_task_state = State::DISCONNECTED;
        } else {
            mock_connection = true;
            // Αν το σύστημα παλεύει να συνδεθεί, δώσε του 50% πιθανότητα να τα καταφέρει
            if (scheduler.getCurrentState() == State::CONNECTING && (rand() % 100 < 50)) {
                mock_connect = State::IDLE;
            }
        }

        // 3. ΤΥΧΑΙΟ TIMEOUT: 5% πιθανότητα το ELM327 να αργήσει να απαντήσει
        if (scheduler.getCurrentState() == State::WAIT_REPLY && (rand() % 100 < 5)) {
            mock_state = State::WAIT_REPLY; // Το ELM327 δεν έχει έτοιμη την απάντηση
        } else {
            mock_state = State::PARSE_REPLY;
            mock_process_task_state = State::WAIT_REPLY; // Επαναφορά κανονικής συμπεριφοράς
        }

        // --- ΤΟ ΧΤΥΠΗΜΑ ---
        // Εκτελούμε τον Scheduler μέσα σε αυτό το απόλυτο χάος
        scheduler.update();

        // 4. ΕΠΙΒΕΒΑΙΩΣΗ (Assertions)
        // Αν ο κώδικας είχε bug, θα είχε πετάξει CTRL_BREAK_EVENT (Crash) πριν καν φτάσει εδώ.

        // Ελέγχουμε ότι το State δεν έχει πάρει κάποια εντελώς άκυρη τιμή μνήμης
        State current = scheduler.getCurrentState();
        bool isValidState = (current == State::IDLE || current == State::SEND_REQUEST ||
                             current == State::WAIT_REPLY || current == State::PARSE_REPLY ||
                             current == State::ERROR || current == State::DISCONNECTED ||
                             current == State::CONNECTING);

        TEST_ASSERT_TRUE_MESSAGE(isValidState, "CRASH: Το State Machine βγήκε εκτός ελέγχου!");

        // Ελέγχουμε ότι το index δεν έχει ξεφύγει από τα όρια των λιστών μας
        // (Η TimeList έχει 2 tasks, η Init έχει 1, άρα το Index δεν πρέπει να πάει ποτέ πάνω από 1)
        TEST_ASSERT_TRUE_MESSAGE(scheduler.getCurrentIndex() <= 1, "CRASH: Το Index ξέφυγε στο υπερπέραν!");
    }
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_Scheduler_WaitsForIdleTime);
    RUN_TEST(test_Scheduler_Fail_SEND_REQUEST_Soft_Error);
    RUN_TEST(test_Scheduler_Fail_Connection_Hard_Error);
    RUN_TEST(test_scheduler_TimeOutWait);
    RUN_TEST(test_scheduler_Weighted_Round_Robin);
    RUN_TEST(test_Scheduler_Time_Based);
    RUN_TEST(test_Scheduler_Switch_TaskList_While_SENDING_REQUEST);
    RUN_TEST(test_scheduler_Empty_TaskList_ZeroTasks);
    RUN_TEST(test_scheduler_Empty_TaskList_nullptr);
    RUN_TEST(test_Scheduler_Disconnect_Fallback_And_Return);
    RUN_TEST(test_Scheduler_Stress_Test);
    return UNITY_END();
}