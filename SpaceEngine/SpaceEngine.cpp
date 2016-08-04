#include "SpaceEngine.h"
SpaceEngine::SpaceEngine(const char* Patch,const short &key)
{
    setings=new EConfig(Patch,key);
    setings->Default();
    ifstream f(Patch);
    CORE=new EPool;
    if(f.is_open())
    {
        setings->Update();
    }
    SpaceEngineEvents=new EEvents(setings);
    SpaceEngineEvents->setGeometry(300,300,setings->windows_skrinn.X,setings->windows_skrinn.Y);
    connect(SpaceEngineEvents,SIGNAL(Resize(QResizeEvent*)),this,SLOT(resize(QResizeEvent*)));
    SpaceEngineEvents->show();
}
void SpaceEngine::resize(QResizeEvent *){
    this->sync();
}
EConfig* SpaceEngine::GlobalSetings()
{
    return setings;
}
EConfig* SpaceEngine::Setings(ECamera *k)
{
    std::vector<ECamera*>::iterator temp=std::find(Camers.begin(),Camers.end(),k);
    if(temp!=Camers.end())
    {
        return (*temp)->config();
    }else
    {
        throw EError(15,"EConfig* SpaceEngine::Setings(ECamera *k)");
    }
}
bool SpaceEngine::syncSetings()
{
    for(ECamera* i:Camers)
    {
        if(i->config()==NULL) return false;
        *i->config()=*setings;
    }
    return true;
}
bool SpaceEngine::addCamera(const EKord &locationInMap, const EKord &GlobalLocation, QWidget *PointerForQt)
{
    if(locationInMap.X<0||locationInMap.Y<0||GlobalLocation.X<0||GlobalLocation.Y<0)
        return false;
    ECamera* temp=new ECamera(locationInMap,EKord(500,500),setings,CORE,PointerForQt);
    temp->setVirtualKord(GlobalLocation);
    temp->setVirtualSize(EKord(0.999999,0.999999));
    temp->setGeometry(QRect(matrix(GlobalLocation),QSize(0,0)));
    Camers.push_back(temp);
    EEvents::connect(SpaceEngineEvents,SIGNAL(Press(short)),temp,SLOT(Press_key(short)));
    EEvents::connect(SpaceEngineEvents,SIGNAL(Release(short)),temp,SLOT(Release_key(short)));
    temp->setParent(SpaceEngineEvents);
    temp->Off();
    return true;
}
bool SpaceEngine::addMap(const EKord &Size)
{
    if(Size.X<0||Size.Y<0) return false;
    Maps.push_back(new EMaps(Size));
    return true;
}
bool SpaceEngine::setMap(EMaps *m, ECamera *k)
{
#ifdef QT_DEBUG
    std::vector<ECamera*>::iterator temp=std::find(Camers.begin(),Camers.end(),k);
    std::vector<EMaps*>::iterator temp2=std::find(Maps.begin(),Maps.end(),m);
    if(temp!=Camers.end()||temp2!=Maps.end())
    {
        k->set_maps(m);
        return true;
    }else
    {
        throw EError(16,"bool SpaceEngine::setMap(EMaps *m, ECamera *k)");
    }
#else
        k->set_maps(m);
        return true;
#endif
}
/*EObject* SpaceEngine::addObject(EObject *o)
{
#ifdef QT_DEBUG
         Elist<EObject*>::iterator temp3=std::find(m->getMainList()->begin(),m->getMainList()->end(),o);
         if(temp3==m->getMainList()->end())
         {
             if(o->getMapAdres()!=NULL)((EMaps*)(o->getMapAdres()))->ForceuUpdate();
             Objects.push_back(o);
             o->setMapAdres(NULL);
             o->_update(m->getSize(),m->getGameList(),m->getTimeSync(),m->getSlowTimeSync(),&CORE);
             o->delete_flag=false;
             return true;
         }else
         {
             throw EError(18,"EObject* SpaceEngine::addObject(EObject *o)");
         }
 #else
    o->delete_flag=true;
    if(o->getMapAdres()!=NULL)((EMaps*)(o->getMapAdres()))->ForceuUpdate();
    Objects.push_back(o);
    o->setMapAdres((void*)m);
    //o->_update(m->getSize(),m->getRenderList(),m->getTimeSync(),m->getSlowTimeSync(),&CORE);
    o->_update(m->getSize(),m->getGameList(),m->getTimeSync(),m->getSlowTimeSync(),&CORE);
    o->delete_flag=false;
    m->add_Object(o);
            return true;
 #endif
}*/
bool SpaceEngine::addObject(EObject *o, EMaps *m)
{
#ifdef QT_DEBUG
     std::vector<EMaps*>::iterator temp=std::find(Maps.begin(),Maps.end(),m);
     if(temp!=Maps.end())
     {
         Elist<EObject*>::iterator temp3=std::find(m->getMainList()->begin(),m->getMainList()->end(),o);
         if(temp3==m->getMainList()->end())
         {
             o->delete_flag=true;
             if(o->getMap()!=NULL)((EMaps*)(o->getMap()))->ForceuUpdate();
             Objects.push_back(o);
             o->setMap((void*)m);
           //  o->update(m->getTimeSync(),m->getSlowTimeSync());
             o->delete_flag=false;
             m->add_Object(o);
             return true;
         }else
         {
             throw EError(18,"bool SpaceEngine::addObject(EObject *o, EMaps *m)");
         }
     }else
     {
         throw EError(17,"bool SpaceEngine::addObject(EObject *o, EMaps *m)");
     }
 #else
    o->delete_flag=true;
    if(o->getMap()!=NULL)((EMaps*)(o->getMap()))->ForceuUpdate();
    Objects.push_back(o);
    o->setMap((void*)m);
   // o->update(m->getTimeSync(),m->getSlowTimeSync());
    o->delete_flag=false;
    m->add_Object(o);
            return true;
 #endif
}
bool SpaceEngine::removeObject(EObject *object){
    std::vector<EObject*>::iterator i=find(Objects.begin(),Objects.end(),object);
    if(i==Objects.end())
        return false;
    (*i)->delete_flag=true;
    if((*i)->getMap()!=NULL)
        ((EMaps*)((*i)->getMap()))->ForceuUpdate();
    delete (*i);
    Objects.erase(i);
    return true;
}
bool SpaceEngine::removeObject(const ui &indexObject){
    if(indexObject>=Objects.size())
        return false;
    Objects.data()[indexObject]->delete_flag=true;
    if(Objects.data()[indexObject]->getMap()!=NULL)
    ((EMaps*)(Objects.data()[indexObject]->getMap()))->ForceuUpdate();
    delete Objects[indexObject];
    Objects.erase(Objects.begin()+indexObject);
    return true;
}
void SpaceEngine::addObject(const int& index_Object, const int& index_Map)
{
#ifdef QT_DEBUG
     std::vector<EMaps*>::iterator temp=std::find(Maps.begin(),Maps.end(),Maps[index_Map]);
     if(temp!=Maps.end())
     {
         Elist<EObject*>::iterator temp3=std::find(Maps[index_Map]->getMainList()->begin(),Maps[index_Map]->getMainList()->end(),Objects[index_Object]);
         if(temp3==Maps[index_Map]->getMainList()->end())
         {
             Objects[index_Object]->delete_flag=true;
             if(Objects[index_Object]->getMap()!=NULL)((EMaps*)(Objects[index_Object]->getMap()))->ForceuUpdate();
             Objects[index_Object]->setMap((void*)Maps[index_Map]);
             Objects[index_Object]->delete_flag=false;
             Maps[index_Map]->add_Object(Objects[index_Object]);
         }else
         {
             throw EError(18,"bool SpaceEngine::addObject(EObject *o, EMaps *m)");
         }
     }else
     {
         throw EError(17,"bool SpaceEngine::addObject(EObject *o, EMaps *m)");
     }
 #else
    Objects[index_Object]->delete_flag=true;
    if(Objects[index_Object]->getMapAdres()!=NULL)((EMaps*)(Objects[index_Object]->getMapAdres()))->ForceuUpdate();
    Objects[index_Object]->setMapAdres((void*)Maps[index_Map]);
    Objects[index_Object]->delete_flag=false;
    Maps[index_Map]->add_Object(Objects[index_Object]);
 #endif
}
short SpaceEngine::addAI(EAi *ai)
{
   return AI_CORE.addAI(ai);
}
bool SpaceEngine::setECameraMod(ECamera *k, const MOD &MOD_player_custom, EObject *Folow_Object)
{
#ifdef QT_DEBUG
    Elist<EObject*>::iterator temp2=std::find(k->getMap()->getMainList()->begin(),k->getMap()->getMainList()->end(),Folow_Object);
    if(temp2==k->getMap()->getMainList()->end()&&MOD_player_custom!=custom)
    {
        throw EError(19,"bool SpaceEngine::setECameraMod(ECamera *k, const short &MOD_player_custom, EObject *Folow_Object)");
    }else
    {
        if(MOD_player_custom==player)
        {
            if(k->getFolow()!=NULL)
                  EEvents::disconnect(SpaceEngineEvents, 0,k->getFolow(), 0);
            k->folow(Folow_Object);
            EEvents::connect(SpaceEngineEvents,SIGNAL(Press(short)),Folow_Object,SLOT(action_Begin(short)));
            EEvents::connect(SpaceEngineEvents,SIGNAL(Release(short)),Folow_Object,SLOT(action_End(short)));
        }
        k->setmode(MOD_player_custom);
        return true;
    }
 #else
        if(MOD_player_custom==player)
        {
            if(k->getFolow()!=NULL)
                  EEvents::disconnect(SpaceEngineEvents, 0,k->getFolow(), 0);
            k->folow(Folow_Object);
            EEvents::connect(SpaceEngineEvents,SIGNAL(Press(short)),Folow_Object,SLOT(action_Begin(short)));
            EEvents::connect(SpaceEngineEvents,SIGNAL(Release(short)),Folow_Object,SLOT(action_End(short)));
        }
        k->setmode(MOD_player_custom);
        return true;
 #endif
}
void SpaceEngine::setCameraVirtual(ECamera *C, const EKord &Size, const EKord &Pos)
{
#ifdef QT_DEBUG
    if(Camers.end()==std::find(Camers.begin(),Camers.end(),C))
        throw EError(29,"void SpaceEngine::setCameraVirtualSize(ECamera *C, const EKord &kord)");
#endif
    C->setVirtualSize(Size);
    C->setVirtualKord(Pos);
    this->sync();
}
void SpaceEngine::setCameraVirtual(const ui&Index, const EKord &Size, const EKord &Pos)
{
#ifdef QT_DEBUG
    if((Camers.size()<=Index)||(Camers.end()==std::find(Camers.begin(),Camers.end(),Camers[Index])))
        throw EError(29,"void SpaceEngine::setCameraVirtual(const int&Index, const EKord &kord)");
#endif
    Camers[Index]->setVirtualSize(Size);
    Camers[Index]->setVirtualKord(Pos);
    this->sync();
}
bool SpaceEngine::setAI(EObject *o, EAi *ai)
{
    return ai->setObject(o);
}
bool SpaceEngine::setAI(const int&index, EAi *ai)
{
    return ai->setObject(Objects[index]);
}
void SpaceEngine::setNewSetings(EConfig *c)
{
    SpaceEngineEvents->setSetings(c);
    delete setings;
    setings=c;
}
std::vector<ECamera*>* SpaceEngine::getCamersList()
{
    return &Camers;
}
std::vector<EObject*>* SpaceEngine::getEObjectList()
{
    return &Objects;
}
std::vector<EMaps*>* SpaceEngine::getMapsList()
{
    return &Maps;
}
std::vector<QWidget*>* SpaceEngine::getQWidgetList()
{
    return &QObjects;
}
std::vector<EAi*>* SpaceEngine::getAIlist()
{
    return AI_CORE.getAiList();
}

bool SpaceEngine::WindowsShow()
{
    for(ECamera* i:Camers)
    {
        if(i->getMap()==NULL)
          return false;
        else
          i->show();
    }
    sync();
    return true;
}
void SpaceEngine::AIOff()
{
    AI_CORE.Off();
}
void SpaceEngine::AIOn()
{
    AI_CORE.On();
}
void SpaceEngine::clearBuffer()
{
    CORE->clear();
}
EEvents * SpaceEngine::getMain()
{
    return SpaceEngineEvents;
}
void SpaceEngine::addQtButton(QPushButton* QObj,EKord kord, EKord size)
{
    QObj->setParent(SpaceEngineEvents);
    QObj->setGeometry(QRect(matrix(kord),matrixs(size)));
    //QObj->setMaximumSize(matrixs(size));
    //QObj->setMinimumSize(matrixs(size));
    //QObj->move(matrix(kord));
    QObj->show();
    Size_.push_back(size);
    Kord_.push_back(kord);
    SpaceEngineEvents->setFocus();
    EEvents::connect(QObj,SIGNAL(released()),SpaceEngineEvents,SLOT(focus()));
    QObjects.push_back(QObj);
}
void SpaceEngine::addQtWidget(QWidget *QObj, EKord kord, EKord size)
{
    QObj->setParent(SpaceEngineEvents);
    QObj->setGeometry(QRect(matrix(kord),matrixs(size)));
    QObj->show();
    Size_.push_back(size);
    Kord_.push_back(kord);
    SpaceEngineEvents->setFocus();
    QObjects.push_back(QObj);
}
void SpaceEngine::OffAll()
{
    for(ECamera*i:Camers)
        i->Off();
}
void SpaceEngine::OnAll()
{
    for(ECamera*i:Camers)
        i->On();
}
QPoint SpaceEngine::matrix(const EKord &point)
{
    return QPoint(SpaceEngineEvents->width()*point.X,SpaceEngineEvents->height()*point.Y);
}
QSize SpaceEngine::matrixs(const EKord &point)
{
    return QSize(SpaceEngineEvents->width()*point.X,SpaceEngineEvents->height()*point.Y);
}
void SpaceEngine::EnableQWidget(QWidget * Q)
{
#ifdef QT_DEBUG
    if(QObjects.end()==std::find(QObjects.begin(),QObjects.end(),Q))
        throw EError(28,"void SpaceEngine::EnableQWidget(QWidget * Q)");
#endif
    Q->setParent(SpaceEngineEvents);
    Q->show();
}
void SpaceEngine::EnableQWidget(const ui & Index)
{
#ifdef QT_DEBUG
    if((QObjects.size()<=Index)||(QObjects.end()==std::find(QObjects.begin(),QObjects.end(),QObjects[Index])))
        throw EError(28,"void SpaceEngine::EnableQWidget(const int & Index)");
#endif
    QObjects[Index]->setParent(SpaceEngineEvents);
    QObjects[Index]->show();
}
void SpaceEngine::DisableQWidget(QWidget *Q)
{
#ifdef QT_DEBUG
    if(QObjects.end()==std::find(QObjects.begin(),QObjects.end(),Q))
        throw EError(28,"void SpaceEngine::DisableQWidget(QWidget *Q)");
#endif
    Q->setParent(NULL);
}
void SpaceEngine::DisableQWidget(const ui &Index)
{
#ifdef QT_DEBUG
    if((QObjects.size()<=Index)||(QObjects.end()==std::find(QObjects.begin(),QObjects.end(),QObjects[Index])))
        throw EError(28,"void SpaceEngine::DisableQWidget(const int &Index)");
#endif
    QObjects[Index]->setParent(NULL);
}
void SpaceEngine::EnableCamera(ECamera* Q)
{
#ifdef QT_DEBUG
    if(Camers.end()==std::find(Camers.begin(),Camers.end(),Q))
        throw EError(29,"void SpaceEngine::EnableCamera(ECamera*)");
#endif
    Q->setParent(SpaceEngineEvents);
    Q->show();
}
void SpaceEngine::EnableCamera(const ui & Index)
{
#ifdef QT_DEBUG
    if((Camers.size()<=Index)||(Camers.end()==std::find(Camers.begin(),Camers.end(),Camers[Index])))
        throw EError(29,"void SpaceEngine::EnableCamera(const ui & Index)");
#endif
    Camers[Index]->setParent(SpaceEngineEvents);
    Camers[Index]->show();
}
void SpaceEngine::DisableCamera(ECamera *Q)
{
#ifdef QT_DEBUG
    if(Camers.end()==std::find(Camers.begin(),Camers.end(),Q))
        throw EError(29,"void SpaceEngine::DisableCamera(ECamera *Q)");
#endif
    Q->setParent(NULL);
}
void SpaceEngine::DisableCamera(const ui &Index)
{
#ifdef QT_DEBUG
    if((Camers.size()<=Index)||(Camers.end()==std::find(Camers.begin(),Camers.end(),Camers[Index])))
        throw EError(29,"void SpaceEngine::DisableCamera(const ui &Index)");
#endif
    Camers[Index]->setParent(NULL);
}
void SpaceEngine::sync()
{
    for(ECamera* i:Camers)
    {
        i->setGeometry(matrix(i->getVirtualKord()).x(),matrix(i->getVirtualKord()).y(),-1,-1);
        i->setSizeSkrin(matrix(i->getVirtualSize()));
        i->show();
    }
    for(ui i(0);i<QObjects.size();i++)
        QObjects[i]->setGeometry(QRect(matrix(Kord_[i]),matrixs(Size_[i])));
}
void SpaceEngine::clearCamersList()
{
    for(ECamera* i:Camers)
        delete i;
}
void SpaceEngine::clearMapsList()
{
    this->OffAll();
    for(EMaps* i:Maps)
        i->Stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(LOWER));
    for(EMaps* i:Maps)
        delete i;
}
void SpaceEngine::clearQWidgetsList()
{
    for(QWidget*i:QObjects)
        delete i;
}
void SpaceEngine::clearObjectsList()
{
    this->OffAll();
    for(EMaps* i:Maps)
        i->Stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(LOWER));
    for(EObject *i:Objects)
        delete i;
}
void SpaceEngine::FullScrin()
{
    SpaceEngineEvents->setGeometry(QApplication::desktop()->geometry());
    SpaceEngineEvents->showFullScreen();
    sync();
}
void SpaceEngine::setCursor(const QString &url)
{
    SpaceEngineEvents->setCursor(QCursor(QPixmap(url)));
}
void SpaceEngine::setColorWindow(const QColor &color){
    SpaceEngineEvents->setPalette(QPalette(color));
}
SpaceEngine::~SpaceEngine()
{
    AI_CORE.Off();
    delete CORE;
    for(ECamera* i:Camers)
        delete i;
    for(EMaps* i:Maps)
        i->Stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(LOWER));
    for(EMaps* i:Maps)
        delete i;
    for(EObject*i:Objects)
        delete i;
    for(QWidget*i:QObjects)
        this->DisableQWidget(i);
    for(QWidget*i:QObjects)
        delete i;

    EEvents::disconnect(SpaceEngineEvents,0,0,0);
    Camers.clear();
    Maps.clear();
    Objects.clear();
    delete SpaceEngineEvents;
    delete setings;
}
