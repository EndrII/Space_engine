#ifndef MODULEPARALAX_H
#define MODULEPARALAX_H
#include "Module.h"
#include <SpaceEngine/Objects/EParalax.h>
#include <QListWidget>
class ModuleParalax: public Module
{
    Q_OBJECT
private:
    EParalax *item;
    QDoubleSpinBox *Up;
    QListWidget *listofSprites;
    ButtonPlay *add;
    ButtonRemove *remove;
protected slots:
   // void frameChanged(unsigned short, unsigned int);
    void factorChanged(double);
    void buttonClick(QPushButton*);
public:
    bool setNewObject(EObject*);
    bool saveObject(const QString &patch);
    ModuleParalax(EParalax*,SpaceEngine*parent, QString *patch, QWidget* Widget=0);
};

#endif // MODULEPARALAX_H
