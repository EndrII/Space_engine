#ifndef ERESURSEPACK_H
#define ERESURSEPACK_H
#include <QFile>
#include <QDataStream>
#include "EResurse.h"
#include <QList>
//#define RESURSE_PACK_DIR static QString _dir__;
//#define RESURSE_PACK_DIR_ACSSES _dir__
/**
 * @brief The EResursePack class класс предстовляет собой
 * интерфейсом между файлом (покетом ресурсов и всеми рисурсами в игре)
 */
class EResursePack
{
private:
    //short _moduleNumber;
    void load();
    QList<EResurse*> source;
public:
    EResursePack();
    /**
     * @brief getResurse
     * @param id
     * @return вернет ресурс по ид
     */
    static EResurse* getResurse(const ui id);
    static QString& ResursePackDir();
    void save();
    EResurse* add(const QString& url);
    QList<EResurse*>* getList();
    bool remove(const unsigned int id);
    static QString getName(const ui id);
    /**
     * @brief chekName проверит занято ли это имя или нет (в соотвецтвии с выбранным языком)
     * @param name проверяемое имя
     * @return вернет истину если емя найдено в пративном случае лож
     */
    static bool chekName(const QString& name);
    ~EResursePack();
};

#endif // ERESURSEPACK_H
