#ifndef LocalServers_H
#define LocalServers_H
#include <QNetworkInterface>
#include <QHostInfo>
#include <QList>
#include <QTimer>
#include "SpaceEngine/System/EError.h"
#include "ETcpSocket.h"
#define LOCAL_PORT 7777
/**
 * @brief The LocalServers class
 * сканирование сети при помащи утилиты пинг
 * андройд  "/system/bin/ping -c 1 8.8.8.8";
 * linux    "ping -c 1  8.8.8.8";
 * windows  "ping -c 1 "8.8.8.8";
 */
/*
 *
 * 2й способ используя ТСП сокеты
 */
class ELocalServers:public QObject{
    Q_OBJECT
private:
    QList<ETcpSocket*> socets;
    QList<ETcpSocket*> results;
    QTimer wiat;
    void clear();
    void clearSocets();
private slots:
    void scaned_();
    void connected(ETcpSocket *);
public:
    void scane();
    void setInterval(int msec);
    static QHostAddress thisAdress();
    ELocalServers();
    ~ELocalServers();
signals:
    void scaned(QList<ETcpSocket*>*);
};
#endif // LocalServers_H
