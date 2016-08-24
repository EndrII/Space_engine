#ifndef POTOK2_H
#define POTOK2_H
#include "SpaceEngine/Objects/EObject.h"
#include <QTime>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include "EList.h"
#define ULTRA_HIGH 0
#define HIGH 1
#define MEDIUM 16
#define LOW 160
#define LOW_PLUS 350
#define LOWER 1600
#define ULTRA_LOW 10000
#define _1_ON_MINUTE 60000
#define _1_ON_5MINUTS 300000
#define STOP 10000000
typedef int priority;
class Potok2 : public EObject //klas dlya sozdaniya 2go potoka dlya renderinga bistrih objectov
{
    Q_OBJECT
private:

    bool *status;//ukazatel na status kameri
    EObject_List** obj_list;//ssilka na vse ibekti karti
protected:
    priority priority_;//zadergka
    bool puls;//viluchatel dannogo potoka
public:
    int* gettimesync();//vernyot ukazatel na vremya sinhronizazii
    void setPriority(const priority&); //ustonovit zadergku vipolneniya
    priority getPriority();//poluchit prioritet
    void render();//pereopridilim render
    bool* getpuls();//vernyot vikluchatel
    Potok2(QObject *ptr=0);
    void update(EObject_List **objectlist,bool*);//poluchenie kluchevih ukozatelei
    ~Potok2();
public slots:
    void Exit();
};





class MultiCorRender:public EObject
{
    Q_OBJECT
private:
    bool *status;//ukazatel na status kameri
    EObject_List** obj_list;//ssilka na vse ibekti karti
    int CORES;  //kolichestvo ispolzuemih yader
    void mThread_0(); //potok 0
    void mThread_1(); //potok 1
    void mThread_2(); //potok 2
    void mThread_3(); //potok 3
    void mThread_4(); //potok 4
    void mThread_5(); //potok 5
    void mThread_6(); //potok 6
    void mThread_7(); //potok 7
    void Plus(Elist<EObject*>::iterator&, int &index_);//izmenit index iteratora v sootveztvi s kolichestva yader
    int index_0,index_1,index_2,index_3,index_4,index_5,index_6,index_7;
    bool index_test;
protected:
    priority priority_;//zadergka
    bool puls;//viluchatel dannogo potoka
public:
    bool setCoresValue(const int&);// ustonovit kolichestvo yader
    void setTimeSync(const int&);//ustonovit prinuditelno vremya sinhronizazii
    int* gettimesync();//vernyot ukazatel na vremya sinhronizazii
    void setPriority(const priority&); //ustonovit zadergku vipolneniya
    priority getPriority();//poluchit prioritet
    void render();//pereopridilim render
    bool* getpuls();//vernyot vikluchatel
    MultiCorRender(const int&COREs,QObject *ptr=0);
    void update(EObject_List **objectlist,bool*);//poluchenie kluchevih ukozatelei
    ~MultiCorRender();
public slots:
    void Exit();
};



class Potok3_CORE:public EObject //potok po raspredeleniya objectov
{
  Q_OBJECT
private:
    void BaseRender();//basivii rnder objectov (bez uchota flagov)
    unsigned short draw_;
    bool cliced;//shelchek misgi
    EMouseEvent * clicedevent;
    bool full,puls;//zapolnen li potok nugnimi dannimi
    void *pointer_void; //ukazatel na void nugen dlya obmena ukozateleei
    priority priority_;//zadergka
    Elist<EKord*> *camers;
    EObject_List  * object_list_, //obshii list objectov
                  ** slow_render_list_, //list medlennogo renderinga (za kameroi)
                  ** render_list_,//spisok dlya bistrogo  renderinga
                  * buffer_for_draw,//bufer obmena
                  * buffer_for_render,//bufer obmena
                  * buffer_for_Game,//bufer game objects
                  **Game_List,//list s igrovimi objectami
                  **draw_list_; //list prorisovki
protected:
    void Sort(int Size); //пузырёк с применением флагов
public:
    Potok3_CORE(QObject* ptr=0);
    void update(EObject_List* object_list,
                EObject_List** slow_render_list,
                EObject_List** render_list,
                EObject_List** draw_list,
                EObject_List **GameObjectList,
                Elist<EKord*> *);
    void render();//pereopridilim render
    void click(EMouseEvent *event);
    void ForseRender();//prinuditelnii render
    bool* getpuls();//vernyot vikluchatel
    void setPriority(const priority&); //ustonovit zadergku vipolneniya
    ~Potok3_CORE();
public slots:
    void Exit();
};

#endif // POTOK2_H
