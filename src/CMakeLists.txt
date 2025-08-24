add_library(c_quantum_computer_simulation STATIC)

find_library(MATH_LIBRARY m)
if (MATH_LIBRARY)
  target_link_libraries(c_quantum_computer_simulation PUBLIC ${MATH_LIBRARY})
endif()

add_subdirectory(complex_numbers)
add_subdirectory(qubits)
add_subdirectory(qucircuit)
add_subdirectory(qugate)