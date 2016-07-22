#include "EContur.h"
EContur::EContur(){
}
EContur::EContur(float*x,float*y,std::list<float> *p){
    mode=elipse;
	points=p;
    points->sort();
	_x=x;
	_y=y;
}
EContur::EContur(float*x,float*y,float *h,float *w){
    mode=rectangle;
	_h=h;
	_w=w;
	_x=x;
	_y=y;
}
void EContur::setPoints(std::list<float> *p){
    if(points!=NULL)
       delete points;
    points=p;
}
QDataStream& operator>>(QDataStream& stream, EContur& cont){
    contur_mode temp;
    short tempEnum;
    stream>>tempEnum;temp=(contur_mode)tempEnum;
    if(cont.mode==temp&&temp==elipse){
        int temp;
        float value;
        stream>>temp;
        for(int i=0;i<temp;i++){
            stream>>value;
            cont.points->push_back(value);
        }
    }
    return stream;
}
QDataStream& operator<<(QDataStream& stream, const EContur& cont){
    stream<<cont.mode;
    if(cont.mode==elipse){
        stream<<(int)cont.points->size();
        for(float i:*cont.points)
            stream<<i;
    }
    return stream;
}
bool EContur::touching(const int&x_,const int &y_){
    if(mode==elipse){
        int index=1;
        std::list<float>::iterator i=points->begin();
        while((EKord::length(*_x,*_y,x_,y_)>*i&&std::rand()%index==0)&&i!=points->end()){
            i++; index+=100/points->size();
        }
        return i!=points->end();
    }else{
        int thistempw=*_w/2,thistemph=*_h/2,
                thistempx=*_x,thistempy=*_y;
        return EKord::inQuan(x_,y_,thistempx-thistempw,thistempy-thistemph,thistempx+thistempw,thistempy+thistemph);
	}
}
bool EContur::touching(const EContur& conturA,const float&x_,const float &y_){
    if(conturA.mode==elipse){
        int index=1;
        std::list<float>::iterator i=conturA.points->begin();
        while((EKord::length(*conturA._x,*conturA._y,x_,y_)>*i&&std::rand()%index==0)&&i!=conturA.points->end()){
            i++; index+=100/conturA.points->size();
        }
        return i!=conturA.points->end();
    }else{
        int thistempw=*conturA._w/2,thistemph=*conturA._h/2,
                thistempx=*conturA._x,thistempy=*conturA._y;
        return EKord::inQuan(x_,y_,thistempx-thistempw,thistempy-thistemph,thistempx+thistempw,thistempy+thistemph);                ;
    }
}
EContur::~EContur(){
    if(mode==elipse&&points!=NULL)
        delete points;
}
