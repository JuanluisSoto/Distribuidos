//Oscar Simon Juanluis Soto
#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include "operaciones.h"
#include "utils.h"

class Matrix_stub
{
private:

	std::string ip = "127.0.0.1";
	int puerto = 10001;
	connection_t serverConnection;
public:
	Matrix_stub() {

		serverConnection = initClient(ip, puerto);
		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;

		std::cout << "He llegado";
		pack(mensaje, constructOp);
		sendMSG(serverConnection.serverId, mensaje);
		recvMSG(serverConnection.serverId, res);

		int ok = unpack<int>(res);
		if (!ok)
		{
			std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << " \n";
		}

	};

	~Matrix_stub() {
		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;

		pack(mensaje, destructOp);
		sendMSG(serverConnection.serverId, mensaje);
		recvMSG(serverConnection.serverId, res);

		int ok = unpack<int>(res);
		if (!ok)
		{
			std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << " \n";
		}

		closeConnection(serverConnection.serverId);
	};

	matrix_t* readMatrix(const char* fileName) {
		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;
		matrix_t* m = new matrix_t;

		pack(mensaje, readMatrixOp);
		serializar_char_array(mensaje, fileName, strlen(fileName) + 1);

		sendMSG(serverConnection.serverId, mensaje);
		recvMSG(serverConnection.serverId, res);

		int ok = unpack<int>(res);
		if (!ok)
		{
			std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << " \n";
		}
		deserializar_matrix(res, m);
		return m;
	}

	matrix_t* multMatrices(matrix_t* m1, matrix_t* m2) {
		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;
		matrix_t* m = new matrix_t;

		pack(mensaje, multMatrixeOp);
		pack(mensaje, m1->rows);
		pack(mensaje, m1->cols);
		packv(mensaje, m1->data, m1->rows * m1->cols);

		pack(mensaje, m2->rows);
		pack(mensaje, m2->cols);
		packv(mensaje, m2->data, m2->rows * m2->cols);

		sendMSG(serverConnection.serverId, mensaje);
		recvMSG(serverConnection.serverId, res);

		int ok = unpack<int>(res);
		if (!ok)
		{
			std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << " \n";
		}
		deserializar_matrix(res, m);
		return m;
	}

	void writeMatrix(matrix_t* m, const char* fileName) {
		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;

		pack(mensaje, writeMatrixOp);
		pack(mensaje, m->rows);
		pack(mensaje, m->cols);
		packv(mensaje, m->data, m->rows * m->cols);
		serializar_char_array(mensaje, fileName, strlen(fileName) + 1);

		sendMSG(serverConnection.serverId, mensaje);
		recvMSG(serverConnection.serverId, res);

		int ok = unpack<int>(res);
		if (!ok)
		{
			std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << " \n";
		}
	}

	matrix_t* createIdentity(int rows, int cols) {
		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;
		matrix_t* m = new matrix_t;

		pack(mensaje, MatrixIdentidadOp);
		pack(mensaje, rows);
		pack(mensaje, cols);
		sendMSG(serverConnection.serverId, mensaje);
		recvMSG(serverConnection.serverId, res);

		int ok = unpack<int>(res);
		if (!ok)
		{
			std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << " \n";
		}
		deserializar_matrix(res, m);
		return m;
	}

	matrix_t* createRandMatrix(int rows, int cols) {
		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;
		matrix_t* m = new matrix_t;

		pack(mensaje, creaMatrixOp);
		pack(mensaje, rows);
		pack(mensaje, cols);
		sendMSG(serverConnection.serverId, mensaje);
		recvMSG(serverConnection.serverId, res);

		int ok = unpack<int>(res);
		if (!ok)
		{
			std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << " \n";
		}
		deserializar_matrix(res, m);
		return m;
	}

	static void print_matrix(matrix_t* m)
	{
		for (int i = 0; i < m->rows; i++)
		{
			for (int j = 0; j < m->cols; j++) std::cout << m->data[i * m->cols + j] << " ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};
