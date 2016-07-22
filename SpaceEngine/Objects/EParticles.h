/*#ifndef EPARTICLES_H
#define EPARTICLES_H
#include "EObject.h"
#include "SpaceEngine/System/EGraphicsConfig.h"
#define Patlicles_Ultra 1000
#define Patlicles_Hugh 500
#define Patlicles_Medium 200
#define Patlicles_Lov 100
#define Patlicles_Max_Performace 10;
class EParticles:public EObject
{
    // Particles system.
    // этот класс предстовляет пакет упровления маленьким элементами
    Q_OBJECT
private:
    EGraphicsConfig* conf;//configurazii grafici
    std::list<EKord> *Particles;//chastizi
    int max;//maximum Particles
    int LengthLive;//dlina gizni elementa
    int Radius;//zona poyavleniya
    int Value;//tekushee kolichestvo elementov
protected:
public:
   explicit EParticles(EGraphicsConfig*Conf,const QString &Url, const EKord&kord=EKord(0,0), const int &Rad=10,
                       const int &Value=Patlicles_Lov, const int &TimeLive=1);
   void render();//
   void ConfigUpdate();//obnovit configurazii
   virtual void setRadius(const int&);//ustonovit radius
   virtual void setValue(const int&);//ustonovit kol vo elementov
   virtual void setLengthLive(const int &);//dlina gizni
   std::list<EKord>* getDraw();//vernyot spisok otrisoovki
    ~EParticles();
signals:
void empty();//signal o tom chto chastiz uge net
void Overfull();//signal o tom chto kolichetvo chastim >max
public slots:
};
*/
#endif // EPARTICLES_H
