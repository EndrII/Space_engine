#include "CompressMenu.h"

CompressMenu::CompressMenu(QWidget *ptr):
    QDialog(ptr)
{
    this->setModal(true);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setObjectName("Box");
    QVBoxLayout *box=new QVBoxLayout;
    header=new QLabel("Веедите длину анимвации в милисекундах и количество кадровв.\n"
                      "Данная опция сожмет анимацию выбрасив не нужные кадры\n"
                      "и раставив подходящее время всем кадрам анимации");
    box->addWidget(header);
    QHBoxLayout *boxH=new QHBoxLayout;
    boxH->addWidget(new QLabel("количество кадр/сек"));
    frame=new QSpinBox();
    frame->setMaximum(60);
    frame->setMinimum(1);
    frame->setValue(24);
    boxH->addWidget(frame);
    box->addLayout(boxH);

    boxH=new QHBoxLayout;
    boxH->addWidget(new QLabel("Длина анимации мс"));
    time=new QSpinBox();
    time->setMaximum(3600000);
    time->setMinimum(100);
    time->setValue(1000);
    boxH->addWidget(time);
    box->addLayout(boxH);


    boxH=new QHBoxLayout;
    __ok=new ButtonGreen("Ok");
    cancle=new ButtonRegulyar("cancle");
    boxH->addWidget(cancle);
    boxH->addWidget(__ok);
    connect(cancle,SIGNAL(clicked(bool)),SLOT(close()));
    connect(__ok,SIGNAL(clicked(bool)),SLOT(_ok(bool)));
    box->addLayout(boxH);
    this->setLayout(box);
}
void CompressMenu::_ok(bool){
    emit ok(time->value(),frame->value());
    close();
}
