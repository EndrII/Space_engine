#ifndef MODULEINFORMATION_H
#define MODULEINFORMATION_H

#include <QDialog>
#include <QSpinBox>
#include "Buttons.h"
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

class ModuleInformation:public QDialog
{
    Q_OBJECT
private:
    ButtonGreen *__ok;
    ButtonRegulyar *cancle;
    QLineEdit *name_E;
    QTextEdit *DescEdit;
    QLabel *header;
    QString *name_,*desc_;
private slots:
    void _ok(bool);
public:
    ModuleInformation(QString* name,QString*desc,QWidget* ptr=NULL);
};

#endif // MODULEINFORMATION_H
