#include "funcs.h"

float fmap(float x, long inMin, long inMax, long outMin, long outMax) {
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
