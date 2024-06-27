//Oscar Simon Juanluis Soto
#pragma once
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include "operaciones.h"
#include "utils.h"
#include "persona.h"

class Persona_imp{
	private:
		int clientId;
		Persona* p=nullptr;

	public:
		bool conexionCerrada=false;
	Persona_imp(){

	}
	void recOp(int clientId){
		std::vector<unsigned char> packetIn;
		std::vector<unsigned char> packetOut;

		recvMSG(clientId,packetIn);

		personaOp op = unpack<personaOp>(packetIn);
		switch(op){
			case constructorOp:
			{
				p=new Persona();
				int OK=1;
				pack(packetOut,OK);
			}
			break;
			case destructorOp:
			{
				delete p;

				pack<int>(packetOut,1);
				conexionCerrada=true;
			}
			break;
			case setDniOp:
			{
				std::string dato;

				int tam=unpack<int>(packetIn);
				char* d = new char[tam];
				unpackv<char>(packetIn,d,tam);
				p->setDni(std::string(d));

				pack<int>(packetOut,1);
				delete[] d;
			}
			break;

			case getDniOp:
			{
				std::string dato;
				dato=p->getDni();
				pack(packetOut,1);
				pack(packetOut,(int)dato.length()+1);
				packv(packetOut,dato.c_str(),dato.length()+1);
			}break;
			case salvarOp:{

			}
			break;
			case cargarOp:{

			}
			break;
			default:
			{
				
			}break;
		}
		sendMSG(clientId,packetOut);
	}
};
