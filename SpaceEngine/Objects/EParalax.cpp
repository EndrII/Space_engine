#include "EParalax.h"

EParalax::EParalax(QString patch,QObject *ptr)
    :EModuleObject(ptr)
{
    QFile f(patch);
    if(!f.open(QIODevice::ReadOnly)){
        throw EError("file no detected!","EObject::EObject(const QString &str, QObject *ptr):");
    }else{
        if(patch.mid(patch.size()-4)!="eprx")
            patch+=".eprx";
        QDataStream s(&f);
        s>>*this;
        f.close();
    }
}
EParalax::EParalax(const float &up,const QStringList &list, QObject *ptr):
    EModuleObject(ptr)
{
    defUp=1;
    ignore_flag=false;
    forceRenderFlag=true;
    class_=E_PARALAX;
    float temp=FIRST_FON;
    for(QString s:list){
        addObject(new EFon(s,defUp+=up,temp+=SLOI_FON));
    }
}
QDataStream& operator<<(QDataStream&stream,EParalax&obj){
    stream<<*((EModuleObject*)&obj);
    return stream;
}
QDataStream& operator>>(QDataStream&stream,EParalax&obj){
    stream>>*((EModuleObject*)&obj);
    obj.Value=obj.getModuleVector()->size();
    return stream;
}
void EParalax::saveObject(QString patch){
    QFile f(patch);
    if(!f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        throw EError("file no detected!","EObject::EObject(const QString &str, QObject *ptr):");
    }else{
        if(patch.mid(patch.size()-4)!="eprx")
            patch+=".eprx";
        QDataStream s(&f);
        s<<*this;
        f.close();
    }
}
void EParalax::render()
{
    for(EObject*i:elements)
        i->render();
}
EParalax::~EParalax()
{

}
