
#include "./SpaceEngine/Objects/EGameObject.h"
EGameObject::EGameObject(QObject *ptr)
    :EModuleObject(ptr)
{
    constructorFork();
}
EGameObject::EGameObject(const EKord& size,const EKord& kord,const QString&objPatch, QObject *ptr)
    :EModuleObject(objPatch,ptr)
{
    setSize(size);
    setKord(kord);
    constructorFork();
}
EGameObject::EGameObject(const QString& createPatch,const EKord& size,const EKord& kord,const QString& patchSprite, QObject *ptr)
    :EModuleObject(createPatch,size,patchSprite,ptr)
{
    setKord(kord);
    constructorFork();
}
void EGameObject::constructorFork(){
    MaxHeals=1;
    dead_effect=NULL;
    Heals=1;
    Defense=0;
    Fire=false;
    noDraw_flag=false;
    class_=E_GAMEOBJECT;
    IndexPlay=0;
}
bool EGameObject::damag(const int &dem)
{
    if(Heals>0)
    {
        Heals-=dem*(100-Defense)/100;
        if(Heals<=0)
        {
            if(dead_effect!=NULL)
                dead_effect->run((EMaps*)getMap(),EKord(_x,_y));
            emit playSound(IndexPlay);
            emit dead(this);
        }
        emit HealsChange(Heals);
    }
    return Heals<=0;
}
QDataStream& operator <<(QDataStream&stream,const EGameObject&obj){
    stream<<*((EModuleObject*)&obj);
    stream<<obj.MaxHeals;
    stream<<obj.RadarPower;
    stream<<obj.MaxHeals;
    stream<<*obj.dead_effect;
    stream<<obj.IndexPlay;
    return stream;
}
QDataStream& operator >>(QDataStream&stream,EGameObject&obj){
    stream>>*((EModuleObject*)&obj);
    stream>>obj.MaxHeals;
    stream>>obj.RadarPower;
    stream>>obj.MaxHeals;
    stream>>*obj.dead_effect;
    stream>>obj.IndexPlay;
    return stream;
}
void EGameObject::saveObject(QString patch){
    if(patch.mid(patch.size()-4)!="gobj")
        patch+=".gobj";
    QFile f(patch);
    QDataStream s(&f);
    if(f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        s<<*this;
        f.close();
    }else{
        throw EError("file no detected!","EObject::EObject(const QString &str, QObject *ptr):");
    }
}
bool EGameObject::repair(const int &rep)
{
    if(Heals>0)
    {
        Heals+=rep;
        emit HealsChange(Heals);
    }else return false;
    if(Heals>=MaxHeals)
    {
        Heals=MaxHeals;
        emit HealsChange(Heals);
        return true;
    }
    return false;
}
void EGameObject::setDeadSound(const int &i)
{
    IndexPlay=i;
}
void EGameObject::setDeadEffect(EEffect *effect){
    dead_effect=effect;
}
void EGameObject::setHealsMax(const int &heals)
{
    Heals=heals;
    MaxHeals=heals;
}
void EGameObject::setHeals(const int &heals)
{
    Heals=heals;
    if(Heals<0) emit dead(this);
    emit HealsChange(Heals);
}
int EGameObject::getHeals()
{
    return Heals;
}
int EGameObject::getHealsMax()
{
    return MaxHeals;
}
void EGameObject::setDefense(const int &def)
{
    Defense=def;
}
void EGameObject::setRadarPower(const int &i){
    RadarPower=i;
}
int EGameObject::getRadarPower()const{
    return RadarPower;
}
int EGameObject::getDefense()
{
    return Defense;
}
void EGameObject::_animation_render()
{
    setCurentFrame((MaxHeals-Heals)*getLongSprite(0)/MaxHeals);
}
void EGameObject::fire(bool b)
{
    Fire=b;
}
bool EGameObject::isLive()
{
    return Heals>0;
}
void EGameObject::render()
{
    _timeRender();
    if(!noDraw_flag)_animation_render();
    _keyRender();
    _render();
}

EGameObject::~EGameObject()
{
    if(dead_effect!=NULL)
        delete dead_effect;
}
