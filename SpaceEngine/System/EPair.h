#ifndef EPAIR
#define EPAIR
class EPair //perenisti v dvigok
{
private:
  public:
    explicit EPair(const FIRST&,const SECOND&);
    explicit EPair();
    FIRST First;
    SECOND Second;
     EPair& operator=(const EPair&);
     bool  operator==(const EPair&);
    virtual ~EPair();
};
template <typename FIRST,typename SECOND>
EPair<FIRST,SECOND>::EPair(const FIRST& f,const SECOND&s)
{
    First=f;
    Second=s;
}
template <typename FIRST,typename SECOND>
EPair<FIRST,SECOND>::EPair()
{
}
template <typename FIRST,typename SECOND>
EPair<FIRST,SECOND>& EPair<FIRST,SECOND>::operator =(const EPair& right)
{
    if(&right==this) return *this;
    else
    {
        this->First=right.First;
        this->Second=right.Second;
       return *this;
    }
}
template <typename FIRST,typename SECOND>
bool EPair<FIRST,SECOND>::operator ==(const EPair&right)
{
    return (this->First==right.First&&this->Second==right.Second);
}
template <typename FIRST,typename SECOND>
EPair<FIRST,SECOND>::~EPair()
{

}
#endif // EPAIR

