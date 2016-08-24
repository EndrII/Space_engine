#ifndef EOBJECT_H
#define EOBJECT_H
#include <QVector>
#include <cmath>
#include "./SpaceEngine/System/EDefkey.h"
#include "./SpaceEngine/System/EKord.h"
#include "./SpaceEngine/System/EMouseEvent.h"
#include "./SpaceEngine/System/EList.h"
#include "./SpaceEngine/System/ESprite.h"
#include "./SpaceEngine/System/EContur.h"
//#define CREATE_SPRITE "CREATE_Z"
//#define EOBJECT Q_OBJECT
const int accs=1000;
typedef unsigned short us;
enum MovMode{Standart,Key,NoMove,NoMovePlus,MoveElepsed};
enum Feedback{inFastRender,inSlowRender};//obratnaya svyazi s yadrom
enum Rotate{RotateLeft,RotateRight,NoRotate};//brashenie objecta pri dvigeni po okrugnosti
//enum EObjectNameClass{EOBJECT,E_MODULEOBJECT,E_FON,E_EFFECT,E_GAMEOBJECT};
enum EObjectNameClass{EOBJECT,E_MODULEOBJECT,E_FON,E_PARALAX,E_EFFECT,E_GAMEOBJECT};
using namespace std;
class EObject:public ESprite //osnovnoi klas obektov dvigka
{
    Q_OBJECT
private:
    void PreConstructor(const QString& createPatch,const EKord& size, const EKord& kord_, EContur *cont);//osnovnoi consructor
    EContur *contur;// kontur dannogo objecta
    float vertixArray[4][3]; //vershini risovki (zavisyat ot razmera i sloya)
    void vertixArrayRefresh();//perescyot vershin hsirini i sloyov;
    void NormalizeUgol();//normlizaziya ugla
    void NoramlizeUgolSrlrct();//povort objecta
    float *ElepsedCenter_X,*ElepsedCenter_Y;//ukazatel na zenter vrashenie
    int Rad;//radius vrasheniya po okrugnosti
    bool DrawContur;// otrisovjk kontura
    double ElepsedUgol;//ugol raspologeniya ovjecta v ragime dvugeniya pokrugu
    Rotate ratateMode;//vid vrasheniya v regime dvigeniya po okrugnosti
    float optimalUgol(float);//vernyot ugol v diapozone 2pi
private slots:
protected:
    QString Objectpatch,_name; //patch from object;
    MovMode movmode;//regim dvigeniya
    void* playerTarget;
    void* map;//karta na kotoroi object nahoditsya
    EObject* slave_;//ukazatel na object roditel (obiek v sostave kotorogo nahoditasy danni object)
    QTime *timeUpdates;//vnutrenii taimer ispolzuetsya v Potokah
    float acceleration;//uskoreni objecta
    float _ugol;//ego ugol povorota otnoositelno X(ugol vectora) (ugol dvigeniya)
    float ugol;//ego ugol povorota otnoositelno X(ugol otrisovki)
    EObjectNameClass class_;//tip dannih classa
    int Tsync; //viborka dlya vremeni sinhronizazii
    float massa;//masssa obekta (1-359)
    float radius;//radius megdu tochkoi dvigeniya
    short speed;//ego skorast
    bool *keys; //klavishi deistvii
    Feedback feedback;//obratnaya svyazi s yadrom
    int *timeSync;//kol vo milisikund proshedhae za 1 iteraziyu
    int *timeSync_slow; //vremya sinchronizasii dlya objectov za kameroi
    float _x,_y,_z,mx,my,_w,_h;//koordinati gde z - sloi
    virtual void _render();//pereshot vseh dannih klassa;
    virtual void _keyRender();//obroobotka klavish i sobitii
    virtual void _timeRender();//podbor vremeni
protected slots:
public:
   virtual void click(Qt::MouseButton);
   friend QDataStream& operator >>(QDataStream&stream,EObject& obj);
   friend QDataStream& operator <<(QDataStream&stream,const EObject& obj);
   bool noDraw_flag,//flag na skorost renderinga//otrisovku
        delete_flag,//flag na udoolenie
        ignore_flag,//flag na ignorirovanie
        forceRenderFlag;// prinudutelnii rendering
   //virtual void saveObject(const QString&str);
  // virtual bool* getDrawPoiter();//vernyot ukazatel na risovku
   //virtual float getElasticity();
   virtual void * getPlayerTarget();//poluchet zel igroka
   virtual float getUgol();//polushit tekushii ugol
   virtual int getMass(); //poluchit massu
   virtual int getSpeed(); //poluchit skorost
   EKord getSize()const;
   EKord getKord()const;
   virtual void* getMap();
   virtual bool* getKeys();//vernyot spisok nagatih klavish
   virtual MovMode getMovMode();//vernyot regim dvigeniya
   EObjectNameClass getEObjectNameClass();//vernyot tip dannih
   virtual Feedback getFeedBack();//uznat gde object
   int* getSlowTime();//
   int* getFastTime();
   EContur* getContur()const;
   virtual void setSlave(EObject*);//ustanovit ovjekt kotoromy on podchinyaetsy
   virtual void setRotateUgol(const float&);//ustonovit ugol dlya regima dvigeniya po okrugnosti
   virtual void setPlayerTaraget(void*);//ustonovit po komu vedyot ogon igrok
   virtual void setFeedBack(const Feedback&f);//
   virtual void setMovMode(const MovMode &m);//ustonovit regim
   virtual bool setMass(const short&); //ustonovit massu
   virtual void setMap(void*);
   virtual void setSize(const EKord&);//ustonovit razmer objecta
   virtual void setSpeed(const int&); //ustonovit skorost
   virtual void setKord(const EKord&);// ustonovit novii kordinati
   virtual void setUgol(const short&);//ustonovit ugol povorota otnositelno osi X
   virtual void setAcceleration(const float& A=1);//ustonovit uskorenie
   virtual void setDrawContur(bool);
   virtual void setName(const QString& name);//ustanovit imya dlya objecta
   void setContur(EContur*);//ustanovit new contur
   float** getMatrix(); //return matrix
   float& x();
   float& y();
   virtual bool isDrawContur()const;
   void setSloi(const float& );
   float getSloi()const;
   float getW()const;
   float getH()const;
   virtual QString getObjectPatch();// vernyot raspologenie objecta
   virtual QString getName();//vernyot imya
   EObject* getSlave()const;
   void setW(const float&);
   void setH(const float&);
   virtual void startElepsedMove(float *Center_X, float *Center_Y, const int& Radius, const Rotate rot=NoRotate);//nachnyot dvigenie ovjecta po okrugnosti
   virtual bool mov_to(const EKord&); //ustonovit tochku dvigeniya
   virtual bool mov_to(const EKord&,const int& _speed); //+skorost
   virtual void saveObject(QString patch="");//sohronit sebya v fail
   EObject(QObject *ptr=0);
   EObject(const QString& createPatch,const EKord& size, const EKord& kord, const QString& name_image, EContur *cont,draw_mode mode=Game_mode, QObject *ptr=0);
    EObject(const QString&patch, QObject *ptr=0);
    ~EObject();
public slots:
virtual void action_Begin(short); //nachat dvigenie object po naprovleniyu
virtual void action_End(short); //zakonchit dvigenie object po naprovleniyu
virtual void render(); //perechislenie dannh klassa obj=vsrobjecti v pole zreniya
virtual void update(int *tsync,int*tsyncslow);
signals:
   void destructed();
   void created();
};
typedef Elist<EObject*> EObject_List;//osnovnoi kontener dvigka
#endif // EOBJECT_H
