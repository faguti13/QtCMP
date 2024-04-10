#include "serverconnection.h"

Server::Server(QObject *parent)
    : QObject(parent)
    , isServerRunning(false)
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &Server::newConnection);
}

void Server::startServer()
{
    if (!isServerRunning) {
        if (!server->listen(QHostAddress::Any, 8080)) {
            qDebug() << "El servidor no pudo iniciar la escucha";
            return;
        }
        qDebug() << "El servidor está esperando conexiones.";
        isServerRunning = true;
    }
}

void Server::stopServer()
{
    if (isServerRunning) {
        server->close();
        qDebug() << "Servidor detenido.";
        isServerRunning = false;
    }
}

void Server::newConnection()
{
    qDebug() << "Nueva conexión entrante";
    QTcpSocket *socket = server->nextPendingConnection();
    if (!socket) {
        qDebug() << "Error al aceptar la conexión del cliente entrante.";
        return;
    }

    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    qDebug() << "Conexión exitosa con el cliente.";
}
