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
               source->push_back(temp);
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
    for(QList<EResurse*>::iterator i=source->begin();i!=source->end();i++){
        if((*i)->id()==id){
            source->erase(i);
            return true;
        }
    }
    return false;
}
EResurse *EResursePack::add(const QString& url){
    QFile f(EResursePack::ResursePackDir());
    if(f.exists()){
        source->push_back(new EResurse(url,f.size()));
        return source->last();
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
    auto i=res->begin();
    while(i!=res->end()&&(*i)->id()!=id){
        i++;
    }
    if(i==res->end()){
        QFile f(EResursePack::ResursePackDir());
        if(f.open(QIODevice::ReadOnly)){
            QDataStream stream(&f);
            result=new EResurse("",0);
            stream.device()->seek(id);
            stream>>*result;
            f.close();
        }
    }else{
        result=*i;
    }
    return result;
}
QList<EResurse*>* EResursePack::getList(){
    return source;
}
QString EResursePack::getName(const ui id){
    QFile f(EResursePack::ResursePackDir());
    QString result; us nametemp;
    if(f.open(QIODevice::ReadOnly)){
        QDataStream stream(&f);
        stream.device()->seek(id);
        stream>>nametemp;
        result=ELanguage::getWord(nametemp,ELanguage::selectedLang());
        f.close();
    }
    return result;
}
EResursePack::~EResursePack(){

}
