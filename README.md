# c_quantum_computer_simulation

A library for constructing and simulating quantum computer operations on qubits.

## Structure

There are three main folders
1. src: Contains all headers and source files used to build the library.
2. test: Contains all headers and source files used to build executables to test the library.
3. app: Contains all headers and source files used to build example programs that use the library.

## Build

Generate your build system of choice with cmake, e.g.

`cmake -S . -B build -G "Your generator of choice"`

## Test

Run tests from the build folder with ctest, e.g.

`ctest -C YourConfigChoice`
