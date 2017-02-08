#include "EModuleObject.h"
ModuleItem::ModuleItem(EObject *i, const float &e, const float &r){
            obj=i; engle=e;range=r;
}
QDataStream& operator>>(QDataStream& stream,ModuleItem& item){
    stream>> item.engle;
    stream>> item.range;
    return stream;
}
QDataStream& operator<<(QDataStream& stream,const ModuleItem& item){
    stream<< item.engle;
    stream<< item.range;
    return stream;
}
EModuleObject::EModuleObject(const QString& createPatch, const EKord&size, const QString& patchSprite, QObject *ptr):
    EObject(createPatch,size,EKord(0),patchSprite,Game_mode,ptr){
    constructorFork();
}
EModuleObject::EModuleObject(const QString&objPatch,QObject *ptr):
    EObject(objPatch,ptr){
    constructorFork();
}
EModuleObject::EModuleObject( QObject *ptr):
    EObject(ptr){
    constructorFork();
}
void EModuleObject::constructorFork(){
    class_=E_MODULEOBJECT;
    multiObject=true;
    noDraw_flag=true;
    ignore_flag=false;
    draw_in_map_=false;
}
QDataStream& operator>>(QDataStream&stream,EModuleObject&obj){
    stream>>*((EObject*)&obj);
    return stream;
}
QDataStream& operator<<(QDataStream&stream,EModuleObject&obj){
    stream<<*((EObject*)&obj);
    return stream;
}
void EModuleObject::update(int *ptr2, int* ptr3)
{
    timeSync=ptr2;
    timeSync_slow=ptr3;
    for(ui i(0);i<elements.size();i++)
        elements.data()[i].obj->update(ptr2,ptr3);
    emit createdModule();
}
void EModuleObject::setSlave(EObject *s)
{
    slave_=s;
     for(ModuleItem &i:elements)
         i.obj->setSlave(s);
}
void EModuleObject::damag_of_target(const int&)
{

}
void EModuleObject::addObject(EObject *Obj, float engle, float range)
{
    elements.push_back(ModuleItem(Obj,engle,range));
    Obj->ignore_flag=true;
    Obj->setSlave(slave_);
    Obj->update(timeSync,timeSync_slow);
}
std::vector<ModuleItem> *EModuleObject::getModuleVector()
{
    return &elements;
}
void EModuleObject::render()
{
    this->_timeRender();
    this->_keyRender();
    this->_render();
    for(ModuleItem& i:elements)
        i.obj->render();
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
    this->noDraw_flag=b;
    for(ModuleItem &i:elements)
    {
        i.obj->noDraw_flag=b;
    }
}
void EModuleObject::setIgnoreFlag(const bool &b)
{
    this->ignore_flag=b;
    for(ModuleItem &i:elements)
    {
        i.obj->ignore_flag=b;
    }
}
void EModuleObject::setDeleteFlag(const bool &b)
{
    this->delete_flag=b;
    for(ModuleItem& i:elements)
    {
        i.obj->delete_flag=b;
    }
}
RelationFraction EModuleObject::getRelation()
{
    return players;
}
void EModuleObject::setForceRenderFlag(const bool &b)
{
    for(ModuleItem& i:elements)
    {
        i.obj->forceRenderFlag=b;
    }
}
bool EModuleObject::deleteElement(EObject *pointer)
{
    std::vector<ModuleItem>::iterator temp =elements.begin();
    for(ui i(0);i<elements.size();i++)
    {
        if((temp->obj)==pointer)
        {
            delete temp->obj;
            elements.erase(temp);
            return true;
        }
        temp++;
    }
    return false;
}
EModuleObject::~EModuleObject()
{
    for(ui i(0);i<elements.size();i++)
        delete elements.data()[i].obj;
}
