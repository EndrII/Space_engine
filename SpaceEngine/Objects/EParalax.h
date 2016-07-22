#ifndef EPARALAX_H
#define EPARALAX_H
#include "EModuleObject.h"
#include "EFon.h"
class  EParalax: public EModuleObject //effect paralaxaa
{
    Q_OBJECT
private:
    float Up,defUp;//prirost fonovih izobrogenii
    int Value;//kolichestvo fonov
protected:
public:
    explicit EParalax(QString patch, QObject *ptr);
    explicit EParalax(const float &up, const QStringList &UrlList, QObject* ptr=NULL);
    friend QDataStream& operator>>(QDataStream&stream,EParalax&);
    friend QDataStream& operator<<(QDataStream&stream,EParalax&);
    void saveObject(QString patch);
    void render();
    ~EParalax();
};

#endif // EPARALAX_H
