#include "ModuleResursObject.h"
#include <SpaceEngine/SpaceEngine.h>
CraftTableModel::CraftTableModel(craftList *craft):QStandardItemModel(),
    craftlist(craft)
{
    this->setHorizontalHeaderLabels(QStringList()<<tr("item")<<tr("count"));
    if(craftlist)
        this->setRowCount(craftlist->size());
} 
QVariant CraftTableModel::data(const QModelIndex &index, int role)const{
    if(!craftlist) return QVariant();
    craftList::iterator idItem=craftlist->begin()+index.row();
    switch (role) {
    case Qt::DisplayRole:{
        if(index.column()==0){
            return EResursePack::getName(idItem.key());
        }else{
            return idItem.value();
        }
    }
    case Qt::DecorationRole:{
        if(index.column()==0){
            return EResursePack::getResurse(idItem.key())->picture()->scaled(20,20);
        }
    }
    case  Qt::EditRole:{
        if(index.column()==1){
            return idItem.value();
        }
    }
    case Qt::TextAlignmentRole:{
        if(index.column()==0){
            return Qt::AlignCenter;
        }else{
            return Qt::AlignRight;
        }
    }
    case Qt::BackgroundColorRole:{
        if(!idItem.value()){
            return QColor(0xff,0xaa,0xaa);
        }
        return QColor(0xaa,0xaa,0xaa);
    }
    case Qt::TextColorRole:
        return QColor(255,255,255);
    default:
        break;
    }
    return QVariant();
}
bool CraftTableModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(role==Qt::EditRole&&index.column()==1){
        craftList::iterator i=craftlist->begin()+index.row();
        bool ok;
        int temp =value.toInt(&ok);
        if(ok&&temp>0)
            i.value()=temp;
        return ok;
    }
    return false;
}
void CraftTableModel::refresh(){
    if(craftlist&&craftlist->size()!=this->rowCount())
        this->setRowCount(craftlist->size());
}
void CraftTableModel::setNew(craftList *craft){
    craftlist=craft;
}
CraftTableModel::~CraftTableModel(){

}
ModuleResursObject::ModuleResursObject(EGameResurs *ite, SpaceEngine *engine, QString *projectDir, QWidget *parent) :
    Module(engine,projectDir,parent)
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
    this->addWidget(new QLabel("name:"));
    this->addWidget(nameObject);
    icon=new QPushButton();
    icon->setText("");
    icon->setIconSize(QSize(50,50));
    this->addWidget(icon);
    connect(icon,SIGNAL(clicked(bool)),SLOT(iconChange(bool)));
    this->newHorizont();
    this->addWidget(new QLabel("Description Object"));
    this->newHorizont();
    description=new QTextEdit();
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
    model=new CraftTableModel((item)?item->getRes()->getSource()->getCraft():NULL);
    constructionList=new QTableView();
    constructionList->setModel(model);
    this->addWidget(constructionList);
    this->newHorizont();
    random=new ButtonRegulyar("Random size Object");
    connect(random,SIGNAL(clickButton(QPushButton*)),SLOT(buttonClic(QPushButton*)));
    this->addWidget(random);
    this->end();
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
    description->setText(item->getRes()->getSource()->rawDesc());
    model->setNew(item->getRes()->getSource()->getCraft());
    nameObject->setText(item->getRes()->getSource()->rawName());
    icon->setIcon(QPixmap::fromImage(*item->getRes()->getSource()->picture()));
    return true;
}
bool ModuleResursObject::saveObject(const QString &patch){
    item->getRes()->getSource()->setDescription(description->toPlainText());
    item->getRes()->getSource()->setName(nameObject->text());
    item->getRes()->getSource()->setUrl(patch);
    item->saveObject(patch);

    return true;
}
void ModuleResursObject::iconChange(bool){
    parent->OffAll();
    if(QMessageBox::information(this,tr("Default"),tr("you want to load default image?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
        item->getRes()->getSource()->setPicture("",true);
    }else{
        QString temp= QFileDialog::getOpenFileName(this,tr("new Picture"),*patch);
        item->getRes()->getSource()->setPicture(temp,false);
    }
    icon->setIcon(QPixmap::fromImage(*item->getRes()->getSource()->picture()));
    parent->OnAll();
}
void ModuleResursObject::buttonClic(QPushButton *b){
    if(b==addCraft){
        int id=AddResurse::staticShow(this);
        if(id){
            item->getRes()->getSource()->getCraft()->insert(id,1);
            model->refresh();
        }
    }else
    if(b==random){
        item->RandomValue();
        mass_item->setValue(item->getMass());
        valueResurse->setValue(item->getRes()->getValue());
    }else
    if(deleteCraft==b){
        item->getRes()->getSource()->getCraft()->erase(item->getRes()->getSource()->getCraft()->begin()+constructionList->currentIndex().row());
        if(model->rowCount()!=item->getRes()->getSource()->getCraft()->size())
            model->setRowCount(item->getRes()->getSource()->getCraft()->size());
    }
}
