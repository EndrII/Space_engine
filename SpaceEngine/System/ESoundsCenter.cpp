#include "ESoundsCenter.h"

ESoundsCenter::ESoundsCenter():
    QObject()
{

}
void ESoundsCenter::LoopPlay(const int &index, const bool &b)
{
    sound_base[index]->setLoopCount(b);
}
bool ESoundsCenter::getLoop(const int &index)
{
    return sound_base[index]->loopCount();
}
void ESoundsCenter::setValue(const float &val)
{
    for(QSoundEffect* i:sound_base)
        i->setVolume(val);
}
int ESoundsCenter::addSound(const QString &Url)

{
    QSoundEffect *temp=new QSoundEffect();
    temp->setSource(QUrl::fromLocalFile(Url));
    sound_base.push_back(temp);
    return sound_base.size();
}
QVector<QSoundEffect *> *ESoundsCenter::getSoundList()
{
    return &sound_base;
}
void ESoundsCenter::clear()
{
    for(QSoundEffect* i:sound_base)
        delete i;
    sound_base.clear();
}
void ESoundsCenter::Play(int i)
{
    if(i<sound_base.size())
        sound_base[i]->play();
}
void ESoundsCenter::Stop(int i)
{
    if(i<sound_base.size())
        sound_base[i]->stop();
}
ESoundsCenter::~ESoundsCenter()
{
    this->clear();
}
