#include "serverconnection.h"
#include <QJsonDocument>
#include <QJsonObject>

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
        emit dataReceived("Datos recibidos del servidor");
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
//Mutex
void Server::dataClient()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket)
        return;

    mutex.lock(); // Bloquea que otros hilos accedan a los datos
    QString data = QString::fromUtf8(socket->readAll());
    mutex.unlock(); // Desbloquea el mutex después de acceder a los datos co

    emit dataReceived(data); // Emite una señal con los datos recibidos
}

/*//Manipulacion Json
void Server::processRequest(const QString &request) {
    QJsonDocument doc = QJsonDocument::fromJson(request.toUtf8());
    if (!doc.isObject()) {
        qWarning() << "La solicitud no es un objeto JSON válido.";
        return;
    }
    QJsonObject obj = doc.object();
    QString action = obj.value("action").toString();

    //Verifica si la accion solicitada en "Get_Playlist"
    if (action == "Get_Playlist") {
        QJsonObject response = getPlaylist();
        QJsonDocument responseDoc(response);
        emit dataReceived(responseDoc.toJson(QJsonDocument::Compact));
        //Verifica si la accion solicitada en "Vote_Up"
    } else if (action == "Vote_Up") {
        QString songId = obj.value("song_id").toString();
        QJsonObject response = voteUp(songId);
        QJsonDocument responseDoc(response);
        emit dataReceived(responseDoc.toJson(QJsonDocument::Compact));
        //Verifica si la accion solicitada en "Vote Down"
    } else if (action == "Vote_Down") {
        QString songId = obj.value("song_id").toString();
        QJsonObject response = voteDown(songId);
        QJsonDocument responseDoc(response);
        emit dataReceived(responseDoc.toJson(QJsonDocument::Compact));
    } else {
        qWarning() << "Acción no reconocida en la solicitud.";
    }
}
*/
