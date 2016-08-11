#include "EKord.h"
EKord::EKord(const float &x,const float &y)
{
    X=x;
    Y=y;
}
EKord::EKord()
{
    X=0;
    Y=0;
}
EKord::EKord(const QSize &s)
{
    X=s.width();
    Y=s.height();
}
EKord::EKord(const QPoint &k)
{
    X=k.x();
    Y=k.y();
}
EKord::EKord(const float &val){
    X=Y=val;
}
QString EKord::GetKord()
{
    return "{X="+QString::number(X)+"}"+"{Y="+QString::number(Y)+"}";
}
 bool EKord::operator!=(const EKord& test)
{
     return (X!=test.X&&Y!=test.Y);
}
 bool EKord::operator==(const EKord& test)
{
     return (X==test.X&&Y==test.Y);
}
 bool EKord::inQuan(const EKord &l, const EKord &r)
 {
     return ((r.X>this->X)&&(r.Y>this->Y)&&(l.X<this->X)&&(l.Y<this->Y));
 }
 bool EKord::inQuan(const EKord &x_y, const EKord &l, const EKord &r)
 {
     return ((r.X>x_y.X)&&(r.Y>x_y.Y)&&(l.X<x_y.X)&&(l.Y<x_y.Y));
 }
 bool EKord::inQuan(const float&x,const float&y,const float &lx,const float& ly,const float& rx,const float& ry)
 {
     return ((rx>x)&&(ry>y)&&(lx<x)&&(ly<y));
 }
 EKord EKord::Random(const int &min, const int &max)
 {
#ifdef QT_DEBUG
     if(min>max) throw EError(35," EKord EKord::Random(const int &min, const int &max)");
#endif
     int temp=max-min;
     return EKord(rand()%temp+min,rand()%temp+min);
 }
 EKord EKord::Random(const int &min, const int &max,const int &scaled)
 {
#ifdef QT_DEBUG
     if(min>max) throw EError(35," EKord EKord::Random(const int &min, const int &max)");
#endif
     int temp=max-min,temp2 =rand()%temp+min;
     return EKord(temp2,temp2*scaled);
 }
 EKord EKord::sintez(const EKord &pr,const float & ch, const Operation &op)
 {
     float temp; EKord result;
     if(pr.X>pr.Y) temp=pr.X; else  temp=pr.Y;
     switch (op) {
     case minus_:
     {
         result=EKord(temp-ch,temp-ch);
         break;
     }
     case plus_:
     {
         result=EKord(temp+ch,temp+ch);
         break;
     }
     case div_:
     {
         if(ch==0)return EKord(0,0);
         result=EKord(temp+ch,temp+ch);
         break;
     }
     case mul_:
     {
         result=EKord(temp+ch,temp+ch);
         break;
     }
     default:
         break;
     }
     return result;
 }
 EKord& EKord::operator=(const EKord &test)
{
    if(this==&test)
        return *this;
    this->X=test.X;
    this->Y=test.Y;
    return *this;
}
EKord EKord::operator+(const EKord &p)
{
    return  EKord (X+p.X,Y+p.Y);;
}
EKord EKord::operator-(const EKord &p)
{
    return EKord (X-p.X,Y-p.Y);
}
EKord EKord::operator*(const EKord &p)
{
    return  EKord (X*p.X,Y*p.Y);
}
EKord EKord::operator/(const EKord &p)
{
    if(p.X!=0&&p.Y!=0)
    return EKord (X/p.X,Y/p.Y) ;
    else
       throw EError(12,"EKord EKord::operator/(const EKord &p)");
}
EKord EKord::operator+(const int &p)
{
    return EKord (X+p,Y+p);
}
EKord EKord::operator-(const int &p)
{
    return EKord (X-p,Y-p);
}
EKord EKord::operator*(const int &p)
{
    return EKord (X*p,Y*p);
}
EKord EKord::operator/(const int &p)
{
    if(p!=0)
    return EKord (X/p,Y/p);
    else
       throw EError(12,"EKord EKord::operator/(const int &p)");
}
EKord EKord::operator+(const double &p)
{
    return EKord (X+p,Y+p);
}
EKord EKord::operator-(const double &p)
{
    return EKord (X-p,Y-p);
}
EKord EKord::operator*(const double &p)
{
    return EKord (X*p,Y*p);
}
EKord EKord::operator/(const double &p)
{
    if(p!=0)
    return EKord (X/p,Y/p);
    else
       throw EError(12,"EKord EKord::operator/(const double &p)");
}
QPoint EKord::TO_QPoint()
{
    return QPoint(X,Y);
}
QPointF EKord::TO_QPointF()
{
    return QPointF(X,Y);
}
float EKord::Distace(const EKord &d)
{
    return sqrt((X-d.X)*(X-d.X)+(Y-d.Y)*(Y-d.Y));
}
float EKord::length(const float &x1, const float &y1, const float &x2, const float &y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
QSize EKord::TO_QSize()
{
    return QSize(X,Y);
}
EKord::~EKord()
{

}
