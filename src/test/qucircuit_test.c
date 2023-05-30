#include <stddef.h>
#include "../qucircuit.h"
#include "../qc_name_map.h"
#include "../qugate.h"

qc_name_map create_simple_map();

int main(int argc, char *argv[]) {
    qc_name_map map = create_simple_map();

    qc_name_map_delete(&map);
}

qc_name_map create_simple_map() {
    qc_name_map map = qc_name_map_init();

    qucircuit q0x = { .num_inputs=1, .input_qubits=NULL, .input_indices=NULL,
        .type=QC_TYPE_GATE, .input_is_fixed=1, .gate = qugate_q0x };
    qucircuit q0y = q0x;
    q0y.gate = qugate_q0y;
    qucircuit q0z = q0x;
    q0z.gate = qugate_q0z;
    qucircuit q01cnot = q0x;
    q01cnot.num_inputs = 2;
    q01cnot.gate = qugate_q01cnot;

    qc_name_map_put(&map, "Q0X", q0x);
    qc_name_map_put(&map, "Q0Y", q0y);
    qc_name_map_put(&map, "Q0Z", q0z);
    qc_name_map_put(&map, "Q0CNOT", q01cnot);

    return map;
}
