#ifndef COMPLEX_NUMBERS
#define COMPLEX_NUMBERS

typedef struct xiy  xiy;

xiy xiy_mul(xiy a, xiy b);
xiy xiy_add(xiy a, xiy b);
double xiy_len(xiy c);

struct xiy {
    double x;
    double y;
};

extern const xiy xiy_one;
extern const xiy xiy_zero;

#endif
