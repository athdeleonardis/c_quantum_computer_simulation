#ifndef QUCIRCUIT_APPLY
#define QUCIRCUIT_APPLY

#include "../qubits/qubits.h"
#include "./qucircuit_context.h"
#include "./qucircuit.h"

void qucircuit_apply(qubits *qs, qucircuit_context qcc, qucircuit_application *application);

#endif
