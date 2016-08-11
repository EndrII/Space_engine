#include "EMusic.h"

EMusic::EMusic():
    QMediaPlayer()
{
    connect(this,SIGNAL(durationChanged(qint64)),this,SLOT(changeDuration_(qint64)));
}
void EMusic::changeDuration_(qint64 qi)
{
    dduration_=qi;
}
bool EMusic::EPlay(const QString&url )
{
    this->setMedia(QUrl::fromLocalFile(url));
    this->play();
    return this->state()==PlayingState ;
}
bool EMusic::EPlay(const int&indesx)
{
    if(this->playlist()==NULL||this->playlist()->mediaCount()<indesx)
        return false;
    else
    {
        this->playlist()->setCurrentIndex(indesx);
        this->play();
        return true;
    }
}
bool EMusic::EJump(const double &procent)
{
    if(this->state()!=StoppedState)
    {
        if(procent>1||procent<0)
            return false;
        this->setPosition(this->duration()*procent);
        return true;
    }else
        return false;
}
bool EMusic::EJump(const int &sec)
{
    if(this->state()!=StoppedState)
    {
        if(sec<0)
            return false;
        this->setPosition(sec*1000);
        return true;
    }else
        return false;
}
bool EMusic::addSound(const QString &Url)
{
    if(this->playlist()!=NULL)
    {
        this->playlist()->addMedia(QUrl::fromLocalFile(Url));
        return true;
    }
    return false;
}
bool EMusic::addSound(const QList<QString>&PlayList)
{
    if(this->playlist()!=NULL)
    {
    for(QString s:PlayList)
       this->playlist()->addMedia(QUrl::fromLocalFile(s));
    return true;
    }else
        return false;
}
int EMusic::isEPlay()
{
    if(this->state()==PlayingState&&this->playlist()!=NULL)
    {
        return this->playlist()->currentIndex();
    }else
        return 0;
}
EMusic::~EMusic()

{
}
