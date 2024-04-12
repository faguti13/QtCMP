#ifndef CONNECTIONSERVER_H
#define CONNECTIONSERVER_H

#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    void startServer(); // Método para iniciar el servidor
    void stopServer();  // Método para detener el servidor
    void sendJsonToListeningClients(const QJsonObject &jsonObject);
    /*void processRequest(const QString &request);
*/
signals:
    void dataReceived(const QString &data);


public slots:
    void newConnection();
    void dataClient();

    // void processRequest(const QString &request); // declaración de la función
    /* QJsonObject getPlaylist();
    QJsonObject voteUp(const QString& songId);
    QJsonObject voteDown(const QString& songId);*/

private:
    QTcpServer *server;
    QList<QTcpSocket *> clientSockets; // Declaración de clientSockets como lista de sockets
    bool isServerRunning; // Variable para controlar el estado del servidor
    QMutex mutex;
};

#endif // CONNECTIONSERVER_H
