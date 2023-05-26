#include <stdio.h>
#include "../complex_numbers.h"
#include "../complex_matrices.h"

void xiy_print(xiy c) {
    printf("xiy: %f %f", c.x, c.y);
}

void xiym_print(xiym m) {
    printf("xiym:\n");
    xiy_print(xiym_get(&m, 0, 0));
    printf(" ");
    xiy_print(xiym_get(&m, 0, 1));
    printf("\n");
    xiy_print(xiym_get(&m, 1, 0));
    printf(" ");
    xiy_print(xiym_get(&m, 1, 1));
    printf("\n");
}

int main(int argc, char *argv[]) {
    printf("Complex numbers:\n");
    xiy i = { 0, 1 };
    xiy j = i;
    for (int k = 0; k < 3; k++) {
        xiy_print(j);
        printf("\n");
        j = xiy_mul(j, i);
    }
    xiy_print(j);
    printf("\n");

    printf("Complex matrices:\n");
    xiym id2x2 = xiym_identity(2);
    xiy val[] = { xiy_zero, xiy_one, xiy_one, xiy_zero };
    xiym X2x2 = { 2, val, xiy_matrix_getter_default };
    xiy res[] = { xiy_zero, xiy_zero, xiy_zero, xiy_zero };
    xiym fin = { 2, res, xiy_matrix_getter_default };
    xiym_mul_i(&id2x2, &X2x2, &fin);
    xiym_print(id2x2);
    xiym_print(X2x2);
    xiym_print(fin);
}
