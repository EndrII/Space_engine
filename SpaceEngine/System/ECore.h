#ifndef ECORE_H
#define ECORE_H
/*
 *
*/
/**
 * @brief The ECore class is global Object in this engine.
 */
#define CORE_DECLARE ECore* public_core=new ECore();
#define CORE_INITIALIZE public_core->setIdCore(new QList<ESpriteBase*>);
#define RepeatedVariableDeclaration 1
#define CORE_ACCESS extern ECore* public_core;
#define CORE public_core;
#define ID_CORE (static_cast<QList<ESpriteBase*>*>(public_core->getIdCore()))
class ECore
{
private:
    void * IDCORE;
    ECore& operator=(const ECore&);
public:
    void * getIdCore()const;
    void setIdCore(void *ptr);
    explicit ECore();
};

#endif // ECORE_H
