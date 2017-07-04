#include "EGameResurs.h"

EGameResurs::EGameResurs(const QString &Patch,EResursePack *pack){
    READ_THIS(Patch)
    pack_=pack;
    class_=E_GAME_RESURS;
}
EGameResurs::EGameResurs(EObject *copy, EResursePack *pack):
    EObject()
{
    this->copy(copy);
    QString patch=Objectpatch;
    pack_=pack;
    if(patch.mid(patch.size()-4)!="robj")
        patch+=".robj";
    description=new EItem(pack->add(patch));
    class_=E_GAME_RESURS;
}
EGameResurs::EGameResurs(EResurse *desc, const QString& createPatch, const EKord& size, const EKord& kord_, const QString &str):
    EObject(createPatch,size,kord_,str)
{
    description= new EItem(desc);
    class_=E_GAME_RESURS;
}
void EGameResurs::size_to_value(){
    setSize(EKord::Random(description->getValue()*massa*0.9,description->getValue()*massa*1.1,_h/_w));
}
EItem *EGameResurs::getRes()const{
    return description;
}
void EGameResurs::generateThisObject(EResurse *r){
    READ_THIS(r->url())
}
void EGameResurs::saveObject(QString patch){
    if(patch.isEmpty()) patch=Objectpatch;
    if(patch.mid(patch.size()-4)!="robj")
        patch+=".robj";
    Objectpatch=patch;
    QFile f(patch);
    if(!f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        throw EError("file not detected!","void EGameResurs::saveObject(QString patch)");
    }else{
        QDataStream s(&f);
        s<<*this;
        f.close();
    }
    pack_->save();
}
void EGameResurs::RandomValue(int max){
    int temp=rand()%max;
    description->setValue(temp);
    size_to_value();
}
QDataStream& operator<<(QDataStream&stream,EGameResurs&obj){
    stream<<*((EObject*)&obj);
    stream<<(ui)obj.description->getValue();
    stream<<(us)obj.description->getSource()->id();
    return stream;
}
QDataStream& operator>>(QDataStream&stream,EGameResurs&obj){
    stream>>*((EObject*)&obj);
    ui temp1; us temp2;
    stream>>temp1;
    stream>>temp2;
    obj.description=new EItem(EResursePack::getResurse(temp2));
    obj.description->setValue(temp1);
    return stream;
}
EGameResurs::~EGameResurs(){
    delete description;
}
