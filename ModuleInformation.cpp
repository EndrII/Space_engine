#include "ModuleInformation.h"

ModuleInformation::ModuleInformation(QString* name,QString*desc,QWidget *ptr):
    QDialog(ptr)
{
    name_=name;
    desc_=desc;
    this->setModal(true);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setObjectName("Box");
    QVBoxLayout *box=new QVBoxLayout;
    header=new QLabel("Project Information\n\n");
    header->setAlignment(Qt::AlignCenter);
    box->addWidget(header);
    box->addWidget(new QLabel("Project name:"));
    name_E=new QLineEdit(*name_);
    box->addWidget(name_E);

    box->addWidget(new QLabel("Description Project"));
    DescEdit=new QTextEdit(*desc_);
    box->addWidget(DescEdit);


    QHBoxLayout* boxH=new QHBoxLayout;
    __ok=new ButtonGreen("Ok");
    cancle=new ButtonRegulyar("cancle");
    boxH->addWidget(cancle);
    boxH->addWidget(__ok);
    connect(cancle,SIGNAL(clicked(bool)),SLOT(close()));
    connect(__ok,SIGNAL(clicked(bool)),SLOT(_ok(bool)));
    box->addLayout(boxH);
    this->setLayout(box);
}
void ModuleInformation::_ok(bool){
    *name_=name_E->text();
    *desc_=DescEdit->toPlainText();
    close();
}
