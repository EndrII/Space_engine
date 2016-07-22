#include "ELanguage.h"

ELanguage::ELanguage(const string &filename)
{
    seek=0;
    name=filename;
    file=new QFile(QString::fromStdString(name));
    if(file->open(QIODevice::ReadOnly| QIODevice::Text))
    {
        stream=new QTextStream(file);
        QString temp; QChar temp2;
        while(true)
        {
            file->seek(seek++);
            (*stream)>>temp2;
            if(temp2=='|'){base.push_back(temp);break;}
            if(temp2!='\n')
                temp.push_back(temp2);
            else
            {
                base.push_back(temp);
                temp.clear();
            }
        }
        file->close();
        delete stream;
    }else
    {
        throw EError(34,"ELanguage::ELanguage(const string &filename)");
        delete this;
        return;
    }
}
QString ELanguage::GetWord(const int &index)
{
    if((unsigned)index>=base.size())
        return "NOT DETECTED";
    else
        return base[index];
}
ELanguage::~ELanguage()
{
    file->flush();
    delete file;
}

