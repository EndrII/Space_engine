#ifndef ETHREAD
#define ETHREAD
#include <QThread>
#include <list>
#include "./SpaceEngine/Objects/EObject.h"
#include "EError.h"
enum thread_stats{_void,_object,_func};
class EThread:public QThread //obolochka dlya potokov qt
{
   Q_OBJECT
private:
    EObject *thread_object; //object potoka
    thread_stats object; //status objecta
    void (*Thread_func)();
    bool *puls;//viclushatel potoka
protected:
    void run();//zapusk potoka (funkzii render(vibronogo objecta))
public:
    thread_stats getStats();//poluchit status ob obiekte
    bool setObject(EObject*,bool*);//ustonavlivoet novii obekt
    bool setFunc(void (*Thread_Func)(),bool*);//ustonovit funkziu dlya potoka
    bool clear(); //otkluchaet ot potoka object ili funkziy
    void _start(); //start potoka
    EThread(EObject *Obj,bool*, QObject *ptr=0);//peredovaemii ukazatel dolgen bit pust(=NUUL)
    EThread(void(*Thread_Func)(),bool*, QObject *ptr=0);
    EThread(QObject *ptr=0);
    ~EThread();
public slots:
    void stop();//ostonovka potoka
signals:
    void finished();//glasit ozavershenie potoka
    void start_();//glasit o nachale vipolneniya
    void fail();//esli potok zaveshilsya ne udachno
};
#endif // ETHREAD

