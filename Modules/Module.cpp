#include "Module.h"
Module::Module(SpaceEngine* parent,QString *patchProject, QWidget *ptr):
    QWidget(ptr){
    patch=patchProject;
    this->parent=parent;
   // this->setObjectName("Box");
    box=new QHBoxLayout;
    vbox=new QVBoxLayout;
    title =new QLabel("Type");
    title->setAlignment(Qt::AlignCenter);
    box->addWidget(title);
    vbox->addLayout(box);
    box=new QHBoxLayout;
    this->setLayout(vbox);
}
void Module::setTitle(const QString &titl){
    title->setText(titl+" Settings\n");
}
void Module::addWidget(QWidget *w){
    box->addWidget(w);
}
void Module::newHorizont(){
    vbox->addLayout(box);
    box=new QHBoxLayout;
}
void Module::end(){
    vbox->addLayout(box);
}
bool Module::setNewObject(EObject *){
    return false;
}
bool Module::saveObject(const QString &){
    return false;
}
Module::~Module(){

}


