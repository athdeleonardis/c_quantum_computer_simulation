#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../src/complex_numbers/complex_numbers.h"

#define TEST_MIN -10
#define TEST_MAX 10
#define EPSILON 1e-9

int xiy_equals(xiy a, xiy b) {
    return fabs(a.x-b.x) < EPSILON && fabs(a.y-b.y) < EPSILON;
}

int sign(int x) {
    if (x == 0)
        return 0;
    if (x > 0)
        return 1;
    return -1;
}

int main(int argc, char *argv[]) {
    // Test addition
    for (int i = TEST_MIN; i < TEST_MAX; i++) {
        for (int j = TEST_MIN; j < TEST_MAX; j++) {
            for (int m = TEST_MIN; m < TEST_MAX; m++) {
                for (int n = TEST_MIN; n < TEST_MAX; n++) {
                    xiy a = { .x=i, .y=j };
                    xiy b = { .x=m, .y=n };
                    xiy r = { .x=i+m, .y=j+n };
                    xiy r_test = xiy_add(a, b);
                    
                    if (!xiy_equals(r, r_test)) {
                        printf("TEST -- complex_numbers -- FAILED -- Addition: Expected {%i,%i}+{%i,%i}={%lf,%lf} but got {%lf,%lf}.\n", i, j, m, n, r.x, r.y, r_test.x, r_test.y);
                        exit(0);
                    }
                }
            }
        }
    }

    // Test multiplication of constants
    int num_constants = 27;
    xiy constants[] = {
        xiy_zero, xiy_zero, xiy_zero,
        xiy_one, xiy_zero, xiy_zero,
        xiy_i, xiy_zero, xiy_zero,
        xiy_zero, xiy_one, xiy_zero,
        xiy_one, xiy_one, xiy_one,
        xiy_i, xiy_one, xiy_i,
        xiy_zero, xiy_i, xiy_zero,
        xiy_one, xiy_i, xiy_i,
        xiy_i, xiy_i, xiy_mul_s(xiy_one, -1)
    };
    for (int i = 0; i < 27; i += 3) {
        xiy a = constants[i];
        xiy b = constants[i+1];
        xiy r = constants[i+2];
        xiy r_test = xiy_mul(a, b);

        if (!xiy_equals(r, r_test)) {
            printf("TEST -- complex_numbers -- FAILED -- Multiplication of constants: Expected {%lf,%lf}*{%lf,%lf}={%lf,%lf} but got {%lf,%lf}.\n", a.x, a.y, b.x, b.y, r.x, r.y, r_test.x, r_test.y);
            exit(0);
        }
    }

    // Test multiplication
    for (int i = TEST_MIN; i < TEST_MAX; i++) {
        for (int j = TEST_MIN; j < TEST_MAX; j++) {
            for (int m = TEST_MIN; m < TEST_MAX; m++) {
                for (int n = TEST_MIN; n < TEST_MAX; n++) {
                    xiy a = { .x=i, .y=j };
                    xiy b = { .x=m, .y=n };
                    xiy r = { .x=(i*m-j*n), .y=(i*n+j*m) };
                    xiy r_test = xiy_mul(a, b);
                    
                    if (!xiy_equals(r, r_test)) {
                        printf("TEST -- complex_numbers -- FAILED -- Multiplication: Expected {%i,%i}*{%i,%i}={%lf,%lf} but got {%lf,%lf}.\n", i, j, m, n, r.x, r.y, r_test.x, r_test.y);
                        exit(0);
                    }
                }
            }
        }
    }

    // Test multiplication by scalar
    for (int i = TEST_MIN; i < TEST_MAX; i++) {
        for (int j = TEST_MIN; j < TEST_MAX; j++) {
            for (int k = TEST_MIN; k < TEST_MAX; k++) {
                xiy z = { .x=i, .y=j };
                xiy r = { .x=k*i, .y=k*j };
                xiy r_test = xiy_mul_s(z, k);

                if (!xiy_equals(r, r_test)) {
                    printf("TEST -- complex_numbers -- FAILED -- Multiplication by scalar: Expected {%lf,%lf}*%i={%lf,%lf} but got {%lf,%lf}.\n", z.x, z.y, k, r.x, r.y, r_test.x, r_test.y);
                    exit(0);
                }
            }
        }
    }

    // Test angle initialization
    for (int i = -2; i < 3; i++) {
        double angle = i * M_PI_2;
        int rx = 1-i*sign(i);
        int ry = (i % 2);
        xiy r = { .x=rx, .y=ry };
        xiy r_test = xiy_from_angle(angle);

        if (!xiy_equals(r, r_test)) {
            printf("TEST -- complex_numbers -- FAILED -- Angle initialization: Expected xiy_from_angle(%i * pi / 2)={%lf,%lf} but got {%lf,%lf}.\n", i, r.x, r.y, r_test.x, r_test.y);
            exit(0);
        }
    }

    printf("TEST -- complex_numbers -- SUCCESS\n");
}
