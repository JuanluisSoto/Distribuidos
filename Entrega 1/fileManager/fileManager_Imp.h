//Oscar Simon Juanluis Soto
#pragma once
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include "operaciones.h"
#include "utils.h"
#include "fileManager.h"

class fileManager_imp {
private:
	int clientId;
	FileManager* c = nullptr;

public:
	bool conexionCerrada = false;
	fileManager_imp() {

	}
	void recOp(int clientId) {
		std::vector<unsigned char> packetIn;
		std::vector<unsigned char> packetOut;

		recvMSG(clientId, packetIn);

		FileManagerOp op = unpack<FileManagerOp>(packetIn);

		switch (op) {
		case constructorOp:
		{
			std::string path;
			int size = unpack<int>(packetIn);
			char* d = new char[size];
			unpackv<char>(packetIn, d, size);
			path = string(d);
			c = new FileManager(path);
			int OK = 1;
			pack(packetOut, OK);
			std::cout << path << std::endl;
		}
		break;

		case destructorOp:
		{
			delete c;
			this->conexionCerrada = true;
			int ok = 1;
			pack(packetOut, ok);
		}
		break;
		case listFilesOp:
		{	
			vector<string*>* vfiles = c->listFiles();
			int OK = 1;
			pack(packetOut, OK);
			serializar_lista_ficheros(packetOut, vfiles);
		}
		break;
		case freeListedFilesOp:
		{
			vector<string*>* vfiles = new vector<string*>();
			deserializar_lista_ficheros(packetIn, vfiles);
			c->freeListedFiles(vfiles); 
			int OK = 1;
			pack(packetOut, OK);
		}
		break;
		case readFileOp:
		{
			int fileSize = unpack<int>(packetIn);
			char* fileName = new char[fileSize];
			unpackv<char>(packetIn, fileName, fileSize);
			char* data;
			unsigned long int dataLength;
			c->readFile(fileName, data, dataLength);

			int OK = 1;
			pack(packetOut, OK);
			pack(packetOut, dataLength);
			packv(packetOut, data, dataLength);
		}
		break;

		case writeFileOp:
		{
			int fileSize = unpack<int>(packetIn);
			char* fileName = new char[fileSize];
			unpackv<char>(packetIn, fileName, fileSize);
			unsigned long int dataLength = unpack<unsigned long int>(packetIn);
			char* data = new char[dataLength];
			unpackv<char>(packetIn, data, dataLength);
			c->writeFile(fileName, data, dataLength);
			int OK = 1;
			pack(packetOut, OK);
		}
		break;

		default:
		{
			std::cout << "Error in " << __FILE__ << "line" << __LINE__ << "\nError instanciando la persona\n";
		}
		break;
		}
		sendMSG(clientId, packetOut);
	}
};