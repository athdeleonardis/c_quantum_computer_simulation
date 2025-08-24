add_executable(qucircuit.test qucircuit.test.c)
target_link_libraries(qucircuit.test PRIVATE c_quantum_computer_simulation)
add_test(NAME qucircuit COMMAND qucircuit.test)