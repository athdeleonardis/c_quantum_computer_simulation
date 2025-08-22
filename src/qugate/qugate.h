#ifndef QUGATE
#define QUGATE

#include "../complex_numbers/complex_numbers.h"

/**
 * @brief Initializes the input matrix to be the 'Identity' gate.
 * 
 * @param mat_2x2 The 2x2 matrix to have its values initialized.
 */
void qugate_i(xiy *mat_2x2);

/**
 * @brief Initializes the input matrix to be the 'Pauli X' gate. AKA 'Not' gate.
 * 
 * @param mat_2x2 The 2x2 matrix to have its values initialized.
 */
void qugate_x(xiy *mat_2x2);

/**
 * @brief Initializes the input matrix to be the 'Pauli Y' gate.
 * 
 * @param mat_2x2 The 2x2 matrix to have its values initialized.
 */
void qugate_y(xiy *mat_2x2);

/**
 * @brief Initializes the input matrix to be the 'Pauli Z' gate.
 * 
 * @param mat_2x2 The 2x2 matrix to have its values initialized.
 */
void qugate_z(xiy *mat_2x2);

/**
 * @brief Initializes the input matrix to be the 'Hadamard' gate.
 * 
 * @param mat_2x2 The 2x2 matrix to have its values initialized.
 */
void qugate_h(xiy *mat_2x2);

/**
 * @brief Intializes the input matrix to be the 'Phase' gate.
 * 
 * @param mat_2x2 The 2x2 matrix to have its values initialized.
 * @param angle The angle of the phase.
 */
void qugate_p(xiy *mat_2x2, double angle);

/**
 * @brief Initializes the input matrix to be the 'S' gate. AKA square root of Z gate, or phase of pi/2 gate.
 * 
 * @param mat_2x2 The 2x2 matrix to have its values initialized.
 */
void qugate_s(xiy *mat_2x2);

/**
 * @brief Initializes the input matrix to be the 'T' gate. AKA the fourth root of Z gate, or the phase of pi/4 gate.
 * 
 * @param mat_2x2 The 2x2 matrix to have its values initialized.
 */
void qugate_t(xiy *mat_2x2);

/**
 * @brief Initializes the input matrix to be the 'S dagger' gate. AKA the hermitian conjugate of the S gate.
 * 
 * @param mat_2x2 The 2x2 matrix to have its values initialized.
 */
void qugate_sd(xiy *mat_2x2);

/**
 * @brief Initializes the input matrix to be the 'T dagger' gate. AKA the hermitian cojugate of the T gate.
 * 
 * @param mat_2x2 The 2x2 matrix to have its values initialized.
 */
void qugate_td(xiy *mat_2x2);

/**
 * @brief Initializes the input matrix to be the 'Controlled X' gate. AKA 'Controlled Not' gate. The first qubit is the control. The second qubit is the target.
 * 
 * @param mat_4x4 The 4x4 matrix to have its values initialized.
 */
void qugate_cx(xiy *mat_4x4);

/**
 * @brief Initializes the input matrix to be the 'Controlled Z' gate. The first qubit is the control. The second qubit is the target.
 * 
 * @param mat_4x4 The 4x4 matrix to have its values initialized.
 */
void qugate_cz(xiy *mat_4x4);

/**
 * @brief Initializes the input matrix to be the 'Controlled U' gate. U is some undefined gate.
 * 
 * @param mat_4x4 The 4x4 matrix to have its values initialized.
 * @param mat_2x2 The 2x2 matrix representing the gate U.
 */
void qugate_cu(xiy *mat_4x4, xiy *mat_2x2);

/**
 * @brief Initializes the input matrix to be the 'Swap' gate. Swaps the first qubit with the second.
 * 
 * @param mat_4x4 The 4x4 matrix to have its values initialized.
 */
void qugate_swap(xiy *mat_4x4);

#endif
