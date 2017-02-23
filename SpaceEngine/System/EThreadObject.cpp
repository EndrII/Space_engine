#include "EThreadObject.h"
EThreadObject::EThreadObject(const priority &p)
{
    priority_=p;
    puls=true;
    timeSync=1;
}
void EThreadObject::update(EObject_List **objectlist,bool* best)
{
    status=best;
    obj_list=objectlist;
}
void EThreadObject::render()
{
    while (puls)
    {
       timeUpdates.restart();
       if(status){
           (*obj_list)->Elock();
           for(auto* obj:**obj_list)
                obj->render();
           (*obj_list)->Eun_lock();
       }
       std::this_thread::sleep_for(std::chrono::milliseconds(priority_));
       timeSync=timeUpdates.elapsed();
    }
}
bool* EThreadObject::getpuls()
{
    return &puls;
}
int* EThreadObject::gettimesync()
{
    return &timeSync;
}
void EThreadObject::setTimeSync(int i){
    timeSync=i;
}
void EThreadObject::Exit()
{
    puls=false;
}
void EThreadObject::setPriority(const priority &p)
{
    priority_=p;
}
priority EThreadObject::getPriority()
{
    return priority_;
}
EThreadObject::~EThreadObject()
{
    puls=false;
    obj_list=NULL;
    status=NULL;
}
