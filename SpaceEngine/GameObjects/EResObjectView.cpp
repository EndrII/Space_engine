#include "EResObjectView.h"

EResObjectView::EResObjectView(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *hbox=new QHBoxLayout();
    resPack=new EResursePack();
    combo=new QComboBox();
    for(EResurse *res:*resPack->getList()){
        combo->addItem(QIcon(QPixmap::fromImage(*res->picture())),res->name());
    }
    desc=new QLabel("None");
    desc->setMinimumSize(300,75);
    hbox->addWidget(combo);
    hbox->addWidget(desc);
    this->setObjectName("Box");
    connect(combo,SIGNAL(currentIndexChanged(int)),SLOT(comboChanged(int)));
    this->setLayout(hbox);
}
void EResObjectView::comboChanged(int i){
    if(i>0){
        desc->setText((*resPack->getList())[i]->desc());
        emit itemChanged((*resPack->getList())[i]->id());
    }
}
EResObjectView::~EResObjectView(){
    delete resPack;
}
