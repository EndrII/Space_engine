#ifndef ELANGUAGE_H
#define ELANGUAGE_H
#include <QTextStream>
#include <QFile>
#include <QString>
#include <string>
#include <vector>
#include "SpaceEngine/System/EError.h"
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
    virtual ~ELanguage();
};

#endif // ELANGUAGE_H
