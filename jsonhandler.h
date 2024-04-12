#ifndef JSONHANDLER_H
#define JSONHANDLER_H
#include<QJsonObject>

class jsonhandler
{
public:
    jsonhandler();
    QJsonObject handleRequest(const QJsonObject &request);

private:
private:
    QJsonObject handleGetPlaylist(const QJsonObject &request);
    QJsonObject handleVotes(const QJsonObject &request);
};


#endif // JSONHANDLER_H
