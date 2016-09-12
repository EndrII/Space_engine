#include "EPool.h"

EPool::EPool(const unsigned int &sizePool){
    poolSize=sizePool/sizeFrame*3;
    poolLastIndex=-1;
    poolFirstIndex=0;
    poolMemorySizeLemit=sizePool;
    poolMemorySize=0;
    pool=new poolElement[poolSize];
}
QOpenGLTexture* EPool::operator [](const int &i){
    return pool[i].textureID;
}
QOpenGLTexture* EPool::call(ESprite *object){
    int temp =object->getFrame();
#ifdef QT_DEBUG
    poolElement &PoolTemp=pool[temp];
#endif
    if(temp>=0){
        if((ui)temp>=poolSize||!pool[temp].textureID){
            poolRender(object);
            return pool[object->getFrame()].textureID;
        }else
            return pool[temp].textureID;
    }else{
        return NULL;
    }
}
unsigned int EPool::getSize()const{
    return poolMemorySizeLemit;
}
int EPool::find(const unsigned int &idFrame){
    int i=poolLastIndex;
    while(!(i<0||pool[i].textureID==NULL)&&pool[i].FrameID!=idFrame){
#ifdef QT_DEBUG
        ui this_pool=pool[i].FrameID;
#endif
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
#ifdef QT_DEBUG
    poolElement &poolLastIndexIndex=pool[poolLastIndex];
#endif
    pool[poolLastIndex].textureID=sprite->Bind(poolLastIndex);
    pool[poolLastIndex].FrameID=sprite->getIdFrame();
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
