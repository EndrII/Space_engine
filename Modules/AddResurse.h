#ifndef ADDRESURSE_H
#define ADDRESURSE_H

#include <QDialog>
#include "ResObjectsView.h"
#include "Buttons.h"
#include <QVBoxLayout>
class AddResurse : public QDialog
{
    Q_OBJECT
private:
    ResObjectsView *obj;
    ButtonGreen *ok;
    int item_id;
    ButtonRegulyar *cancel;
private slots:
    void complit(bool);
    void clos(bool);
    void itemChanged(int);
public:
    explicit AddResurse(QWidget *parent = 0);
    static int staticShow(QWidget *ptr);
signals:

public slots:
};

#endif // ADDRESURSE_H
