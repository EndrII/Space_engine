#include "GameResurs.h"

GameResurs::GameResurs(const QString &Patch):
    EObject(Patch)
{
}
GameResurs::GameResurs(EResurse *desc, const QString& createPatch,const EKord& size, const EKord& kord_, const QString &str):
    EObject(createPatch,size,kord_,str)
{
    description=desc;
}
EResurse* GameResurs::getRes()const{
    return description;
}
void GameResurs::saveObject(QString patch){
    if(patch.mid(patch.size()-4)!="robj")
        patch+=".robj";
    QFile f(patch);
    if(!f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        throw EError("file not detected!","void GameResurs::saveObject(QString patch)");
    }else{
        QDataStream s(&f);
        s<<*this;
        f.close();
    }
}
QDataStream& operator<<(QDataStream&stream,GameResurs&obj){
    stream<<*((EObject*)&obj);
    stream<<(us)obj.description->id();
    return stream;
}
QDataStream& operator>>(QDataStream&stream,GameResurs&obj){
    stream>>*((EObject*)&obj);
    us temp;
    stream>>temp;
    obj.description=EResursePack::getResurse(temp);
    return stream;
}
GameResurs::~GameResurs(){
    delete description;
}
