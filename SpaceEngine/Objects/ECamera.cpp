#include "ECamera.h"
ECamera::ECamera(const EKord &kord, const EKord &size,EConfig *cfg,EPool*pool_, QWidget *ptr):
    QOpenGLWidget(ptr)
{
      pool=pool_;
      event=true;
      //setings=new EConfig(cfg);
      setings=cfg;
      setings->Update();
      speed_kord_X=0;
      speed_kord_Y=0;
      folow_Obj=NULL;
      speed_siz_H=0;
      map=NULL;
      speed_siz_W=0;
      Windows_Skrin=setings->windows_skrinn.X/(float)setings->windows_skrinn.Y;
      min_siz=EKord(100*Windows_Skrin,100);
      max_siz=EKord(10000*Windows_Skrin,10000);
      default_siz_min=EKord(100,100);
      default_siz_max=EKord(10000,10000);
      keys=new bool[9];
      for(int i(0);i<9;i++)
          keys[i]=false;
      status=OFF;
      mode=custom;
      X_new=kord.X;
      Y_new=kord.Y;
      _X_=kord.X;
      _Y_=kord.Y;
      this->setBaseSize(setings->windows_skrinn.TO_QSize());
      this->setMinimumSize(setings->windows_skrinn.TO_QSize());
      this->setMaximumSize(setings->windows_skrinn.TO_QSize());
      siz=EKord(size.X*Windows_Skrin,size.Y);
      new_siz=siz;
      krai=new EKord[2];
      krai[0].X=kord.X-siz.X/2;
      krai[0].Y=kord.Y-siz.Y/2;
      krai[1].X=kord.X+siz.X/2;
      krai[1].Y=kord.Y+siz.Y/2;
      connect(&timer,SIGNAL(timeout()),this,SLOT(Render()));
      timer.start(1000/60);
      indexArray[0][0]=0;
      indexArray[0][1]=1;
      indexArray[0][2]=2;
      indexArray[0][3]=3;
      draw_list=NULL;
      this->show();
      }
void ECamera::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0,0.0,0.0,1.0);//ustonovim zvet fona okna
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(krai[0].X,krai[1].X,krai[1].Y,krai[0].Y,1.0,-1.0);
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);// функция прозрачности
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
}
void ECamera::Off()
{
     status=OFF;
     emit ECamera_Off();
}
bool ECamera::On()
{
    if(draw_list==NULL)
    {
     status=OFF;
    return false;
    }
    else
    {
        status=ON;
        emit ECamera_On();
        return true;
    }
}
void ECamera::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(status)
    {
        glLoadIdentity();
        glOrtho(krai[0].X,krai[1].X,krai[1].Y,krai[0].Y,1.0,-1.0);
        (*draw_list)->Elock();
        for(EObject* element:**draw_list)//vozmogen bag
        {
            if(element->getEObjectNameClass()==E_MODULEOBJECT)
                for(EObject *obj:*((EModuleObject*)element)->getModuleVector())
                    draw_Object(obj);
            else
                draw_Object(element);
        }
        (*draw_list)->Eun_lock();
        glFlush();
    }
}
void ECamera::resizeGL(int w,  int h)
{
    glViewport(0,0,w,h);
}
void ECamera::Render()
{
    if(status)
    {
         _render();
    }
}
void ECamera::_seting_update()
{
     setings->sync();
}
void ECamera::_key_render()
{
    X_new+=quan*keys[_right];
    X_new-=quan*keys[_left];
    Y_new-=quan*keys[_up];
    Y_new+=quan*keys[_down];
}
void ECamera::_render()
{
    quan=sqrt(siz.X*siz.Y)/20;
    if(mode==custom)
    {
       _key_render();
    }else
    {
       X_new=folow_Obj->x();
       Y_new=folow_Obj->y();
    }
    if(new_siz.X<max_siz.X&&new_siz.Y<max_siz.Y&&keys[_mous_up]&&!keys[_mous_down])
         new_siz=EKord(new_siz.X+100*Windows_Skrin,new_siz.Y+100);
    if(new_siz.X>min_siz.X&&new_siz.Y>min_siz.Y&&keys[_mous_down]&&!keys[_mous_up])
         new_siz=EKord(new_siz.X-100*Windows_Skrin,new_siz.Y-100);
    speed_kord_X=(X_new-_X_)/10.0;
    speed_kord_Y=(Y_new-_Y_)/10.0;
    speed_siz_W=(new_siz.X-siz.X)/10.0;
    speed_siz_H=(new_siz.Y-siz.Y)/10.0;
    _X_+=speed_kord_X;
    _Y_+=speed_kord_Y;
    siz=EKord(siz.X+speed_siz_W,speed_siz_H+siz.Y);
    krai[0].X=_X_-siz.X/2.0;
    krai[0].Y=_Y_-siz.Y/2.0;
    krai[1].X=_X_+siz.X/2.0;
    krai[1].Y=_Y_+siz.Y/2.0;
    repaint();
 }
/*void ECamera::poolRender(EObject *sprite){
    sprite->stop(true);
    int i=poolLastIndex;
    unsigned int tempID=sprite->getIdFrame();
    while(i!=-1||pool[i].textureID!=NULL||pool[i].FrameID!=tempID){
        i--;
    }
    if(i<0||pool[i].textureID==NULL){
        while(poolMemorySize>poolMemorySizeLemit)
        {
            poolMemorySize-=SIZE_FRAME(poolFirstIndex);
            delete pool[poolFirstIndex].textureID;
            pool[poolFirstIndex].textureID=NULL;
            if(poolFirstIndex<poolSize-1)
                poolFirstIndex++;
            else
                poolFirstIndex=0;
        }
        if(poolLastIndex<poolSize-1)
            poolLastIndex++;
        else
            poolLastIndex=0;
        pool[poolLastIndex].textureID=sprite->Bind(poolLastIndex);
        poolMemorySize+=SIZE_FRAME(poolLastIndex);
    }else{
        sprite->newAdresFromFrame(i);
    }
    sprite->stop(false);
}*/
void ECamera::draw_Object(EObject * Object)
{
    switch(Object->getEObjectNameClass()){
    case EOBJECT:{
        try{
            (*pool)[Object->getFrame()]->bind();
        }catch(...){
            pool->poolRender(Object);
        }
        glPushMatrix();
        glTranslatef(Object->x(),Object->y(),Object->getSloi());
        glRotatef(Object->getUgol(),0,0,1);
        glVertexPointer(4,GL_FLOAT,0,Object->getMatrix());
        glTexCoordPointer(4,GL_FLOAT,0,Object->getMatrix());
        glDrawElements(GL_QUADS,4,GL_FLOAT,indexArray);
        glPopMatrix();
        break;
    }
    case E_FON:{
        try{
            (*pool)[Object->getFrame()]->bind();
        }catch(...){
            pool->poolRender(Object);
        }
        glPushMatrix();
        //glTranslatef(krai->X,krai->Y,Object->getSloi());
        Object->getMatrix()[0][0]=krai->X;
        Object->getMatrix()[0][1]=krai->Y;
        //Object->getMatrix()[0][2]=Object->getSloi();

        Object->getMatrix()[1][0]=krai[0].X;
        Object->getMatrix()[1][1]=krai[1].Y;
        //Object->getMatrix()[1][2]=0;

        Object->getMatrix()[2][0]=krai[1].X;
        Object->getMatrix()[2][1]=krai[0].Y;
        //Object->getMatrix()[2][2]=0;

        Object->getMatrix()[3][0]=krai[1].X;
        Object->getMatrix()[3][1]=krai[1].Y;
        //Object->getMatrix()[3][2]=0;

        glVertexPointer(4,GL_FLOAT,0,Object->getMatrix());
        glTexCoordPointer(4,GL_FLOAT,0,Object->getMatrix());
        glDrawElements(GL_QUADS,4,GL_FLOAT,indexArray);
        glPopMatrix();
        break;
    }
    default:break;
    }
}
void ECamera::Press_key(short key)
{
    if(event)
    keys[key]=true;
}
void ECamera::Release_key(short key)
{
    if(event)
    keys[key]=false;
}
void ECamera::folow(EObject *obj)
{
   folow_Obj=obj;
}
void ECamera::setmode(const MOD &m)
{
    switch (m) {
    case player:
    {
        if(folow_Obj==NULL)
            throw EError(11,"void ECamera::setmode(MOD m)");
        else
        {
        max_siz=EKord((400<folow_Obj->getSpeed())?folow_Obj->getSpeed()*2:800);
        min_siz=EKord((400<folow_Obj->getSpeed())?folow_Obj->getSpeed():400);
        mode=m;
        }
        break;
    }
    case custom:
    {
        max_siz=default_siz_max;
        min_siz=default_siz_min;
        mode=m;
        break;
    }
    default:
        break;
    }
}
void ECamera::skroll_size(const EKord &s)
{
    new_siz=s;
}
void ECamera::Mov_ECamera_To(int x, int y)
{
    if(mode==custom)
    {
        X_new=x;
        Y_new=y;
    }
}
void ECamera::setConfig(const EConfig &cfg)
{
    *setings=cfg;
    update();
}
void ECamera::setSize(const int &s)
{
    siz=EKord(s*Windows_Skrin,s);
    new_siz=siz;
}
EKord ECamera::getSize()
{
    return siz;
}
EObject* ECamera::getFolow()
{
    return folow_Obj;
}
EKord* ECamera::getKrai()
{
    return krai;
}
MOD ECamera::getMode()
{
    return mode;
}
EConfig ECamera::getConfig()
{
    return *setings;
}
EKord ECamera::getVirtualKord()const{
    return Vkord;
}
EKord ECamera::getVirtualSize()const{
    return VSize;
}
EMaps* ECamera::getMap(){
    return map;
}
void ECamera::set_maps(EMaps *m){
    map=m;
    map->Load(krai);
}
void ECamera::setVirtualKord(const EKord &kord){
    Vkord=kord;
}
void ECamera::setVirtualSize(const EKord &kord){
    VSize=kord;
}
void ECamera::setSizeSkrin(const EKord &kord)
{
    setings->windows_skrinn=kord;
    update();
}
void ECamera::setSizeSkrin(const int&X,const int &Y)
{
    setings->windows_skrinn.X=X;
    setings->windows_skrinn.Y=Y;
    update();
}
void ECamera::setDrawList(EObject_List **o){
    draw_list=o;
}
EConfig* ECamera::config()
{
    return setings;
}
void ECamera::update()
{
    this->setBaseSize(setings->windows_skrinn.TO_QSize());
    this->setMinimumSize(setings->windows_skrinn.TO_QSize());
    this->setMaximumSize(setings->windows_skrinn.TO_QSize());
    Windows_Skrin=setings->windows_skrinn.X/(float)setings->windows_skrinn.Y;
    min_siz=EKord(100*Windows_Skrin,100);
    max_siz=EKord(10000*Windows_Skrin,10000);
    if(siz.X<siz.Y)
        new_siz=EKord(siz.X*Windows_Skrin,siz.X);
    else
        new_siz=EKord(siz.Y*Windows_Skrin,siz.Y);
}
void ECamera::setEvent(const bool &b)
{
    event=b;
}
ECamera::~ECamera()
{
        Off();
        timer.stop();
        delete[] keys;
        //delete setings;
        glDisable(GL_ALPHA_TEST);
        glDisable(GL_BLEND);
        draw_list=NULL;
}
