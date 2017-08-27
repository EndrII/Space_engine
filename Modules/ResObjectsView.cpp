#include "ResObjectsView.h"

ResObjectsView::ResObjectsView(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *hbox=new QHBoxLayout();
    resPack=new EResursePack();
    combo=new QComboBox();
    for(EResurse *res:*resPack->getList()){
        if(res->isValid())
            combo->addItem(QIcon(QPixmap::fromImage(*res->picture())),res->name());
    }
    view=new EResObjectView(nullptr);
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
    resursMap::iterator iter=resPack->getList()->begin()+i;
    if(iter!=resPack->getList()->end()){
        desc->setText(iter.value()->desc());
        delete view->getItem();
        view->changeResurs(new EItem(iter.value()));
        emit itemChanged(iter.key());
    }
}
ResObjectsView::~ResObjectsView(){
    delete resPack;
}
