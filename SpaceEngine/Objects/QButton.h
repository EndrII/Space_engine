#ifndef QBUTTON_H
#define QBUTTON_H
#include <QPushButton>
#include <QPixmap>
class QButton:public QPushButton
{
public:
   explicit QButton(const  QString&fon, const QString &text="");
   explicit QButton(QPixmap*,const QString &text="");
};

#endif // QBUTTON_H
