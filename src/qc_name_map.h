#ifndef QC_NAME_MAP
#define QC_NAME_MAP

#include "qucircuit.h"

#define QC_NAME_LENGTH 16

typedef struct qc_name_map qc_name_map;

qc_name_map qc_name_map_init();
// Puts a deep copy of qucircuit into the map
void qc_name_map_put(qc_name_map *map, char *name, qucircuit qc);
// Gets a deep copy of qucircuit inside map
qucircuit *qc_name_map_get(qc_name_map *map, char *name);
// Required, as deep copies are malloc'd
void qc_name_map_delete(qc_name_map *map);

typedef struct qc_name_node qc_name_node;

struct qc_name_map {
    qc_name_node *name_list_start;
    qc_name_node *name_list_end;
};

#endif
