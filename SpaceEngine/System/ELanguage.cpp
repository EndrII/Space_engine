#include "ELanguage.h"

QString& ELanguage::selectedLang(){
    static QString lang;
    return lang;
}
void ELanguage::setLanguage(const QString &patch){
    selectedLang()=patch;
    Buffer().clear();
}
QStringList& ELanguage::Buffer(){
    static QStringList temp;
    return temp;
}
QString ELanguage::getWord(const int &index,const QString&patch)
{
    QFile f((patch==LANG_DEF)?selectedLang():patch);
    QString tempString;
    QStringList &buffer = ELanguage::Buffer();
    if(buffer.size()<=index&&f.open(QIODevice::ReadOnly)){
        QTextStream stream(&f);
        stream.setCodec("UTF8");
        tempString=stream.readAll();
        buffer.clear();
        int end=0;
        while((end=tempString.indexOf('{'))>-1){
            buffer.push_back(tempString.left(end));
            tempString.remove(0,tempString.indexOf('}')+2);
        }
        f.close();
    }
    if(buffer.size()<=index)
        return "NO DETECTED";
    return buffer[index];
}



