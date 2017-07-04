#include "EResObjectView.h"

EResObjectView::EResObjectView(EItem *res,QWidget *parent) : QWidget(parent)
{
    this->res=res;
    this->setToolTip(QString("<b>%1</b>: \n%2").arg(res->getSource()->name(),res->getSource()->desc()));
    img=new EImage(*res->getSource()->picture(),this);
    value=new QLabel(QString::number(res->getValue()),this);
    connect(res,SIGNAL(valueChanged(int)),SLOT(valueChanged(int)));
}
void EResObjectView::changeResurs(EItem *res){
    disconnect(this->res,SIGNAL(valueChanged(int)),this,SLOT(valueChanged(int)));
    this->res=res;
    this->setToolTip(QString("<b>%1</b>: \n%2").arg(res->getSource()->name(),res->getSource()->desc()));
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
void EResObjectView::mousePressEvent(QMouseEvent *){
    img->setEnabled(false);
}
void EResObjectView::mouseReleaseEvent(QMouseEvent *event){
    if(!img->isEnabled()){
        img->setEnabled(true);
        emit mouseClickEvent(event);
    }
}
void EResObjectView::valueChanged(int i){
    value->setText(QString::number(i));
}
EResObjectView::~EResObjectView(){
}
