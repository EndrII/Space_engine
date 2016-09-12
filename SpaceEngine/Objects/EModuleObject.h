#ifndef EMODULEOBJECT
#define EMODULEOBJECT
#include "EObject.h"
#include "SpaceEngine/System/EMaps.h"
#define WRITEMODULE(type) \
    for(ModuleItem&i:obj.elements){\
        stream<<i;\
        stream<<*((type*)i.obj);\
    }
#define READMODULE(type)\
    for(us i=0;i<temp;i++){\
        ModuleItem temp1;\
        stream>>temp1;\
        temp1.obj=new type ();\
        stream>>*((type *)temp1.obj);\
        temp1.obj->setSlave(obj.slave_);\
        obj.elements.push_back(temp1);\
    }

enum RelationFraction{players,allies,enemies};
typedef  unsigned int ui;
typedef unsigned short us;

struct ModuleItem{
    ModuleItem(EObject*i=0,const float& e=0,const float& r=0);
    EObject* obj;
    float engle;
    float range;
};
QDataStream& operator>>(QDataStream& stream,ModuleItem& item);
QDataStream& operator<<(QDataStream& stream,const ModuleItem& item);
class EModuleObject: public EObject//modulni object vse objecti v nem ne yavlyayutsa polnzennimi i ih net osnovnom spiske ih dobovlenie proishodit v kobstruktore
{
    Q_OBJECT
private:
   // bool emptyModule;//flag otvechayushi za to cho budet zapissano v fail (stoit li pisati obolocku)
    void constructorFork();// nastroika objecta posle constructora
    bool draw_in_map_;//flag na risovku objecta na karte
protected:
    std::vector<ModuleItem> elements;//spisok otrisovivoemih elementov
    virtual void addObject(EObject* Obj,float engle=0,float range=0);//dobavit object v modul
protected slots:
public:
    explicit EModuleObject(const QString &createPatch, const EKord&size, const QString& patchSprite, QObject *ptr=0);//konstruktor dlya regima inPoint
    explicit EModuleObject(const QString&objPatch, QObject *ptr=0);//konstruktor dlya regima inPoint
    explicit EModuleObject(QObject *ptr=0);//konstruktor dlya regima inPoint
    friend QDataStream& operator>>(QDataStream& stream,EModuleObject&obj);
    friend QDataStream& operator<<(QDataStream& stream,EModuleObject&obj);
    void render();//
    //virtual writeAngle(QDataStream& stream);// zapishet ugli i rastoyaniya objectov conteinera
    virtual void damag_of_target(const int&);
    virtual bool firetest(void*);//test moget li eta puska nanesti urob etomu objectu
    virtual bool isDraw_in_map();
    virtual void draw_in_map(const bool&);//risovat li object na karte
    virtual void setNoDrawFlag(const bool&);//ustonovit draw flag dlya vsego objecta
    virtual void setIgnoreFlag(const bool&);//ustonovit render flag dlya vsego objecta
    virtual void setDeleteFlag(const bool&);//ustonovit delete flag dlya vsego objecta
    virtual void setForceRenderFlag(const bool&);//ustonovit force flag dlya vsego objecta
    void setSlave(EObject*);
    virtual bool deleteElement(EObject*pointer);//ydolit element i vernyot true esli on sushestvuet ili false esli net
    virtual std::vector<ModuleItem> *getModuleVector();//vernyot  spisok vsheh eelementov
    //virtual std::vector<float>* getAddUgol();
    virtual RelationFraction getRelation();//vernyot otnosheni k igroku
    void update(int *ptr2, int* ptr3);
    ~EModuleObject();
signals:
    void createdModule();
};
#endif // EMODULEOBJECT

