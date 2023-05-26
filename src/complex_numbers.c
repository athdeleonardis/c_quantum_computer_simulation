#include <math.h>
#include <stdio.h>
#include "complex_numbers.h"

const xiy xiy_one = { 1, 0 };
const xiy xiy_zero = { 0, 0 };
const xiy xiy_i = { 0, 1 };

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

xiy xiy_mul_s(xiy a, double c) {
    xiy b = { a.x * c, b.x * c };
    return b;
}

void xiy_print(xiy c) {
    printf("xiy: %f %f", c.x, c.y);
}
