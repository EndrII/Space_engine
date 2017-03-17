#ifndef EITEM_H
#define EITEM_H
#include "SpaceEngine/GameObjects/EResurse.h"
class EItem :protected QObject
{
    Q_OBJECT
private:
    ui value;
    EResurse *res;
public:
    EItem(EResurse*base);
    void setValue(ui newValue);
    ui getValue()const;
    /**
     * @brief push
     * @param pushedValue
     * @return new value the item.
     */
    ui push(ui pushedValue);
    /**
     * @brief pop
     * @param popedValue
     * @return poped value of the item
     */
    ui pop(ui popedValue);
    /**
     * @brief getSource
     * @return sourse
     */
    EResurse* getSource()const;
    ~EItem();
signals:
    void valueChanged(int);
};

#endif // EITEM_H
