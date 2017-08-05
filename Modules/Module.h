#ifndef MODULE
#define MODULE
#include <QWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <Buttons.h>
#include "projectdir.h"
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "SpaceEngine/Objects/EObject.h"
#include <QLabel>
#include <QCheckBox>
class SpaceEngine;
class Module: public QWidget{
    Q_OBJECT
private:
    QLabel *title;
    QHBoxLayout *box;
    QVBoxLayout *vbox;
protected:
    QString *patch;
    SpaceEngine *parent;
    void setTitle(const QString& titl);
    void newHorizont();
    virtual bool setNewObject(EObject * obj);
    void addWidget(QWidget*);
    void end();
public:
    explicit Module(SpaceEngine* parent,QString* patchProject,QWidget* ptr=0);
    virtual bool saveObject(const QString &);
    //addObject
    ~Module();
};
#endif

