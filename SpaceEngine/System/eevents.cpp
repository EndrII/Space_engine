#include "eevents.h"

EEvents::EEvents(EConfig*cfg, QWidget *parent) :
    QWidget(parent)
{
    setings=cfg;
    this->setPalette(QPalette(QColor(0,0,0,255)));
    timer=new QTimer;
    timer->start(10000);
    connect(timer,SIGNAL(timeout()),this,SLOT(_update()));
    connect(&timer2,SIGNAL(timeout()),this,SLOT(_release()));
}
short EEvents::convert(const int &Key)
{
    int J=setings->getLength();
    for(int i(0);i<J;i++)
    {
        if(setings->keys[i]==Key)
            return i;
    }
    return -1;
}

void EEvents::_update()
{
    setings->sync();
}
void EEvents::setSetings(EConfig* c)
{
    setings=c;
}
void EEvents::keyPressEvent(QKeyEvent *Event)
{
       emit Press(convert(Event->key()));
}
void EEvents::keyReleaseEvent(QKeyEvent *Event)
{
    emit Release(convert(Event->key()));
}
void EEvents::mousePressEvent(QMouseEvent *Event)
{
    switch (Event->button()) {
    case Qt::LeftButton:{
       emit Press(_mous_left);break;}
    case Qt::MidButton:{
       emit Press(_mous_mid); break;}
    case Qt::RightButton:{
       emit Press(_mous_right);break;}
    default:
        break;
    }

}
void EEvents::mouseDoubleClickEvent(QMouseEvent*)
{

}
void EEvents::resizeEvent(QResizeEvent *event){
    emit Resize(event);
}
void EEvents::wheelEvent(QWheelEvent * event)
{
    if(event->delta()>0)
    {
        emit Press(_mous_up);
        timer2.start(100);
    }
    else
    {
        emit Press(_mous_down);
        timer2.start(100);
    }
}
void EEvents::_release()
{
    emit Release(_mous_down);
    emit Release(_mous_up);
    timer2.stop();
}
void EEvents::mouseReleaseEvent(QMouseEvent *Event)
{
    switch (Event->button()) {
    case Qt::LeftButton:{
       emit Release(_mous_left);break;}
    case Qt::MidButton:{
       emit Release(_mous_mid); break;}
    case Qt::RightButton:{
       emit Release(_mous_right);break;}
    default:
        break;
    }

}
void EEvents::mouseMoveEvent(QMouseEvent *Event)
{
    emit Mousemov(EKord(Event->x(),Event->y()));
}
void EEvents::focus()
{
    setFocus();
}
EEvents::~EEvents()
{
    timer->stop();
    delete timer;
}
