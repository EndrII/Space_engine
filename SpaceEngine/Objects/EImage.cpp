#include "EImage.h"
EImage::EImage(const QString &url, QWidget *ptr):
    EImage(new QPixmap(url),ptr){}
EImage::EImage(const QPixmap &im, QWidget *ptr):
    EImage(new QPixmap(im),ptr){}
EImage::EImage(const QImage &im, QWidget *ptr):
    EImage(QPixmap::fromImage(im),ptr){}
EImage::EImage(QPixmap *im,QWidget *ptr):
    QLabel(ptr)
{
    img=im;
    this->setPixmap(img->scaled(this->size()));
    _resize();
}
void EImage::change(QPixmap *im)
{
    delete img;
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
    this->setPixmap(img->scaled(this->size()));
}
void EImage::resizeEvent(QResizeEvent *){
    _resize();
}
EImage::~EImage()
{
    delete img;
}

