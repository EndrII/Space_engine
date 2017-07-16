#ifndef MODULERESURSOBJECT_H
#define MODULERESURSOBJECT_H
#include "Module.h"
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QList>
#include <QTableWidget>
//#include <QListView>
#include <QSpinBox>
#include "Modules/AddResurse.h"
#include "SpaceEngine/GameObjects/EGameResurs.h"
class ModuleResursObject : public Module
{
    Q_OBJECT
private:
    QLineEdit *nameObject;
    QTextEdit *description;
    QSpinBox *valueResurse;
    QDoubleSpinBox *mass_item;
    EGameResurs *item;
    ButtonRegulyar *random;
    EResObjectView *view;
    QTableWidget *constructionList;
    //QLabel *name,*decript;
    ButtonPlay *addCraft;
    ButtonRemove *deleteCraft;
    void showTable();
private slots:
    void buttonClic(QPushButton*);
    void itemChanged(int row, int column);
    void massChanged(double);
    void nameChanged();
    void valueChanged(int);
 //   void nameIndexChanged(int i);
    void descChanged();
  //  void descIndexChanged(int);
public:
    bool setNewObject(EObject *obj);
    bool saveObject(const QString &patch);
    explicit ModuleResursObject(EGameResurs*ite, QString *projectDir, QWidget *parent = 0);
signals:
public slots:
};

#endif // MODULERESURSOBJECT_H
