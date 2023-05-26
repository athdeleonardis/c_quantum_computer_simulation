#ifndef COMPLEX_MATRICES
#define COMPLEX_MATRICES

#include "complex_numbers.h"

typedef struct xiym xiym;
typedef xiy (*xiym_getter)(xiym *m, int x, int y);

void xiym_set(xiym *m, xiy c, int x, int y);
xiy xiym_get(xiym *m, int x, int y);
void xiym_mul_i(xiym *a, xiym *b, xiym *out);
xiym *xiym_tensor_prod(xiym *a, xiym *b);
xiym xiym_identity(int length);

struct xiym {
    int length;
    xiy *values;
    xiym_getter getter;
};

xiy xiy_matrix_getter_default(xiym *m, int x, int y);
xiy xiy_matrix_getter_identity(xiym *m, int x, int y);

#endif
