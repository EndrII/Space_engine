#ifndef BUTTONS_H
#define BUTTONS_H
#include <QPushButton>
class ButtonPlay:public QPushButton
{
    Q_OBJECT
public:
    ButtonPlay(const QString &text,QWidget* widget=NULL);
private slots:
    void cli(bool);
signals:
    void clickButton(QPushButton*);
};
class ButtonGreen:public QPushButton
{
    Q_OBJECT
public:
    ButtonGreen(const QString &text,QWidget* widget=NULL);
private slots:
    void cli(bool);
signals:
    void clickButton(QPushButton*);
};
class ButtonRegulyar:public QPushButton
{
    Q_OBJECT
public:
    ButtonRegulyar(const QString &text,QWidget* widget=NULL);
private slots:
    void cli(bool);
signals:
    void clickButton(QPushButton*);
};

class ButtonRemove:public QPushButton
{
    Q_OBJECT
public:
    ButtonRemove(const QString &text,QWidget* widget=NULL);
private slots:
    void cli(bool);
signals:
    void clickButton(QPushButton*);
};

#endif // BUTTONS_H
