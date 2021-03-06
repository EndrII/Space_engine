#ifndef ELANGUAGE_H
#define ELANGUAGE_H
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QUrl>
#include <string>
#include <vector>
#include <unordered_map>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
//#include "SpaceEngine/System/EError.h"
#define LANG_ENG "/language/ENG"
#define LANG_DEF "Default"
#define NONE "_no_translate_"

using namespace std;

class ELanguage
{
    typedef QMap<QString,QString> SourceMap;
protected:
    static SourceMap& source();
    static const QString& empty();

    static bool ParseJson(const QString &url,bool forse=false);
    static void WriteToJson();
public:
    static QString& SelectedLang(); //url to source file
    static void setLanguage(const QString& patch);
    static void setLanguage(const QUrl& patch);
    static SourceMap::iterator add(const QString&word);
    static void remove(const QString&word);
    static void save();
    static const QString &getWord(const QString &index, const QString&patch=LANG_DEF);
};

#endif // ELANGUAGE_H
