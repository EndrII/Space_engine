#ifndef CONTUR_H
#define CONTUR_H
#include "EKord.h"
#include <QDataStream>
#include <list>/**
    * @brief The contur_mode enum
    * режим котура (элиптический и прямоугольный )
    * rectangle - проверяет или входит точка в прямоугольник
    * elipse - проверяет на столкновение поля
    */
enum contur_mode{elipse,rectangle};
/**
 * @brief The EContur class
 * предстоаляет собой контур выбронного обьекта по которому определяються столкновения
*/
class EContur{
private:

    contur_mode mode;
    float *_x,*_y,*_h,*_w;
    std::list<float>* points;

public:
    void setPoints(std::list<float> *p);
    friend QDataStream& operator>>(QDataStream& stream,EContur& cont);
    friend QDataStream& operator<<(QDataStream& stream,const EContur& cont);
    /**
     * @brief touching данный метод проверит входит ли точка в данный контур
     * @param x_ х точки
     * @param y_ у точки
     * @return
     */
    bool touching(const int &x_, const int &y_);
    /**
     * @brief touching анологично пред идущему методу но этот метод статичен
     * @param conturA
     * @param x_
     * @param y_
     * @return
     */
    static bool touching(const EContur& conturA, const float &x_, const float &y_);
    /**
     * @brief EContur конструктор для режима окружностей
     * @param x указатель на центр обьекта
     * @param y указатель на центр обьекта
     * @param point список точек окружностей (радиусы окружностей)
     */
    explicit EContur(float*x,float*y,std::list<float> *point=NULL);
    /**
     * @brief EContur конструктор для режима прямоугольников
     * @param x центер обьекта
     * @param y центер обьекта
     * @param h высота
     * @param w ширина
     */
    explicit EContur(float*x,float*y,float *h,float *w);
    /**
     * @brief EContur конструктор для чтения.
     */
    explicit EContur();

    ~EContur();
};
#endif // CONTUR_H
