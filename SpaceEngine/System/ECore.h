#ifndef ECORE_H
#define ECORE_H
/**
 * @brief The ECore class is global Object in this engine.
 */
#include <QList>
#include <QMap>
class ESpriteBase;
class EResurse;
typedef QList<ESpriteBase*>                 spriteSet;
typedef QMap<unsigned int,EResurse*>        resursMap;
#define CORE_DECLARE ECore* public_core=new ECore();
#define CORE_INITIALIZE \
    public_core->setIdCore(new spriteSet);\
    public_core->setRes(new resursMap);
#define RepeatedVariableDeclaration 1
#define CORE_ACCESS extern ECore* public_core;
#define CORE public_core;
#define CORE_GET_ID (static_cast<spriteSet*>(public_core->getIdCore()))
#define CORE_GET_RES (static_cast<resursMap*>(public_core->getRes()))

class ECore
{
private:
    void * IDCORE;
    void * RES;
    ECore& operator=(const ECore&);
public:
    void * getIdCore()const;
    void * getRes()const;
    void setIdCore(void *ptr);
    void setRes(void *ptr);
    explicit ECore();
};

#endif // ECORE_H
