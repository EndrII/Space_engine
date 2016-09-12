#ifndef ERESURSEPACK_H
#define ERESURSEPACK_H
#include <QFile>
#include <QDataStream>
#include "EResurse.h"
#define RESURSE_PACK_DIR static QString dir;
#define RESURSE_PACK_DIR_ACSSES dir
/**
 * @brief The EResursePack class класс предстовляет собой
 * интерфейсом между файлом (покетом ресурсов и всеми рисурсами в игре)
 */
class EResursePack
{
private:
    //short _moduleNumber;
public:
    EResursePack();
    /**
     * @brief getResurse
     * @param id
     * @return вернет ресурс по ид
     */
    static EResurse* getResurse(const ui id);
    /**
     * @brief chekName проверит занято ли это имя или нет (в соотвецтвии с выбранным языком)
     * @param name проверяемое имя
     * @return вернет истину если емя найдено в пративном случае лож
     */
    static bool chekName(const QString& name);
};

#endif // ERESURSEPACK_H
