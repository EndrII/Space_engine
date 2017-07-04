#include "AddResurse.h"

AddResurse::AddResurse(QWidget *parent) : QDialog(parent)
{
    this->setModal(true);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setObjectName("Box");
    QVBoxLayout *box=new QVBoxLayout();
    QHBoxLayout *hbox=new QHBoxLayout();
    ok=new ButtonGreen("Add");
    item_id=-1;
    cancel=new ButtonRegulyar("Сancel");
    hbox->addWidget(cancel);
    hbox->addWidget(ok);
    obj=new ResObjectsView();
    box->addWidget(obj);
    box->addLayout(hbox);
    this->setLayout(box);
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(clos(bool)));
    connect(ok,SIGNAL(clicked(bool)),SLOT(complit(bool)));
    connect(obj,SIGNAL(itemChanged(int)),SLOT(itemChanged(int)));
}
void AddResurse::complit(bool){
    if(obj->getSize()>0)
        item_id=0;
    this->close();
}
void AddResurse::clos(bool){
    item_id=-1;
    this->close();
}
void AddResurse::itemChanged(int id){
    item_id=id;
}
int AddResurse::staticShow(QWidget *ptr){
    AddResurse *temp=new AddResurse(ptr);
    temp->exec();
    return temp->item_id;
}
