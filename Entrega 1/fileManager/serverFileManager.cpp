//Oscar Simon & Juanluis Soto
#include <iostream>
#include <thread>
#include <signal.h>

#include "filemanager_imp.h"


bool RUNNING = true;

void atiende_cliente(int clientID)
{
    fileManager_imp* fm_imp = new fileManager_imp();

    while (!fm_imp->conexionCerrada) fm_imp->recOp(clientID);

    delete fm_imp;
}

int main(int argc, char** argv)
{
    int ipport = 10002;

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