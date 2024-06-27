//Oscar Simon Juanluis Soto
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <map>
#include <functional>
#include <vector>
#include <signal.h>

#include "fileManager.h"
#include "fileManager_Stub.h"

int main(int argc, char** argv)
{
    string path = "./dirprueba";

    // Mostrar informacion de la terminal
    cout << "Terminal de File Manager" << endl;

	fileManagerStub* fm = new fileManagerStub(path);
    auto ficheros = fm->listFiles();
	for (auto i : *ficheros)
	{
		cout << i->c_str() << endl;
	}

	char* fileName = (char*)"Hola_mundo.txt";
	char* message = (char*)"Hola mundo";

	fm->writeFile(fileName, message, strlen(message));

	ficheros = fm->listFiles();
	for (auto i : *ficheros)
	{
		cout << i->c_str() << endl;
    }

	char* data;
	unsigned long int dataLength = 0;

	fm->readFile(fileName, data, dataLength);
	cout << data << endl;

	fm->freeListedFiles(ficheros);

	delete fm;

    return 0;
}