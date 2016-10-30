#ifndef ELANGUAGE_H
#define ELANGUAGE_H
#include <QTextStream>
#include <QFile>
#include <QString>
#include <string>
#include <vector>
#include "SpaceEngine/System/EError.h"
#define LANG_ENG "/language/ENG"
using namespace std;
/*
 * TEMPLATE
 *
 *  start{comments}
 *  exit{}
*/
class ELanguage
{
public:
    static QString& selectedLang();
    static QString getWord(const unsigned int &index,const QString&patch=LANG_ENG);
};

#endif // ELANGUAGE_H
