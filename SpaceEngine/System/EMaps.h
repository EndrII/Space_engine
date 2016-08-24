#ifndef EMAPS_H
#define EMAPS_H
#include <QSize>
#include "EKord.h"
#include "EError.h"
#include "EInterface.h"
//#include "SpaceEngine/Objects/EExplosion.h"
#include "EThread.h"
#include <QTimer>
#define MAP_LOADED 1000
#define MAP_HIGH 10000
#define MAP_MEDIUM 60000
#define MAP_LOW 300000
typedef int priority_map;//prioritet karti pri renderinge
using namespace std;
class EMaps:public QObject //klass glabalinoi karti
{
    Q_OBJECT
private:
    QTimer timer;//taimer obnovleniya
    void (*Func_For_High)();//dlya bistrogo viponeniya
    void (*Func_For_Medium)(); //dlya srednego viponeniya
    void (*Func_For_Low)();//dlya medlennogo viponeniya
    MultiCorRender *P_slow,*P_fast;
    Potok3_CORE P_CORE;//potok raspredeleniya
    EThread T_slow,T2_fast,T_CORE;//potoki
    bool stats_fast,stats_slow;//sostoyanie renderinga
    EKord siz_map;// razmer karti
    Elist<EObject*> *ist,//spisok obiektov na karte
                    **render_list_,//spisok objectov v pole zreniya
                    **draw_list_,//spisok objectov dllya otrisovki
                    **slow_render_list_,//spisok objectov za kameroi
                    **GameObjectList;//list igrovih objectov na etoi karte
    priority_map priority_,default_priority;//prioritet
    Elist<EKord*> krai;//kamera na kotora kotoraya vedyot syomku v dannii moment
protected slots:
   void Render();//obnovlenie karti
public:
    EMaps(const EKord&s=EKord(0,0));
    bool isLoaded();
    void Pause(const bool&);//ustonovit pauzu
    void Update();//obnovit dannie kagdogo objecta na karte
    void setSize(const EKord&); //ustonavit razmer karti
    void setPriority(const priority_map&);//ustonovit novii prioritet dlya offline renderinga
    void setValueCoresRender(const int&);//ustonovit kolichestvo yader na rendering
    void setFunc_High(void (*Func)());//ustonovit novii szenarii pri prioritete high
    void setFunc_Medium(void (*Func)());//ustonovit novii szenarii pri prioritete medium
    void setFunc_Low(void (*Func)());//ustonovit novii szenarii pri prioritete low
    void Load(EKord*);//zagruska kameri
    bool UnLoad(EKord*);//razgruska kameri (vernyot resultat vipolneniya)
    bool add_Object(EObject*); //dibaviti obiect v kartu (budut dobavleni ego kordinati)
    bool add_Object(const QString &patchObject);
    bool clear();//otchistiti kartu effect =flag na udolenie effectov
    int* getTimeSync();//vernyot ukazatel na vremya sinhronizazii
    int* getSlowTimeSync();//vernyot ukazatel na vremya sinhronizazii
    EKord getSize(); //poluchiti tekushii razmer karti
    EObject_List* getMainList();//vernot adress spiska objectov
    EObject_List**getDrawList();//vernyot adris kontenera dkya risovki
    EObject_List** getRenderList();//vernyot adris kontenera bistrogo renderinga
    EObject_List** getSlowRenderList();//vernot adris kontenera medlennogo renderinga
    EObject_List** getGameList();//vernyot adris kontener game objectov
    void Stop();
    void ForceuUpdate();//prinuditelnoe obnovlenie pereraspredelenie objectov na karte;
    priority_map getPrioryty();//vernyot tekushii prioritet
    void ClickEvent(EMouseEvent*);// peredacha soo bsheniya o nagatii klavishi mishi na object (na kavere)
    EMaps& operator  = (const EMaps&);
    bool operator !=  (const EMaps&);
    bool operator ==  (const EMaps&);
    bool operator <   (const EMaps&);
    bool operator >   (const EMaps&);
    bool operator >=  (const EMaps&);
    bool operator <=  (const EMaps&);
    ~EMaps();
signals:
};
#endif // EMAPS_H
