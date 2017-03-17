#include "EResObjectView.h"

EResObjectView::EResObjectView(EItem *res,QWidget *parent) : QWidget(parent)
{
    this->res=res;
    img=new EImage(*res->getSource()->picture(),this);
    value=new QLabel(QString::number(res->getValue()),this);
    connect(res,SIGNAL(valueChanged(int)),SLOT(valueChanged(int)));
}
void EResObjectView::changeResurs(EItem *res){
    disconnect(this->res,SIGNAL(valueChanged(int)),this,SLOT(valueChanged(int)));
    this->res=res;
    connect(res,SIGNAL(valueChanged(int)),SLOT(valueChanged(int)));
    img->change(*res->getSource()->picture());
}
void EResObjectView::resizeEvent(QResizeEvent *){
    img->setGeometry(this->geometry());
    value->setGeometry(width()*0.5,height()*0.5,width()*0.5,height()*0.5);
    value->setStyleSheet(QString("font-size: %1px").arg(value->height()/((int)(log10(res->getValue())+1))));
}
EItem* EResObjectView::getItem(){
    return res;
}
void EResObjectView::valueChanged(int i){
    value->setText(QString::number(i));
}
EResObjectView::~EResObjectView(){
}
