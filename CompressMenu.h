#ifndef COMPRESSMENU_H
#define COMPRESSMENU_H
#include <QDialog>
#include <QSpinBox>
#include "Buttons.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
class CompressMenu: public QDialog
{
    Q_OBJECT
private:
    ButtonGreen *__ok;
    ButtonRegulyar *cancle;
    QSpinBox *time,*frame;
    QLabel *header;
private slots:
    void _ok(bool);
public:
    CompressMenu(QWidget* ptr=0);
signals:
    void ok(int,int);
};

#endif // COMPRESSMENU_H
