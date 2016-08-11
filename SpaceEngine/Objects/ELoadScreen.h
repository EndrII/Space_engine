#ifndef ELOADSCREEN_H
#define ELOADSCREEN_H
#include <QProgressBar>
#include "EImage.h"
#include <QTimer>
class ELoadScreen : public QWidget
{
    Q_OBJECT
private:
    QTimer *timer;
    QProgressBar *bar;
    EImage *img;
    QStringList images;
    QList<QString>::iterator imageIterator;
protected slots:
    void resizeEvent(QResizeEvent *);
    void imgUpdate();
public:
    ELoadScreen(QWidget * ptr=0);
    ELoadScreen(const QStringList& img,QWidget * ptr=0);
    void setInterval(const int&interval);
    void setImages(const QStringList& img);
    //void Disconnect();
    ~ELoadScreen();
public slots:
    void setmax(const int& max,QString);
    //void progress(float);
    void progress(int);

};

#endif // ELOADSCREEN_H
