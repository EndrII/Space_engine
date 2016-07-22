#include "EFon.h"
EFon::EFon(const QString &urlSprite, const float& kf, const float &sloi)
    :EObject(urlSprite)
{
    this->setW(10000000);
    this->setH(10000000);
    class_=E_FON;
    Max=kf;
    this->setSloi(sloi);
    this->setCurentFrame(0);
}
QDataStream& operator>>(QDataStream&stream,EFon&obj){
    stream>>*((EObject*)&obj);
    stream>>obj.Max;
    return stream;
}
QDataStream& operator<<(QDataStream&stream,EFon&obj){
    stream<<*((EObject*)&obj);
    stream<<obj.Max;
    return stream;
}
float EFon::getMax(){
    return Max;
}

void EFon::render(){
    this->render_sprite();
}
EFon::~EFon(){
}
