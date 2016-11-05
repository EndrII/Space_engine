#include "ELanguage.h"

QString& ELanguage::selectedLang(){
    static QString lang;
    return lang;
}
QString ELanguage::getWord(const unsigned int &index,const QString&patch)
{
    QFile f((patch==LANG_DEF)?selectedLang():patch);
    QString result="";
    if(f.open(QIODevice::ReadOnly)){
        QTextStream stream(&f);
        QChar temp;unsigned int indexTemp=0;
        while(index>indexTemp&&!stream.atEnd())
        {
            stream>>temp;
            if(temp=='{')
                indexTemp++;
        }
        while(indexTemp&&temp!='}'&&!stream.atEnd())
            stream>>temp;
        if(indexTemp)stream>>temp;
        while(!stream.atEnd()){
            stream>>temp;
            if(temp!='{')
                result.push_back(temp);
            else
                break;
        }
        f.close();
    }
    if(result.isEmpty())
        return "NO DETECTED";
    return result;
}



