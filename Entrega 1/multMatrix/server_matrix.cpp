#include <signal.h>
#include <thread>

#include "operaciones.h"
#include "matrix_imp.h"

bool RUNNING = true;

void atiende_cliente(int cliente_id)
{
	Matrix_imp* mm_imp = new Matrix_imp();

	while (!mm_imp->conexionCerrada) mm_imp->recOp(cliente_id);

	delete mm_imp;
}

int main(int argc, char** argv)
{
	int ipport = 10001;

	// Inicializacion del servidor
	int socket = initServer(ipport);
	std::cout << "Creando instancia del servidor." << std::endl;

	// Bucle principal
	while (RUNNING)
	{
		if (!checkClient()) usleep(1000);
		else
		{
			// Crear un nuevo thread para atender al cliente
			std::cout << "Nuevo cliente conectado." << std::endl;
			new std::thread(atiende_cliente, getLastClientID());
		}
	}

	// Cierre de la conexion
	close(socket);
}
