#ifndef EMODULEOBJECT
#define EMODULEOBJECT
#include "EObject.h"
#include "SpaceEngine/System/EMaps.h"
enum RelationFraction{players,allies,enemies};
typedef  unsigned int ui;
typedef unsigned short us;
class EModuleObject: public EObject//modulni object vse objecti v nem ne yavlyayutsa polnzennimi i ih net osnovnom spiske ih dobovlenie proishodit v kobstruktore
{
    Q_OBJECT
  private:
  inline void constructorFork();// nastroika objecta posle constructora
  bool draw_in_map_;//flag na risovku objecta na karte
  protected:
    std::vector<EObject*> elements;//spisok otrisovivoemih elementov
    std::vector<float> additionalUgol;
    virtual void addObject(EObject* Obj);//dobavit object v modul
protected slots:
public:
    explicit EModuleObject(const EKord&size,const QString& patchSprite,EContur*, QObject *ptr=0);//konstruktor dlya regima inPoint
    explicit EModuleObject(const QString&objPatch, QObject *ptr=0);//konstruktor dlya regima inPoint
    explicit EModuleObject(QObject *ptr=0);//konstruktor dlya regima inPoint
    friend QDataStream& operator>>(QDataStream& stream,EModuleObject&obj);
    friend QDataStream& operator<<(QDataStream& stream,EModuleObject&obj);
    void render();//
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
    virtual std::vector<EObject*>* getModuleVector();//vernyot  spisok vsheh eelementov
    virtual std::vector<float>* getAddUgol();
    virtual RelationFraction getRelation();//vernyot otnosheni k igroku
    void update(int *ptr2, int* ptr3);
    ~EModuleObject();
signals:
    void createdModule();
};
#endif // EMODULEOBJECT

