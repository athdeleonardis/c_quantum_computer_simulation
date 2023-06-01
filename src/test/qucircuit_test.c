#include <stddef.h>
#include <stdio.h>
#include "../qucircuit.h"
#include "../qc_name_map.h"
#include "../qugate.h"

qc_name_map create_simple_map();
qucircuit *create_simple_circuit(qc_name_map *map);

int main(int argc, char *argv[]) {
    qc_name_map map = create_simple_map();

    qucircuit *qc = create_simple_circuit(&map);
    printf("A\n");
    qucircuit_print(qc);
    qucircuit_compile(qc);
    printf("B\n");
    qucircuit_free(qc);
    printf("C\n");

    qc_name_map_delete(&map);
}

qc_name_map create_simple_map() {
    qc_name_map map = qc_name_map_init();

    qucircuit gate = { .num_inputs=1, .input_qubits=NULL, .input_indices=NULL,
        .type=QC_TYPE_GATE, .input_is_fixed=1, .gate = qugate_q0x };
    qc_name_map_put(&map, "Q0X", gate);

    gate.gate = qugate_q0y;
    qc_name_map_put(&map, "Q0Y", gate);

    gate.gate = qugate_q0z;
    qc_name_map_put(&map, "Q0Z", gate);

    gate.gate = qugate_q0h;
    qc_name_map_put(&map, "Q0H", gate);

    gate.num_inputs = 2;
    gate.gate = qugate_q01cnot;
    qc_name_map_put(&map, "Q01CNOT", gate);

    return map;
}

qucircuit *create_simple_circuit(qc_name_map *map) {
    qucircuit *qc = qucircuit_alloc(2, QC_TYPE_SEQUENTIAL, 0);
    int inputs2[] = { 0, 1 };
    qucircuit_set_inputs(qc, inputs2);
    qucircuit_alloc_sequential(qc, 5);

    qc->subcircuits.subcircuit[0] = qc_name_map_get(map, "Q0H");
    int inputs0[] = { 0 };
    qucircuit_set_inputs(qc->subcircuits.subcircuit, inputs0);

    qc->subcircuits.subcircuit[1] = qc_name_map_get(map, "Q0H");
    inputs0[0] = 1;
    qucircuit_set_inputs(qc->subcircuits.subcircuit+1, inputs0);

    qc->subcircuits.subcircuit[2] = qc_name_map_get(map, "Q01CNOT");
    qucircuit_set_inputs(qc->subcircuits.subcircuit+2, inputs2);

    qc->subcircuits.subcircuit[3] = qc_name_map_get(map, "Q0H");
    inputs0[0] = 0;
    qucircuit_set_inputs(qc->subcircuits.subcircuit+3, inputs0);

    qc->subcircuits.subcircuit[4] = qc_name_map_get(map, "Q0H");
    inputs0[0] = 1;
    qucircuit_set_inputs(qc->subcircuits.subcircuit+4, inputs0);

    return qc;
}
