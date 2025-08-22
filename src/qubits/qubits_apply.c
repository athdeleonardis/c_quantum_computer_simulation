#include "./qubits_apply.h"

void qubits_apply_2x2(qubits *qs, xiy *mat_2x2, int q) {
    /**
     * For each possible state where qubit q is 0 or 1:
     * ( w0n ) = ( z11 z12 )( w0 ) = ( z11*w0 + z12*w1 ) = ( w0n1 + w0n2 )
     * ( w1n )   ( z21 z22 )( w1 )   ( z21*w0 + z22*w1 )   ( w1n1 + w1n2 )
     */
    int q_set_1 = 1 << q;
    int q_set_0 = !q_set_1;

    for (int s = 0; s < qs->n_values; s++) {
        // Whether qubit q is 0 or 1, qv = !!(s & q_set_1)
        // Calculate the offset in the matrix based on this
        // i.e. qv = 0 => row 1, qv = 1 => row 2
        int x = 2 * !!(s & q_set_1);
        xiy wxn1 = xiy_mul(mat_2x2[x], qs->values_in[s & q_set_0]);
        xiy wxn2 = xiy_mul(mat_2x2[x+1], qs->values_in[s | q_set_1]);
        qs->values_out[s] = xiy_add(wxn1, wxn2);
    }

    qubits_swap_in_out(qs);
}

void qubits_apply_4x4(qubits *qs, xiy *mat_4x4, int q1, int q2) {
    /**
     * For each possible state where qubits q1 is 0 or 1, q2 is 0 or 1:
     * ( w00n ) = ( z11 z12 z13 z14 )( w00 ) = ( z11*w00 + z12*w01 + z13*w10 + z14*w11 ) = ( w00n1 + w00n2 + w00n3 + w00n4 )
     * ( w01n )   ( z21 z22 z23 z24 )( w01 )   ( z21*w00 + z22*w01 + z23*w10 + z24*w11 )   ( w01n1 + w01n2 + w01n3 + w01n4 )
     * ( w10n )   ( z31 z32 z33 z34 )( w10 )   ( z31*w00 + z32*w01 + z33*w10 + z34*w11 )   ( w10n1 + w10n2 + w10n3 + w10n4 )
     * ( w11n )   ( z41 z42 z43 z44 )( w11 )   ( z41*w00 + z42*w01 + z43*w10 + z44*w11 )   ( w11n1 + w11n2 + w11n3 + w11n4 )
     */
    int q1_set_1 = 1 << q1;
    int q1_set_0 = !q1_set_1;
    int q2_set_1 = 1 << q2;
    int q2_set_0 = !q2_set_1;

    for (int s = 0; s < qs->n_values; s++) {
        // Whether qubit q is 0 or 1, qv = !!(s & q_set_1)
        // Calculate the offset in the matrix based on this
        // i.e. qvs = [0,0] => row 1, qvs = [0,1] => row 2, qvs = [1,0] => row 3, qvs = [1,1] => row 4
        int x = 4 * (2 * !!(s & q1_set_1) + !!(s & q2_set_1));
        xiy wxyn1 = xiy_mul(mat_4x4[x], qs->values_in[(s & q1_set_0) & q2_set_0]);
        xiy wxyn2 = xiy_mul(mat_4x4[x+1], qs->values_in[(s & q1_set_0) | q2_set_1]);
        xiy wxyn3 = xiy_mul(mat_4x4[x+2], qs->values_in[(s | q1_set_1) & q2_set_0]);
        xiy wxyn4 = xiy_mul(mat_4x4[x+3], qs->values_in[(s | q1_set_1) | q2_set_1]);
        qs->values_out[s] = xiy_add(xiy_add(wxyn1, wxyn2), xiy_add(wxyn3, wxyn4));
    }

    qubits_swap_in_out(qs);
}
