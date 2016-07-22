/*#include "./SpaceEngine/Objects/EShell.h"
EShell::EShell(const QString &url, EObject *faiter, const EKord&Size, const int&timelive, const int &spied, Control *ctr, EModuleObject **Target):
    EObject(size,kord,)
{
    timLive=new QTime();
    this->setSpeed(spied);
    Live=timelive;
    Faiter=faiter;
    control=ctr;
    target=Target;
    this->setAcceleration(10000);
    this->setMovMode(Key);
    indexSound=0;
    Off();
}
bool EShell::isOn()
{
    return action;
}
void EShell::Off()
{
    this->draw_flag=false;
    this->action=false;
}
void EShell::On()
{
    kord=Faiter->getKord();
    movKord=Faiter->getKord();
    this->draw_flag=true;
    this->action=true;
}
void EShell:: setDamage(const int &de)
{
    Damage=de;
}
void EShell::setSoundIndex(const int &SoundIndex_in_ESoundCenter)
{
    indexSound=SoundIndex_in_ESoundCenter;
}
int EShell::getDamage()
{
    return Damage;
}
void EShell::start()
{
    On();
    timLive->start();
    this->setUgol(Faiter->getUgol());
    this->action_Begin(_up);
}
void EShell::_timeRender()
{
    Tsync=*timeSync;
}
void EShell::_render()
{
    radius+=acceleration/1000*Tsync;
    if(abs(radius)>speed) radius=speed;
    if(type==Sprite&&testsprite)
    {
        Sprite_->render();
        skrin=Sprite_->getFrames();
    }
    _ugol=ugol;
    movKord.X=kord.X+radius*cos(_ugol*PI/180);
    movKord.Y=kord.Y+radius*sin(_ugol*PI/180);
    kord.X+=(movKord.X-kord.X)/1000*Tsync;
    kord.Y+=(movKord.Y-kord.Y)/1000*Tsync;
}

void EShell::render()
{
   //if(PriorityControl()) return;
    if(action)
    {
        if(timLive->elapsed()>=Live)
            Off();
        switch (*control)
        {
        case selectAI:
            if(kord.inQuan((*target)->getKord()-(*target)->getSize()+(rand()%(int)(*target)->getSize().X),
                            (*target)->getKord()+(*target)->getSize()-(rand()%(int)(*target)->getSize().X)))
            {
                (*target)->damag_of_target(Damage);
                ((EMaps*)this->getMapAdres())->callExplosion(this);
                emit SoundPlay(indexSound);
                Off();
            }

            break;
        case selectPlayer:
            for(EObject *i:**object_list)
                 if((((EGameObject*)i)->isLive())&&
                      (i!=this)&&(i->getSlave()!=Faiter->getSlave())&&
                      (kord.inQuan(i->getKord()-i->getSize()-siz+(rand()%(int)i->getSize().X),
                       i->getKord()+i->getSize()+siz-rand()%(int)i->getSize().X)))

                 {
                        ((EGameObject*)i)->damag(Damage);
                        ((EMaps*)this->getMapAdres())->callExplosion(this);
                        emit SoundPlay(indexSound);
                        ((EObject*)this->getSlave())->setPlayerTaraget(i->getSlave());
                        Off();
                 }
            break;
        default:
            break;
        }
        this->_timeRender();
        this->_render();
    }
}
EShell::~EShell()
{
    delete timLive;
}
*/
