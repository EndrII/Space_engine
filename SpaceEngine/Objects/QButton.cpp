#include "QButton.h"

QButton::QButton(const QString& url,const QString &text)
{
    setText(text);
    QPalette pal;
    pal.setBrush(this->backgroundRole(),QBrush(QPixmap(url)));
    this->setFlat(true);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
  //  setIcon(QIcon(url));
  //  setPalette();
  //  this->setIconSize(this->size());
    //setBackgroundRole(QPalette(QBrush(QPixmap(url))));
}
QButton::QButton(QPixmap *p,const QString &text)
{
    setText(text);
    setIcon(QIcon(*p));
    this->setIconSize(this->size());
}

