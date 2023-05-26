#include "complex_numbers.h"
#include <math.h>

const xiy xiy_one = { 1, 0 };
const xiy xiy_zero = { 0, 0 };

xiy xiy_mul(xiy a, xiy b) {
    xiy c = { a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x };
    return c;
}

xiy xiy_add(xiy a, xiy b) {
    xiy c = { a.x + b.x, a.y + b.y };
    return c;
}

double xiy_len(xiy c) {
    return sqrt(c.x * c.x + c.y * c.y);
}
