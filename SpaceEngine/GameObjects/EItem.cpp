#include "EItem.h"

EItem::EItem(EResurse *base){
    res=base;
    value=0;
}
void EItem::setValue(ui newValue){
    value=newValue;
}
ui EItem::getValue()const{
    return value;
}
EResurse* EItem::getSource()const{
    return res;
}
ui EItem::push(ui pushedValue){
    emit valueChanged(value+=pushedValue);
    return value;
}
ui EItem::pop(ui popedValue){
    if(value<popedValue){
       ui result=popedValue-value;
       value=0;
       emit valueChanged(result);
       return result;
    }
    value-=popedValue;
    emit valueChanged(popedValue);
    return popedValue;
}
EItem::~EItem(){
}
