#include "EMinimap.h"


EMinimap::EMinimap(EGameObject *obj,EPool*pool_,EConfig *cfg,QWidget *widget)
    :ECamera(EKord(0),EKord(1000),cfg,pool_,widget)
{
    this->folow(obj);
    radar=obj->getRadarPower();
    timer.setInterval(1000);
    this->setmode(player);
    this->setSizeSkrin(100,100);
}
void EMinimap::draw_Object(EObject * Object){
    if(Object->getEObjectNameClass()!=E_MODULEOBJECT||!((EModuleObject*)Object)->isDraw_in_map())
        return;
    QColor DefaultColor,VectorColor;
            switch (((EModuleObject*)Object)->getRelation())
            {
            case players:{DefaultColor=QColor(25,250,25);
                          VectorColor =QColor(25,250,210);
                          break;}
            case allies:{DefaultColor=QColor(25,25,250);
                         VectorColor =QColor(187,230,250);
                          break;}
            case enemies:{DefaultColor=QColor(250,25,25);
                          VectorColor =QColor(250,194,25);
                          break;}
            default:break;
            }
                   glPushMatrix();
                   glTranslatef(Object->x(),Object->y(),0);
                   glRotatef(Object->getUgol()+90,0,0,1);
                   glBegin(GL_TRIANGLES);
                    //qglColor(VectorColor);
                   glColor3b(VectorColor.red(),VectorColor.green(),VectorColor.blue());
                    glVertex2f(0,0-radar/40);
                    glColor3b(DefaultColor.red(),DefaultColor.green(),DefaultColor.blue());
                    glVertex2f(0-radar/60,radar/60);
                    glVertex2f(radar/60,radar/60);
                   glEnd();
                   glPopMatrix();
}
/*void EMinimap::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(status)
    {
        draw_fon();
        _list->Elock();
        for(auto* element:*_list)
        {
                 draw_object(element);
        }
        _list->Eun_lock();
    glFlush();
    }
}
*/
void EMinimap::folow(EGameObject * p){
    ECamera::folow(p);
    radar=p->getRadarPower();
    max_siz=EKord(p->getRadarPower());
    min_siz=EKord(p->getRadarPower());
}
EMinimap::~EMinimap(){

}
/*EMinimap::EMinimap(EObject_List *mapList, QWidget*ptr):
    QOpenGLWidget(ptr)
{
    fon=NULL;

    _list=mapList;
    if(map!=NULL)size_elements=map->getSize().X/LOGSIZE;
    timer=new QTimer;
    status=false;
    fastDrawFlag=false;
    timer->setInterval(1000);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(_render()));
}
void EMinimap::set_maps(EMaps *m)
{
    _map=m;
    _list=m->getMainList();
    size_elements=_map->getSize().X/LOGSIZE;
    glOrtho(0.0,_map->getSize().X,_map->getSize().Y,0.0,1.0,-1.0);
}
void EMinimap::setImageMap(QPixmap *I)
{
    fon=I;
}
void EMinimap::setTimeUpdate(const int &t)
{
    timer->setInterval(t);
}
int EMinimap::getTimeUpdate()
{
    return timer->interval();
}
QPixmap* EMinimap::getImageMap()
{
    return fon;
}
void EMinimap::draw_fon()
{
    if(fon!=NULL)
    {
        qglColor(Qt::white);
        glBegin(GL_TEXTURE);
        drawTexture(QRect(0,0,_map->getSize().X,_map->getSize().Y),bindTexture(*fon));
        glEnd();
    }
}
void EMinimap::resizeGL(int w,  int h)
{
    glViewport(0,0,w,h);
}
void EMinimap::Off()
{
    status=false;
}
void EMinimap::On()
{
    status=true;
}
void EMinimap::draw_object(EObject *Object)
{
    if(Object->getEObjectNameClass()!=emoduleobject||!((EModuleObject*)Object)->isDraw_in_map())
        return;
    QColor DefaultColor,VectorColor;
            switch (((EModuleObject*)Object)->getRelation())
            {
            case players:{DefaultColor=QColor(25,250,25);
                          VectorColor =QColor(25,250,210);
                          break;}
            case allies:{DefaultColor=QColor(25,25,250);
                         VectorColor =QColor(187,230,250);
                          break;}
            case enemies:{DefaultColor=QColor(250,25,25);
                          VectorColor =QColor(250,194,25);
                          break;}
            default:break;
            }
                   glPushMatrix();
                   glTranslatef(Object->getKord().X,Object->getKord().Y,0);
                   glRotatef(Object->getUgol()+90,0,0,1);
                   glBegin(GL_TRIANGLES);
                    qglColor(VectorColor);
                    glVertex2f(0,0-size_elements/2);
                    qglColor(DefaultColor);
                    glVertex2f(0-size_elements/3,size_elements/3);
                    glVertex2f(size_elements/3,size_elements/3);
                   glEnd();
                   glPopMatrix();
}
void EMinimap::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(status)
    {
        draw_fon();
        _list->Elock();
        for(auto* element:*_list)
        {
                 draw_object(element);
        }
        _list->Eun_lock();
    glFlush();
    }
}
void EMinimap::initializeGL()
{
    qglClearColor(Qt::black);//ustonovim zvet fona okna
   // glMatrixMode(GL_PROJECTION);
  //  glLoadIdentity();
     //glOrtho(0.0,1000.0,1000.0,0.0,1.0,-1.0);
    // glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);// функция прозрачности
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
}
void EMinimap::_render()
{
    updateGL();
}
EMinimap::~EMinimap()
{
    fon=NULL;
    timer->stop();
    delete timer;
}
*/
