#include "connectionserver.h"

Server::Server(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);

    // Intenta iniciar el servidor en todas las interfaces de red y en el puerto 8080
    if (!server->listen(QHostAddress::Any, 8080)) {
        //Si el server no se puede iniciar....
        qDebug() << "El servidor no pudo iniciar la escucha";
        exit(1); //El programa se cierra
    }
    //Si el server se inicia correctamente,podrá esperar solictudes de conexión de los clientes.
    qDebug() << "El servidor está esperando conexiones.";

    //Manejo de la conexión establecida con el cliente
    connect(server, &QTcpServer::newConnection, this, &Server::newConnection);
}

//Función que establece una nueva conexión con un cliente
void Server::newConnection()
{
    qDebug() << "Nueva conexión entrante";
    //Obtiene las conexiones pendientes de clientes (manejo de varios clientes)
    QTcpSocket *socket = server->nextPendingConnection();
    if (!socket) {
        qDebug() << "Error al aceptar la conexión del cliente entrante.";
        return;
    }

    //Elimina el socket cuando se desconecte del cliente
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    qDebug() << "Conexión exitosa con el cliente.";

}
