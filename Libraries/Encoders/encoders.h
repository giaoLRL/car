#ifndef __ENCODERS_H
#define __ENCODERS_H

#include "ti_msp_dl_config.h"

#define __STATIC_INLINE static inline

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    ENCODER_ID_0 = 0,
    ENCODER_ID_1,
    ENCODER_ID_2,
    ENCODER_ID_3,
    ENCODER_ID_4,
    ENCODER_ID_5,
    ENCODER_ID_6,
    ENCODER_ID_7,
} EncodersID_EnumTypedef;

extern uint16_t Encoders_counters[8];
void Encoders_resetAllCounters();
__STATIC_INLINE void Encoders_increaseCounter(EncodersID_EnumTypedef id, int16_t x)
{
    Encoders_counters[id] += x;
}
__STATIC_INLINE void Encoders_resetCounter(EncodersID_EnumTypedef id)
{
    Encoders_counters[id] = 0x00000000u;
}
__STATIC_INLINE uint16_t Encoders_getCounter(EncodersID_EnumTypedef id)
{
    return Encoders_counters[id];
}


#ifdef __cplusplus
}
#endif

#endif