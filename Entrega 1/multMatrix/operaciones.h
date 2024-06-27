#pragma once
#ifndef MULTMATRIX_SERIALIZACION_H
#define MULTMATRIX_SERIALIZACION_H

#include <vector>
#include "multmatrix.h"

typedef enum tipoOperacion {
	opSumaInt = 1,
	opSumaFloat = 2,
	opSumaDouble = 3,
	opSuma3Int = 4
}tipoOperacion;

typedef enum matrixOp
{
	constructOp = 1,
	destructOp = 2,

	creaMatrixOp = 3,
	MatrixIdentidadOp = 4,

	multMatrixeOp = 5,
	writeMatrixOp = 6,
	readMatrixOp = 7
}matrixOp;

template<typename T>
inline void pack(std::vector<unsigned char>& packet, T data)
{
	auto* ptr = (unsigned char*)&data;
	int dsize = sizeof(T), init = packet.size();

	packet.resize(init + dsize);
	std::copy(ptr, ptr + dsize, packet.begin() + init);
}

template<typename T>
inline T unpack(std::vector<unsigned char>& packet)
{
	T* ptr = (T*)packet.data();
	T data = ptr[0];
	int dsize = sizeof(T), init = packet.size();

	for (int i = dsize; i < packet.size(); i++) packet[i - dsize] = packet[i];
	packet.resize(init - dsize);

	return data;
}

template<typename T>
inline void packv(std::vector<unsigned char>& packet, T* arr, int size)
{
	for (int i = 0; i < size; i++) pack(packet, arr[i]);
}

template<typename T>
inline void unpackv(std::vector<unsigned char>& packet, T* arr, int size)
{
	for (int i = 0; i < size; i++) arr[i] = unpack<T>(packet);
}

void serializar_matrix(std::vector<unsigned char>& packet, matrix_t* matrix)
{
	pack(packet, matrix->rows);
	pack(packet, matrix->cols);
	packv(packet, matrix->data, matrix->rows * matrix->cols);
}

void deserializar_matrix(std::vector<unsigned char>& packet, matrix_t* matrix)
{
	matrix->rows = unpack<int>(packet);
	matrix->cols = unpack<int>(packet);
	matrix->data = new int[matrix->rows * matrix->cols];
	unpackv(packet, matrix->data, matrix->rows * matrix->cols);
}

void serializar_char_array(std::vector<unsigned char>& packet, const char* arr, int size)
{
	pack(packet, size);
	packv(packet, arr, size);
}

/* void serializar_lista_ficheros(std::vector<unsigned char>& packet, std::vector<string*>* flist) */
/* { */
/*     int listSize = flist->size(); */
/*     pack(packet, listSize); */

/*     for (int i = 0; i < listSize; i++) */
/*     { */
/*         string dato = string(flist->at(i)->c_str()); */
/*         int datoSize = dato.length() + 1; */
/*         pack(packet, datoSize); */
		/* packv(packet, dato.c_str(), datoSize); */
	/* } */
/* } */

/* void deserializar_lista_ficheros(std::vector<unsigned char>& packet, std::vector<string*>* flist) */
/* { */
	/* int listSize = unpack<int>(packet); */

	/* for (int i = 0; i < listSize; i++) */
	/* { */
		/* int strSize = unpack<int>(packet); */
		/* char* d = new char[strSize]; */
		/* unpackv<char>(packet, d, strSize); */
		/* string* dato = new string(d); */
		/* delete[] d; */

		/* flist->push_back(dato); */
	/* } */
/* } */

#endif //MULTMATRIX_SERIALIZACION_H
