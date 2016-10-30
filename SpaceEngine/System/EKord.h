#ifndef EKORD_H
#define EKORD_H
#include <QString>
#include <QPoint>
#include <QDataStream>
#include <QSize>
#include "EError.h"
enum Operation{plus_,minus_,mul_,div_};
class EKord //soderget 2 znacheniya x i y
{
public:
    EKord(const float &x, const float &y); //konstruktor
    EKord(const QPoint &);
    EKord(const QSize &);
    EKord(const float& val);
    EKord(); //konstruktor
    QPoint TO_QPoint();//transliruet v QPoint
    QPointF TO_QPointF();//
    QSize TO_QSize();//transliruet v QSize
    static EKord sintez(const EKord&,const float&,const Operation&);//vipolnet orefmeticheskuyu operaziyu s chislom po max
    static EKord Random(const unsigned int &min, const unsigned int &max);//vernyot sluchainie koordinati v diapozone
    static EKord Random(const unsigned int &min, const unsigned int &max, const float &skale);//vernyot dvva chisla raznizai v skale
    float Distace(const EKord&);//vernyot distanziyu ot this do ukazonnogo objecta
    static float length(const float& x1,const float& y1,const float& x2,const float& y2); //dlina megdu tickami
    float X,Y;//kordinati
    QString GetKord();//vozvroshaeet znachenie
    bool inQuan(const EKord& l,const EKord& r);//proveriyaet vhodit li dannie kordinati v kvadrat r-l
    static bool inQuan(const EKord& x_y,const EKord& l,const EKord& r);//proveriyaet vhodit li dannie kordinati v kvadrat r-l
    static bool inQuan(const float&x,const float&y,const float &lx,const float& ly,const float& rx,const float& ry);
    EKord& operator=(const EKord&);
    EKord operator +(const EKord&);
    EKord operator -(const EKord&);
    EKord operator *(const EKord&);
    EKord operator /(const EKord&);
    EKord operator +(const int&);
    EKord operator -(const int&);
    EKord operator *(const int&);
    EKord operator /(const int&);
    EKord operator +(const double&);
    EKord operator -(const double&);
    EKord operator *(const double&);
    EKord operator /(const double&);
    bool operator==(const EKord&);
    bool operator!=(const EKord&);
    friend QDataStream& operator <<(QDataStream&stream,const EKord& object);
    friend QDataStream& operator >>(QDataStream&stream,EKord& object);
    ~EKord();
};
#endif // EKORD_H
