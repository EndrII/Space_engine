#ifndef ECamera_H
#define ECamera_H
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
//#include "./SpaceEngine/System/EMaps.h"
#include "EModuleObject.h"
#include "EFon.h"
#include <cmath>
#include <QTimer>
#include <QTime>
#include "./SpaceEngine/System/EDefkey.h"
#include "./SpaceEngine/System/EConfig.h"
#include "./SpaceEngine/System/EPool.h"
using namespace std;
enum{OFF,ON};
enum MOD{player,custom};//regim kameri (dlya igroka ili svobodnii)

class ECamera: public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
private:
    void update();//obnovlenie razmera kameri po novim nastroikam
    void drawContur(EObject*);
    EMouseEvent tempEvent;//временный элемент для хронения дискриптора последнего клика мыши
    EPool* pool;
    int LineWidth;//ширина линий контура
    QColor clearColor;
    QOpenGLTexture*tempTexture;// vremennaya peremennaya dlya sozzdaniya ne sozdanih textur
    EObject_List** draw_list; //spisok na otrisovku
    GLubyte indexArray[1][4];
    GLfloat idintyMatrix[4][2];
    GLfloat fonMatrix[4][3];
    EMaps *map;//karta kotoruyu risuet eta camera
    EKord Vkord,VSize;// virtualnie koordinati kameri na osnownom ekrane
    bool status;//status off/on
    EConfig *setings;//nastroiki kameri
    MOD mode;//mod regim kameri (dlya igroka ili svobodnii)
    bool *keys;//klavishi
    float speed_siz_W,speed_siz_H,speed_kord_X,speed_kord_Y;
    float Windows_Skrin;//sootnohenie storon ekrana
    EKord *krai;//dlevie i pravie kordinati ploskosti kamari
    float _X_,_Y_,X_new,Y_new;//kordinati kameri na glabalinoi karte
    int quan;//koren iz razresheniya kameri
protected:
    EKord siz,new_siz,min_siz,max_siz;//razmer ohvata kameri
    EKord default_siz_max,default_siz_min;//razmer kameri pri svobodnoi manipolyazii
    EObject *folow_Obj;//object slegki
    QTimer timer;//taimer obnovleniya ekrana;
    bool event;//flag na sobitiya nagatiya klavish
    void mousePressEvent(QMouseEvent *event);
    void initializeGL(); //iniziolizaziya okna GL
    void paintGL(); //ego otrisovka
    void resizeGL(int w, int h);//pererazmetka
protected slots:
  virtual void draw_Object(EObject*);//otrisovka staticheskogo ojecta
  virtual void _render();//obnovleni kameri
  virtual void _key_render();//obrobotka klavish
  virtual void _seting_update();//obnovleniye nastroek
public:
    virtual void folow(EObject*);//sledit za ubjectom
    explicit ECamera(const EKord &kord, const EKord &size, EConfig *, EPool *pool_, QWidget *ptr=0);//prostoi konsstruktor
    MOD getMode();//poluchit tekushii regim
    EKord getSize();//vernyot razmer siyomki
    EKord* getKrai(); //verniot obe chasti cameri
    EKord getmovCenter();//vernyot poziziyo kameri na karte
    EObject* getFolow();//vernyot ukozatel na sleduemii object
    EConfig getConfig();//vernyot tekusie konfigurazii
    EKord getVirtualKord()const;
    EKord getVirtualSize()const;
    void set_maps(EMaps*);
    void setLineWidth(const int& LineWidth_);//ustanovit shirennu linii contura
    EMaps* getMap();
    void setEvent(const bool&);//ustonovit flag na reogirovanie na sobitiya
    void setDrawList(EObject_List**);//
    void setConfig(const EConfig&);//ustonofit novii konfigurazii i sohronit ih v fail
    EConfig* config();//vernyot ukazatel na kobfigurazii
    void setVirtualKord(const EKord&);
    void setVirtualSize(const EKord&);
    void setBackgroundColor(const QColor&color);
    void setmode(const MOD &mode); // ustonovit mod kameri(custom/atomatik)
    void setSize(const int&);//ustonovit novi razmer siyomki
    void setSizeSkrin(const EKord& kord=EKord(640,480));//ustonovit novii razmer okna
    void setSizeSkrin(const int&X=640,const int &Y=480);//to-ge samoe
    ~ECamera();
public slots:
   virtual void Press_key(short);//klawisha nagata
   virtual void Release_key(short);//klawisha otgata
   virtual void Mov_ECamera_To(float x, float y);//peredvinut kameru v x,y na globalinoi karte
   void skroll_size(const EKord&); //ustonovit novie razmeri karti
   void Off(); //vikluchit kameru
   bool On();  //vklushit kameru
   virtual void Render();//obnovlenie objectov na karte
signals:
   void MouseClikedEvent(EMouseEvent*);
   void ECamera_On();//start
   void ECamera_Off();//ECamera otklyachena
};
#endif // ECamera_H
