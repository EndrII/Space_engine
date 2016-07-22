/*#include "ESound.h"

ESound::ESound(QObject *ptr):
    QObject(ptr)
{
   value=0;
   zap=0;
   sond=false;
}
void ESound::setSoundValue(short s)
{
    if(sond) delete[] sounds;
    sounds=new QSound[s];
    sond=true;
}
short ESound::getSoundValue()
{
    return value;
}
bool ESound::addSound(QString name)
{
    if(sond)
    {
        sounds[zap].s
    }
}
ESound::~ESound()
{

}

*/
