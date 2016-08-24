#include "EContur.h"
EContur::EContur(float *x,float*y,QVector<EKord> *p){
    points=p;
    edge=points->data()[FindEdge()];
	_x=x;
	_y=y;
}
unsigned short EContur::FindEdge(){
    unsigned short result=0;
    for(int i=0;i<points->size();i++){
        if(points->data()[i].X>points->data()[result].X)
            result=i;
    }
    return result;
}
void EContur::setPoints(QVector<EKord> *p){
    if(points!=NULL)
       delete points;
    points=p;
}
unsigned int EContur::size()const{
    return points->size();
}
QDataStream& operator>>(QDataStream& stream, EContur& cont){
    int tempEnum;
    stream>>tempEnum;
    for(int i=0;i<tempEnum;i++){
        EKord kord;
        stream>>kord;
        cont.points->push_back(kord);
    }
    stream>>cont.depth;
    stream>>cont.edge;
    if(cont.depth)
        stream>>cont.depchLong;
    return stream;
}
QDataStream& operator<<(QDataStream& stream, const EContur& cont){
    stream<<(int)cont.points->size();
    for(EKord i:*cont.points)
        stream<<i;
    stream<<cont.depth;
    stream<<cont.edge;
    if(cont.depth)
        stream<<cont.depchLong;
    return stream;
}
float EContur::generateX(const int &index)const{
    return (*_x)+points->data()[index].X*cos(points->data()[index].Y);
}
float EContur::generateY(const int &index)const{
    return (*_y)+points->data()[index].X*sin(points->data()[index].Y);
}
bool EContur::touching(const float &x, const float &y)const{
    if(EKord::length(x,y,*_x,*_y)>edge.X)return false;
    unsigned short size=points->size();
    bool result=false;
    int oldX=generateX(size-1),oldY=generateY(size-1),X,Y;
    for(int i=0;i<size;i++){
        X=generateX(i);
        Y=generateY(i);
        if((Y>y)!=(oldY>y)&&(x<(oldX-X)*(y-Y)/(oldY-Y)+X))
            result=!result;
        oldY=Y;
        oldX=X;
    }
    return result;
}
bool EContur::touching(const EContur &contur)const{
    unsigned short size=contur.points->size();
    while(!touching(contur.generateX(size-1),contur.generateY(size-1))&&size--);
    return size;
}
bool EContur::touching(const EContur &conturA, EContur &conturB){
    unsigned short size=conturB.points->size();
    while(!conturA.touching(conturB.generateX(size-1),conturB.generateY(size-1))&&size--);
    return size;
}
bool EContur::touching(const EContur& conturA,const float&x,const float &y){
    if(EKord::length(x,y,*conturA._x,*conturA._y)>conturA.edge.X)return false;
    unsigned short size=conturA.points->size();
    bool result=false;
    int oldX=conturA.generateX(size-1),oldY=conturA.generateY(size-1),X,Y;
    for(int i=0;i<size;i++){
        X=conturA.generateX(i);
        Y=conturA.generateY(i);
        if((Y>y)!=(oldY>y)&&(x<(oldX-X)*(y-Y)/(oldY-Y)+X))
            result=!result;
        oldY=Y;
        oldX=X;
    }
    return result;
}
void EContur::setKord(float *x, float *y){
    _x=x;
    _y=y;
}
EContur::~EContur(){
    if(points!=NULL)
        delete points;
}
