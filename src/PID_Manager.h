//
// Created by User on 23/6/2026.
//

#ifndef OBD_AUTOMOTIVE_DISPLAY_PID_MANAGER_H
#define OBD_AUTOMOTIVE_DISPLAY_PID_MANAGER_H
#include <cstdint>
class PID_Manager {
    public:
    PID_Manager();
    static float processData(uint8_t pid,uint8_t A,uint8_t B);
};
#endif //OBD_AUTOMOTIVE_DISPLAY_PID_MANAGER_H
