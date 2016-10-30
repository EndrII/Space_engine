#ifndef GAMERESURS_H
#define GAMERESURS_H
#include "./SpaceEngine/Objects/EObject.h"
class EGameResurs:public EObject
{
        Q_OBJECT
private:
    //bool first;//pervicniii li object
    EResurse *description;
    EResursePack* pack_;
protected:
    void size_to_value();
public:
    EGameResurs(const QString &Patch,EResursePack*pack=NULL);
    EGameResurs(EObject *copy,EResursePack*);
    EGameResurs(EResurse*,const QString& createPatch,const EKord& size, const EKord& kord_, const QString &str);
    EResurse* getRes()const;
    virtual void RandomValue(int max=1000);
    void generateThisObject(EResurse*);
    friend QDataStream& operator>>(QDataStream&stream,EGameResurs&);
    friend QDataStream& operator<<(QDataStream&stream,EGameResurs&);
    void saveObject(QString patch);
    ~EGameResurs();
};

#endif // GAMERESURS_H
