#include "ObjectEditor.h"

ObjectEditor::ObjectEditor(QString *patchProject,ELanguage *lan, QWidget *parent):
    SpaceEngine()
{
    SpaceEngineEvents->setParent(parent);
    addCamera();
    pack=new EResursePack();
    camera=getCamersList()->front();
   // camera->setLineWidth(5);
    connect(camera,SIGNAL(MouseClikedEvent(EMouseEvent*)),SLOT(cameraClick(EMouseEvent*)));
    connect(camera,SIGNAL(scrollEnd(EKord&)),this,SLOT(cameraSizeChanged(EKord&)));
    setCameraVirtual(camera,EKord(0.70,0.88),EKord(0,0.1));
    Projectpatch=patchProject;
    lang=lan;
    log=new ELoadScreen();
    addMap();
    ObjectRender=NULL;
    setMap(getMapsList()->front(),camera);
    createVerticalMenu();
    createHorizontalMenu();
    addQtWidget(log,EKord(0),EKord(1,0.1));
    log->setHidden(true);
    ugol=lastX=0;
    connect(getMain(),SIGNAL(EmouseMoveEvent(QMouseEvent*)),SLOT(MouseMove(QMouseEvent*)));
    connect(getMain(),SIGNAL(EkeyPressEvent(QKeyEvent*)),SLOT(press(QKeyEvent*)));
    connect(getMain(),SIGNAL(EkeyReleaseEvent(QKeyEvent*)),SLOT(release(QKeyEvent*)));
    alt=ShiftPressd=ctrlPresed=false;
}
QStringList ObjectEditor::readProject(){
    QStringList temp;
    QDir *dir=new QDir(*Projectpatch);
    dir->cd(SPRITE_DIR);
    dir->setFilter(QDir::Files);
    for(QString i: dir->entryList()){
        if(i.mid(i.size()-3).compare("spr",Qt::CaseInsensitive)==0)
            temp.push_back(i);
    }
    return temp;
}
void ObjectEditor::cameraClick(EMouseEvent *e){
    if(ObjectRender&&ConturEdit->checkState()==Qt::Checked){
        switch(e->button){
        case Qt::LeftButton:{
            ObjectRender->getContur()->addVertix(fromContur(e->x,e->y));
            break;
        }
        case Qt::MidButton:{
            ObjectRender->getContur()->removeLastVertix();
            break;
        }
        case Qt::RightButton:{
            ObjectRender->getContur()->removeLastVertix();
            break;
        }
        default:break;
        }
    }
    if(alt&&e->button==Qt::LeftButton){
        camera->Mov_ECamera_To(e->x,e->y);
    }
    if(alt&&e->button==Qt::RightButton){
        camera->Mov_ECamera_To(0,0);
    }
}
EKord ObjectEditor::fromContur(const float &x, const float &y){
    EKord result;
    result.X=EKord::length(0,0,x,y);
    result.Y=acos(x/result.X)/TO_RADIAN;
    if(y<0)result.Y*=-1;
    return result;
}
void ObjectEditor::createVerticalMenu(){
    QVBoxLayout *MainBox=new QVBoxLayout();
    QWidget *pane=new QWidget;
    QVBoxLayout *LayoutPane=new QVBoxLayout();
    QHBoxLayout *box=new QHBoxLayout();

    pane->setObjectName("Box");
    box=new QHBoxLayout();
    box->addWidget(new QLabel("Bacground color:"));
    Bcolor=new ButtonRegulyar("Change color");
    connect(Bcolor,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    box->addWidget(Bcolor);
    LayoutPane->addLayout(box);

    box=new QHBoxLayout();
    ObjectName=new QLineEdit("");
    connect(ObjectName,SIGNAL(editingFinished()),SLOT(RenameObject()));
    box->addWidget(new QLabel("Object Name: "));
    box->addWidget(ObjectName);
    LayoutPane->addLayout(box);

    box=new QHBoxLayout();
    sizeX=new QSpinBox();

    sizeY=new QSpinBox();
    box->addWidget(new QLabel("Width:"));
    box->addWidget(sizeX);
    box->addWidget(new QLabel(" Height:"));
    box->addWidget(sizeY);
    connect(sizeX,SIGNAL(valueChanged(int)),this,SLOT(ObjectSizeXChanged(int)));
    connect(sizeY,SIGNAL(valueChanged(int)),this,SLOT(ObjectSizeYChanged(int)));

    LayoutPane->addLayout(box);

    box=new QHBoxLayout();
    ConturEdit=new QCheckBox("Edit HitBox");
    ConturEdit->setEnabled(false);
    showHitBox=new QCheckBox("Show Box");
    ConturEdit->setCheckState(Qt::Unchecked);
    showHitBox->setCheckState(Qt::Unchecked);
    box->addWidget(showHitBox);
    box->addWidget(ConturEdit);
    connect(showHitBox,SIGNAL(stateChanged(int)),SLOT(conturShowChanged(int)));

    LayoutPane->addLayout(box);
    pane->setLayout(LayoutPane);
    pane->setMaximumHeight(120);
    MainBox->addWidget(pane);

    pane=new QWidget;
    pane->setObjectName("Box");
    LayoutPane=new QVBoxLayout();
    box=new QHBoxLayout();
    AnimationsIndex=new QComboBox();
   // connect(AnimationsIndex,SIGNAL(currentIndexChanged(int)),this,SLOT(updateFrameList(int)));
    box->addWidget(new QLabel("Animation :"));
    box->addWidget(AnimationsIndex);
    PlayAnimation=new ButtonRegulyar("Play");
    connect(PlayAnimation,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    PlayAnimation->setToolTip("Воспроизведет выбранную анимацию");
    box->addWidget(PlayAnimation);
    LayoutPane->addLayout(box);
    box=new QHBoxLayout();
    ClearAnimation=new ButtonRegulyar("StopAll");
    connect(ClearAnimation,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    box->addWidget(ClearAnimation);
    LayoutPane->addLayout(box);
    box=new QHBoxLayout();
    box->addWidget(new QLabel("Type: "));
    TypeObject=new QComboBox();
    QStringList tempList;
    tempList.push_back("OBJECT");
    tempList.push_back("PARALAX");
    tempList.push_back("RESURS");

    TypeObject->addItems(tempList);
    connect(TypeObject,SIGNAL(currentIndexChanged(int)),SLOT(typeChanged(int)));
    box->addWidget(TypeObject);
    LayoutPane->addLayout(box);

    pane->setLayout(LayoutPane);

    pane->setMaximumHeight(100);
    MainBox->addWidget(pane);

    adventSettings=new QWidget();
    adventSettings->setObjectName("Box");
    ModuleLayout =new QHBoxLayout();
    adventSettings->setLayout(ModuleLayout);
    module=new QStackedWidget();
   // Module->addWidget(NULL);
    moduleResursObject=new ModuleResursObject(NULL,Projectpatch);
    moduleParalax=new ModuleParalax(NULL,this,Projectpatch);
    module->addWidget(moduleParalax);
    module->addWidget(moduleResursObject);
    module->addWidget(moduleResursObject);

    ModuleLayout->addWidget(module);
    MainBox->addWidget(adventSettings);

    VBoxWidget=new QWidget();
    VBoxWidget->setLayout(MainBox);
    VBoxWidget->setEnabled(false);
    this->addQtWidget(VBoxWidget,EKord(0.70,0.1),EKord(0.30,0.85));
}
void ObjectEditor::typeChanged(int type){
    switch(type){
    case 0: retype(EOBJECT); break;
    case 1: retype(E_PARALAX);break;
    case 2: retype(E_GAME_RESURS);break;
    default: break;
    }
}
void ObjectEditor::ObjectSizeXChanged(int i){
    if(ObjectRender)
        ObjectRender->setW(i);
}
void ObjectEditor::ObjectSizeYChanged(int i){
    if(ObjectRender)
        ObjectRender->setH(i);
}
void ObjectEditor::cameraSizeChanged(EKord &obj){
    scrollSizeX->setText("Camera size: X-"+QString::number(obj.X));
    scrollSizeY->setText("Y-"+QString::number(obj.Y));
}
void ObjectEditor::conturShowChanged(int i){
    if(ObjectRender){
        if(i<2){
            ConturEdit->setEnabled(false);
            ConturEdit->setCheckState(Qt::Unchecked);
            ObjectRender->setDrawContur(false);
        }else{
            ObjectRender->setDrawContur(true);
            ConturEdit->setEnabled(true);
        }
    }
}
void ObjectEditor::RenameObject(){
    if(ObjectRender)
        ObjectRender->setName(ObjectName->text());
}
void ObjectEditor::createHorizontalMenu(){
    OpenObjectButton=new ButtonRegulyar("Open Object");
    connect(OpenObjectButton,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));

    Save=new ButtonRegulyar("Save Object");
    Save->setShortcut(QKeySequence(Qt::Key_Save));
    Delete=new ButtonRemove("Remove Object");
    Delete->setShortcut(QKeySequence(Qt::Key_Delete));
    create=new ButtonPlay("Create Object");
    create->setShortcut(QKeySequence(Qt::Key_New));
    connect(create,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    connect(Save,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    connect(Delete,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));

    QHBoxLayout *Hbox=new QHBoxLayout();
    Hbox->addWidget(OpenObjectButton);
    Hbox->addWidget(Save);
    Hbox->addWidget(Delete);
    Hbox->addWidget(create);
    QWidget *HBoxWidget=new QWidget();
    HBoxWidget->setLayout(Hbox);
    this->addQtWidget(HBoxWidget,EKord(0),EKord(1,0.1));
    Hbox=new QHBoxLayout();
    scrollSizeX=new QLabel("Camera size: X-100");
    scrollSizeY=new QLabel("Y-100");
    Hbox->addWidget(scrollSizeX);
    Hbox->addWidget(scrollSizeY);
    HBoxWidget=new QWidget();
    HBoxWidget->setLayout(Hbox);
    this->addQtWidget(HBoxWidget,EKord(0,0.06),EKord(0.2,0.05));

}
void ObjectEditor::press(QKeyEvent *key){
    if(key->key()==Qt::Key_Shift)
        ShiftPressd=true;
    if(key->key()==Qt::Key_Control)
        ctrlPresed=true;
    if(key->key()==Qt::Key_Z)
        alt=true;
}
void ObjectEditor::release(QKeyEvent *key){
    if(key->key()==Qt::Key_Shift){
        ShiftPressd=false;
        sizeX->setValue(ObjectRender->getW());
        sizeY->setValue(ObjectRender->getH());
    }
    if(key->key()==Qt::Key_Control)
        ctrlPresed=false;
    if(key->key()==Qt::Key_Z)
        alt=false;
}
void ObjectEditor::MouseMove(QMouseEvent *event){
    if(ShiftPressd&&ObjectRender){
        float xy=event->x()/(float)event->y();
        ObjectRender->setSize(EKord(sizeX->value()*xy,sizeY->value()));
    }
    if(ctrlPresed&&ObjectRender){
        ugol+=event->x()-lastX;
        ObjectRender->setUgol(ugol);
        lastX=event->x();
    }
}
bool ObjectEditor::createObject(const QString &patch ){
    bool test=true;
    while(test){
        test=false;
        OffAll();
        QUrl createname=QFileDialog::getOpenFileUrl(SpaceEngineEvents,"Select base sprite for creating object",QUrl::fromLocalFile(patch),"*.spr");
        OnAll();
        if(createname.isEmpty()) //(*Projectpatch)+"/"+SPRITE_DIR
            return false;
        QString tempPatch= createname.path();
    #ifdef Q_OS_WIN
        tempPatch=tempPatch.right(tempPatch.size()-1);
    #endif
        if(ObjectRender!=NULL)
            removeObject(ObjectRender);
        ObjectRender=new EObject((*Projectpatch)+"/"+OBJECT_DIR+"/"+createname.fileName().left(createname.fileName().size()-4),EKord(100,100),EKord(0),tempPatch,Edit_Mode);
        addObject(ObjectRender,this->getMapsList()->front());
        if(ObjectRender->getSource()->size()<1){
            QMessageBox::information(this->getMain(),"Error","this sprite is empty! selected new sprite!");
            test=true;
        }
    }
    ObjectName->setText(ObjectRender->getName());
    ObjectRender->setW(ObjectRender->getW()*ObjectRender->getSource()->operator [](0)->width()/ObjectRender->getSource()->operator [](0)->height());
    VBoxWidget->setEnabled(true);
    sizeX->setValue(ObjectRender->getW());
    sizeY->setValue(ObjectRender->getH());
    updateAnimationsList();
    retype(EOBJECT);
    return true;
}
void ObjectEditor::openObject(const QString &patch){
    camera->Off();
    QUrl createname=QFileDialog::getOpenFileUrl(SpaceEngineEvents,"Select opened object",QUrl::fromLocalFile(patch),OBJECTS_FILTERS);
    camera->On();
    if(createname.isEmpty())
        return;
    QString tempPatch= createname.path();
#ifdef Q_OS_WIN
    tempPatch=tempPatch.right(tempPatch.size()-1);
#endif
    if(ObjectRender!=NULL){
        removeObject(ObjectRender);
        ObjectRender=NULL;
        VBoxWidget->setEnabled(false);
    }
    if(patchTypes(tempPatch)){
        addObject(ObjectRender,this->getMapsList()->front());
        ObjectName->setText(ObjectRender->getName());
        VBoxWidget->setEnabled(true);
        sizeX->setMaximum(10000);
        sizeY->setMaximum(10000);
        sizeX->setValue(ObjectRender->getW());
        sizeY->setValue(ObjectRender->getH());
        updateAnimationsList();
    }else{
        QMessageBox::information(this->getMain(),"Open Error","this file type is not suported");
    }
    //typeChanged(ObjectRender->getEObjectNameClass());
}
bool ObjectEditor::patchTypes(const QString &patch){
    if(patch.right(5)==".eobj"){
        ObjectRender=new EObject(patch);
        TypeObject->setCurrentIndex(-1);
        TypeObject->setCurrentText("OBJECT");
        return true;
    }
    if(patch.right(5)==".eprx"){
        ObjectRender=new EParalax(patch);
        TypeObject->setCurrentIndex(-1);
        TypeObject->setCurrentText("PARALAX");
        return true;
    }
    if(patch.right(5)==".robj"){
        ObjectRender=new EGameResurs(patch,pack);
        TypeObject->setCurrentIndex(-1);
        TypeObject->setCurrentText("RESURS");
        return true;
    }
    return false;
}
void ObjectEditor::saveObject(){
    this->OffAll();
    QUrl patch=QFileDialog::getSaveFileUrl(SpaceEngineEvents,"Save object",QUrl::fromLocalFile(*Projectpatch+"/"+OBJECT_DIR+"/"+ObjectRender->getName()),OBJECTS_FILTERS);
    this->OnAll();
    QString tempPatch=patch.path();
#ifdef Q_OS_WIN
    tempPatch=tempPatch.right(tempPatch.size()-1);
#endif
    if(!ObjectRender->getContur()){
        QMessageBox::information(getMain(),"Save fail!","Object is not saved, HitBox not detected!");
    }else{
        //ObjectRender->saveObject(tempPatch);
        static_cast<Module*>(module->currentWidget())->saveObject(tempPatch);
    }
    /*if(ObjectRender->getEObjectNameClass()==E_GAME_RESURS){
        pack->save();
    }*/
}
void ObjectEditor::retype(EObjectNameClass type){ //repare
    switch(type){
    case EOBJECT:{
        if(ObjectRender->getEObjectNameClass()!=EOBJECT){
            camera->Off();
            if(ObjectRender->getPatch()=="none"){
                createObject(*Projectpatch+"/"+SPRITE_DIR);
            }
            else{
                EObject *temp=new EObject();
                temp->copy(ObjectRender);
                this->removeObject(ObjectRender);
                ObjectRender=temp;
                this->addObject(ObjectRender,this->getMapsList()->front());
            }
            adventSettings->setEnabled(false);
            camera->On();
        }
        module->setCurrentWidget(NULL);
        break;
    }
    case E_PARALAX:{
        if(ObjectRender->getEObjectNameClass()!=E_PARALAX){
            camera->Off();
            QStringList temp1;
            temp1.push_front(ObjectRender->getPatch());
            this->removeObject(ObjectRender);
            ObjectRender=new EParalax(0.0,temp1);
            this->addObject(ObjectRender,this->getMapsList()->front());
            camera->On();
        }
        moduleParalax->setNewObject(ObjectRender);
        module->setCurrentWidget(moduleParalax);
        adventSettings->setEnabled(true);
        break;
    }
    case E_GAME_RESURS:{
        if(ObjectRender->getEObjectNameClass()!=E_GAME_RESURS){
            camera->Off();
            if(ObjectRender->getPatch()=="none"){
                if(!createObject(*Projectpatch+"/"+SPRITE_DIR)){
                    camera->On();
                    return;
                }
            }
            EGameResurs *temp=new EGameResurs(ObjectRender,pack);
            removeObject(ObjectRender);
            ObjectRender=temp;
            addObject(ObjectRender,this->getMapsList()->front());
            camera->On();
        }
        moduleResursObject->setNewObject(ObjectRender);
        module->setCurrentWidget(moduleResursObject);
        adventSettings->setEnabled(true);
    }
    default:break;
    }
}
void ObjectEditor::updateAnimationsList(){
    if(ObjectRender!=NULL){
        AnimationsIndex->clear();
        for(int i=0;i<ObjectRender->getValueSprite();i++){
            AnimationsIndex->addItem(ObjectRender->getNameAnimation(i));
        }
    }
}
void ObjectEditor::ClikedButton(QPushButton *b){
    if(b==OpenObjectButton){
        openObject((*Projectpatch)+"/"+OBJECT_DIR);
    }
    if(b==PlayAnimation&&ObjectRender!=NULL&&AnimationsIndex->count()){
        ObjectRender->Play(AnimationsIndex->currentIndex());
    }
    if(b==create){
        createObject((*Projectpatch)+"/"+SPRITE_DIR);
    }
    if(b==ClearAnimation&&ObjectRender!=NULL){
        ObjectRender->Replay();
    }
    if(b==Save&&ObjectRender){
        saveObject();
    }
    if(b==Bcolor&&ObjectRender!=NULL&&AnimationsIndex->count()){
        QColor temp=QColorDialog::getColor(Qt::black,getMain());
        camera->setBackgroundColor(temp);
    }
    if(b==Delete&&ObjectRender){
        int temp = QMessageBox::question(getMain(), "Warning","delete \'"+ObjectRender->getObjectPatch()+"\' Object?",
                                      QMessageBox::No|QMessageBox::Yes);
        if(temp== QMessageBox::Yes){
            if(ObjectRender->getEObjectNameClass()==E_GAME_RESURS){
                pack->remove(((EGameResurs*)ObjectRender)->getRes()->getSource()->id());
                pack->save();
            }
            QString temp=ObjectRender->getObjectPatch();
            this->removeObject(ObjectRender);
            QFile(temp).remove();
            ObjectRender=NULL;
        }
    }
}
ObjectEditor::~ObjectEditor(){
    delete pack;
}
