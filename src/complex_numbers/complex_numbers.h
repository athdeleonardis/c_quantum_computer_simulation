#ifndef COMPLEX_NUMBERS
#define COMPLEX_NUMBERS

#ifndef COMPLEX_NUMBERS_PRECISION
    #define COMPLEX_NUMBERS_PRECISION double
#endif

typedef struct xiy xiy;

struct xiy {
    COMPLEX_NUMBERS_PRECISION x;
    COMPLEX_NUMBERS_PRECISION y;
};

/**
 * @brief The complex number 1.
 */
extern const xiy xiy_one;

/**
 * @brief The complex number 0.
 */
extern const xiy xiy_zero;

/**
 * @brief The complex number i.
 */
extern const xiy xiy_i;

/**
 * @brief Returns the complex number represented by an angle rotated anti-clockwise about the origin.
 * 
 * @param theta The angle to rotate anti-clockwise about the origin.
 */
xiy xiy_from_angle(double theta);

/**
 * @brief Returns the multiplication of two complex numbers.
 * 
 * @param a The first complex number to be multiplied.
 * @param b The second complex number to be multiplied.
 */
xiy xiy_mul(xiy a, xiy b);

/**
 * @brief Returns the addition of two complex numbers.
 * 
 * @param a The first complex number to be added.
 * @param b The second complex number to be added.
 */
xiy xiy_add(xiy a, xiy b);

/**
 * @brief Returns the length of a complex number.
 * 
 * @param z The complex number to return the length of.
 */
COMPLEX_NUMBERS_PRECISION xiy_len(xiy z);

/**
 * @brief Returns the multiplication of a complex number by a scalar factor.
 * 
 * @param z The complex number.
 * @param c The scalar.
 */
xiy xiy_mul_s(xiy z, COMPLEX_NUMBERS_PRECISION c);

/**
 * @brief Prints a complex number to the console.
 * 
 * @param z The complex number to be printed.
 */
void xiy_print(xiy z);

#endif
