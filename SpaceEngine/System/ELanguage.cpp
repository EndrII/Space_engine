#include "ELanguage.h"


QString& ELanguage::SelectedLang(){
    static QString lang;
    return lang;
}
void ELanguage::setLanguage(const QString &patch){
    SelectedLang()=patch;
}
void ELanguage::setLanguage(const QUrl &patch){
    QString tempPatch= patch.path();
#ifdef Q_OS_WIN
    tempPatch=tempPatch.right(tempPatch.size()-1);
#endif
    SelectedLang()=tempPatch;
}
ELanguage::SourceMap& ELanguage::source(){
    static ELanguage::SourceMap temp;
    return temp;
}
const QString& ELanguage::empty(){
    static QString temp("NO DETECTED");
    return temp;
}
void ELanguage::WriteToJson(){
    QFile lang(SelectedLang());
    if(lang.open(QFile::WriteOnly|QFile::Truncate)){
        ELanguage::SourceMap::iterator i=source().begin();
        QJsonObject object;
        while(i!=source().end()){
            object.insert(i.key(),i.value());
            i++;
        }
        lang.write(QJsonDocument(object).toJson());
        lang.close();
    }
}
bool ELanguage::ParseJson(const QString &url,bool forse){
    if(source().size()<=0||SelectedLang()!=url||forse){
        QFile lang(SelectedLang());
        if(lang.open(QFile::ReadOnly)){
            QJsonObject obj(QJsonDocument::fromJson(lang.readAll()).object());
            source().clear();
            QJsonObject::iterator i=obj.begin();
            while(i!=obj.end()){
                source().insert(i.key(),i.value().toString());
                i++;
            }
            lang.close();
            return true;
        }
        return false;
    }
    return true;
}
void ELanguage::save(){
    WriteToJson();
}
ELanguage::SourceMap::iterator ELanguage::add(const QString &word){
    return  source().insert(word,NONE);
}
void ELanguage::remove(const QString &word){
    source().remove(word);
}
const QString& ELanguage::getWord(const QString &index,const QString&patch)
{
    if(ParseJson((patch==LANG_DEF)?SelectedLang():patch)&&
            source().find(index)!=source().end())
        return source()[index];
    else
        return empty();
}



