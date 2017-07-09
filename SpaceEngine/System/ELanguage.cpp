#include "ELanguage.h"

//QString& ELanguage::selectedLang(){
//    static QString lang;
//    return lang;
//}
void ELanguage::setLanguage(const QString &patch){
    SelectedLang=patch;
}
void ELanguage::setLanguage(const QUrl &patch){
    QString tempPatch= patch.path();
#ifdef Q_OS_WIN
    tempPatch=tempPatch.right(tempPatch.size()-1);
#endif
    SelectedLang=tempPatch;
}
//QStringList& ELanguage::Buffer(){
//    static QStringList temp;
//    return temp;
//}
void ELanguage::WriteToJson(){
    QFile lang(SelectedLang);
    if(lang.open(QFile::WriteOnly|QFile::Truncate)){
        lang.write(QJsonDocument(source).toBinaryData());
    }
}
bool ELanguage::ParseJson(const QString &url,bool forse){
    if(source.size()<=0||SelectedLang!=url||forse){
        QFile lang(SelectedLang);
        if(lang.open(QFile::ReadOnly)){
            source=QJsonDocument(QJsonDocument::fromBinaryData(lang.readAll())).object();
            return true;
        }
        return false;
    }
    return true;
}
QJsonObject::iterator ELanguage::add(const QString &word){
    return  source.insert(word,NONE);
}
void ELanguage::remove(const QString &word){
    return source.remove(word);
}
QString ELanguage::getWord(const QString &index,const QString&patch)
{
    if(ParseJson((patch==LANG_DEF)?SelectedLang:patch))
        return "NO DETECTED";
    QJsonValue result(source[index].toString());
    if(result.isUndefined())
        return "NO DETECTED";
    return result.toString();\
}



