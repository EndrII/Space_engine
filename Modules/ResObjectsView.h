#ifndef ResObjectsView_H
#define ResObjectsView_H

#include <QWidget>
#include "SpaceEngine/GameObjects/EResObjectView.h"
#include "SpaceEngine/GameObjects/EResursePack.h"
#include <QHBoxLayout>
#include <QComboBox>
class ResObjectsView : public QWidget
{
    Q_OBJECT
private:
    EResursePack *resPack;
    EResObjectView* view;
    QComboBox *combo;
    QLabel *desc;
private slots:
    void comboChanged(int);
public:
    explicit ResObjectsView(QWidget *parent = 0);
    int getSize();
    ~ResObjectsView();
signals:
    void itemChanged(int id_item);
public slots:
};

#endif // ERESOBJECTVIEW_H
