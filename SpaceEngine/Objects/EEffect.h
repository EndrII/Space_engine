#ifndef EEFFECT
#define EEFFECT
#include "EObject.h"
#include "./SpaceEngine/System/EMaps.h"
/**
 * @brief The EEffect class
 * данный класс предстовляет собой оболочку для EObject содержит
 * спрайт всего из 1й анимации в которой 1й кадр полностью пустой
 */
class EEffect: public EObject{
Q_OBJECT
private:
    EObject *tar;
protected:
public:
    /**
     * @brief EEffect оболочка для обьекта.
     * @param str путь к объкту хронящий в себе спрайт эффекта
     */
    explicit EEffect(const QString& str);
    /**
     * @brief run запкстит данный эффект на выбронной карте
     * @param map карта запуска анимации
     * @param center место запуска
     * @param size размер по умолчанию равен 1
     */
    virtual void run(EMaps*map,const EKord& center,const EKord&size=EKord(1));
    void render();
    /**
     * @brief run запустит анимацию на обьекте
     * @param target цель
     * @param size размер по умолчанию 1
     */
    virtual void run(EObject* target,const EKord&size=EKord(1));
    ~EEffect();
};
#endif // EEFFECT
