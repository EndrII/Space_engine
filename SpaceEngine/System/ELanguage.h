#ifndef ELANGUAGE_H
#define ELANGUAGE_H
#include <QTextStream>
#include <QFile>
#include <QString>
#include <string>
#include <vector>
//#include "SpaceEngine/System/EError.h"
#define LANG_ENG "/language/ENG"
#define LANG_DEF "Default"
using namespace std;
/*
 * TEMPLATES
 *
 *  start{comments}
 *  exit{}
*/
class ELanguage
{
protected:
public:
    static QStringList& Buffer();
    static QString& selectedLang();
    static void setLanguage(const QString& patch);
    static QString getWord(const int &index, const QString&patch=LANG_DEF);
};

#endif // ELANGUAGE_H
