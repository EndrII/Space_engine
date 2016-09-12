#ifndef ELANGUAGE_H
#define ELANGUAGE_H
#include <QTextStream>
#include <QFile>
#include <QString>
#include <string>
#include <vector>
#include "SpaceEngine/System/EError.h"
#define LANG_ENG "./language/ENG"
#define PROGRAMM_LANGUAGE static QString lang;
#define PROGRAMM_LANGUAGE_ACSSES lang
using namespace std;
/*
 * TEMPLATE
 *
 *  start
 *  exit|
*/
class ELanguage
{
private:
    int seek;
    QFile *file;
    QTextStream *stream;
    vector<QString> base;
    string name;
public:
    explicit ELanguage(const string &filename);
    QString GetWord(const int& index);//vernyot prevedyonnuyu frazu esli ona sushestvuet
    static QString getWord(const unsigned int &index,const QString&patch=LANG_ENG);
    virtual ~ELanguage();
};

#endif // ELANGUAGE_H
