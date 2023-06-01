#include <stdio.h>
#include <stdlib.h>
#include "qucircuit.h"
#include "qucircuit_context.h"

//
// qucircuit.c declarations
//

void qucircuit_compile_hidden(qucircuit *qc, qc_context_global qccg, qc_context_local qccl);
void qucircuit_print_hidden(qucircuit *qc, int indentation);

//
// qucircuit.h implementations
//

void qucircuit_free(qucircuit *qc) {
    if (qc->input_qubits)
        free(qc->input_qubits);
    if (qc->input_indices)
        free(qc->input_indices);

    switch (qc->type) {
        case QC_TYPE_SEQUENTIAL:
            for (int i = 0; i < qc->subcircuits.num; i++) {
                qucircuit_free(qc->subcircuits.subcircuit+i);
            }
            break;
        case QC_TYPE_MATRIX:
            xiym_free(qc->matrix);
            break;
        case QC_TYPE_COMPILED:
            if (qc->compiled.matrix)
                xiym_free(qc->compiled.matrix);
            break;
    }

    free(qc);
}

void qucircuit_compile(qucircuit *qc) {
    qc_context_global qccg = qc_context_global_init(qc->num_inputs);
    qc_context_local qccl = qc_context_local_init(NULL, qc);

    qucircuit_compile_hidden(qc, qccg, qccl);
    printf("Finished successfully.\n");

    qc_context_global_delete(qccg);
    qc_context_local_delete(qccl);
}

void qucircuit_print(qucircuit *qc) {
    qucircuit_print_hidden(qc, 0);
}

qucircuit *qucircuit_alloc(int num_qubits, int type, int input_is_fixed) {
    qucircuit *qc = (qucircuit *)malloc(sizeof(qucircuit));
    qc->num_inputs = num_qubits;
    qc->input_qubits = NULL;
    qc->input_indices = NULL;
    qc->type = type;
    qc->input_is_fixed = input_is_fixed;
    switch (type) {
        case QC_TYPE_SEQUENTIAL:
            qc->subcircuits.num = 0;
            qc->subcircuits.subcircuit = NULL;
            break;
        case QC_TYPE_MATRIX:
            qc->matrix = NULL;
            break;
        case QC_TYPE_GATE:
            qc->gate = NULL;
            break;
        case QC_TYPE_COMPILED:
            qc->compiled.matrix = NULL;
            qc->compiled.compiler = NULL;
            break;
    }
    return qc;
}

void qucircuit_set_inputs(qucircuit *qc, int *input_qubits) {
    qc->input_qubits = (int *)malloc(sizeof(int) * qc->num_inputs);
    for (int i = 0; i < qc->num_inputs; i++)
        qc->input_qubits[i] = input_qubits[i];
}

void qucircuit_alloc_sequential(qucircuit *qc, int num_subcircuits) {
    qc->subcircuits.num = num_subcircuits;
    qc->subcircuits.subcircuit = (qucircuit *)malloc(sizeof(qucircuit) * num_subcircuits);
}

//
// qucircuit.c implementations
//

void qucircuit_compile_hidden(qucircuit *qc, qc_context_global qccg, qc_context_local qccl) {
    if (qc->input_is_fixed) {
        qc_context_global_fix(qccg, qccl, qc);
    }
    printf("Fixed input.\n");

    qc->input_indices = (int *)malloc(sizeof(int) * qc->num_inputs);
    for (int i = 0; i < qc->num_inputs; i++) {
        int global_qubit = qccl.local_to_global_qubit[qc->input_qubits[i]];
        qc->input_indices[i] = qccg.qubit_to_index[global_qubit];
    }
    printf("Set inputs.\n");

    switch (qc->type) {
        case QC_TYPE_COMPILED:
            printf("Attempt compiled.\n");
            qc->compiled.matrix = qc->compiled.compiler(qc->num_inputs, qc->input_indices, qccg.num_qubits);
            printf("Compiled.");
            break;
        case QC_TYPE_SEQUENTIAL: ;
            printf("Attempt sequential.\n");
            qc_context_local qccl_inner = qc_context_local_init(&qccl, qc);
            printf("Created local context.\n");
            for (int i = 0; i < qc->subcircuits.num; i++) {
                printf("Start %d\n", i);
                qucircuit_compile_hidden(qc->subcircuits.subcircuit+i, qccg, qccl_inner);
                printf("Finish %d\n", i);
            }
            printf("Deleting local context.\n");
            qc_context_local_delete(qccl_inner);
            printf("Local context deleted.\n");
            break;
    }
}

void print_indented(int indentation, char *text) {
    for (int i = 0; i < 2*indentation; i++)
        printf("-");
    printf(text);
}

void qucircuit_print_hidden(qucircuit *qc, int indentation) {
    print_indented(indentation, "Qucircuit:\n");
    print_indented(indentation+1, "Type: ");
    switch (qc->type) {
        case QC_TYPE_SEQUENTIAL:
            printf("Sequential\n");
            break;
        case QC_TYPE_MATRIX:
            printf("Matrix\n");
            break;
        case QC_TYPE_GATE:
            printf("Gate\n");
            break;
        case QC_TYPE_COMPILED:
            printf("Compiled\n");
            break;
    }
    print_indented(indentation+1, "Number of inputs: ");
    printf("%d\n", qc->num_inputs);
    if (qc->input_is_fixed)
        print_indented(indentation+1, "Input is fixed\n");
    else
        print_indented(indentation+1, "Input is not fixed\n");

    if (qc->input_qubits) {
        print_indented(indentation+1, "Local qubit inputs: ");
        for (int i = 0; i < qc->num_inputs; i++)
            printf("%d, ", qc->input_qubits[i]);
        printf("\n");
    }
    else
        print_indented(indentation+1, "Input qubits not set");

    if (qc->input_indices) {
        print_indented(indentation+1, "Indice inputs: ");
        for (int i = 0; i < qc->num_inputs; i++)
            printf("%d, ", qc->input_indices[i]);
        printf("\n");
    }
    else
        print_indented(indentation+1, "Indices not set\n");

    switch (qc->type) {
        case QC_TYPE_SEQUENTIAL:
            print_indented(indentation+1, "Subcircuits:\n");
            for (int i = 0; i < qc->subcircuits.num; i++)
                qucircuit_print_hidden(qc->subcircuits.subcircuit+i, indentation+1);
            break;
        case QC_TYPE_MATRIX:
            xiym_print(qc->matrix);
            break;
        case QC_TYPE_COMPILED:
            if (qc->compiled.matrix)
                xiym_print(qc->compiled.matrix);
            else
                print_indented(indentation+1, "Uncompiled\n");
            break;
        case QC_TYPE_GATE:
            print_indented(indentation+1, "Gate\n");
    }
}
