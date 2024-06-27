//Oscar Simon Juanluis Soto
#pragma once
#include <vector>
#include <iostream>

using namespace std;

typedef enum FileManagerOp{

	constructorOp = 1,
	destructorOp = 2,
	listFilesOp=3,
	readFileOp=4,
	writeFileOp=5,
	freeListedFilesOp=6,

}FileManagerOp;

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

void serializar_char_array(std::vector<unsigned char>& packet, const char* arr, int size)
{
    pack(packet, size);
    packv(packet, arr, size);
}

void serializar_lista_ficheros(std::vector<unsigned char>& packet, std::vector<string*>* flist)
{
    int listSize = flist->size();
    pack(packet, listSize);

    for (int i = 0; i < listSize; i++)
    {
        std::string dato = std::string(flist->at(i)->c_str());
        int datoSize = dato.length() + 1;
        pack(packet, datoSize);
        packv(packet, dato.c_str(), datoSize);
    }
}

void deserializar_lista_ficheros(std::vector<unsigned char>& packet, std::vector<string*>* flist)
{
    int listSize = unpack<int>(packet);

    for (int i = 0; i < listSize; i++)
    {
        int strSize = unpack<int>(packet);
        char* d = new char[strSize];
        unpackv<char>(packet, d, strSize);
        std::string* dato = new std::string(d);
        delete[] d;

        flist->push_back(dato);
    }
}