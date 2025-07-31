#ifndef __MOTOR_H
#define __MOTOR_H

#include <cstdint>

#include "ti_msp_dl_config.h"
#include "encoders.h"
#include "PID.hpp"

// 限制值
#define __CONSTRUCT_VALUE(x,xmin,xmax) (x<xmin)?xmin:((x>xmax)?xmax:x)

class Motor
{
    public:
        Motor(const PID &pid,const EncodersID_EnumTypedef id,const float ratio) : 
        pid(pid){
            encoderID = id;
            gearRatio = ratio;
        };
        void setExpectedSpeed(float rpm)
        {
            expectedRPM = rpm;
            pid.SetTarget(expectedRPM);
        }
        // 更新占空比，这个应当定时被调用
        inline float updateDutyCycle(float dt)
        {
            uint16_t currentCounter = Encoders_getCounter(encoderID);
            int16_t diffCounter = currentCounter - prevCounter;
            float currentRPM = (float)(diffCounter) / gearRatio / dt * 60.0;
            float feedback = pid.calc(currentRPM);
            prevCounter = currentCounter;
            return __CONSTRUCT_VALUE(feedback,-1,1);
        }
    private:
        PID pid; 
        uint16_t prevCounter;
        float expectedRPM;
        float gearRatio;
        EncodersID_EnumTypedef encoderID;
};

#endif