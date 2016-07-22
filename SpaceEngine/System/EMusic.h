#ifndef EMUSIC_H
#define EMUSIC_H
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QFile>
class EMusic:public QMediaPlayer//klas dlya vosproizvedenii musiki
{
    Q_OBJECT
private:
    qint64 dduration_;
private slots:
    void changeDuration_(qint64);
public:
    explicit EMusic();
    bool EPlay(const QString &url);
    bool EPlay(const int&indesx);//vosproizvedyot pesnyo iz play lista
    bool EJump(const double &procent); //0 - 1
    bool EJump(const int &sec);//
    bool addSound(const QString&Url);//dobavit v spisok vosproizvedeniya
    bool addSound(const QList<QString>&PlayList);
    int  isEPlay();//vrnyot 0 esli ne igraet ili nomer kompozozii
    ~EMusic();
};

#endif // EMUSIC_H
