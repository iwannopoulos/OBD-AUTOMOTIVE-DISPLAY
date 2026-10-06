//
// Created by User on 1/7/2026.
//

#ifndef OBD_AUTOMOTIVE_DISPLAY_SHEDULER_H
#define OBD_AUTOMOTIVE_DISPLAY_SHEDULER_H
#include "CommunicationStates.h"
#include "ScreenPidConfig.h"

class Scheduler {
    public:
    typedef unsigned long (*MillisProvider)();
    static MillisProvider getMillis;
    void setActiveTask(const TaskList* taskList);
    void update();
    void setFallbackTask(const TaskList* taskList);
    State getCurrentState() const;
    uint8_t getCurrentIndex() const;
private:
    unsigned long lastRunTime[16];
    bool isReady() const;
    unsigned long startTime=0;
    unsigned long lastTime=0;
    State currentState=State::IDLE;
    uint8_t currentIndex=0;
    uint8_t currentWeight=0;
    const TaskList *currentTaskList = nullptr;
    const TaskList* fallbackTaskList = nullptr;
    const TaskList* previousTaskList = nullptr;
    const Task *currentTask = nullptr;
    void handleConnection();
    void handleIdle();
    void handleRequest();
    void handleReply();
    void handleError();
    void handleParse();
    void handleDisconnected();
};
#endif //OBD_AUTOMOTIVE_DISPLAY_SHEDULER_H
