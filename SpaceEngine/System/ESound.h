/*#ifndef ESOUND_H
#define ESOUND_H
#include <QSound>

class ESound:public QObject
{
    Q_OBJECT
private:
    QSound *sounds;//massiv zvukov
    short value,zap;//razmer massiva
    bool sond;//proverka
public:
    ESound(QObject *ptr=0);
    void setSoundValue(short s=1);//ustonovit kol vo zvukov
    short getSoundValue();//poluchit kol vo zvukov
    bool addSound(QString); //dobavit zvuk
    ~ESound();
public slots:
   void play(short number);//slot oo nachale
   void stop(short number);//slot ob ostonovki
signals:
  void finished(short);//signal ozaverheniya;
};

#endif // ESOUND_H
*/
