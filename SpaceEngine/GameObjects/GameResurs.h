#ifndef GAMERESURS_H
#define GAMERESURS_H
#include "./SpaceEngine/Objects/EObject.h"
#include "./SpaceEngine/GameObjects/EResursePack.h"
class GameResurs:public EObject
{
        Q_OBJECT
private:
    //bool first;//pervicniii li object
    EResurse *description;
public:
    GameResurs(const QString &Patch);
    GameResurs(EResurse*,const QString& createPatch,const EKord& size, const EKord& kord_, const QString &str);
    EResurse* getRes()const;
    friend QDataStream& operator>>(QDataStream&stream,GameResurs&);
    friend QDataStream& operator<<(QDataStream&stream,GameResurs&);
    void saveObject(QString patch);
    ~GameResurs();
};

#endif // GAMERESURS_H
