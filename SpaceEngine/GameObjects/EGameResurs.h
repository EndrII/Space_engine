#ifndef GAMERESURS_H
#define GAMERESURS_H
#include "./SpaceEngine/Objects/EObject.h"
class EGameResurs:public EObject
{
        Q_OBJECT
private:
    //bool first;//pervicniii li object
    EItem *description;
    EResursePack* pack_;
protected:
    void size_to_value();
public:
    /**
     * @brief EGameResurs
     * @param Patch патч ресурса
     * @param pack покет ресурсов
     */
    EGameResurs(const QString &Patch,EResursePack*pack=NULL);
    /**
     * @brief EGameResurs ресурс на базе которого будет создан
     * @param copy обьек основа
     */
    EGameResurs(EObject *copy,EResursePack* pack=NULL);
    /**
     * @brief EGameResurs создаст обькт заного
     * @param createPatch путь расположения обьекта
     * @param size размер обьекта
     * @param kord_ его место расположения
     * @param str путь к спрайту на основе которого бужет создан обьект
     */
    EGameResurs(EResurse*,const QString& createPatch,const EKord& size, const EKord& kord_, const QString &str);
    EItem* getRes()const;
    virtual void RandomValue(int max=1000);
    void generateThisObject(EResurse*);
    friend QDataStream& operator>>(QDataStream&stream,EGameResurs&);
    friend QDataStream& operator<<(QDataStream&stream,EGameResurs&);
    void saveObject(QString patch);
    ~EGameResurs();
};

#endif // GAMERESURS_H
