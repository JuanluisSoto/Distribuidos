//Oscar Simon Juanluis Soto

#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include "utils.h"
#include "operaciones.h"
#include "multmatrix.h"

class Matrix_imp {
private:
	int clientId;
	multMatrix* m = nullptr;
public:
	bool conexionCerrada = false;

	Matrix_imp()
	{}

	void recOp(int clientId)
	{
		std::vector<unsigned char> packetIn;
		std::vector<unsigned char> packetOut;

		recvMSG(clientId, packetIn);

		matrixOp op = unpack<matrixOp>(packetIn);

		switch (op)
		{
		case constructOp:
		{
			m = new multMatrix();
			int Ok = 1;
			pack(packetOut, Ok);

		}
		break;

		case destructOp:
		{
			delete m;
			pack<int>(packetOut, 1);
			conexionCerrada = true;
		}
		break;

		case creaMatrixOp:
		{
			int rows = unpack<int>(packetIn);
			int cols = unpack<int>(packetIn);
			matrix_t* matrix = m->createRandMatrix(rows, cols);
			int Ok = 1;
			pack(packetOut, Ok);
			serializar_matrix(packetOut, matrix);
		}
		break;

		case MatrixIdentidadOp:
		{
			int rows = unpack<int>(packetIn);
			int cols = unpack<int>(packetIn);
			matrix_t* matrix = m->createIdentity(rows, cols);
			int Ok = 1;
			pack(packetOut, Ok);
			serializar_matrix(packetOut, matrix);
		}
		break;

		case multMatrixeOp:
		{
			matrix_t* matrix1 = new matrix_t;
			matrix_t* matrix2 = new matrix_t;
			deserializar_matrix(packetIn, matrix1);
			deserializar_matrix(packetIn, matrix2);
			matrix_t* matrix = m->multMatrices(matrix1, matrix2);
			int Ok = 1;
			pack(packetOut, Ok);
			if (matrix != nullptr) {
				serializar_matrix(packetOut, matrix);
			}
		}
		break;

		case writeMatrixOp:
		{
			matrix_t* matrix = new matrix_t;
			deserializar_matrix(packetIn, matrix);
			int size = unpack<int>(packetIn);
			char* fileName = new char[size];
			unpackv(packetIn, fileName, size);
			this->m->writeMatrix(matrix, fileName);
			int Ok = 1;
			pack(packetOut, Ok);
		}
		break;

		case readMatrixOp:
		{
			int size = unpack<int>(packetIn);
			char* fileName = new char[size];
			unpackv(packetIn, fileName, size);
			matrix_t* matrix = this->m->readMatrix(fileName);
			int Ok = 1;
			pack(packetOut, Ok);
			if (matrix != nullptr) {
				serializar_matrix(packetOut, matrix);
			}
		}
		break;

		default:
		{
			std::cout << "ERROR: operación no válida\n";
		}break;
		};

		sendMSG(clientId, packetOut);
	}
};
