add_executable(qubits_apply.test qubits_apply.test.c)
target_link_libraries(qubits_apply.test PRIVATE c_quantum_computer_simulation)

add_executable(qubits.test qubits.test.c)
target_link_libraries(qubits.test PRIVATE c_quantum_computer_simulation)