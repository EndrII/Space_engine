#ifndef EMOUSEEVENT_H
#define EMOUSEEVENT_H
#include <QMouseEvent>
class EMouseEvent
{
public:
    EMouseEvent();
    float x,y;
    Qt::MouseButton button;
};

#endif // EMOUSEEVENT_H
