//Oscar Simon Juanluis Soto
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "multmatrix.h"
#include "utils.h"
#include "operaciones.h"
#include "matrix_stub.h"

int main(int argc, char** argv)
{
	Matrix_stub m = Matrix_stub();

	matrix_t* m1 = m.createRandMatrix(8, 8);
	Matrix_stub::print_matrix(m1);

	matrix_t* m2 = m.createIdentity(8, 8);
	Matrix_stub::print_matrix(m2);

	matrix_t* m3 = m.createRandMatrix(8, 8);

	matrix_t* res = m.multMatrices(m1, m3);
	Matrix_stub::print_matrix(res);

	m.writeMatrix(res, "Matrix_res.txt");
	matrix_t* read = m.readMatrix("Matrix_res.txt");

	Matrix_stub::print_matrix(read);

	return 0;
}
