#ifndef ERESOBJECTVIEW_H
#define ERESOBJECTVIEW_H

#include <QWidget>
#include "EResursePack.h"
#include <QHBoxLayout>
#include <QComboBox>
class EResObjectView : public QWidget
{
    Q_OBJECT
private:
    EResursePack *resPack;
    QComboBox *combo;
    QLabel *desc;
private slots:
    void comboChanged(int);
public:
    explicit EResObjectView(QWidget *parent = 0);
    ~EResObjectView();
signals:
    void itemChanged(int id_item);
public slots:
};

#endif // ERESOBJECTVIEW_H
