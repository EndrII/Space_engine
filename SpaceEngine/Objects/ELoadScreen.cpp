#include "ELoadScreen.h"

ELoadScreen::ELoadScreen(QWidget *ptr):
    QWidget(ptr)
{
    timer=new QTimer();
    timer->setInterval(10000);
    timer->start();
    img=new EImage("none");
    connect(timer,SIGNAL(timeout()),SLOT(imgUpdate()));
    bar=new QProgressBar(this);
    this->setHidden(true);
    //this->show();
}
ELoadScreen::ELoadScreen(const QStringList &img, QWidget *ptr):
    ELoadScreen(ptr)
{
    setImages(img);
}
void ELoadScreen::setImages(const QStringList &img){
    images=img;
    imageIterator=images.begin();
}
void ELoadScreen::progress(int i){
    if(i<0)
        this->setHidden(true);
    else
        bar->setValue(i);
}
void ELoadScreen::imgUpdate(){
    if(images.empty())return;
    img->change(*imageIterator);
    imageIterator++;
    img->resize();
}
void ELoadScreen::setInterval(const int &interval){
    timer->setInterval(interval);
}
void ELoadScreen::setmax(const int &max, QString name){
    this->setHidden(false);
    bar->setMaximum(max);
    bar->setTextVisible(name.size());
    bar->setToolTip(name);
}
void ELoadScreen::resizeEvent(QResizeEvent*){
    bar->setMaximumSize(this->width(),this->height()*0.1);
    bar->setMinimumSize(this->width(),this->height()*0.1);
    bar->setGeometry(0,this->height()*0.9,this->width(),this->height()*0.1);
    img->setMaximumSize(this->width(),this->height()*0.9);
    img->setMinimumSize(this->width(),this->height()*0.9);
    img->setGeometry(0,0,this->width(),this->height()*0.9);
    img->resize();
}
ELoadScreen::~ELoadScreen(){
    delete img;
    delete bar;
    delete timer;
}
