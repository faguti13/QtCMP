#ifndef CONNECTIONSERVER_H
#define CONNECTIONSERVER_H

#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    void startServer(); // Método para iniciar el servidor
    void stopServer();  // Método para detener el servidor

signals:

public slots:
    void newConnection();

private:
    QTcpServer *server;
    bool isServerRunning; // Variable para controlar el estado del servidor
};

#endif // CONNECTIONSERVER_H
