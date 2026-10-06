    //
    // Created by User on 1/7/2026.
    //

#include "CommunicationStates.h"
#include "Elm327Controller.h"
#include "Scheduler.h"

#include "PidManager.h"
#include "StringParser.h"
    Scheduler::MillisProvider Scheduler::getMillis = nullptr;
    void Scheduler::setActiveTask(const TaskList* taskList) {
        currentTaskList=taskList;
        currentWeight=0;
        currentIndex=0;
        lastTime=getMillis();
        for(unsigned long & i : lastRunTime) {
            i = 0;
        }
        if (Elm327Controller::isConnected()){
            currentState=State::IDLE;
        }else {
            currentState=State::DISCONNECTED;
        }
    }
    void Scheduler::handleConnection(){
        if (getMillis()-lastTime>3000) {
            currentState=Elm327Controller::Connect();
            if (currentState==State::CONNECTING) {
                lastTime=getMillis();
            }
        }
    }
void Scheduler::handleIdle()
    {
        uint8_t start = currentIndex;
        do
        {
            if (isReady())
            {
                currentState = State::SEND_REQUEST;
                return;
            }

            currentIndex++;
            if(currentIndex >= currentTaskList->taskCount)
                currentIndex = 0;
        } while(currentIndex != start);
    }
    void Scheduler::handleRequest() {
        currentState=Elm327Controller::ProcessTask(currentTask->TaskId);//nullptr exception is checked in update
        if (currentState==State::WAIT_REPLY) {
            startTime=getMillis();
            lastTime=getMillis();
            lastRunTime[currentIndex] = getMillis();
        }
    }

    void Scheduler::handleReply() {
        if (getMillis()-startTime>OBD_TIMEOUT_MS) {
            currentState=State::ERROR;

        }else {
            currentState=Elm327Controller::getReply();//if reply is complete state==PARSE ELSE WAIT
        }
    }
    void Scheduler::handleParse(){
        StringParser::processArray(Elm327Controller::getBuffer());
        if (currentTaskList->scheduler==WEIGHTED_RR) {
            currentWeight++;
            if (currentWeight>=currentTask->weight) {
                currentWeight=0;
                currentIndex++;
            }
        }else {
            currentIndex++;
        }
        if (currentIndex >= currentTaskList->taskCount) {

            // 1. Ελέγχουμε αν τελειώσαμε την InitList ΚΑΙ αν έχουμε αποθηκεύσει προηγούμενη λίστα
            if (currentTaskList->isInit && previousTaskList != nullptr) {
                setActiveTask(previousTaskList); //We return to normal list
                previousTaskList = nullptr;      //We dont need to keep init as Previous Task
                return; //so we dont get to IDLE and finish Init
            }
            currentIndex = 0; //if its not init it loops

        }
        currentState = State::IDLE;
    }
    void Scheduler::handleError() {
        currentWeight=0;
        currentIndex++;
        if(currentIndex>=currentTaskList->taskCount) {
                currentIndex=0;
        }
        currentState = State::IDLE;
    }
    void Scheduler::handleDisconnected() {
        // to prevent saving InitList as Previous if it disconnects during Init
        if (!currentTaskList->isInit) {
            previousTaskList = currentTaskList;
        }
        if (fallbackTaskList!=nullptr) {
            setActiveTask(fallbackTaskList);
        }
        //State::Idle if it is connected State::Connecting If its not connected yet
        currentState = Elm327Controller::Connect();
        if (currentState==State::CONNECTING) {
            lastTime=getMillis();
        }
    }
    inline bool Scheduler::isReady() const {
        const Task& task=currentTaskList->task[currentIndex];
        return (getMillis() - lastRunTime[currentIndex]) >= task.wait;
    }
    void Scheduler::update() {
        if (currentTaskList==nullptr || currentTaskList->taskCount==0)return;
        currentTask=&currentTaskList->task[currentIndex];
        switch (currentState) {
            case State::CONNECTING : handleConnection(); break;
            case State::IDLE: handleIdle(); break;
            case State::SEND_REQUEST:handleRequest(); break;
            case State::WAIT_REPLY: handleReply(); break;
            case State::PARSE_REPLY: handleParse(); break;
            case State::ERROR:handleError(); break;
            case State::DISCONNECTED :handleDisconnected(); break;
        }
    }
    State Scheduler::getCurrentState() const {
        return currentState;
    }
    uint8_t Scheduler::getCurrentIndex() const {
        return currentIndex;
    }
void Scheduler::setFallbackTask(const TaskList* taskList) {
        fallbackTaskList=taskList;
    }
