#ifndef MODULERESURSOBJECT_H
#define MODULERESURSOBJECT_H
#include "Module.h"
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QList>
#include <QTableWidget>
#include <QTableView>
#include <QStandardItemModel>
//#include <QListView>
#include <QSpinBox>
#include <QMessageBox>
#include "Modules/AddResurse.h"
#include "SpaceEngine/GameObjects/EGameResurs.h"
class CraftTableModel : public QStandardItemModel{
    Q_OBJECT
protected:
    craftList *craftlist;
public:
    CraftTableModel(craftList *craft);
    void setNew(craftList* craft);
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) ;
    void refresh();
    ~CraftTableModel();
};
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
    QTableView *constructionList;
    CraftTableModel *model;
    ButtonPlay *addCraft;
    ButtonRemove *deleteCraft;
    QPushButton *icon;
private slots:
    void buttonClic(QPushButton*);
    void iconChange(bool);
    void massChanged(double);
    void valueChanged(int);
public:
    bool setNewObject(EObject *obj);
    bool saveObject(const QString &patch);
    explicit ModuleResursObject(EGameResurs*ite,SpaceEngine*engine, QString *projectDir, QWidget *parent = 0);
signals:
public slots:
};

#endif // MODULERESURSOBJECT_H
