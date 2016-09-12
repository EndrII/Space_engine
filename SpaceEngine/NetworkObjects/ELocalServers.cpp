#include "ELocalServers.h"
ELocalServers::ELocalServers():
    QObject()
{
   wiat.setInterval(1000);
   connect(&wiat,SIGNAL(timeout()),SLOT(scaned_()));
}
void ELocalServers::clear(){
    results.clear();
}
void ELocalServers::setInterval(int msec){
    wiat.setInterval(msec);
}
void ELocalServers::clearSocets(){
    for(ETcpSocket* i:socets)
        delete i;
    socets.clear();
}
QHostAddress ELocalServers::thisAdress(){
    QList<QHostAddress> adress= QNetworkInterface::allAddresses();
    for(QHostAddress &ip:adress)
        if(ip.protocol() == QAbstractSocket::IPv4Protocol && ip != QHostAddress(QHostAddress::LocalHost))
            return ip;
    return QHostAddress::LocalHost;
}
void ELocalServers::scane(){
    if(!socets.empty())
        return ;
    QList<QHostAddress> adress= QNetworkInterface::allAddresses();
    clear();
    wiat.start();
    for(QHostAddress &ip:adress){
        if(ip.protocol() == QAbstractSocket::IPv4Protocol && ip != QHostAddress(QHostAddress::LocalHost)){
            for(int i=0;i<256;i++){
                QString adr= ip.toString();
                adr=adr.left(adr.lastIndexOf("."))+"."+QString::number(i);
                ETcpSocket *temp=new ETcpSocket;
                connect(temp,SIGNAL(Connected(ETcpSocket*)),SLOT(connected(ETcpSocket*)));
                temp->getSource()->connectToHost(adr,LOCAL_PORT);
                socets.push_back(temp);
            }
        }
    }
}
void ELocalServers::scaned_(){
    wiat.stop();
    emit scaned(&results);
    clearSocets();
}
void ELocalServers::connected(ETcpSocket *c){
    socets.removeOne(c);
    results.push_back(c);
}
ELocalServers::~ELocalServers(){
    for(ETcpSocket* i: socets)
        delete i;
    socets.clear();

}
