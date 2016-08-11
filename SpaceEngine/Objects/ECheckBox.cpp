#include "ECheckBox.h"

ECheckBox::ECheckBox(const QString &sta0url, const QString &sta1url,
                     QWidget *ptr):
QAbstractButton(ptr)
{
    State0=new QPixmap(sta0url);
    State1=new QPixmap(sta1url);
    stateBox=Unchecked;
    connect(this,SIGNAL(clicked(bool)),this,SLOT(Click_(bool)));
}
void ECheckBox::Click_(bool)
{
    stateBox=(ECheckBoxState)((((int)stateBox)+1)%2);
    emit StateChanged(stateBox);
    this->update();
}
void ECheckBox::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    switch (stateBox) {
    case Unchecked:
        p.drawPixmap(1,1,this->size().width(),this->size().height(),*State0);
        break;
    case Checked:
        p.drawPixmap(1,1,this->size().width(),this->size().height(),*State1);
        break;
    default:
        break;
    }
}
ECheckBoxState ECheckBox::getState()
{
    return stateBox;
}
void ECheckBox::Resize(const EKord &k)
{
    setMaximumSize(k.X,k.Y);
    setMinimumSize(k.X,k.Y);

}
void ECheckBox::setState(ECheckBoxState state)
{
    stateBox=state;
    this->update();
}
ECheckBox::~ECheckBox()
{
    delete State0;
    delete State1;
}



