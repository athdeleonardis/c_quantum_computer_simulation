#include "../qubits/qubits.h"

/**
 * @brief A function type for qugates with one target.
 * 
 * @param qs The qubits for the function to act upon.
 * @param q The target qubit.
 */
typedef void (*qugate_func_u)(qubits *qs, int q);

/**
 * @brief A function type for qugates with a control qubit and target qubit
 * 
 * @param qs The qubits for the function to act upon.
 * @param qc The control qubit.
 * @param qt The target qubit.
 */
typedef void (*qugate_func_cu)(qubits *qs, int qc, int qt);

/**
 * @brief A function type for qugates with multiple control qubits and one target qubit.
 * 
 * @param qs The qubits for the function to act upon.
 * @param n_controls The number of control qubits.
 * @param inputs The array of inputs (length 'n_controls+1'). The first 'n_controls' inputs are the controls, the last input is the target.
 */
typedef void (*qugate_func_mcu)(qubits *qs, int n_controls, int *inputs);

/**
 * @brief A function type for qugates with multiple control qubits and multiple target qubits.
 * 
 * @param qs The qubits for the function to act upon.
 * @param n_controls The number of control qubits.
 * @param n_targets The number of target qubits.
 * @param inputs The array of inputs (length 'n_controls=n_targets'). The first 'n_controls' inputs are the controls, and the next 'n_targets' inputs are the targets.
 */
typedef void (*qugate_func_mcmu)(qubits *qs, int n_controls, int n_targets, int *inputs);

/**
 * @brief A function that applies the 'Pauli X' gate.
 * 
 * @param qs The qubits for the function to act upon.
 * @param q The target qubit.
 */
void qugate_func_x(qubits *qs, int q);

/**
 * @brief A function that applies the 'Pauli Y' gate. AKA 'Not' gate.
 * 
 * @param qs The qubits for the function to act upon.
 * @param q The target qubit.
 */
void qugate_func_y(qubits *qs, int q);

/**
 * @brief A function that applies the 'Pauli Z' gate.
 * 
 * @param qs The qubits for the function to act upon.
 * @param q The target qubit.
 */
void qugate_func_z(qubits *qs, int q);

/**
 * @brief A function that applies the 'Controlled X' gate. AKA 'Controlled Not'. Applies the 'X' gate to the target qubit if the control qubit is 1.
 * 
 * @param qs The qubits for the function to act upon.
 * @param qc The control qubit.
 * @param qt The target qubit.
 */
void qugate_func_cx(qubits *qs, int qc, int qt);

/**
 * @brief A function that applies the 'Controlled Y' gate. Applies the 'Y' gate to the target qubit if the control qubit is 1.
 * 
 * @param qs The qubits for the function to act upon.
 * @param qc The control qubit.
 * @param qt The target qubit.
 */
void qugate_func_cy(qubits *qs, int qc, int qt);

/**
 * @brief A function that applies the 'Controlled Z' gate. Applies the 'Z' gate if both qubits are 1.
 * 
 * @param qs The qubits for the function to act upon.
 * @param qc The first qubit.
 * @param qt The second qubit.
 */
void qugate_func_cz(qubits *qs, int qc, int qt);


/**
 * @brief A function that applies the 'Swap' gate.
 * 
 * @param qs The qubits for the function to act upon.
 * @param qc The first qubit.
 * @param qt The second qubit.
 */
void qugate_func_swap(qubits *qs, int qc, int qt);

/**
 * @brief A function that applies the 'Multi-Controlled X' Gate. Applies the 'X' gate to the target qubit only if all control qubits are 1.
 * 
 * @param qs The qubits for the function to act upon.
 * @param n_controls The number of control qubits.
 * @param inputs The array of inputs (length 'n_controls+1'). The first 'n_controls' inputs are the controls, the last input is the target.
 */
void qugate_func_mcx(qubits *qs, int n_controls, int *inputs);

/**
 * @brief A function that applies the 'Multi-Controlled Y' Gate. Applies the 'Y' gate to the target qubit only if all control qubits are 1.
 * 
 * @param qs The qubits for the function to act upon.
 * @param n_controls The number of control qubits.
 * @param inputs The array of inputs (length 'n_controls+1'). The first 'n_controls' inputs are the controls, the last input is the target.
 */
void qugate_func_mcy(qubits *qs, int n_controls, int *inputs);

/**
 * @brief A function that applies the 'Multi-Controlled Z' Gate. Applies the 'Z' gate to all qubits only if all qubits are 1.
 * 
 * @param qs The qubits for the function to act upon.
 * @param n_controls The number of control qubits.
 * @param inputs The array of inputs (length 'n_controls+1'). The first 'n_controls' inputs are the controls, the last input is the target.
 */
void qugate_func_mcz(qubits *qs, int n_controls, int *inputs);
