//
// Created by User on 28/7/2026.
//

#ifndef OBD_AUTOMOTIVE_DISPLAY_DATASTORAGE_H
#define OBD_AUTOMOTIVE_DISPLAY_DATASTORAGE_H


class DataStorage {

    static float rpm;
    static float speed;
    static float coolantTemp;
    static float engineLoad;
    static float throttle;
    static float mafFlowRate;
    static float ignition;
    static float intakeAirTemp;
    static float mapSensor;
    static float moduleVoltage;
    static float shortFuelTrim;
    static float longFuelTrim;
    static float distanceWithMalfunction;
    static float catalystTemp;
    static float barometricPres;
    static float engineRunTime;

public:
    static void setRpm(float val);
    static void setSpeed(float val);
    static void setCoolantTemp(float val);
    static void setEngineLoad(float val);
    static void setThrottle(float val);
    static void setMafFlowRate(float val);
    static void setIgnition(float val);
    static void setIntakeAirTemp(float val);
    static void setMapSensor(float val);
    static void setModuleVoltage(float val);
    static void setShortFuelTrim(float val);
    static void setLongFuelTrim(float val);
    static void setDistanceWithMalfunction(float val);
    static void setCatalystTemp(float val);
    static void setBarometricPres(float val);
    static void setEngineRunTime(float val);
    static float getRpm();
    static float getSpeed();
    static float getCoolantTemp();
    static float getEngineLoad();
    static float getThrottle();
    static float getMafFlowRate();
    static float getIgnition();
    static float getIntakeAirTemp();
    static float getMapSensor();
    static float getModuleVoltage();
    static float getShortFuelTrim();
    static float getLongFuelTrim();
    static float getDistanceWithMalfunction();
    static float getCatalystTemp();
    static float getBarometricPres();
    static float getEngineRunTime();
};
#endif //OBD_AUTOMOTIVE_DISPLAY_DATASTORAGE_H
