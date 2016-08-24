#include "ECamera.h"
ECamera::ECamera(const EKord &kord, const EKord &size,EConfig *cfg,EPool*pool_, QWidget *ptr):
    QOpenGLWidget(ptr)
{
      pool=pool_;
      event=true;
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
      timer.setInterval(1000/60);
      idintyMatrix[0][0]=-0.0;
      idintyMatrix[0][1]=-0.0;

      idintyMatrix[1][0]=+1.0;
      idintyMatrix[1][1]=-0.0;

      idintyMatrix[2][0]=+1.0;
      idintyMatrix[2][1]=+1.0;

      idintyMatrix[3][0]=-0.0;
      idintyMatrix[3][1]=+1.0;
      indexArray[0][0]=0;
      indexArray[0][1]=1;
      indexArray[0][2]=2;
      indexArray[0][3]=3;
      draw_list=NULL;
      LineWidth=3;
      this->show();
}
void ECamera::mousePressEvent(QMouseEvent *event){
    tempEvent.button=event->button();
    tempEvent.x=krai[0].X+siz.X*event->x()/width();
    tempEvent.y=krai[0].Y+siz.Y*event->y()/height();
    map->ClickEvent(&tempEvent);
    emit MouseClikedEvent(&tempEvent);
}
void ECamera::initializeGL()
{
    initializeOpenGLFunctions();
    clearColor =QColor(0,0,0,1);
    glClearColor(0.0,0.0,0.0,1.0);//ustonovim zvet fona okna
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);// функция прозрачности
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glMatrixMode(GL_MODELVIEW);
}
void ECamera::Off()
{
    timer.stop();
     status=OFF;
     emit ECamera_Off();
}
bool ECamera::On()
{
    if(draw_list==NULL)
    {
        timer.stop();
        status=OFF;
    return false;
    }
    else
    {
        timer.start();
        status=ON;
        emit ECamera_On();
        return true;
    }
}
void ECamera::paintGL()
{
    glClearColor(clearColor.redF(),clearColor.greenF(),clearColor.blueF(),1.0);
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
         new_siz=EKord(new_siz.X*1.05,new_siz.Y*1.05);
    if(new_siz.X>min_siz.X&&new_siz.Y>min_siz.Y&&keys[_mous_down]&&!keys[_mous_up])
         new_siz=EKord(new_siz.X*0.95,new_siz.Y*0.95);
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
void ECamera::drawContur(EObject *c){
    unsigned int size = c->getContur()->size();
    if(!size) return ;
    glPointSize(LineWidth*2);
    glBegin(GL_POINTS);
        glColor3f(1.0,0.4,0.3);
        for(unsigned int j=0,i=size-1;j<size;i=j++){
            glVertex2f(c->getContur()->generateX(i),c->getContur()->generateY(i));
            glVertex2f(c->getContur()->generateX(j),c->getContur()->generateY(j));
        }
    glEnd();
    glLineWidth(LineWidth);
    glBegin(GL_LINES);
        glColor3f(0.3,1.0,0.3);
        for(unsigned int j=0,i=size-1;j<size;i=j++){
            glVertex2f(c->getContur()->generateX(i),c->getContur()->generateY(i));
            glVertex2f(c->getContur()->generateX(j),c->getContur()->generateY(j));
        }
    glEnd();
    glColor3f(1.0,1.0,1.0);
}
void ECamera::draw_Object(EObject * Object)
{
    switch(Object->getEObjectNameClass()){
    case EOBJECT:{
        glPushMatrix();
        if(Object->isDrawContur())
            drawContur(Object);
        tempTexture=pool->call(Object);
        if(tempTexture)
            tempTexture->bind();
        else
            return;
        glTranslatef(Object->x(),Object->y(),Object->getSloi());
        glRotatef(Object->getUgol(),0,0,1);
        glVertexPointer(3,GL_FLOAT,0,Object->getMatrix());
        glTexCoordPointer(2,GL_FLOAT,0,idintyMatrix);
        glDrawElements(GL_QUADS,4,GL_UNSIGNED_BYTE,indexArray);

        glPopMatrix();
        break;
    }
    case E_FON:{
        tempTexture=pool->call(Object);
        if(tempTexture)
            tempTexture->bind();
        else
            return;
        glPushMatrix();
        Object->getMatrix()[0][0]=krai->X;
        Object->getMatrix()[0][1]=krai->Y;

        Object->getMatrix()[1][0]=krai[0].X;
        Object->getMatrix()[1][1]=krai[1].Y;

        Object->getMatrix()[2][0]=krai[1].X;
        Object->getMatrix()[2][1]=krai[0].Y;

        Object->getMatrix()[3][0]=krai[1].X;
        Object->getMatrix()[3][1]=krai[1].Y;
        glVertexPointer(3,GL_FLOAT,0,Object->getMatrix());
        glTexCoordPointer(2,GL_FLOAT,0,idintyMatrix);
        glDrawElements(GL_QUADS,4,GL_UNSIGNED_BYTE,indexArray);
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
void ECamera::Mov_ECamera_To(float x, float y)
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
EKord ECamera::getmovCenter(){
    return EKord(X_new,Y_new);
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
void ECamera::setLineWidth(const int &LineWidth_){
    LineWidth=LineWidth_;
}
void ECamera::set_maps(EMaps *m){
    bool temp=status;
    status=false;
    map=m;
    map->Load(krai);
    draw_list=m->getDrawList();
    status=temp;
}
void ECamera::setVirtualKord(const EKord &kord){
    Vkord=kord;
}
void ECamera::setVirtualSize(const EKord &kord){
    VSize=kord;
}
void ECamera::setBackgroundColor(const QColor &color){
    clearColor=color;
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
       // glDisable(GL_ALPHA_TEST);
       // glDisable(GL_BLEND);
        draw_list=NULL;
}
