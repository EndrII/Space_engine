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
void EResurse::setName(const QString &IndexName){
    _name=IndexName;
}
/*void EResurse::setNameId(us id){
    setName(id_name=id);
}*/
void EResurse::setDescription(const QString &desc){
    _descript=desc;
}
/*void EResurse::setDescriptionId(us id){
    setDescription(id_desc=id);
}*/
const QString& EResurse::name(){
    return ELanguage::getWord(_name);
}
const QString& EResurse::desc(){
    return ELanguage::getWord(_descript);
}
QImage* EResurse::picture(){
    /*if(!Picture)
        loadImage();*/
    return Picture;
}
//us EResurse::idDesc()const{
//    return id_desc;
//}
//us EResurse::idName()const{
//    return id_name;
//}
QDataStream& operator >>(QDataStream &stream,EResurse& res){
    stream>>res._name;
    stream>>res._url;
    stream>>res._descript;
    stream>>res._id;
    stream>>res.mass;
    res.Picture=new QImage();
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
    stream<<*res.Picture;
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
