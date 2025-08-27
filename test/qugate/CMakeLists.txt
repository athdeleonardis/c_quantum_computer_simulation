add_executable(qugate_func.test qugate_func.test.c)
target_link_libraries(qugate_func.test PRIVATE c_quantum_computer_simulation)
add_test(NAME qugate_func COMMAND qugate_func.test)

add_executable(qugate_mat.test qugate_mat.test.c)
target_link_libraries(qugate_mat.test PRIVATE c_quantum_computer_simulation)
add_test(NAME qugate_mat COMMAND qugate_mat.test)