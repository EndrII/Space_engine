#include "EAi.h"
EAi::EAi():
    EObject()
{

}
void EAi::startAI()
{

}
void EAi::render()
{

}
bool EAi::setObject(EObject*)
{
    return false;
}
void EAi::setAiType(const int &type)
{
    AiType=type;
}
int EAi::getAiType()
{
    return AiType;
}
EAi::~EAi()
{

}
