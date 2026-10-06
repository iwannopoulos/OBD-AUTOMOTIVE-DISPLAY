//
// Created by User on 28/6/2026.
//

#ifndef OBD_AUTOMOTIVE_DISPLAY_SCREEN_PID_CONFIG_H
#define OBD_AUTOMOTIVE_DISPLAY_SCREEN_PID_CONFIG_H
#include <cstdint>
/**
 * This Header File Is Used To Reduce the Magic Numbers Used
 * Also It Contains Task TaskList
 * Task is a struct that contains the waitTime needed between requests ,the TaskId witch is a Number ,and the weight of a task that is used for weighted round robin
 * All the Bellow were created in such way that they consume :
 * Performance: 8 bytes Elm32Init:20 bytes Data : 64 bytes PerformanceList : 8 bytes DataList (struct): 8 bytes Elm32List (struct): 8 bytes
 * total 116 bytes in flash
*/

constexpr unsigned long OBD_TIMEOUT_MS = 150;//4 bytes

enum ObdCommand: uint8_t {
    Rpm=0x0C,
    Speed=0x0D,
    EngineLoad=0x04,
    CoolantTemp=0x05,
    ShortFuelTrim=0x06,
    LongFuelTrim=0x07,
    MapSensor=0x0B,
    Ignition=0x0E,
    IntakeAirTemp=0x0F,
    MafFlowRate=0x10,
    Throttle=0x11,
    EngineRunTime=0x1F,
    DistanceWithMalfunction=0x21,
    BarometricPres=0x33,
    CatalystTemp=0x3C,
    ModuleVoltage=0x42,

    InitATZ=0x80,
    EchoOff=0x81,
    HeadersOff=0x82,
    AutoProtocol=0x83,
    LineFeedsOn=0x84

};//1 byte

struct Task {
    uint16_t wait; //2 bytes
    uint8_t TaskId;//1 byte
    uint8_t weight; //1 byte
};//4 bytes
enum SchedulerType : uint8_t {
    WEIGHTED_RR=0,
    TIME_BASED=1,
};//1byte
enum refreshRate: uint16_t {
    REF_FAST=80,
    REF_HIGH=100,
    REF_MEDIUM=200,
    REF_LOW=1000,
    REF_STATIC=5000,
  };
struct TaskList {
    const Task* task; //4 byte
    SchedulerType scheduler; //1 byte
    uint8_t taskCount; //1 byte
    bool isInit;//1 byte
};//7+(1 padding)= 8  bytes


constexpr Task Performance[]={
    {125,Rpm,3},
    {125,Speed,1}
};//8bytes

constexpr Task Elm32Init[]={
    {2000,InitATZ, 0},  // ATZ   (Reset - Θέλει χρόνο, άρα 2000ms)
    {500,EchoOff,   0},  // ATE0  (Echo Off - 500ms)
    {500,HeadersOff,   0},  // ATH0  (Headers Off - 500ms)
    {500 ,AutoProtocol,   0},  // ATSP0 (Auto Protocol - 500ms)
    {500,LineFeedsOn,   0},  // ATL1  (Linefeeds On - 500ms)}
};//20 bytes
constexpr Task Data[]={
    {REF_FAST,   Rpm, 0},
    {   REF_FAST,   Speed, 0},
    {REF_HIGH,   EngineLoad, 0},
    {REF_HIGH,   Throttle, 0},
    {REF_MEDIUM, MapSensor, 0},
    {REF_MEDIUM, Ignition, 0},
    {REF_MEDIUM, MafFlowRate, 0},
    {REF_LOW,    CoolantTemp, 0},
    {REF_LOW,    ShortFuelTrim, 0},
    {REF_LOW,    LongFuelTrim, 0},
    {REF_LOW,    IntakeAirTemp, 0},
    {REF_LOW,    ModuleVoltage, 0},
    {REF_STATIC, EngineRunTime, 0},
    {REF_STATIC, DistanceWithMalfunction, 0},
    {REF_STATIC, BarometricPres, 0},
    {REF_STATIC, CatalystTemp, 0}
};//64 bytes

constexpr TaskList PerformanceList{
    .task=&Performance[0],//4 byte (pointer)
    .scheduler=WEIGHTED_RR,//1 byte
    .taskCount=2,//1 byte
    .isInit=false,//1 byte
}; // 7 + (1 padding) = 8 bytes
constexpr TaskList DataList{
    .task=&Data[0],//4 byte (pointer)
    .scheduler=TIME_BASED,//1 byte
    .taskCount=16,//1 byte
    .isInit=false,//1 byte
};//6+(2 padding)=8 bytes
constexpr TaskList Elm32List{
    .task=&Elm32Init[0],//4 byte (pointer)
    .scheduler=TIME_BASED,//1 byte
    .taskCount=5, // 1 byte
    .isInit=true,//1 byte
}; //7+(1 padding) = 8 byte


#endif //OBD_AUTOMOTIVE_DISPLAY_SCREEN_PID_CONFIG_H
