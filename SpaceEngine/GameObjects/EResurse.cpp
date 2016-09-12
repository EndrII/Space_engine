#include "EResurse.h"

EResurse::EResurse(const QString &url,const ui&id, const ui& name, const ui val, const ui &descript)
{
    _url=url;
   PROGRAMM_LANGUAGE
    _name=ELanguage::getWord(id_name=name,PROGRAMM_LANGUAGE_ACSSES);
    _descript=ELanguage::getWord(id_desc=descript,PROGRAMM_LANGUAGE_ACSSES);
    if(val>0)
       value=val;
    Picture=NULL;
    _id=id;
}
void EResurse::loadImage(){
    if(!Picture)
        deleteImage();
    Picture= ESprite::getHeidImage(_url);
}
void EResurse::deleteImage(){
    if(Picture){
        delete Picture;
        Picture=NULL;
    }
}
void EResurse::setValue(const ui &val){
    value=val;
}
ui EResurse::getValue()const{
    return  value;
}
ui EResurse::id()const{
    return _id;
}
/*void EResurse::setId(const ui &id){
    _id=id;
}*/
QMap<us,us>* EResurse::getCraft(){
    return &craft;
}
void EResurse::setName(const ui &IndexName){
    PROGRAMM_LANGUAGE
    _name=ELanguage::getWord(IndexName,PROGRAMM_LANGUAGE_ACSSES);
}
void EResurse::setDescription(const ui &desc){
    PROGRAMM_LANGUAGE
    _descript=ELanguage::getWord(desc,PROGRAMM_LANGUAGE_ACSSES);
}
const QString& EResurse::name(){
    return _name;
}
const QString& EResurse::desc(){
    return _descript;
}
QImage* EResurse::picture(){
    if(Picture)
        loadImage();
    return Picture;
}
QDataStream& operator >>(QDataStream &stream,EResurse& res){
    PROGRAMM_LANGUAGE
    stream>>res.id_name;
    res._name=ELanguage::getWord(res.id_name,PROGRAMM_LANGUAGE_ACSSES);
    stream>>res._url;
    stream>>res.id_desc;
    res._name=ELanguage::getWord(res.id_desc,PROGRAMM_LANGUAGE_ACSSES);
    stream>>res._id;
    return stream;
}
QDataStream& operator <<(QDataStream &stream,const EResurse& res){
    stream<<res.id_name;
    stream<<res._url;
    stream<<res.id_desc;
    stream<<res._id;
    return stream;
}
EResurse::~EResurse(){
    if(Picture)
        deleteImage();
}
