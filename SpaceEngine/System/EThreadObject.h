#ifndef ETHREADOBJECT_H
#define ETHREADOBJECT_H
#include <SpaceEngine/Objects/EObject.h>
#include <thread>
#define ULTRA_HIGH 0
#define HIGH 1
#define MEDIUM 16
#define LOW 160
#define LOW_PLUS 350
#define LOWER 1600
#define ULTRA_LOW 10000
#define _1_ON_MINUTE 60000
#define _1_ON_5MINUTS 300000
#define STOP 10000000
typedef int priority;
class EThreadObject
{
private:
    QTime timeUpdates;
protected:
    EObject_List** obj_list;//ssilka na vse ibekti karti
    bool *status;//ukazatel na status kameri
    int timeSync;
    priority priority_;//zadergka
    bool puls;//viluchatel dannogo potoka
public:
    explicit EThreadObject(const priority&p=LOW);
    int* gettimesync();//vernyot ukazatel na vremya sinhronizazii
    void setTimeSync(int);
    void setPriority(const priority&); //ustonovit zadergku vipolneniya
    priority getPriority();//poluchit prioritet
    bool* getpuls();//vernyot vikluchatel
    virtual void render();
    void Exit();
    void update(EObject_List **objectlist,bool*);//poluchenie kluchevih ukozatelei
    ~EThreadObject();
};

#endif // ETHREADOBJECT_H
