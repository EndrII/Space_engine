#ifndef POTOK2_H
#define POTOK2_H
#include "SpaceEngine/System/EThreadObject.h"
#include <QTime>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include "EList.h"
typedef int priority;
class EMapCore:public EThreadObject //potok po raspredeleniya objectov
{
private:
    void BaseRender();//basivii rnder objectov (bez uchota flagov)
    unsigned short draw_;
    bool cliced;//shelchek misgi
    EMouseEvent * clicedevent;
    bool full;//zapolnen li potok nugnimi dannimi
    void *pointer_void; //ukazatel na void nugen dlya obmena ukozateleei
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
    //void Sort(int Size); //пузырёк с применением флагов
public:
    EMapCore();
    void update(EObject_List* object_list,
                EObject_List** slow_render_list,
                EObject_List** render_list,
                EObject_List** draw_list,
                EObject_List **GameObjectList,
                Elist<EKord*> *);
    void render();//pereopridilim render
    void click(EMouseEvent *event);
    void ForseRender();//prinuditelnii render
    ~EMapCore();
};

#endif // POTOK2_H
