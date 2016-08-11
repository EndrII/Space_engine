#include "EButton.h"
EButton::EButton(const QString &Default, const QString &curent, QWidget *ptr)
    :QPushButton(ptr)
{
    default_=QColor(239,199,102,195);
    presed_=QColor(74,0,38,195);
   // this->font()
    current=false;
    Default_=new QPixmap(Default);
    curent_=new QPixmap(curent);
    connect(this,SIGNAL(pressed()),this,SLOT(presed()));
    connect(this,SIGNAL(released()),this,SLOT(release()));

}
EButton::EButton(const QString &Default,const QString &curent,const QString &text ,const QFont&F,
                 const QColor&def,const QColor&select,QWidget*ptr)
    :QPushButton(ptr)
{
    default_=def;
    presed_=select;
    setFont(F);
    current=false;
    Default_=new QPixmap(Default);
    curent_=new QPixmap(curent);
    this->setText(text);
    connect(this,SIGNAL(pressed()),this,SLOT(presed()));
    connect(this,SIGNAL(released()),this,SLOT(release()));
}
void EButton::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    if(current)
    {
        p.drawPixmap(0,0,this->geometry().width(),this->geometry().height(),*curent_);
        p.setPen(QPen(presed_));
    }
    else
    {
        p.drawPixmap(0,0,this->geometry().width(),this->geometry().height(),*Default_);
        p.setPen(QPen(default_));
    }

    p.setFont(this->font());
    p.drawText(QRectF(0,0,this->geometry().width(),this->geometry().height()),Qt::AlignCenter,this->text());
}
void EButton::presed()
{
    current=true;
    this->update();
}
void EButton::release()
{
    current=false;
     this->update();
    emit EClick(this);
}
EButton::~EButton()
{
 delete Default_;
 delete curent_;
 disconnect(this,0,0,0);
}
