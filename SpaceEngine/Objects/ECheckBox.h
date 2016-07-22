#ifndef ECHECKBOX_H
#define ECHECKBOX_H
#include <QAbstractButton>
#include <QPainter>
#include <QPixmap>
#include "SpaceEngine/System/EKord.h"
enum ECheckBoxState{Unchecked,Checked};
class ECheckBox :public QAbstractButton
{
    Q_OBJECT

private:
    ECheckBoxState stateBox;
    QPixmap *State0,*State1;
private slots:
    void Click_(bool);
protected:
    void paintEvent(QPaintEvent*);
public:
    ECheckBox(const QString&sta0url, const QString&sta1url, QWidget *ptr=NULL);
    ECheckBoxState getState();
    void Resize(const EKord&);
    ~ECheckBox();
public slots:
    void setState(ECheckBoxState);
signals:
    void StateChanged(ECheckBoxState);

};

#endif // ECHECKBOX_H
