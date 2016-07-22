#ifndef EIMAGE_H
#define EIMAGE_H
#include <QLabel>
#include <QBitmap>
class EImage:public QLabel //izobragenie
{
private:
    QString Url;
    QPixmap *img;
protected:
    void _resize();
public:
    //void resizeGL(int w,int h);
    explicit  EImage(const QString&url);
    virtual void change(const QString&url);
    virtual void resize();//obnovleni
    ~EImage();
};

#endif // EIMAGE_H
