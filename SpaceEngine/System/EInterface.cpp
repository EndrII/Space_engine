#include "EInterface.h"

Potok2::Potok2(QObject *ptr):
    EObject(ptr)
{
    priority_=HIGH;
    puls=true;
    timeSync=new int;
    timeUpdates=new QTime;
    *timeSync=1;
}
void Potok2::update(EObject_List **objectlist,bool* best)
{
    status=best;
    obj_list=objectlist;
}
void Potok2::render()
{
    while (puls)
    {
       timeUpdates->restart(); 
       if(status)
       {
       (*obj_list)->Elock();
       for(auto* obj:**obj_list)
           obj->render();
       (*obj_list)->Eun_lock();
       }
       std::this_thread::sleep_for(std::chrono::milliseconds(priority_));
       *timeSync=timeUpdates->elapsed();
    }
}
bool* Potok2::getpuls()
{
    return &puls;
}
int* Potok2::gettimesync()
{
    return timeSync;
}
void Potok2::Exit()
{
    puls=false;
}
void Potok2::setPriority(const priority &p)
{
    priority_=p;
}
priority Potok2::getPriority()
{
    return priority_;
}
Potok2::~Potok2()
{

    puls=false;
    delete timeUpdates;
    delete timeSync;
    obj_list=NULL;
    status=NULL;
}







MultiCorRender::MultiCorRender(const int &COREs, QObject *ptr):
    EObject(ptr)
{
    priority_=HIGH;
    puls=true;
    CORES=COREs;
    index_0=COREs;index_1=COREs;index_2=COREs;index_3=COREs;
    index_4=COREs;index_5=COREs;index_6=COREs;index_7=COREs;
    timeSync=new int;
    index_test=false;
    timeUpdates=new QTime;
    *timeSync=1;
}
void MultiCorRender::Plus(Elist<EObject*>::iterator &I,int&index_)
{
    for(int i(0);i<CORES;i++)
        I++;
    if(index_test){index_=(index_+CORES)%(*obj_list)->size();return;}
    index_test=true;
}
void MultiCorRender::update(EObject_List **objectlist,bool* best)
{
    status=best;
    obj_list=objectlist;
}
bool MultiCorRender::setCoresValue(const int &cors)
{
    if(cors>8) return false;
    CORES=cors; return true;
}
void MultiCorRender::mThread_0()
{
    Elist<EObject*>::iterator i=(*obj_list)->begin();
    for(;i!=(*obj_list)->end();Plus(i,index_0))
    {
        if(index_0<CORES) break;
        (*i)->render();
    }

}
void MultiCorRender::mThread_1()
{
    Elist<EObject*>::iterator i=++(*obj_list)->begin();++index_1;
    for(;i!=(*obj_list)->end();Plus(i,index_1))
    {
        if(index_1<CORES) break;
        (*i)->render();
    }
}
void MultiCorRender::mThread_2()
{
    Elist<EObject*>::iterator i=++++(*obj_list)->begin();index_2+=2;
    for(;i!=(*obj_list)->end();Plus(i,index_2))
    {
        if(index_2<CORES) break;
        (*i)->render();
    }
}
void MultiCorRender::mThread_3()
{
    Elist<EObject*>::iterator i=++++++(*obj_list)->begin();index_3+=3;
    for(;i!=(*obj_list)->end();Plus(i,index_3))
    {
        if(index_3<CORES) break;
        (*i)->render();
    }
}
void MultiCorRender::mThread_4()
{
    Elist<EObject*>::iterator i=++++++++(*obj_list)->begin();index_4+=4;
    for(;i!=(*obj_list)->end();Plus(i,index_4))
    {
        if(index_4<CORES) break;
        (*i)->render();
    }
}
void MultiCorRender::mThread_5()
{
    Elist<EObject*>::iterator i=++++++++++(*obj_list)->begin();index_5+=5;
    for(;i!=(*obj_list)->end();Plus(i,index_5))
    {
        if(index_5<CORES) break;
        (*i)->render();
    }
}
void MultiCorRender::mThread_6()
{
    Elist<EObject*>::iterator i=++++++++++++(*obj_list)->begin();index_6+=6;
    for(;i!=(*obj_list)->end();Plus(i,index_6))
    {
        if(index_6<CORES) break;
        (*i)->render();
    }
}
void MultiCorRender::mThread_7()
{
    Elist<EObject*>::iterator i=++++++++++++++(*obj_list)->begin();index_7+=7;
    for(;i!=(*obj_list)->end();Plus(i,index_7))
    {
        if(index_7<CORES) break;
        (*i)->render();
    }
}
void MultiCorRender::render()
{
    while (puls)
    {
       timeUpdates->restart();
       if(status)
       {
       (*obj_list)->Elock();


           index_test=false;
           switch (CORES) {
           case 1:
           {
               for(EObject* i:(**obj_list))
                   i->render();
               break;
           }
           case 2:
           {
               index_0=CORES;index_1=CORES;
               std::thread t0(&MultiCorRender::mThread_0,this),t1(&MultiCorRender::mThread_1,this);
               t0.join();t1.join();
               break;
           }
           case 3:
           {
               index_0=CORES;index_1=CORES;index_2=CORES;
               std::thread t0(&MultiCorRender::mThread_0,this),t1(&MultiCorRender::mThread_1,this),t2(&MultiCorRender::mThread_2,this);
               t0.join();t1.join();t2.join();
               break;
           }
           case 4:
           {
               index_0=CORES;index_1=CORES;index_2=CORES;index_3=CORES;
               std::thread t0(&MultiCorRender::mThread_0,this),t1(&MultiCorRender::mThread_1,this),t2(&MultiCorRender::mThread_2,this),t3(&MultiCorRender::mThread_3,this);
               t0.join();t1.join();t2.join();t3.join();
               break;
           }
           case 5:
           {
               index_0=CORES;index_1=CORES;index_2=CORES;index_3=CORES;
               index_4=CORES;
               std::thread t0(&MultiCorRender::mThread_0,this),t1(&MultiCorRender::mThread_1,this),t2(&MultiCorRender::mThread_2,this),t3(&MultiCorRender::mThread_3,this),
                           t4(&MultiCorRender::mThread_4,this);
               t0.join();t1.join();t2.join();t3.join(),
               t4.join();
               break;
           }
           case 6:
           {
               index_0=CORES;index_1=CORES;index_2=CORES;index_3=CORES;
               index_4=CORES;index_5=CORES;
               std::thread t0(&MultiCorRender::mThread_0,this),t1(&MultiCorRender::mThread_1,this),t2(&MultiCorRender::mThread_2,this),t3(&MultiCorRender::mThread_3,this),
                           t4(&MultiCorRender::mThread_4,this),t5(&MultiCorRender::mThread_5,this);
               t0.join();t1.join();t2.join();t3.join(),
               t4.join();t5.join();
               break;
           }
           case 7:
           {
               index_0=CORES;index_1=CORES;index_2=CORES;index_3=CORES;
               index_4=CORES;index_5=CORES;index_6=CORES;
               std::thread t0(&MultiCorRender::mThread_0,this),t1(&MultiCorRender::mThread_1,this),t2(&MultiCorRender::mThread_2,this),t3(&MultiCorRender::mThread_3,this),
                           t4(&MultiCorRender::mThread_4,this),t5(&MultiCorRender::mThread_5,this),t6(&MultiCorRender::mThread_6,this);
               t0.join();t1.join();t2.join();t3.join(),
               t4.join();t5.join();t6.join();
               break;
           }
           case 8:
           {
               index_0=CORES;index_1=CORES;index_2=CORES;index_3=CORES;
               index_4=CORES;index_5=CORES;index_6=CORES;index_7=CORES;
               std::thread t0(&MultiCorRender::mThread_0,this),t1(&MultiCorRender::mThread_1,this),t2(&MultiCorRender::mThread_2,this),t3(&MultiCorRender::mThread_3,this),
                           t4(&MultiCorRender::mThread_4,this),t5(&MultiCorRender::mThread_5,this),t6(&MultiCorRender::mThread_6,this),t7(&MultiCorRender::mThread_7,this);
               t0.join();t1.join();t2.join();t3.join(),
               t4.join();t5.join();t6.join();t7.join();
               break;
           }
           default:
               break;
           }

       (*obj_list)->Eun_lock();
       }
       std::this_thread::sleep_for(std::chrono::milliseconds(priority_));
       *timeSync=timeUpdates->elapsed();
    }
}
bool* MultiCorRender::getpuls()
{
    return &puls;
}
void MultiCorRender::setTimeSync(const int &tim)
{
    *timeSync=tim;
    timeUpdates->restart();
}
int* MultiCorRender::gettimesync()
{
    return timeSync;
}
void MultiCorRender::Exit()
{
    puls=false;
}
void MultiCorRender::setPriority(const priority &p)
{
    priority_=p;
}
priority MultiCorRender::getPriority()
{
    return priority_;
}
MultiCorRender::~MultiCorRender()
{
    puls=false;
    delete timeUpdates;
    delete timeSync;
    obj_list=NULL;
    status=NULL;
}





Potok3_CORE::Potok3_CORE(QObject *obj):
    EObject(obj)
{
   full=false;
   priority_=LOW_PLUS;
   puls=true;
   buffer_for_draw=new EObject_List;
   buffer_for_render=new EObject_List;
   buffer_for_Game=new EObject_List;
}
/*void Potok3_CORE::Sort(int Size)
{
    bool flag =1;
    while(--Size&&flag)
    {
       flag=0;
       int j=0; EObject* temp=buffer_for_draw->front();
       for(EObject_List::iterator i=++buffer_for_draw->begin();j<Size;i++)
       {
           j++;
           if(**i>*temp)
           {
               flag=1;
               EObject *temp2=*i;
               *i=temp;
               *(--i)=temp2; i++;
           }
            temp=*i;
       }
    }
}*/
void Potok3_CORE::update(EObject_List *object_list,
                         EObject_List **slow_render_list,
                         EObject_List **render_list,
                         EObject_List **draw_list,
                         EObject_List **GameObjectList,
                         Elist<EKord*> *k)
{
    camers=k;
    object_list_=object_list;
    slow_render_list_=slow_render_list;
    render_list_=render_list;
    Game_List=GameObjectList;
    draw_list_=draw_list;
    full=true;
}
void Potok3_CORE::setPriority(const priority &p)
{
    priority_=p;
}
void Potok3_CORE::Exit()
{
    puls=false;
}
bool* Potok3_CORE::getpuls()
{
    return &puls;
}
void Potok3_CORE::render()
{
    while(puls&&full)
    {
        BaseRender();
        (*draw_list_)->Elock();
        pointer_void=*draw_list_;
        *draw_list_=buffer_for_draw;
        buffer_for_draw=(EObject_List*)(pointer_void);
        buffer_for_draw->Eun_lock();
        (*draw_list_)->Eun_lock();
        buffer_for_draw->clear();

        (*render_list_)->Elock();
        pointer_void=*render_list_;
        *render_list_=buffer_for_render;
        buffer_for_render=(EObject_List*)(pointer_void);
        buffer_for_render->Eun_lock();
        (*render_list_)->Eun_lock();
        buffer_for_render->clear();

        (*Game_List)->Elock();
        pointer_void=*Game_List;
        *Game_List=buffer_for_Game;
        buffer_for_Game=(EObject_List*)(pointer_void);
        buffer_for_Game->Eun_lock();
        (*Game_List)->Eun_lock();
        buffer_for_Game->clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(priority_));
    }
}
void Potok3_CORE::BaseRender(){
    (*slow_render_list_)->Eclear();
    for(Elist<EObject*>::iterator  i=object_list_->begin();i!=object_list_->end();i++)
    {
        //bool b=(*i)->delete_flag;
        if((*i)->delete_flag)
        {
            object_list_->erase(i);
            i--;
            if(object_list_->size()==0)
                return;
        }else
        {
            if((*i)->getEObjectNameClass()==E_GAMEOBJECT)
                buffer_for_Game->Epush_back(*i);
            draw_=0;
            for(EKord* j:*camers)
               draw_+=(!(*i)->noDraw_flag&&(*i)->getKord().inQuan(j[0]-(*i)->getSize(),j[1]+(*i)->getSize()));
            if(draw_>0)
            {
                if(!(*i)->noDraw_flag)
                    buffer_for_draw->push_back(*i);
                if(!(*i)->ignore_flag)
                {
                    buffer_for_render->push_back(*i);
                    (*i)->setFeedBack(inFastRender);
                }
            }else
            {
                 if((*i)->forceRenderFlag)
                 {
                      buffer_for_render->push_back(*i);
                     (*i)->setFeedBack(inFastRender);
                 }
                 else
                 { 
                     (*slow_render_list_)->push_back(*i);
                     (*i)->setFeedBack(inSlowRender);
                 }
            }
        }
    }
}
void Potok3_CORE::ForseRender()
{
    if(full){
        BaseRender();
        (*draw_list_)->Elock();
        pointer_void=*draw_list_;
        *draw_list_=buffer_for_draw;
        buffer_for_draw=(EObject_List*)(pointer_void);
        buffer_for_draw->Eun_lock();
        (*draw_list_)->Eun_lock();
        buffer_for_draw->clear();

        (*render_list_)->Elock();
        pointer_void=*render_list_;
        *render_list_=buffer_for_render;
        buffer_for_render=(EObject_List*)(pointer_void);
        buffer_for_render->Eun_lock();
        (*render_list_)->Eun_lock();
        buffer_for_render->clear();

        (*Game_List)->Elock();
        pointer_void=*Game_List;
        *Game_List=buffer_for_Game;
        buffer_for_Game=(EObject_List*)(pointer_void);
        buffer_for_Game->Eun_lock();
        (*Game_List)->Eun_lock();
        buffer_for_Game->clear();
    }
}
Potok3_CORE::~Potok3_CORE()
{
    puls=false;
    delete buffer_for_Game;
    delete buffer_for_draw;
    delete buffer_for_render;
}
