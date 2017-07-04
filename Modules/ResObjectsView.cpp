#include "ResObjectsView.h"

ResObjectsView::ResObjectsView(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *hbox=new QHBoxLayout();
    resPack=new EResursePack();
    combo=new QComboBox();
    for(EResurse *res:*resPack->getList()){
        combo->addItem(QIcon(QPixmap::fromImage(*res->picture())),res->name());
    }
    view=new EResObjectView(new EItem((*resPack->getList())[combo->currentIndex()]));
    desc=new QLabel("None");
    desc->setMinimumSize(300,75);
    hbox->addWidget(combo);
    hbox->addWidget(desc);
    this->setObjectName("Box");
    connect(combo,SIGNAL(currentIndexChanged(int)),SLOT(comboChanged(int)));
    this->setLayout(hbox);
}
int ResObjectsView::getSize(){
    return combo->count();
}
void ResObjectsView::comboChanged(int i){
    if(i>0){
        desc->setText((*resPack->getList())[i]->desc());
        delete view->getItem();
        view->changeResurs(new EItem((*resPack->getList())[i]));
        emit itemChanged((*resPack->getList())[i]->id());
    }
}
ResObjectsView::~ResObjectsView(){
    delete resPack;
}
