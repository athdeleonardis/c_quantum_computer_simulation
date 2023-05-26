#include <stdio.h>
#include "../complex_numbers.h"
#include "../complex_matrices.h"

void xiy_print(xiy c) {
    printf("xiy: %f %f", c.x, c.y);
}

void xiym_print(xiym *m) {
    printf("xiym:\n");
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            xiy_print(xiym_get(m, j, i));
            printf(" ");
        }
        printf("\n");
    }
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

    printf("Complex matrix multiplication:\n");
    xiym id2x2 = xiym_identity(2);
    xiy val[] = { xiy_zero, xiy_one, xiy_one, xiy_zero };
    xiym X2x2 = { 2, 2, val, xiym_getter_default };
    xiy res[] = { xiy_zero, xiy_zero, xiy_zero, xiy_zero };
    xiym fin = { 2, 2, res, xiym_getter_default };
    xiym_mul_i(&id2x2, &X2x2, &fin);
    xiym_print(&id2x2);
    xiym_print(&X2x2);
    xiym_print(&fin);

    printf("Complex matrix tensor product:\n");
    xiym id3x3 = xiym_identity(3);
    xiy res0[36];
    xiym fin0 = { 6, 6, res0, xiym_getter_default };
    xiym_tensor_prod_i(&id3x3, &X2x2, &fin0);
    xiym_print(&fin0);
    xiym_tensor_prod_i(&X2x2, &id3x3, &fin0);
    xiym_print(&fin0);
}
