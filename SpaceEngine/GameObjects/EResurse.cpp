#include "EResurse.h"

EResurse::EResurse(const QString &url,const ui&id, const QString& name, const ui val, const QString &descript)
{
    _url=url;
    _name=name;
    _descript=descript;
    if(val>0)
       mass=val;
    Picture=NULL;
    _id=id;
    loadImage();
}
void EResurse::loadImage(){
    if(Picture)
        deleteImage();
    QFile f(_url);
    if(f.open(QIODevice::ReadOnly)){
        QDataStream stream(&f);
        QString patch;
        stream>>patch;
        Picture= ESprite::getHeidImage(patch);
        f.close();
    }else{
        Picture=new QImage();
    }
}
void EResurse::deleteImage(){
    if(Picture){
        delete Picture;
        Picture=NULL;
    }
}
void EResurse::setMass(const ui &val){
    mass=val;
}
ui EResurse::getMass()const{
    return  mass;
}
ui EResurse::id()const{
    return _id;
}
const QString& EResurse::url() const{
    return _url;
}
QMap<us,us>* EResurse::getCraft(){
    return &craft;
}
void EResurse::setUrl(const QString &url){
    _url=url;
}
void EResurse::setName(const QString &IndexName){
    _name=IndexName;
    ELanguage::add(IndexName);
}
void EResurse::setDescription(const QString &desc){
    _descript=desc;
    ELanguage::add(desc);
}
void EResurse::setPicture(const QString &url, bool _default){
    if(_default){
        loadImage();
    }else{
        if(Picture)
            delete Picture;
        Picture=new QImage(url);
    }
}
const QString& EResurse::name(){
    return ELanguage::getWord(_name);
}
const QString & EResurse::desc(){
    return ELanguage::getWord(_descript);
}
QImage* EResurse::picture(){
    return Picture;
}
const QString & EResurse::rawDesc()const{
    return _descript;
}
const QString & EResurse::rawName()const{
    return _name;
}
bool EResurse::isValid()const{
    return QFile(_url).exists();
}
QDataStream& operator >>(QDataStream &stream,EResurse& res){
    stream>>res._name;
    stream>>res._url;
    stream>>res._descript;
    stream>>res._id;
    stream>>res.mass;
    stream>>*res.Picture;
    ui temp=0;
    stream>>temp;
    while(temp--){
        us val,key;
        stream>>key;
        stream>>val;
        res.craft.insert(key,val);
    }
    return stream;
}
QDataStream& operator <<(QDataStream &stream,EResurse& res){
    stream<<res._name;
    stream<<res._url;
    stream<<res._descript;
    stream<<res._id;
    stream<<res.mass;
    if(!res.Picture)
        res.loadImage();
    stream<<(*res.Picture);
    stream<<(ui)res.craft.size();
    for(QMap<us,us>::const_iterator i=res.craft.begin();i!=res.craft.end();i++){
        stream<<i.key();
        stream<<i.value();
    }
    return stream;
}
EResurse::~EResurse(){
    if(Picture)
        deleteImage();
}
