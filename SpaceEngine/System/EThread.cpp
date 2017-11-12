#include "EThread.h"
EThread::EThread(QObject *ptr):
    QThread(ptr)
{
    object=_void;
}
EThread::EThread(EThreadObject *Obj, bool *p, QObject *ptr):
    QThread(ptr)
{
    if(Obj!=NULL)
    {
        object=_object;
        thread_object=Obj;
        puls=p;
    }else
        throw EError(9,"EThread::EThread(EObject *Obj, QObject *ptr):");
}
EThread::EThread(void (*Thread_Func)(), bool *p, QObject *ptr):
    QThread(ptr)
{
    Thread_func=Thread_Func;
    object=_func;
    puls=p;
}
thread_stats EThread::getStats()
{
    return object;
}
bool EThread::setObject(EThreadObject *Obj, bool *p)
{
    if(object==_void){
      thread_object=Obj;
      object=_object;
      puls=p;
      return true;
      }else
      {
        return false;
      }
}
bool EThread::setFunc(void (*Thread_Func)(), bool *p)
{
    if(object==_void)
    {
        Thread_func=Thread_Func;
        object=_func;
        puls=p;
        return true;
    }
    return false;
}
void EThread::run()
{
    switch (object) {
    case 1:
    {
        emit _start();
        thread_object->render();
        emit finished();
        break;
    }
    case 2:
    {
        emit _start();
        (*Thread_func)();
        emit finished();
        break;
    }
    default:{
        emit fail();
        throw EError(8,"void EThread::run()");
        break;
    }
}
}
void EThread::_start()
{
    *puls=true;
    this->start();
}
void EThread::stop()
{
    *puls=false;
    //this->exit();
    emit fail();
}
bool EThread::clear()
{
    if(isFinished())
    {
        thread_object=NULL;
        Thread_func=NULL;
        object=_void;
        return true;
    } return false;
}
EThread::~EThread()
{
     puls=NULL;
     thread_object=NULL;
     Thread_func=NULL;
     emit fail();
}
