#ifndef SpaceEngine_H
#define SpaceEngine_H
//#define EOBJECT Q_OBJECT
#include "./SpaceEngine/Objects/ECamera.h"
#include "./SpaceEngine/Objects/EButton.h"
#include "./SpaceEngine/Objects/QButton.h"
#include "./SpaceEngine/System/eevents.h"
#include "./SpaceEngine/Objects/EFon.h"
#include "./SpaceEngine/Objects/EGameObject.h"
#include "./SpaceEngine/Objects/EShell.h"
#include "./System/EAiControle.h"
#include "./SpaceEngine/Objects/EImage.h"
#include <QBoxLayout>
#include "System/ELanguage.h"
#include <QApplication>
#include <QDesktopWidget>
#include <SpaceEngine/System/EMusic.h>
#include "./SpaceEngine/Objects/EEffect.h"
#include "./SpaceEngine/Objects/EMinimap.h"
typedef unsigned int ui;
class SpaceEngine:public QObject
{
    Q_OBJECT
private:

    std::vector<ECamera*> Camers;//spisok okon;
    std::vector<EMaps*> Maps;//spisok kart;
    std::vector<EObject*> Objects;//spisok vseh objectov
    std::vector<QWidget*> QObjects;//spisook elementov interfeisa
    std::vector<EKord> Size_,Kord_;//razmer i raspologenie na vitualnoi matrize QObjectow
    EConfig *setings;//nastroiki
    AiControle AI_CORE;//yadro iskustvennogo intelecta
protected:
    EPool *CORE;//yadro pamyati
    EEvents *SpaceEngineEvents;//obrobotcik sobitii
    virtual QPoint matrix(const EKord&);//dlya udobstva
    virtual QSize matrixs(const EKord&);
protected slots:
    virtual void resize(QResizeEvent*);
public:
    explicit SpaceEngine(const char* Patch="./setings.cfg",const short &key=_Key_value);//konstruktor s putem k failu nastroek
    virtual EConfig *GlobalSetings();//vernyot nastroiki dvigka
    virtual EConfig *Setings(ECamera*);//vernyot nastroiki otdelnooi kamerii
    virtual std::vector<ECamera*>* getCamersList();//vernut spisok okon
    virtual std::vector<EMaps*>* getMapsList();//vernut spisok kart
    virtual std::vector<EObject*>* getEObjectList();//vernut spisok objectov postroinih v igre
    virtual std::vector<QWidget*>* getQWidgetList();//vernyot vse ispolzuemie elementi QWidget
    virtual std::vector<EAi*>* getAIlist();//vernyot list ai
    virtual EEvents* getMain();//vernyot ukazatel na osnovnoe okno dvigka
    virtual bool syncSetings();//sinhroniziruet nastroiki s globalnimi
    virtual bool addCamera(const EKord& locationInMap=EKord(0,0),const EKord& GlobalLocation=EKord(0,0),QWidget*PointerForQt=0);//dobavit kameru(okno)
    virtual bool addMap(const EKord& Size=EKord(10000,10000));//dobavit kartu
    virtual bool setMap(EMaps*,ECamera*);//ustonovit kartu dlya otobrageniya vibronai kamere
    virtual bool addObject(EObject*,EMaps*);//dobavit object v kartu
    virtual void addObject(const int& index_Object, const int& index_Map);
    virtual bool removeObject(const ui &indexObject);//udalit object
    virtual bool removeObject(EObject*object);//dlya udobstva
    virtual void addQtButton(QPushButton*,  EKord kord,  EKord size);//dobovlaet object qt v glavnoe okno dvigka
    virtual void addQtWidget(QWidget*,  EKord kord,  EKord size);//dobovlaet object qt v glavnoe okno dvigka
    virtual short addAI(EAi*);//dobavit AI vernyot nomer ai
    virtual void AIOff();//viclushit AI;
    virtual void AIOn();//vklushit AI
    virtual void clearBuffer();//otshistit buffer pamyati
    virtual void EnableQWidget(QWidget*);//vkluchit object
    virtual void EnableQWidget(const ui &);//vkluchit object
    virtual void DisableQWidget(QWidget*);//vicluchi object
    virtual void DisableQWidget(const ui &);//vicluchi object
    virtual void EnableCamera(ECamera*);//vkluchit Cameru
    virtual void EnableCamera(const ui &);//vkluchit Cameru
    virtual void DisableCamera(ECamera*);//vicluchi Cameru
    virtual void DisableCamera(const ui &);//vicluchi Cameru
    virtual bool setECameraMod(ECamera*,const MOD& MOD_player_custom=custom,EObject* Folow_Object=0);//ustonovit povedenie dlya kameri
    virtual void setCameraVirtual(ECamera*,const EKord&Size,const EKord &Pos);//ustonovit virtualnii razmer kameri
    virtual void setCameraVirtual(const ui &, const EKord&Size, const EKord &Pos);// dlya udobstva
    virtual bool setAI(EObject*,EAi*);//ustonovit ai objectu
    virtual bool setAI(const int&index,EAi*);//ustonovit ai objectu
    virtual void setNewSetings(EConfig*);//ustonovit novii nastroiki (zamenit nastroiki dvigka na novi clas nastroek igri)
    virtual void clearCamersList();//udolit vse kameri
    virtual void clearObjectsList();//udalist vse objecti
    virtual void clearQWidgetsList();//udalit vse elementi interfeisa
    virtual void clearMapsList();//udalit vse karti;
    virtual bool WindowsShow();//proresuet vse kameri
    virtual void OffAll();//vikluchit vse kameri
    virtual void OnAll();//vkluchit vse kameri
    virtual void sync();// sinhotniziruet razmeri vseh objectov dvigka s razmerom glovnogo okna
    virtual void FullScrin();//ustonovit polnoekrannii regim
    virtual void setCursor(const QString &url);//ustonovit cursor
    virtual void setColorWindow(const QColor& color);
    virtual ~SpaceEngine();
};
#endif // SpaceEngine_H
