#ifndef EPARALAX_H
#define EPARALAX_H
#include "EModuleObject.h"
#include "EFon.h"
class  EParalax: public EModuleObject //effect paralaxaa
{
    Q_OBJECT
private:
    float Up,defUp;//prirost fonovih izobrogenii
protected:
public:
    explicit EParalax(QString patch, QObject *ptr=0);
    explicit EParalax(const float &up, const QStringList &UrlList, QObject* ptr=NULL);
    friend QDataStream& operator>>(QDataStream&stream,EParalax&);
    friend QDataStream& operator<<(QDataStream&stream,EParalax&);
    void restore(const QStringList &UrlList, const float &up);
    void removeLast();
    void addBack(const QString& url, const float &up);
    void saveObject(QString patch);
    void changeUp(const float& up);// ustanovit novii kooficent mastaba
    void render();
    ~EParalax();
};

#endif // EPARALAX_H
