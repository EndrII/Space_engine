#ifndef ESERVER_H
#define ESERVER_H
#include <QTcpServer>
#include <QList>
#include <QDataStream>
#include "ETcpSocket.h"
class EServer:public QTcpServer{
    Q_OBJECT
protected:
    QList<ETcpSocket*> clients;
private slots:
    void acceptError_(ETcpSocket*);
    void newConnection_();
    void readData(ETcpSocket*_client);
public:
    EServer();
    void WriteAll(const QByteArray&);
    void disconnectClient(ETcpSocket*);
    QList<ETcpSocket*>* getClients();
    ~EServer();
signals:
    void Error(QString);
    void Message(ETcpSocket*);
    void ClientDisconnected(ETcpSocket*);
    void ClientConnected(ETcpSocket*);
};

#endif // CLIENT_H
