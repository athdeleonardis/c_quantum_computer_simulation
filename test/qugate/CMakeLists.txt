add_executable(qugate.test qugate.test.c)
target_link_libraries(qugate.test PRIVATE c_quantum_computer_simulation)
add_test(NAME qugate COMMAND qugate.test)