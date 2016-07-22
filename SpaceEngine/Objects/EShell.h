/*#ifndef ESHELL
#define ESHELL
#include "EObject.h"
#include "EModuleObject.h"
#include <QTime>
enum Control{selectAI,selectPlayer};
class EShell: public EObject// obstrakziya  dlya impulsnogo snaryada
{
    Q_OBJECT
private:
    int indexSound;
    QTime *timLive;//vremya gizni puli
    int Live;//vremya
    EModuleObject **target;//zel parageniya
    Control *control;//kontroliruet
    bool action;//activen li snaryad
    EObject *Faiter;//strelok
    int Damage;//uron
protected:
    //virtual void damage(EObject *);
    virtual void Off();//vkluchit polu
    virtual void On();//vikluchit
    void _timeRender();
    void _render();
public:
    EShell(const QString &url, EObject *faiter, const EKord &Size, const int &timelive, const int &spied,Control*,EModuleObject **Target);
    void render();
    void setSoundIndex(const int& SoundIndex_in_ESoundCenter);
     void setDamage(const int &de);//
     int getDamage();
     bool isOn();
    ~EShell();
public slots:
    virtual void start();//vistrrel
signals:
     void SoundPlay(int);

};
#endif // EShell
*/
