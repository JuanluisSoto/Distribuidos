cmake_minimum_required (VERSION 2.8.11)

project (multMatrixServer)
add_executable (multMatrixServer multmatrix.cpp utils.cpp matrix_imp.h server_matrix.cpp)

project (multMatrixClient)
add_executable (multMatrixClient multmatrix.cpp utils.cpp matrix_stub.h client_matrix.cpp)
