#include "ECore.h"

ECore::ECore()
{
    IDCORE=RES=0;
}
void * ECore::getIdCore()const{
    return IDCORE;
}
void * ECore::getRes()const{
    return RES;
}
void ECore::setIdCore(void *ptr){
    if(IDCORE) throw RepeatedVariableDeclaration;
    IDCORE=ptr;
}
void ECore::setRes(void *ptr){
    if(RES) throw RepeatedVariableDeclaration;
    RES=ptr;
}
