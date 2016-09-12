#include "EParalax.h"

EParalax::EParalax(QString patch, QObject *ptr)
    :EModuleObject(ptr)
{
    QFile f(patch);
    setW(100000000);
    setH(100000000);
    class_=E_PARALAX;
    noDraw_flag=false;
    ignore_flag=false;
    forceRenderFlag=true;
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
    setW(100000000);
    setH(100000000);
    class_=E_PARALAX;
    defUp=1-up;
    noDraw_flag=false;
    ignore_flag=false;
    forceRenderFlag=true;
   // class_=E_PARALAX;
    float temp=FIRST_FON;
    for(QString s:list){
        addObject(new EFon(s,defUp+=up,temp+=SLOI_FON));
    }
}
void EParalax::changeUp(const float &up){
    defUp=1-up;
    for(ModuleItem o: elements){
        ((EFon*)o.obj)->setMax(defUp+=up);
    }
}
QDataStream& operator<<(QDataStream&stream,EParalax&obj){
    stream<<*((EModuleObject*)&obj);
    stream<<(us)obj.elements.size();
    WRITEMODULE(EFon)
    return stream;
}
QDataStream& operator>>(QDataStream&stream,EParalax&obj){
    stream>>*((EModuleObject*)&obj);
    us temp;
    stream>>temp;
    READMODULE(EFon)
    return stream;
}
void EParalax::restore(const QStringList &UrlList,const float& up){
    elements.clear();
    defUp=1-up;
    float temp=FIRST_FON;
    for(QString s:UrlList){
        addObject(new EFon(s,defUp+=up,temp+=SLOI_FON));
    }
}
void EParalax::addBack(const QString &url,const float &up){
    if(elements.size()!=0){
        addObject(new EFon(url,defUp+=up,elements.back().obj->getSloi()+SLOI_FON));
    }else{
        addObject(new EFon(url,defUp+=up,FIRST_FON));
    }
}
void EParalax::removeLast(){
    if(elements.size()>0)
        deleteElement(elements.back().obj);
}
void EParalax::saveObject(QString patch){
    if(patch.mid(patch.size()-4)!="eprx")
        patch+=".eprx";
    QFile f(patch);
    if(!f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        throw EError("file no detected!","EObject::EObject(const QString &str, QObject *ptr):");
    }else{
        QDataStream s(&f);
        s<<*this;
        f.close();
    }
}
void EParalax::render()
{
    EModuleObject::render();
}
EParalax::~EParalax()
{

}
