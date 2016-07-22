#include "EModuleObject.h"
EModuleObject::EModuleObject(const EKord&size,const QString& patchSprite,EContur*cont, QObject *ptr):
    EObject(size,EKord(0),patchSprite,cont,ptr){
    constructorFork();
}
EModuleObject::EModuleObject(const QString&objPatch,QObject *ptr):
    EObject(objPatch,ptr){
    constructorFork();
}
EModuleObject::EModuleObject(QObject *ptr):
    EObject(ptr){
    constructorFork();
}
void EModuleObject::constructorFork(){
    class_=E_MODULEOBJECT;
    noDraw_flag=true;
    ignore_flag=false;
    draw_in_map_=false;
}
QDataStream& operator>>(QDataStream&stream,EModuleObject&obj){
    us temp;
    stream>>temp;
    EObject* objectTemp;float ugolTemp;
    for(us i=0;i<temp;i++){
        objectTemp=new EObject;
        stream>>*objectTemp;
        objectTemp->setSlave(obj.slave_);
        obj.elements.push_back(objectTemp);
    }
    for(us i=0;i<temp;i++){
        stream>>ugolTemp;
        obj.additionalUgol.push_back(ugolTemp);
    }
    return stream;
}
QDataStream& operator<<(QDataStream&stream,EModuleObject&obj){
    stream<<(us)obj.elements.size();
    for(EObject*i:obj.elements){
        stream<<*i;
    }
    for(float f:obj.additionalUgol){
        stream<<f;
    }
    return stream;
}
void EModuleObject::update(int *ptr2, int* ptr3)
{
    timeSync=ptr2;
    timeSync_slow=ptr3;
    for(ui i(0);i<elements.size();i++)
        elements.data()[i]->update(ptr2,ptr3);
    emit createdModule();
}
void EModuleObject::setSlave(EObject *s)
{
    slave_=s;
   // feedback=((EObject*)s)->getFeedBack();
     for(EObject *i:elements)
         i->setSlave(s);
}
void EModuleObject::damag_of_target(const int&)
{

}
std::vector<float>* EModuleObject::getAddUgol(){
    return &additionalUgol;
}
void EModuleObject::addObject(EObject *Obj)
{
    elements.push_back(Obj);
    additionalUgol.push_back(0);
    Obj->ignore_flag=true;
    Obj->setSlave(slave_);
    Obj->update(timeSync,timeSync_slow);
}
/*void EModuleObject::changeLacation(EMaps *m, const EKord &new_kord)
{
        this->delete_flag=true;
        this->setKord(new_kord);
        if(this->getMapAdres()!=NULL)
            ((EMaps*)(this->getMapAdres()))->ForceuUpdate();
        this->setMapAdres((void*)m);
        this->_update(m->getSize(),m->getGameList(),m->getTimeSync(),m->getSlowTimeSync(),CORE);
        this->delete_flag=false;
        m->add_Object(this);
        for(EObject*i:elements)
        {
            if(i->getEObjectNameClass()==emoduleobject)
                ((EModuleObject*)i)->changeLacation(m,new_kord);
            else
            {
                i->delete_flag=true;
                i->setKord(new_kord);
                if(i->getMapAdres()!=NULL)
                    ((EMaps*)(i->getMapAdres()))->ForceuUpdate();
                i->setMapAdres((void*)m);
                i->_update(m->getSize(),m->getGameList(),m->getTimeSync(),m->getSlowTimeSync(),CORE);
                i->delete_flag=false;
                m->add_Object(i);
            }
        }
}*/
std::vector<EObject *> *EModuleObject::getModuleVector()
{
    return &elements;
}
void EModuleObject::render()
{
    this->_timeRender();
    this->_keyRender();
    this->_render();
    for(EObject* o:elements)
        o->render();
}
bool EModuleObject::isDraw_in_map()
{
    return draw_in_map_;
}
void EModuleObject::draw_in_map(const bool &b)
{
    draw_in_map_=b;
}
bool EModuleObject::firetest(void *v)
{
    return slave_!=v;
}
void EModuleObject::setNoDrawFlag(const bool &b)
{
    for(EObject* i:elements)
    {
        i->noDraw_flag=b;
    }
}
/*void EModuleObject::setPrior(const int &i)
{
    Prioryty_add=1;
    Prioryty_=i;
    for(EObject* i:elements)
    {
        i->setPriorAdd(Prioryty_*Prioryty_add);
    }
}*/
void EModuleObject::setIgnoreFlag(const bool &b)
{
    for(EObject* i:elements)
    {
        i->ignore_flag=b;
    }
}
/*void EModuleObject::setPriorALL(const int &i)
{
    Prioryty_=i;
    for(EObject* j:elements)
    {
        j->setPrior(i);
        j->setPriorAdd(Prioryty_*Prioryty_add);
    }

}*/
void EModuleObject::setDeleteFlag(const bool &b)
{
    for(EObject* i:elements)
    {
        i->delete_flag=b;
    }
}
RelationFraction EModuleObject::getRelation()
{
    return players;
}
void EModuleObject::setForceRenderFlag(const bool &b)
{
    for(EObject* i:elements)
    {
        i->forceRenderFlag=b;
    }
}
/*std::vector<float>* EModuleObject::getAdditionalUgol()
{
    return &additionalUgol;
}*/
bool EModuleObject::deleteElement(EObject *pointer)
{
    std::vector<EObject*>::iterator temp =elements.begin();
    std::vector<float>::iterator temp2= additionalUgol.begin();
    for(ui i(0);i<elements.size();i++)
    {
        if((*temp)==pointer)
        {
            elements.erase(temp);
            additionalUgol.erase(temp2);
            return true;
        }
        temp++;temp2++;
    }
    return false;
}
EModuleObject::~EModuleObject()
{
    for(ui i(0);i<elements.size();i++)
        delete elements.data()[i];
}
