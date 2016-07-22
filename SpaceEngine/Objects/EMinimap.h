#ifndef EMINIMAP_H
#define EMINIMAP_H
#include "SpaceEngine/Objects/ECamera.h"
#include "SpaceEngine/Objects/EGameObject.h"
#include <list>
#define LOGSIZE 20
/*class EMinimap:public  QOpenGLWidget,protected QOpenGLFunctions //kalss mini karti dlya igr
{
    Q_OBJECT
private:
    QPixmap *fon;//fon minikarti
    QTimer *timer;//taimer obnovleniya
    bool fastDrawFlag;//flag otrisovki animazii
    //EPictureCore *CORE;//yadro
    int size_elements;//razmer triugolnikov
protected:
    bool status;//status
    virtual void draw_fon();//otrisuet fon
    virtual void draw_object(EObject *Object);//narisuet object
    EObject_List *_list;//spisok vseh objectov
   // EMaps*_map;//karta k kotoroi privyazana minikarta
    void initializeGL(); //iniziolizaziya okna GL
    void paintGL(); //ego otrisovka
    void resizeGL(int w, int h);//pererazmetka
protected slots:
    virtual void _render();//obnovlenie ekranna
public:
    explicit EMinimap(EObject_List *mapList=NULL, QWidget*ptr=NULL);
    void Off();
    virtual void On();
    int getTimeUpdate();//vernyot vremya obnovleniya
    virtual QPixmap* getImageMap();//vernyot fon
    void setTimeUpdate(const int&);//ustonovit vremya obnovleniya
    virtual void setImageMap(QPixmap*);//vernyot fon
    virtual void set_maps(EMaps*);//privyagit karty k minikarte
    ~EMinimap();
};*/
class EMinimap: public ECamera{
    Q_OBJECT
private:
    int radar;
protected slots:
   // void paintGL(); //ego otrisovka
    void draw_Object(EObject *);
public:
    EMinimap(EGameObject* obj, EPool*pool_,EConfig*cfg, QWidget *widget=NULL);
    void folow(EGameObject*);
    ~EMinimap();
};
#endif // EMINIMAP_H
