add_executable(qucircuit_apply.test qucircuit_apply.test.c)
target_link_libraries(qucircuit_apply.test PRIVATE c_quantum_computer_simulation)
add_test(NAME qucircuit_apply COMMAND qucircuit_apply.test)

add_executable(qucircuit_context.test qucircuit_context.test.c)
target_link_libraries(qucircuit_context.test PRIVATE c_quantum_computer_simulation)
add_test(NAME qucircuit_context COMMAND qucircuit_context.test)

add_executable(qucircuit.test qucircuit.test.c)
target_link_libraries(qucircuit.test PRIVATE c_quantum_computer_simulation)
add_test(NAME qucircuit COMMAND qucircuit.test)