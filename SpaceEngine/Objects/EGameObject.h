#ifndef EGAMEOBJECT
#define EGAMEOBJECT
#include "EModuleObject.h"
#include "EEffect.h"
/*#define LIVE_ANIMATION live
#define FIRE_ANIMATION fait
#define SEVEN_ANIMATION custom_2
#define FIFTI_ANIMATION custom_1
#define THWO_ANIMATION custom_3
#define DEATH_ANIMATION death*/
#define KILL_DAMAGE 255*255*255*127
class EGameObject:public EModuleObject
{
    Q_OBJECT
  private:
    void constructorFork();
    int IndexPlay;
protected:
    int MaxHeals;
    int RadarPower;//sila radara
    int Heals;// zdorovie objecta
    int Defense;//zashita objecta d %
    EEffect *dead_effect;// effect vosproizvodimii pri unictogenii
    bool Fire;// flag na strilbu
    virtual void _animation_render();//obrobotka animzii objecta
public:
   explicit EGameObject(QObject *ptr=0);
   explicit EGameObject(const QString &createPatch, const EKord& size, const EKord& kord, const QString& patchSprite, QObject *ptr=0);
   explicit EGameObject(const EKord& size, const EKord& kord, const QString&objPatch, QObject *ptr=0);
   explicit EGameObject(const QString& patch_GameObject,draw_mode mode=Game_mode, QObject *ptr=0);
   friend QDataStream& operator>>(QDataStream&stream,EGameObject&obj);
   friend QDataStream& operator<<(QDataStream&stream,const EGameObject&obj);
   virtual bool damag(const int &dem);//poluchenie urona vernyot true esli unichtogen
   virtual bool repair(const int &rep);//remont vernyot true esli object budet polnostiyu otremontirovan
   virtual void setHealsMax(const int& heals);//ustonovit novoe zdorovie (maximum)
   virtual void setHeals(const int& heals);//ustonovit novoe zdorovie (maximum)
   virtual void setDefense(const int& def);
   virtual void setDeadSound(const int&);
   void saveObject(QString patch);
   virtual void setDeadEffect(EEffect* effect);
   virtual void setRadarPower(const int & i);
   virtual int getRadarPower()const;
    virtual int getDefense();
   virtual bool isLive();//giv li object
   void render();
   virtual int getHeals();//vernyot heals
   virtual int getHealsMax();//vernyot heals
    ~EGameObject();
public slots:
    void fire(bool);
signals:
    void HealsChange(int);
    void dead(EObject*);
    void playSound(int);
};
#endif // EGAMEOBJECT

