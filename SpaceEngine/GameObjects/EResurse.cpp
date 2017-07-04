#include "EResurse.h"

EResurse::EResurse(const QString &url,const ui&id, const ui& name, const ui val, const ui &descript)
{
    _url=url;
    _name=ELanguage::getWord(id_name=name,ELanguage::selectedLang());
    _descript=ELanguage::getWord(id_desc=descript,ELanguage::selectedLang());
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
void EResurse::setName(const ui &IndexName){
    _name=ELanguage::getWord(IndexName,ELanguage::selectedLang());
}
void EResurse::setNameId(us id){
    setName(id_name=id);
}
void EResurse::setDescription(const ui &desc){
    _descript=ELanguage::getWord(desc,ELanguage::selectedLang());
}
void EResurse::setDescriptionId(us id){
    setDescription(id_desc=id);
}
const QString& EResurse::name(){
    return _name;
}
const QString& EResurse::desc(){
    return _descript;
}
QImage* EResurse::picture(){
    /*if(!Picture)
        loadImage();*/
    return Picture;
}
us EResurse::idDesc()const{
    return id_desc;
}
us EResurse::idName()const{
    return id_name;
}
QDataStream& operator >>(QDataStream &stream,EResurse& res){
    stream>>res.id_name;
    res._name=ELanguage::getWord(res.id_name,ELanguage::selectedLang());
    stream>>res._url;
    stream>>res.id_desc;
    res._name=ELanguage::getWord(res.id_desc,ELanguage::selectedLang());
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
    stream<<res.id_name;
    stream<<res._url;
    stream<<res.id_desc;
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
