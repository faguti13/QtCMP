#ifndef CONNECTIONSERVER_H
#define CONNECTIONSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent);

signals:

public slots:
    void newConnection();

private:
    QTcpServer *server;
};

#endif // CONNECTIONSERVER_H
