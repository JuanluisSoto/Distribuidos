//Oscar Simon Juanluis Soto
#pragma once
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include "operaciones.h"
#include "utils.h"


void sendStringOp(int serverId, std::string dato, FileManagerOp op);
std::string recibeStringOp(int serverId, FileManagerOp op);


class fileManagerStub {
private:
	//Ip Makina 1 AWS Elastica
	std::string ip = "127.0.0.1";
	int puerto = 10002;
	connection_t serverConnection;
public:
	fileManagerStub(std::string path) {

		serverConnection = initClient(ip, puerto);

		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;

		sendStringOp(serverConnection.serverId, path, constructorOp);

	}

	~fileManagerStub() {
		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;

		pack(mensaje, destructorOp);
		sendMSG(serverConnection.serverId, mensaje);
		recvMSG(serverConnection.serverId, res);

		int ok = unpack<int>(res);
		if (!ok) {
			std::cout << "Error in " << __FILE__ << "line" << __LINE__ << std::endl;
		}

		closeConnection(serverConnection.serverId);
	};

	std::vector<std::string*>* listFiles() {
		std::vector<std::string*>* vfiles = new std::vector<std::string*>();
		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;

		pack(mensaje, listFilesOp);
		sendMSG(serverConnection.serverId, mensaje);
		recvMSG(serverConnection.serverId, res);

		int ok = unpack<int>(res);
		if (ok) {
			deserializar_lista_ficheros(res, vfiles);
		}
		return vfiles;
	};

	void readFile(char* fileName, char*& data, unsigned long int& dataLength)
	{
		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;

		string file = string(fileName);
		int size = file.length() + 1;
		pack(mensaje, readFileOp);
		pack(mensaje, size);
		packv(mensaje, fileName, size);

		sendMSG(serverConnection.serverId, mensaje);
		recvMSG(serverConnection.serverId, res);

		int ok = unpack<int>(res);
		if (!ok)
		{
			std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << "\n";
		}
		else
		{
			std::cout << "DataLength: " << dataLength << std::endl;
			unsigned long int strSize = unpack<unsigned long int>(res);
			dataLength = strSize;
			std::cout << "DataLength: " << dataLength << std::endl;
			data = new char[dataLength];

			unpackv<char>(res, data, dataLength);
		}
	}

	void writeFile(char* fileName, char* data, unsigned long int dataLength)
	{
		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;

		std::string file = std::string(fileName);
		int size = file.length() + 1;
		pack(mensaje, writeFileOp);
		pack(mensaje, size);
		packv(mensaje, fileName, size);
		pack(mensaje, dataLength);
		packv(mensaje, data, dataLength);

		sendMSG(serverConnection.serverId, mensaje);
		recvMSG(serverConnection.serverId, res);

		int ok = unpack<int>(res);
		if (!ok)
		{
			std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << "\n";
		}
	}


	void freeListedFiles(std::vector<std::string*>* fileList) {
		std::vector<unsigned char> mensaje;
		std::vector<unsigned char> res;

		pack(mensaje, freeListedFilesOp);
		serializar_lista_ficheros(mensaje, fileList);

		sendMSG(serverConnection.serverId, mensaje);
		recvMSG(serverConnection.serverId, res);
		int ok = unpack<int>(res);

		if (!ok) {
			std::cout << "Error in " << __FILE__ << "line" << __LINE__ << std::endl;
		}
	};
};

void sendStringOp(int serverId, std::string dato, FileManagerOp op) {
	std::vector<unsigned char> mensaje;
	std::vector<unsigned char> res;

	int tam = (dato.length() + 1);
	pack(mensaje, op);
	pack(mensaje, tam);
	packv(mensaje, dato.c_str(), dato.length() + 1);

	sendMSG(serverId, mensaje);
	recvMSG(serverId, res);


	int ok = unpack<int>(res);
	if (!ok) {
		std::cout << "Error in " << __FILE__ << "line" << __LINE__ << "\nError instanciando la persona\n";
	}
}

std::string recibeStringOp(int serverId, FileManagerOp op) {
	std::string dato = "";

	std::vector<unsigned char> mensaje;
	std::vector<unsigned char> res;

	pack(mensaje, op);

	sendMSG(serverId, mensaje);
	recvMSG(serverId, res);


	int ok = unpack<int>(res);

	if (ok != 1) {
		std::cout << "Error in " << __FILE__ << "line" << __LINE__ << "\nError instanciando la persona\n";
	}
	else {
		int tam = unpack<int>(res);
		char* d = new char[tam];
		unpackv<char>(res, d, tam);
		dato = std::string(d);
		delete[] d;
	}
	return dato;
}