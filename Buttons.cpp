#include "Buttons.h"

ButtonPlay::ButtonPlay(const QString &text, QWidget *widget):
    QPushButton(text,widget)
{
    setStyleSheet("QPushButton {"
                  "font-size: 16px;"
                  "outline: none;"
                  "color: #fff;"
                  "background-color: #777777;"
                  "border: 1px solid #4CAF50;"
                  "border-radius: 5px;"
                "}"
                "QPushButton:hover {"
                  "background-color: #778A77}"
                "QPushButton:pressed {"
                  "background-color: #4CAF50}"
                "QPushButton:disabled {"
                  "background-color: #AAAAAA}"
                );
    connect(this,SIGNAL(clicked(bool)),this,SLOT( cli(bool)));
}
void ButtonPlay::cli(bool){
    emit clickButton(this);
}

ButtonGreen::ButtonGreen(const QString &text, QWidget *widget):
    QPushButton(text,widget)
{
    setStyleSheet("QPushButton {"
                  "font-size: 16px;"
                  "outline: none;"
                  "color: #fff;"
                  "background-color: #4CAF50;"
                  "border: none;"
                  "border-radius: 5px;"
                "}"
                "QPushButton:hover {"
                  "background-color: #4CBF50}"
                "QPushButton:pressed {"
                  "background-color: #4CBFA0}"
                "QPushButton:disabled {"
                  "background-color: #AAAAAA}"
                );
    connect(this,SIGNAL(clicked(bool)),this,SLOT( cli(bool)));
}
void ButtonGreen::cli(bool){
    emit clickButton(this);
}

ButtonRegulyar::ButtonRegulyar(const QString &text, QWidget *widget):
    QPushButton(text,widget)
{
    setStyleSheet("QPushButton {"
                  "font-size: 16px;"
                  "outline: none;"
                  "color: #fff;"
                  "background-color: #777777;"
                  "border: 1px solid #CCCCCC;"
                  "border-radius: 5px;"
                "}"
                "QPushButton:hover {"
                  "background-color: #888888}"
                "QPushButton:pressed {"
                  "background-color: #BBBBBB}"
                "QPushButton:disabled {"
                  "background-color: #AAAAAA}"
                );
    connect(this,SIGNAL(clicked(bool)),this,SLOT( cli(bool)));
}
void ButtonRegulyar::cli(bool){
    emit clickButton(this);
}

ButtonRemove::ButtonRemove(const QString &text, QWidget *widget):
    QPushButton(text,widget)
{
    setStyleSheet("QPushButton {"
                  "font-size: 16px;"
                  "outline: none;"
                  "color: #fff;"
                  "background-color: #777777;"
                  "border: 1px solid #FF6F41;"
                  "border-radius: 5px;"
                "}"
                "QPushButton:hover {"
                  "background-color: #8A7777}"
                "QPushButton:pressed {"
                  "background-color: #EB9F71}"
                "QPushButton:disabled {"
                  "background-color: #BBAAAA}"
                );
    connect(this,SIGNAL(clicked(bool)),this,SLOT( cli(bool)));
}
void ButtonRemove::cli(bool){
    emit clickButton(this);
}
