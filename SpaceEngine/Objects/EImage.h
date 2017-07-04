#ifndef EIMAGE_H
#define EIMAGE_H
#include <QLabel>
#include <QBitmap>
class EImage:public QLabel //izobragenie
{
private:
    QPixmap *img;
protected:
    void _resize();
    void resizeEvent(QResizeEvent *);
public:
    explicit  EImage(const QString&url,QWidget *ptr=0);
    explicit  EImage(const QImage&im,QWidget *ptr=0);
    explicit  EImage(const QPixmap&im,QWidget *ptr=0);
    explicit  EImage(QPixmap*im,QWidget *ptr=0); //warning this class automaticly deleted images, if you use a QPixmap pointer.
    void change(const QString&url);
    void change(const QImage&im);
    void change(const QPixmap&im);
    void change(QPixmap*im);
    ~EImage();
};

#endif // EIMAGE_H
