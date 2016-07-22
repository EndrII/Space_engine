#ifndef EPOOL_H
#define EPOOL_H
#include <QOpenGLTexture>
#include "ESprite.h"
#define sizeFrame 100000
#define _4GB 4294967296
#define _2GB 2147483648
#define _1GB 1073741824
#define _512MB 536870912
#define _256MB 268435456
#define _128MB 134217728
#define _64MB 67108864
#define _32MB 33554432
#define _16MB 16777216
#define SIZE_FRAME(INDEX) pool[INDEX].textureID->width()*pool[INDEX].textureID->height()*4
/**
 * @brief The poolElement struct
 * данная структура содержит в себе указатель на текстуру (её адресс)
 * и уникальный адресс кадра
 */
struct poolElement{
    QOpenGLTexture * textureID=NULL;
    unsigned int FrameID;
};
/**
 * @brief The EPool class графический пуул в котором хроняться все изображения всех спрайтов
 */
class EPool
{
private:
    poolElement * pool;// графический пуул камеры
    //void poolRender(EObject* sprite);// podkachka izobragenie
    unsigned int poolMemorySize,
    poolMemorySizeLemit,
    poolSize,
    poolLastIndex,
    poolFirstIndex;//razmer i index poslednego elementa v poole
public:
    QOpenGLTexture* operator[](const unsigned int&i);
    EPool(const unsigned int& sizePool=_512MB);
    /**
     * @brief getSize
     * @return вернёт размер пулла в байтах
     */
    unsigned int getSize()const;
    /**
     * @brief find
     * @return вернет адресс текстуры в пулле, или вернет -1 если её не найдет.
     */
    inline unsigned int find(const unsigned int &idFrame);
    /**
     * @brief malloc выделит память под новый кадр
     */
    inline void malloc(ESprite*);
    /**
     * @brief poolRender
     * обработает кадр если ему требуеться выделение памяти
     */
     void poolRender(ESprite*);
     void clear();
    ~EPool();
};

#endif // EPOOL_H
