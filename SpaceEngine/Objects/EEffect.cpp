#include "EEffect.h"
EEffect::EEffect(const QString &str): EObject(str){
    delete_flag=true;
    tar=NULL;
    setMovMode(Standart);
}
void EEffect::run(EMaps *map, const EKord &center,const EKord& size){
    delete_flag=false;
    map->add_Object(this);
    mx=_x=center.X;
    my=_y=center.Y;
    setW(size.X);
    setH(size.Y);
}
void EEffect::run(EObject *target, const EKord &size){
    tar=target;
    setW(size.X);
    setH(size.Y);
}
void EEffect::render(){
    _timeRender();
    _render();
    render_sprite();
    if(tar!=NULL){
        mov_to(EKord(tar->x(),tar->y()),tar->getSpeed());
    }
    if(!getAnimationStackValue()){
        delete_flag=true;
        tar=NULL;
    }
}
EEffect::~EEffect(){

}
