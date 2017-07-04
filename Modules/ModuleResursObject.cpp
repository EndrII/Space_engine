#include "ModuleResursObject.h"

ModuleResursObject::ModuleResursObject(EGameResurs *ite, QString *projectDir, QWidget *parent) :
    Module(projectDir,parent)
{
    item=ite;
    this->setTitle("Resurce");
    valueResurse=new QSpinBox();
    valueResurse->setMaximum(10000000);
    mass_item=new QDoubleSpinBox();
    mass_item->setMinimum(0.01);
    mass_item->setMaximum(100.01);
    connect(mass_item,SIGNAL(valueChanged(double)),SLOT(massChanged(double)));
    this->addWidget(new QLabel("Resurse mass:"));
    this->addWidget(mass_item);
    this->addWidget(new QLabel("Resurse Value:"));
    this->addWidget(valueResurse);
    connect(valueResurse,SIGNAL(valueChanged(int)),SLOT(valueChanged(int)));
    this->newHorizont();
    nameObject=new QLineEdit();
    connect(nameObject,SIGNAL(editingFinished()),this,SLOT(nameChanged()));
    this->addWidget(new QLabel("name:"));
    nameIndex=new QSpinBox();
    //nameIndex->setValue(ite->getRes()->idName());
    connect(nameIndex,SIGNAL(valueChanged(int)),this,SLOT(nameIndexChanged(int)));
    this->addWidget(nameIndex);
    this->addWidget(nameObject);
    this->newHorizont();
    this->addWidget(new QLabel("Description Object"));
    descIndex=new QSpinBox();
   // descIndex->setValue(ite->getRes()->idDesc());
    connect(descIndex,SIGNAL(valueChanged(int)),this,SLOT(descIndexChanged(int)));
    this->addWidget(descIndex);
    this->newHorizont();
    description=new QTextEdit();
    connect(description,SIGNAL(textChanged()),this,SLOT(descChanged()));
    this->addWidget(description);
    this->newHorizont();
    this->addWidget(new QLabel("Craft:"));
    this->newHorizont();
    addCraft=new ButtonPlay("addCraftItem");
    connect(addCraft,SIGNAL(clickButton(QPushButton*)),SLOT(buttonClic(QPushButton*)));
    deleteCraft=new ButtonRemove("deleteCraftItem");
    connect(deleteCraft,SIGNAL(clickButton(QPushButton*)),SLOT(buttonClic(QPushButton*)));
    this->addWidget(addCraft);
    this->addWidget(deleteCraft);
    this->newHorizont();
    constructionList=new QTableWidget();
    this->addWidget(constructionList);
    this->newHorizont();
    random=new ButtonRegulyar("Random size Object");
    connect(random,SIGNAL(clickButton(QPushButton*)),SLOT(buttonClic(QPushButton*)));
    this->addWidget(random);
    this->end();
}
void ModuleResursObject::showTable(){
    constructionList->setColumnCount(1);
    constructionList->setRowCount(item->getRes()->getSource()->getCraft()->size());
    constructionList->horizontalHeaderItem(0)->setText("value");
    QMapIterator<us,us> i(*item->getRes()->getSource()->getCraft());
    int z=0;
    while(i.hasNext()){
        constructionList->setCellWidget(z,0,new QSpinBox());
        constructionList->verticalHeaderItem(z++)->setText(EResursePack::getName(item->getRes()->getSource()->getCraft()->first()));
    }
    connect(constructionList,SIGNAL(cellChanged(int,int)),SLOT(itemChanged(int,int)));
}
void ModuleResursObject::itemChanged(int row,int column){
    item->getRes()->getSource()->getCraft()->operator[](row)=((QSpinBox*)constructionList->cellWidget(row,column))->value();
}
void ModuleResursObject::nameChanged(){
}
void ModuleResursObject::descIndexChanged(int i){
    item->getRes()->getSource()->setDescriptionId(i);
    description->setText(item->getRes()->getSource()->desc());
}
void ModuleResursObject::nameIndexChanged(int i){
    item->getRes()->getSource()->setNameId(i);
    nameObject->setText(item->getRes()->getSource()->name());
}
void ModuleResursObject::descChanged(){

}
void ModuleResursObject::valueChanged(int v){
    item->getRes()->setValue(v);
}
void ModuleResursObject::massChanged(double m){
    item->getRes()->getSource()->setMass(m);
}
bool ModuleResursObject::setNewObject(EObject *i){
    if(i->getEObjectNameClass()!=E_GAME_RESURS)
        return false;
    item=static_cast<EGameResurs*>(i);
    nameIndex->setValue(item->getRes()->getSource()->idName());
    descIndex->setValue(item->getRes()->getSource()->idDesc());
    description->setText(item->getRes()->getSource()->desc());
    nameObject->setText(item->getRes()->getSource()->name());
    return true;
}
void ModuleResursObject::buttonClic(QPushButton *b){
    if(b==addCraft){
        int id=AddResurse::staticShow(this);
        if(id>=0){
            item->getRes()->getSource()->getCraft()->insert(id,1);
        }
    }
    if(b==random){
        item->RandomValue();
        mass_item->setValue(item->getMass());
        valueResurse->setValue(item->getRes()->getValue());
    }
    if(deleteCraft==b){
       // QMapIterator<us,us> i(item->getRes()->getCraft());
        //QMap<us,us> *temp=item->getRes()->getCraft();
        //temp->erase(temp->find(constructionList->verticalHeader().cconstructionList->currentRow()))
    }
}