#include <stdlib.h>
#include <string.h>
#include "qc_name_map.h"

//
// qc_name_map.c declarations
//

void qc_deep_copy(qucircuit *in, qucircuit *out, int copy_inputs);
void name_list_append(qc_name_map *map, char *name, qucircuit *qc);
qucircuit *qc_name_map_find(qc_name_map *map, char *name);
void qc_free(qucircuit *qc);

//
// qc_name_map.h struct implementations
//

struct qc_name_node {
    qc_name_node *next;
    char name[QC_NAME_LENGTH];
    qucircuit *qc;
};

//
// qc_name_map.h implementations
//

qc_name_map qc_name_map_init() {
    qc_name_map map = { NULL, NULL };
    return map;
}

void qc_name_map_put(qc_name_map *map, char *name, qucircuit qc) {
    qucircuit *deep_copy = (qucircuit *)malloc(sizeof(qucircuit));
    qc_deep_copy(&qc, deep_copy, 0);
    name_list_append(map, name, deep_copy);
}

qucircuit *qc_name_map_get(qc_name_map *map, char *name) {
    qucircuit *qc = qc_name_map_find(map, name);
    if (!qc)
        return NULL;
    qucircuit *out = (qucircuit *)malloc(sizeof(qucircuit));
    qc_deep_copy(qc, out, 0);
    return out;
}

void qc_name_map_delete(qc_name_map *map) {
    qc_name_node *nn = map->name_list_start;

    qc_name_node *nnnext;
    while (nn) {
        nnnext = nn->next;
        qucircuit_free(nn->qc);
        free(nn);
        nn = nnnext;
    }
}

//
// qc_name_map.c implementations
//

void qc_deep_copy(qucircuit *in, qucircuit *out, int copy_inputs) {
    out->num_inputs = in->num_inputs;
    out->input_qubits = NULL;
    if (copy_inputs) {
        out->input_qubits = (int *)malloc(sizeof(int)*out->num_inputs);
        for (int i = 0; i < in->num_inputs; i++)
            out->input_qubits[i] = out->input_qubits[i];
    }
    out->input_indices = NULL;
    out->type = in->type;
    out->input_is_fixed = in->input_is_fixed;

    switch (out->type) {
        case QC_TYPE_SEQUENTIAL:
            out->subcircuits.num = in->subcircuits.num;
            out->subcircuits.subcircuit =
                (qucircuit *)malloc(sizeof(qucircuit) * out->subcircuits.num);
            for (int i = 0; i < out->subcircuits.num; i++)
                qc_deep_copy(in->subcircuits.subcircuit+i, out->subcircuits.subcircuit+i, 1);
            break;
        case QC_TYPE_MATRIX:
            out->matrix = NULL;
            break;
        case QC_TYPE_GATE:
            out->gate = in->gate;
            break;
        case QC_TYPE_COMPILED:
            out->compiled.compiler = in->compiled.compiler;
            out->compiled.matrix = NULL;
            break;
    }
}

void name_list_append(qc_name_map *map, char *name, qucircuit *qc) {
    qc_name_node *node = (qc_name_node *)malloc(sizeof(qc_name_node));
    node->next = NULL;
    strcpy(node->name, name);
    node->qc = qc;

    if (map->name_list_start)
        map->name_list_end->next = node;
    else
        map->name_list_start = node;
    map->name_list_end = node;
}

qucircuit *qc_name_map_find(qc_name_map *map, char *name) {
    qc_name_node *nn = map->name_list_start;
    while (nn) {
        if (strcmp(nn->name, name) == 0)
            return nn->qc;
        nn = nn->next;
    }
    return NULL;
}
