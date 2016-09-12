#include "EFon.h"
EFon::EFon(){
}
EFon::EFon(const QString &urlSprite, const float& kf, const float &sloi)
    :EObject(urlSprite,EKord(0),EKord(0),urlSprite)
{
    this->setW(10000000);
    this->setH(10000000);
    class_=E_FON;
    Max=kf;
   //size_=this->get
   // size_=(this->getSource()->data()[0]->width()>this->getSource()->data()[0]->height())?this->getSource()->data()[0]->height():this->getSource()->data()[0]->width();
    this->setSloi(sloi);
    this->setCurentFrame(0);
}
QDataStream& operator>>(QDataStream&stream,EFon&obj){
    stream>>*((EObject*)&obj);
    stream>>obj.Max;
    //stream>>obj.size_;
    return stream;
}
QDataStream& operator<<(QDataStream&stream,EFon&obj){
    stream<<*((EObject*)&obj);
    stream<<obj.Max;
    //stream<<obj.size_;
    return stream;
}
/*float EFon::getminsize(){
    return size_*(Max-1);
}*/
float EFon::getMax()const{
    return Max-1;
}
void EFon::setMax(const  float &max){
    Max=max;
}
void EFon::render(){
    this->render_sprite();
}
EFon::~EFon(){
}
