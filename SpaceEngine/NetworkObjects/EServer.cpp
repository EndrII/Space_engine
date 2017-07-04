#include "EServer.h"

EServer::EServer():QTcpServer(){
  //  connect(this,SIGNAL(acceptError(QAbstractSocket::SocketError)),SLOT(acceptError_(QAbstractSocket::SocketError)));
    connect(this,SIGNAL(newConnection()),SLOT(newConnection_()));
}
void EServer::acceptError_(ETcpSocket*c){//возможна утечка памяти сокеты не удаляються
    //c->close();
    clients.removeOne(c);
    emit ClientDisconnected(c);
    delete c;
}
QList<ETcpSocket*>* EServer::getClients(){
    return &clients;
}
void EServer::newConnection_(){
    ETcpSocket *newClient=new ETcpSocket(nextPendingConnection());
    clients.push_back(newClient);
    connect(newClient,SIGNAL(Disconnected(ETcpSocket*)),this,SLOT(acceptError_(ETcpSocket*)));
    connect(newClient,SIGNAL(Message(ETcpSocket*)),this,SLOT(readData(ETcpSocket*)));
    emit ClientConnected(newClient);
}
void EServer::readData(ETcpSocket *c){
    emit Message(c);
}
void EServer::WriteAll(const QByteArray &data){
    for(ETcpSocket*i:clients){
        i->Write(data);
    }
}
void EServer::disconnectClient(ETcpSocket *c){
    c->getSource()->close();
    clients.removeOne(c);
    delete c;
}

EServer::~EServer(){
    for(ETcpSocket *i:clients){
        i->getSource()->abort();
        delete i;
    }
    this->close();
}
