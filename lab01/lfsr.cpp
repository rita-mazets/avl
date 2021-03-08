#include <iostream>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    *reg = (*reg >> 1) | ((*reg ^ (*reg >> 2) ^ (*reg >> 3) ^ (*reg >> 5))<< 15);
}

