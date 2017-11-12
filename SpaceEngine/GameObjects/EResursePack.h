#ifndef ERESURSEPACK_H
#define ERESURSEPACK_H
#include <QFile>
#include <QDataStream>
#include "EItem.h"
#include <QList>
#include "SpaceEngine/System/ECore.h"
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
    /**
     * @brief load all resurses into memory
     */
    void load();
    resursMap* source;
public:
    EResursePack();
    /**
     * @brief getResurse
     * @param id
     * @return вернет ресурс по ид
     */
    static EResurse* getResurse(const ui id);
    /**
     * @brief ResursePackDir
     * @return
     */
    static QString& ResursePackDir();
    /**
     * @brief save all resurses into hard disk
     */
    void save();
    /**
     * @brief bufferClear cleen memory
     */
    static void bufferClear();
    /**
     * @brief add new resurse into resurs list adn memory
     * @param url -url to a has been created resurs object
     * @return
     */
    EResurse* add(const QString& url);
    /**
     * @brief getList
     * @return all objects
     */
    resursMap* getList();
    /**
     * @brief remove resurse from resurses
     * @param id
     * @return
     */
    bool remove(const unsigned int id);
    /**
     * @brief getName
     * @param id
     * @param translated
     * @return a name of object by they id
     */
    static QString getName(const ui id, bool translated=false);
    /**
     * @brief chekName проверит занято ли это имя или нет (в соотвецтвии с выбранным языком)
     * @param name проверяемое имя
     * @return вернет истину если емя найдено в пративном случае лож
     */
    static bool chekName(const QString& name);
    ~EResursePack();
};

#endif // ERESURSEPACK_H
