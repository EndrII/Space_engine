#ifndef EIMAGE_H
#define EIMAGE_H
#include <QLabel>
#include <QBitmap>
class EImage:public QLabel //izobragenie
{
    Q_OBJECT
    /**
     * @brief The resize_policy enum
     * fixed - no scale image
     * horizontal - resize by horizontal size with save proportion.
     * vertical - resize by vertical size with save proportion.
     * fill - resize image with filling free space.
     */
    enum resize_policy{fixed,horizontal,vertical,fill};
private:
    QPixmap *img;
    QSize fixedSize;
    resize_policy _policy;
protected:
    void _resize();
    void resizeEvent(QResizeEvent *);
public:
    explicit  EImage(const QString&url,QWidget *ptr=0);
    explicit  EImage(const QImage&im,QWidget *ptr=0);
    explicit  EImage(const QPixmap&im,QWidget *ptr=0);
    explicit  EImage(QWidget *ptr=0); //warning this class automaticly deleted images, if you use a QPixmap pointer.
    explicit  EImage(QPixmap*im,QWidget *ptr=0); //warning this class automaticly deleted images, if you use a QPixmap pointer.
    void change(const QString&url);
    void change(const QImage&im);
    void change(const QPixmap&im);
    void change(QPixmap*im);
    resize_policy resizepolicy()const;
    void setResizepolicy(resize_policy policy= EImage::fill);
    void setFixedSize(const QSize& size);
    QSize FixedSize()const;
    ~EImage();
};

#endif // EIMAGE_H
