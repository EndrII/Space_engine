#ifndef ELIST_H
#define ELIST_H
#include <QList>
#include <mutex>
using namespace std;
template <typename T>
class Elist:public QList<T> //dannii shablonnii klass yavlyaetisya klonnom list no so vshitim mutexom
{
private:
    mutex mutex_;// vshitii mutex
protected:
public:
    Elist();// konstriktor po umolxhaniyu
    Elist(const Elist<T>&);// konstruktor 2
   void Elock();//ruchnaya blokirovka
   void Eun_lock();// ruchnaya razblokirovka
   bool Etry_lock(); //ruchnaya proverka
   void Epop_back();//bezopasnoe udolenie iz koneza
   void Epop_front();//bezopasnoe udolenie iz nachalo
   Elist<T> operator=(Elist<T> &);// operator prisvaevoniya
   void Epush_back(const T&);//bezopasnoe dobolenie v konez
   void Epush_front(const T&);//bezopasnoe dobolenie v nachalo
   void Eclear();//bezopasnaya otchistka
   //void Eerase(iterator<T> position);// bezopasnoe udolenie
    ~Elist();
};
template <typename T>
Elist<T>::Elist():
    QList<T>()
{

}
template <typename T>
Elist<T>::Elist(const Elist<T> &obj):
    QList<T>()
{

    for(auto a:obj)
    {
        this->push_back(a);
    }
//    obj.Eunlock();
}
template <typename T>
void Elist<T>::Elock()
{
     mutex_.lock();
}
template <typename T>
void Elist<T>::Eun_lock()
{
    mutex_.unlock();
}
template <typename T>
bool Elist<T>::Etry_lock()
{
  return  mutex_.try_lock();
}
template <typename T>
void Elist<T>::Epop_back()
{
    mutex_.lock();
    this->pop_back();
    mutex_.unlock();
}
template <typename T>
void Elist<T>::Epop_front()
{
    mutex_.lock();
    this->pop_front();
    mutex_.unlock();
}
template <typename T>
void Elist<T>::Epush_back(const T & obj)
{
    mutex_.lock();
    this->push_back(obj);
    mutex_.unlock();
}
template <typename T>
void Elist<T>::Epush_front(const T & obj)
{
    mutex_.lock();
    this->push_front(obj);
    mutex_.unlock();
}
template <typename T>
void Elist<T>::Eclear()
{
    mutex_.lock();
    this->clear();
    mutex_.unlock();
}
template <typename T>
Elist<T> Elist<T>::operator =(Elist<T>& obj)
{
    mutex_.lock();
    this->clear();
    obj.Elock();
    for(auto a:obj)
    {
        this->push_back(a);
    }
    obj.Eun_lock();
    mutex_.unlock();
    return *this;
}
template <typename T>
Elist<T>::~Elist()
{

}
#endif // ELIST_H
