#include "ModuleParalax.h"

ModuleParalax::ModuleParalax(EParalax *i, QString *patch, QWidget *Widget):
    Module(patch,Widget)
{
    item=i;
    setTitle("Paralax");
    addWidget(new QLabel("Factor"));
    Up=new QDoubleSpinBox();
    Up->setMaximum(2.0);
    Up->setMinimum(0.0);
    Up->setValue(0);
    addWidget(Up);
    newHorizont();
    addWidget(new QLabel("Fons:"));
    newHorizont();
    listofSprites=new QListWidget;
    listofSprites->addItem(patch->right(patch->size()-patch->indexOf("/")));
    addWidget(listofSprites);
    newHorizont();
    add=new ButtonPlay("add fon");
    remove=new ButtonRemove("remove last fon");
    addWidget(add);
    addWidget(remove);
    end();
    connect(add,SIGNAL(clickButton(QPushButton*)),this,SLOT(buttonClick(QPushButton*)));
    connect(remove,SIGNAL(clickButton(QPushButton*)),this,SLOT(buttonClick(QPushButton*)));
    connect(Up,SIGNAL(valueChanged(double)),this,SLOT(factorChanged(double)));
    //connect(item,SIGNAL(FrameValueChanged(unsigned short,uint)),SLOT(frameChanged(unsigned short,uint)));
}
/*void ModuleParalax::frameChanged(unsigned short animation, unsigned int value){
    if(animation==0){
        i
    }
}*/
bool ModuleParalax::setNewObject(EObject *i){
    if(i->getEObjectNameClass()!=E_PARALAX)
        return false;
    item=static_cast<EParalax*>(i);
    return true;
}
bool ModuleParalax::saveObject(const QString &patch){
    item->saveObject(patch);
    return true;
}
void ModuleParalax::factorChanged(double f){
    item->changeUp(f);
}
void ModuleParalax::buttonClick(QPushButton *b){
    if(b==add){
        QList<QUrl> list= QFileDialog::getOpenFileUrls(this,"selected sprite(s) for fons",*patch+"/"+SPRITE_DIR,"*.spr");
        for(QUrl url:list){
            QString tempPatch=url.path();
#ifdef Q_OS_WIN
            tempPatch.remove(0,1);
#endif
            item->addBack(tempPatch,Up->value());
            listofSprites->addItem(url.fileName());
        }
    }
    if(b==remove&&listofSprites->count()>0){
        item->removeLast();
        listofSprites->takeItem(listofSprites->count()-1);
    }
}
