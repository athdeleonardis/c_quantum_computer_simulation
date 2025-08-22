#include <math.h>
#include <stdio.h>
#include "./complex_numbers.h"

const xiy xiy_one = { 1, 0 };
const xiy xiy_zero = { 0, 0 };
const xiy xiy_i = { 0, 1 };

xiy xiy_from_angle(COMPLEX_NUMBERS_PRECISION theta) {
    xiy z = { .x=cos(theta), .y=sin(theta) };
    return z;
}

xiy xiy_mul(xiy a, xiy b) {
    xiy c = { a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x };
    return c;
}

xiy xiy_add(xiy a, xiy b) {
    xiy c = { a.x + b.x, a.y + b.y };
    return c;
}

xiy xiy_mul_s(xiy z, COMPLEX_NUMBERS_PRECISION c) {
    xiy w = { z.x * c, z.y * c };
    return w;
}

COMPLEX_NUMBERS_PRECISION xiy_len(xiy z) {
    return sqrt(z.x * z.x + z.y * z.y);
}

void xiy_print(xiy z) {
    printf("xiy: %f %f", z.x, z.y);
}
