#include "encoders.h"

uint16_t Encoders_counters[8];

void Encoders_resetAllCounters()
{
    uint8_t i;
    for(i=0;i<8;i++)
    {
        Encoders_resetCounter(i);
    }
}
