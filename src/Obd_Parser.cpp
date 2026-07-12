    //
    // Created by User on 23/6/2026.
    //


    #include "Obd_Parser.h"
         float Obd_Parser::parseRpm(const uint8_t A,const uint8_t B) {
            return (A*256.0f+B)/4.0f;
        }
         float Obd_Parser::parseSpeed(const uint8_t A) {
            return static_cast<float>(A);
        }
        float Obd_Parser::parseTemperature(const uint8_t A) {
            return static_cast<float>(A-40);
        }
        float Obd_Parser::parseEngineLoad(const uint8_t A) {
            return (A/255.0f)*100.0f;
        }
        float Obd_Parser::parseThrottle(const uint8_t A) {
            return (A/255.0f)*100.0f;
        }
        float Obd_Parser::parseMafFlowRate(const uint8_t A,const uint8_t B) {
            return (A*256.0f+B)/100.0f;
        }
        float Obd_Parser::parseIgnition(const uint8_t A) {
            return  (A/2.0f)-64.0f;
        }
        float Obd_Parser::parseIntakeAirTemp(uint8_t A) {
             return static_cast<float>(A-40);
         }
        float Obd_Parser::parseMapSensor(uint8_t A) {
            return static_cast<float>(A);
        }
        float Obd_Parser::parseModuleVoltage(uint8_t A,uint8_t B) {
              return (A*256.0f+B)/1000.0f;
         }
        float Obd_Parser::parseShortFuelTrim(uint8_t A) {
            return (A/1.28f)-100;
        }
        float Obd_Parser::parseLongFuelTrim(uint8_t A) {
             return (A/1.28f)-100;
         }

    float Obd_Parser::parseDistanceWithMalfunction(uint8_t A, uint8_t B) {
        return (A*256.0f +B);
    }

    float Obd_Parser::parseCatalystTemp(uint8_t A, uint8_t B) {
        return ((A*256.0f +B)/10.0f)-40.0f;
    }

    float Obd_Parser::parseBarometricPres(uint8_t A) {
        return static_cast<float>(A);
    }

    float Obd_Parser::parseEngineRunTime(uint8_t A, uint8_t B) {
        return (A*256.0f+B);
    }



