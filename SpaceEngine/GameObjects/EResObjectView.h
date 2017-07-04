#ifndef ERESOBJECTVIEW_H
#define ERESOBJECTVIEW_H

#include <QWidget>
#include "EItem.h"
#include "SpaceEngine/Objects/EImage.h"
#include <cmath>
/**
 * @brief The EResObjectView class
 * view items is inventory
 */
class EResObjectView : public QWidget
{
    Q_OBJECT
private:
    EItem *res;
    EImage *img;
    QLabel *desc,*value;
private slots:
    void valueChanged(int);
protected:
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    explicit EResObjectView(EItem *res, QWidget *parent = 0);
    void changeResurs(EItem *res);
    EItem * getItem();
    ~EResObjectView();
public slots:
signals:
    void mouseClickEvent(QMouseEvent*);
};

#endif // ERESOBJECTVIEW_H
