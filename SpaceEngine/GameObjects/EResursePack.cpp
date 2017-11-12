#include "EResursePack.h"

EResursePack::EResursePack()
{
    load();
}
void EResursePack::save(){
    QFile f(EResursePack::ResursePackDir());
    if(f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
       QDataStream stream(&f);
       stream<<(int)source->size();
       for(EResurse *res:*source){
           stream<<*res;
       }
       f.close();
    }
}
void EResursePack::bufferClear(){
     auto source=CORE_GET_RES;
     for(EResurse *res:*source){
         delete res;
     }
     source->clear();
}
void EResursePack::load(){
    static bool isLoad(false);
    source=CORE_GET_RES;
    if(!isLoad){
        QFile f(EResursePack::ResursePackDir());
        if(f.open(QIODevice::ReadOnly)){
           QDataStream stream(&f);
           int size;
           stream>>size;
           for(int i=0;i<size;i++){
               EResurse *temp=new EResurse("",0);
               stream>>*temp;
               source->operator[](temp->id())=temp;
           }
           f.close();
        }else{
            f.open(QIODevice::WriteOnly|QIODevice::Truncate);
            f.close();
        }
    }
    isLoad=true;
}
bool EResursePack::remove(const unsigned int id){
    return source->remove(id);
}
EResurse *EResursePack::add(const QString& url){
    QFile f(EResursePack::ResursePackDir());
    if(f.exists()){
        ui id=(f.size())?f.size():sizeof(int);
        if(source->count(id)){
            delete source->operator [](id);
            source->remove(id);
        }
        return source->operator [](id)=new EResurse(url,id);
    }else{
        throw EError("Error RESURSE_PACK_DIR, this dir is not detected","EResurse *EResursePack::add(const QString& url)");
    }
    return NULL;
}
bool EResursePack::chekName(const QString &name){
    QFile f(EResursePack::ResursePackDir());
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
QString& EResursePack::ResursePackDir(){
    static QString _dir__;
    return _dir__;
}
EResurse* EResursePack::getResurse(const ui id){
    EResurse* result=NULL;
    auto res=CORE_GET_RES;
    result=res->operator [](id);
    if(!result){
        QFile f(EResursePack::ResursePackDir());
        if(f.open(QIODevice::ReadOnly)){
            QDataStream stream(&f);
            result=new EResurse("",0);
            stream.device()->seek(id);
            stream>>*result;
            f.close();
        }
    }
    return result;
}
resursMap *EResursePack::getList(){
    return source;
}
QString EResursePack::getName(const ui id, bool translated){
    QFile f(EResursePack::ResursePackDir());
    QString result("");
    if(f.open(QIODevice::ReadOnly)){
        QDataStream stream(&f);
        stream.device()->seek(id);
        if(translated){
            QString nametemp;
            stream>>nametemp;
            result=ELanguage::getWord(nametemp);
        }else{
            stream>>result;
        }
        f.close();
    }
    return result;
}
EResursePack::~EResursePack(){

}
