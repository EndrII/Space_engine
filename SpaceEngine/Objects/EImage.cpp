#include "EImage.h"

EImage::EImage(const QString &url, QWidget *ptr):
    EImage(new QPixmap(url),ptr){}
EImage::EImage(const QPixmap &im, QWidget *ptr):
    EImage(new QPixmap(im),ptr){}
EImage::EImage(const QImage &im, QWidget *ptr):
    EImage(QPixmap::fromImage(im),ptr){}
EImage::EImage(QWidget *ptr):
    EImage(NULL,ptr){}
EImage::EImage(QPixmap *im,QWidget *ptr):
    QLabel(ptr),
    fixedSize(10,10)
{
    _policy = EImage::fixed;
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    img=im;
    _resize();
}
void EImage::change(QPixmap *im)
{
    if(img)delete img;
    img=im;
    _resize();
}
void EImage::change(const QString &url)
{
    change(new QPixmap(url));
}
void EImage::change(const QPixmap &im)
{
    change(new QPixmap(im));
}
void EImage::change(const QImage &im)
{
    change(QPixmap::fromImage(im));
}
void EImage::_resize()
{
    if(!img) return;
    switch (_policy) {
    case EImage::fixed:
        this->setPixmap(img->scaled(fixedSize));
        break;
    case EImage::horizontal:{
        float praportion=(float)img->height()/img->width();
        this->setPixmap(img->scaled(QSize(this->height()*praportion,this->height())));
        break;
    }
    case EImage::vertical:{
        float praportion=(float)img->height()/img->width();
        this->setPixmap(img->scaled(QSize(this->width(),this->width()*praportion)));
        break;
    }
    case EImage::fill:
        this->setPixmap(img->scaled(this->size()));
        break;
    default:
        break;
    }
}
void EImage::resizeEvent(QResizeEvent *){
    _resize();
}
EImage::resize_policy EImage::resizepolicy()const{
    return _policy;
}
void EImage::setResizepolicy(EImage::resize_policy policy){
    _policy=policy;
}
QSize EImage::FixedSize()const{
    return fixedSize;
}
void EImage::setFixedSize(const QSize &size){
    fixedSize=size;
}
EImage::~EImage()
{
    if(img)delete img;
}
