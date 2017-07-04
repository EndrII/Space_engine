#include "EMaps.h"
EMaps::EMaps(const EKord &s ):
    QObject(0)
{
    siz_map=s;
    ist=new EObject_List;
    slow_render_list_=new EObject_List*;
    *slow_render_list_=new EObject_List;
    render_list_=new EObject_List*;
    *render_list_=new EObject_List;
    draw_list_=new EObject_List*;
    *draw_list_=new EObject_List;
    GameObjectList=new EObject_List*;
    *GameObjectList=new EObject_List;
    Func_For_High=NULL;
    Func_For_Medium=NULL;
    Func_For_Low=NULL;
    stats_fast=true;
    stats_slow=true;
    P_slow=new EThreadObject();
//#ifdef QT_DEBUG
    P_fast=new EThreadObject();
//#else
  //  P_fast=new MultiCorRender(4);
//#endif
    T_slow.setObject(P_slow,P_slow->getpuls());
    T2_fast.setObject(P_fast,P_fast->getpuls());
    T_CORE.setObject(&P_CORE,P_CORE.getpuls());
    timer.start(MAP_HIGH);
    connect(&timer,SIGNAL(timeout()),this,SLOT(Render()));
    default_priority=MAP_HIGH;
    priority_=MAP_HIGH;
    P_slow->update(slow_render_list_,&stats_slow);
    P_slow->setPriority(LOWER);
    P_fast->update(render_list_,&stats_fast);
    P_fast->setPriority(HIGH);
    T2_fast.setPriority(QThread::TimeCriticalPriority);
    P_CORE.update(ist,slow_render_list_,render_list_,
                  draw_list_,GameObjectList,&krai);
}
/*void EMaps::setValueCoresRender(const int &cor)
{
    P_fast->setCoresValue(cor);
}*/
void EMaps::Pause(const bool &Paus)
{
    if(Paus)
    {
        stats_fast=false;
        stats_slow=false;
    }else
    {
        P_slow->setTimeSync(1);
        P_fast->setTimeSync(1);
        stats_fast=true;
        stats_slow=true;
    }
}
void EMaps::Render()
{
    timer.setInterval(priority_);
    switch (priority_) {
    case MAP_LOADED:
    {
        stats_fast=true;
        P_slow->setPriority(LOWER);
        P_fast->setPriority(HIGH);
        T_slow._start();
        T2_fast._start();
        T_CORE._start();
        break;
    }
    case MAP_HIGH:
        stats_fast=false;
        //T_slow.setPriority(ULTRA_LOW);
        P_slow->setPriority(ULTRA_LOW);
        T2_fast.stop();
        T_CORE.stop();
        if(Func_For_High!=NULL)(*Func_For_High)();
        break;
    case MAP_MEDIUM:
        stats_fast=false;
        //T_slow.setPriority(_1_ON_MINUTE);
         P_slow->setPriority(_1_ON_MINUTE);
        T2_fast.stop();
        T_CORE.stop();
        if(Func_For_Medium!=NULL)(*Func_For_Medium)();
        break;
    case MAP_LOW:
        stats_fast=false;
        //T_slow.setPriority(_1_ON_5MINUTS);
        P_slow->setPriority(_1_ON_5MINUTS);
        T2_fast.stop();
        T_CORE.stop();
         if(Func_For_Low!=NULL)(*Func_For_Low)();
        break;
    default:
        throw EError(20,"void EMaps::Render()");
        break;
    }
}
void EMaps::setFunc_High(void (*Func)())
{
    Func_For_High=Func;
}
void EMaps::setFunc_Low(void (*Func)())
{
    Func_For_Medium=Func;
}
void EMaps::setFunc_Medium(void (*Func)())
{
    Func_For_Low=Func;
}
void EMaps::setSize(const EKord &s)
{
    siz_map=s;
}
void EMaps::setPriority(const priority_map &p)
{
    default_priority=p;
    timer.setInterval(priority_);
}
priority_map EMaps::getPrioryty()
{
    return priority_;
}
void EMaps::ClickEvent(EMouseEvent *e){
    P_CORE.click(e);
}
EObject_List* EMaps::getMainList()
{
    return ist;
}
EObject_List** EMaps::getDrawList()
{
    return draw_list_;
}
EObject_List **EMaps::getSlowRenderList()
{
    return slow_render_list_;
}
EObject_List** EMaps::getRenderList()
{
    return render_list_;
}
EObject_List** EMaps::getGameList()
{
    return GameObjectList;
}
void EMaps::Load(EKord *C)
{
    priority_=MAP_LOADED;
    krai.Epush_back(C);
    timer.setInterval(priority_);
}
bool EMaps::UnLoad(EKord *C)
{
     for(Elist<EKord*>::iterator i=krai.begin();i!=krai.end();i++)
        if(*i==C)
        {
            krai.Elock();
            krai.erase(i);
            krai.Eun_lock();
            if(krai.size()==0)
            {
                priority_=default_priority;
            }
            Render();
            timer.setInterval(priority_);
            return true;
        }
    return false;
}
bool EMaps::add_Object(EObject *obj)
{
    if(siz_map.X>100&&siz_map.Y>100&&ist!=NULL)
    {
        obj->update(this->getTimeSync(),this->getSlowTimeSync());
        ist->Epush_front(obj);
        return true;
    }
    if(ist!=NULL)
    {
        throw EError(1,"bool EMaps::add_Object(EObject *obj)");
    }else
    {
        throw EError(0,"bool EMaps::add_Object(EObject *obj)");
    }
    return false;
}
bool EMaps::add_Object(const QString& patchObject)
{
    if(siz_map.X>100&&siz_map.Y>100&&ist!=NULL)
    {
        EObject *a=new EObject(patchObject);
        a->update(this->getTimeSync(),this->getSlowTimeSync());
       ist->Epush_front(a); //bag (utechka pamati)
        return true;
    }
    if(ist!=NULL)
    {
        throw EError(1,"bool EMaps::add_Object(EObject *obj)");
    }else
    {
        throw EError(0,"bool EMaps::add_Object(EObject *obj)");
    }
    return false;
}
EKord EMaps::getSize()
{
     return siz_map;
}
int* EMaps::getTimeSync()
{
    return P_fast->gettimesync();
}
int* EMaps::getSlowTimeSync()
{
    return P_slow->gettimesync();
}
EMaps& EMaps::operator =(const EMaps& Em)
{
    if(this==&Em) return *this;
    *this->ist=*Em.ist;
    this->siz_map=Em.siz_map;
    *this->draw_list_=*Em.draw_list_;
    *this->render_list_=*Em.render_list_;
    *this->GameObjectList=*Em.GameObjectList;
    *this->slow_render_list_=*Em.slow_render_list_;
    return *this;
}
bool EMaps::operator!=(const EMaps& Em)
{
    return (this->siz_map.Y*this->siz_map.X!=Em.siz_map.Y*Em.siz_map.X);
}
bool EMaps::operator==(const EMaps& Em)
{
    return (this->siz_map.Y*this->siz_map.X==Em.siz_map.Y*Em.siz_map.X);
}
bool EMaps::operator<(const EMaps& Em)
{
    return (this->siz_map.Y*this->siz_map.X<Em.siz_map.Y*Em.siz_map.X);
}
bool EMaps::operator<=(const EMaps& Em)
{
    return (this->siz_map.Y*this->siz_map.X<=Em.siz_map.Y*Em.siz_map.X);
}
bool EMaps::operator>(const EMaps& Em)
{
    return (this->siz_map.Y*this->siz_map.X>Em.siz_map.Y*Em.siz_map.X);
}
bool EMaps::operator>=(const EMaps& Em)
{
    return (this->siz_map.Y*this->siz_map.X>=Em.siz_map.Y*Em.siz_map.X);
}
bool EMaps::clear()
{
    ist->Eclear();
    (*draw_list_)->Eclear();
    (*render_list_)->Eclear();
    (*GameObjectList)->Eclear();
    (*slow_render_list_)->Eclear();
    return true;
}
void EMaps::Stop()
{
    stats_fast=false;
    stats_slow=false;
    timer.stop();
    if(priority_==MAP_LOADED)
    {
        T2_fast.stop();
        T_CORE.stop();
    }
    T_slow.stop();
    T_slow.terminate();
}
void EMaps::ForceuUpdate()
{
    P_CORE.ForseRender();
}
EMaps::~EMaps()//dodelat
{
     clear();
     delete *GameObjectList;
     delete GameObjectList;
     delete *draw_list_;
     delete draw_list_;
     delete *render_list_;
     delete render_list_;
     delete *slow_render_list_;
     delete slow_render_list_;
     delete ist;
}
