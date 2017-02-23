#include "ECore.h"

ECore::ECore()
{
    IDCORE=0;
}
void * ECore::getIdCore()const{
    return IDCORE;
}
void ECore::setIdCore(void *ptr){
    if(IDCORE) throw RepeatedVariableDeclaration;
    IDCORE=ptr;
}
