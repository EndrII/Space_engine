#ifndef ESOUNDSCENTER_H
#define ESOUNDSCENTER_H
#include <QSoundEffect>
#include <QVector>
class ESoundsCenter:public QObject
{
    Q_OBJECT
private:
    QVector<QSoundEffect*> sound_base;
public:
    explicit ESoundsCenter();
    virtual void setValue(const float& );// ot 0 - 1
    virtual int addSound(const QString&Url);
    virtual void LoopPlay(const int &index,const bool&);//nastroika vosproizvedeniya po krugu
    virtual bool getLoop(const int &index);//proverka na povtor
    virtual QVector<QSoundEffect*>* getSoundList();
    virtual void clear();
    ~ESoundsCenter();
public slots:
    void Play(int);
    void Stop(int);
};

#endif // ESOUNDSCENTER_H
