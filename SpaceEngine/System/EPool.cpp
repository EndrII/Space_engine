#include "EPool.h"

EPool::EPool(const unsigned int &sizePool){
    poolSize=sizePool/sizeFrame*3;
    poolLastIndex=poolFirstIndex=0;
    poolMemorySizeLemit=sizePool;
    poolMemorySize=0;
    pool=new poolElement[poolSize];
}
QOpenGLTexture* EPool::operator [](const unsigned int &i){
    return pool[i].textureID;
}
unsigned int EPool::getSize()const{
    return poolMemorySizeLemit;
}
unsigned int EPool::find(const unsigned int &idFrame){
    int i=poolLastIndex;
    while(i!=-1||pool[i].textureID!=NULL||pool[i].FrameID!=idFrame){
        i--;
    }
    if(pool[i].textureID==NULL)
        return -1;
    return i;
}
void EPool::malloc(ESprite *sprite){
    while(poolMemorySize>poolMemorySizeLemit)
    {
        poolMemorySize-=SIZE_FRAME(poolFirstIndex);
        delete pool[poolFirstIndex].textureID;
        pool[poolFirstIndex].textureID=NULL;
        if(poolFirstIndex<poolSize-1)
            poolFirstIndex++;
        else
            poolFirstIndex=0;
    }
    if(poolLastIndex<poolSize-1)
        poolLastIndex++;
    else
        poolLastIndex=0;
    pool[poolLastIndex].textureID=sprite->Bind(poolLastIndex);
    poolMemorySize+=SIZE_FRAME(poolLastIndex);
}
void EPool::poolRender(ESprite *sprite){
    sprite->stop(true);
    if(!sprite->newAdresFromFrame(find(sprite->getIdFrame()))){
        malloc(sprite);
    }
    sprite->stop(false);
}
void EPool::clear(){
    while(poolMemorySize>0)
    {
        poolMemorySize-=SIZE_FRAME(poolFirstIndex);
        delete pool[poolFirstIndex].textureID;
        pool[poolFirstIndex].textureID=NULL;
        if(poolFirstIndex<poolSize-1)
            poolFirstIndex++;
        else
            poolFirstIndex=0;
    }
}
EPool::~EPool(){
    clear();
    delete[] pool;
    pool=new poolElement[poolSize];
}
