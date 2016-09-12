#include "EResursePack.h"

EResursePack::EResursePack()
{

}
bool EResursePack::chekName(const QString &name){
    RESURSE_PACK_DIR;
    QFile f(RESURSE_PACK_DIR_ACSSES);
    if(f.open(QIODevice::ReadOnly)){
        QDataStream stream(&f);
        EResurse find("",0);
        while(find.name()!=name&&!f.atEnd()){
            stream>>find;
        }
        f.close();
        return true;
    }
    return false;
}
EResurse* EResursePack::getResurse(const ui id){
    RESURSE_PACK_DIR;
    QFile f(RESURSE_PACK_DIR_ACSSES);
    EResurse* result=NULL;
    if(f.open(QIODevice::ReadOnly)){
        QDataStream stream(&f);
        result=new EResurse("",0);
        stream.device()->seek(id);
        stream>>*result;
        f.close();
    }
    return result;
}
