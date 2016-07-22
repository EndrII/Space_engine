#include "EImage.h"
EImage::EImage(const QString &url):
    QLabel()
{
    img=new QPixmap(url);
    this->setPixmap(img->scaled(this->size()));
    Url=url;
}
void EImage::change(const QString &url)
{
    delete img;
    img=new QPixmap(url);
    this->setPixmap(img->scaled(this->size()));
}
void EImage::_resize()
{
    this->setPixmap(img->scaled(this->size()));
}
void EImage::resize()
{
    _resize();
}
EImage::~EImage()
{
}

