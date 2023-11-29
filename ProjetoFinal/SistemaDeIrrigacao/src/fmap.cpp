#include "fmap.h"

float fmap(float x, long inMax, long inMin, long outMax, long outMin) {
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
