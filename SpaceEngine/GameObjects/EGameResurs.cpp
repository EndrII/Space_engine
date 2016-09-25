#include "EGameResurs.h"

EGameResurs::EGameResurs(const QString &Patch){
    READ_THIS(Patch)
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
    description=pack->add(patch);
    class_=E_GAME_RESURS;
}
EGameResurs::EGameResurs(EResurse *desc, const QString& createPatch,const EKord& size, const EKord& kord_, const QString &str):
    EObject(createPatch,size,kord_,str)
{
    description=desc;
    class_=E_GAME_RESURS;
}
EResurse* EGameResurs::getRes()const{
    return description;
}
void EGameResurs::generateThisObject(EResurse *r){
    READ_THIS(r->url())
}
void EGameResurs::saveObject(QString patch){
    if(patch.isEmpty()) patch=Objectpatch;
    Objectpatch=patch;
    if(patch.mid(patch.size()-4)!="robj")
        patch+=".robj";
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
QDataStream& operator<<(QDataStream&stream,EGameResurs&obj){
    stream<<*((EObject*)&obj);
    stream<<(us)obj.description->id();
    return stream;
}
QDataStream& operator>>(QDataStream&stream,EGameResurs&obj){
    stream>>*((EObject*)&obj);
    us temp;
    stream>>temp;
    obj.description=EResursePack::getResurse(temp);
    return stream;
}
EGameResurs::~EGameResurs(){
    delete description;
}
