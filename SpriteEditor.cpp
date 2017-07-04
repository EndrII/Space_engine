#include "SpriteEditor.h"

SpriteEditor::SpriteEditor(QString *patchProject,ELanguage *lan, QWidget *parent){
    lang=lan;
    addMap();
    ObjectRender=NULL;
    SpaceEngineEvents->setParent(parent);
    addCamera();
    camera=getCamersList()->front();
    connect(camera,SIGNAL(MouseClikedEvent(EMouseEvent*)),SLOT(cameraClick(EMouseEvent*)));
    Projectpatch=patchProject;
    setMap(getMapsList()->front(),camera);
    setCameraVirtual(camera,EKord(0.70,0.65),EKord(0,0.1));
    OnAll();
    createHorizontalMenu();
    createVerticalMenu();
    createHorizontalListFrame();
    SpriteListChanged("");
    log=new ELoadScreen();
    addQtWidget(log,EKord(0),EKord(1,0.1));
    log->setHidden(true);
    ugol=lastX=OldCurentFrame=0;
    shortKey=presed_none;
    tempCopyAnimation=tempCopyIndex=tempPasteAnimation=tempPasteIndex=-1;
    connect(getMain(),SIGNAL(EmouseMoveEvent(QMouseEvent*)),SLOT(MouseMove(QMouseEvent*)));
    connect(getMain(),SIGNAL(EkeyPressEvent(QKeyEvent*)),SLOT(press(QKeyEvent*)));
    connect(getMain(),SIGNAL(EkeyReleaseEvent(QKeyEvent*)),SLOT(release(QKeyEvent*)));
    ShiftPressd=ctrlPresed=false;
}
void SpriteEditor::cameraClick(EMouseEvent *e){
    if(alt&&e->button==Qt::LeftButton){
        camera->Mov_ECamera_To(e->x,e->y);
    }
    if(alt&&e->button==Qt::RightButton){
        camera->Mov_ECamera_To(0,0);
    }
}
void SpriteEditor::press(QKeyEvent *key){
    if(key->key()==Qt::Key_Shift)
        ShiftPressd=true;
    if(key->key()==Qt::Key_Control)
        ctrlPresed=true;
    if(key->key()==Qt::Key_Z)
        alt=true;
    if(ctrlPresed&&key->key()==Qt::Key_C&&AnimationsIndex->count()&&
            ListFrame->selectedRanges().size()){
        shortKey=presed_copy;
        tempCopyAnimation=AnimationsIndex->currentIndex();
        tempCopyIndex=ListFrame->selectedRanges().front().leftColumn();
    }
    if(ctrlPresed&&key->key()==Qt::Key_X&&AnimationsIndex->count()&&
            ListFrame->selectedRanges().size()){
        shortKey=presed_move;
        tempCopyAnimation=AnimationsIndex->currentIndex();
        tempCopyIndex=ListFrame->selectedRanges().front().leftColumn();
    }
    if(ctrlPresed&&key->key()==Qt::Key_V&&ObjectRender!=NULL){
        switch (shortKey) {
        case presed_copy:
            ObjectRender->copyFrame(tempCopyAnimation,AnimationsIndex->currentIndex(),tempCopyIndex,ListFrame->selectedRanges().front().leftColumn());
            break;
        case presed_move:
            ObjectRender->moveFrame(tempCopyAnimation,AnimationsIndex->currentIndex(),tempCopyIndex,ListFrame->selectedRanges().front().leftColumn());
            shortKey=presed_none;
            break;
        default:
            break;
        }
        updateFrameList(AnimationsIndex->currentIndex());
    }
}
void SpriteEditor::release(QKeyEvent *key){
    if(key->key()==Qt::Key_Shift){
        ShiftPressd=false;
    }
    if(key->key()==Qt::Key_Control)
        ctrlPresed=false;
    if(key->key()==Qt::Key_Z)
        alt=false;
}
void SpriteEditor::MouseMove(QMouseEvent *event){
    if(ShiftPressd&&ObjectRender){
        float xy=event->x()/(float)event->y();
        ObjectRender->setSize(EKord(100*xy,100));
    }
    if(ctrlPresed&&ObjectRender){
        ugol+=event->x()-lastX;
        ObjectRender->setUgol(ugol);
        lastX=event->x();
    }
}
QStringList SpriteEditor::readProject(){
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
void SpriteEditor::createHorizontalMenu(){
    OpenSpriteButton=new ButtonRegulyar("Open Sprite");
    connect(OpenSpriteButton,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));

    Save=new ButtonRegulyar("Save Sprite");
    Save->setShortcut(QKeySequence(Qt::Key_Save));
    Delete=new ButtonRemove("Remove Sprite");
    Delete->setShortcut(QKeySequence(Qt::Key_Delete));
    create=new ButtonPlay("Create Sprite");
    create->setShortcut(QKeySequence(Qt::Key_New));
    connect(create,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    connect(Save,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    connect(Delete,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));

    QHBoxLayout *Hbox=new QHBoxLayout();
    Hbox->addWidget(OpenSpriteButton);
    Hbox->addWidget(Save);
    Hbox->addWidget(Delete);
    Hbox->addWidget(create);
    HBoxWidget=new QWidget();
    HBoxWidget->setLayout(Hbox);
    this->addQtWidget(HBoxWidget,EKord(0),EKord(1,0.1));
}
void SpriteEditor::ModeChanged(int mode){
    if(ObjectRender==NULL){
        TimeMode->setEnabled(false);
        modeTimeC->setCheckState(Qt::Unchecked);
        return;
    }
    if(mode==Qt::Checked){
        TimeMode->setEnabled(true);
        ObjectRender->setMode(StaticAni,TimeMode->value());
    }else{
        TimeMode->setEnabled(false);
        ObjectRender->setMode(DefaultAni);
    }
}
void SpriteEditor::TimeModeChanged(int i){
    ObjectRender->setMode(StaticAni,i);
}
void SpriteEditor::createVerticalMenu(){
    QVBoxLayout *MainBox=new QVBoxLayout();
    QWidget *FrameAnimationControl=new QWidget;
    QVBoxLayout *BoxFrameAnimation=new QVBoxLayout();
    QHBoxLayout *box=new QHBoxLayout();

    FrameAnimationControl=new QWidget;
    FrameAnimationControl->setObjectName("Box");
    box=new QHBoxLayout();
    TimeModeL=new QLabel("Animation Mode:");
    BoxFrameAnimation->addWidget(TimeModeL);
    modeTimeC=new QCheckBox("Static animation mode");
    TimeMode=new QSpinBox(); TimeMode->setMaximum(1); TimeMode->setMaximum(1000000);
    TimeMode->setEnabled(false);
    box->addWidget(modeTimeC);
    box->addWidget(TimeMode);
    connect(TimeMode,SIGNAL(valueChanged(int)),this,SLOT(TimeModeChanged(int)));
    connect(modeTimeC,SIGNAL(stateChanged(int)),this,SLOT(ModeChanged(int)));
    BoxFrameAnimation->addLayout(box);

    box=new QHBoxLayout();
    box->addWidget(new QLabel("Bacground color:"));
    Bcolor=new ButtonRegulyar("Change color");
    connect(Bcolor,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    box->addWidget(Bcolor);
    BoxFrameAnimation->addLayout(box);


    FrameAnimationControl->setLayout(BoxFrameAnimation);
    FrameAnimationControl->setMaximumHeight(100);
    MainBox->addWidget(FrameAnimationControl);

    BoxFrameAnimation=new QVBoxLayout;
    FrameAnimationControl=new QWidget;
    AnimationsIndex=new QComboBox();
    connect(AnimationsIndex,SIGNAL(currentIndexChanged(int)),this,SLOT(updateFrameList(int)));
    AnimationIndexL=new QLabel("Animation:");
    PlayAnimation=new ButtonRegulyar("Play");
    compress=new ButtonRegulyar("Compress");
    PlayAnimation->setToolTip("Воспроизведет выбранную анимацию");
    addEmpty=new ButtonPlay("addEmpty");
    ClearAnimation=new ButtonRegulyar("StopAll");
    RemoveAnimation=new ButtonRemove("Remove");
    RenameAnimation=new ButtonRegulyar("Rename");
    AddAnimation=new ButtonPlay("AddGif");
    connect(compress,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    connect(addEmpty,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    connect(PlayAnimation,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    connect(ClearAnimation,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    connect(RemoveAnimation,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    connect(RenameAnimation,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    connect(AddAnimation,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));

    box=new QHBoxLayout();
    box->addWidget(AnimationsIndex);
    box->addWidget(PlayAnimation);
    BoxFrameAnimation->addWidget(AnimationIndexL);
    BoxFrameAnimation->addLayout(box);
    box=new QHBoxLayout();
    box->addWidget(addEmpty);
    box->addWidget(AddAnimation);
    BoxFrameAnimation->addLayout(box);
    box=new QHBoxLayout();
    box->addWidget(RenameAnimation);
    box->addWidget(RemoveAnimation);
    BoxFrameAnimation->addLayout(box);
    box=new QHBoxLayout;
    box->addWidget(compress);
    box->addWidget(ClearAnimation);
    BoxFrameAnimation->addLayout(box);
    FrameAnimationControl->setLayout(BoxFrameAnimation);
    FrameAnimationControl->setObjectName("Box");
    FrameAnimationControl->setMaximumHeight(130);
    MainBox->addWidget(FrameAnimationControl);





    BoxFrameAnimation=new QVBoxLayout;
    FrameAnimationControl=new QWidget;
    FrameAnimationControl->setObjectName("Box");
    box=new QHBoxLayout();
    RenderFrame=new ButtonRegulyar("RenderFrame");
    RenderValue=new QSpinBox(); RenderValue->setMinimum(0);RenderValue->setMaximum(100);

    connect(RenderFrame,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));

    ListRenderSprite=new QComboBox();
    ListRenderSprite->addItems(readProject());
    box->addWidget(ListRenderSprite);
    box->addWidget(RenderValue);
    box->addWidget(RenderFrame);
    BoxFrameAnimation->addWidget(new QLabel("Automatically add frames to the animation system:"));
    BoxFrameAnimation->addLayout(box);
    FrameAnimationControl->setLayout(BoxFrameAnimation);
    FrameAnimationControl->setMaximumHeight(70);
    MainBox->addWidget(FrameAnimationControl);



    BoxFrameAnimation=new QVBoxLayout;
    FrameAnimationControl=new QWidget;
    FrameAnimationControl->setObjectName("Box");
    box=new QHBoxLayout();
    MoveFrame=new ButtonRegulyar("MoveFrame");
    CopyFrame=new ButtonRegulyar("CopyFrame");
    connect(MoveFrame,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    connect(CopyFrame,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));

    box->addWidget(CopyFrame);
    box->addWidget(MoveFrame);
    BoxFrameAnimation->addLayout(box);

    box=new QHBoxLayout();
    ofL=new QLabel("Move of:");
    ofAnimationIndexL=new QLabel("Animation:");
    ofFrameIndexL=new QLabel("Frame:");
    ofAnimationsIndex=new QSpinBox();
    ofFrameIndex=new QSpinBox();

    box->addWidget(ofL);
    box->addWidget(ofAnimationIndexL);
    box->addWidget(ofAnimationsIndex);
    box->addWidget(ofFrameIndexL);
    box->addWidget(ofFrameIndex);
    BoxFrameAnimation->addLayout(box);

    box=new QHBoxLayout();
    toL=new QLabel("Move to:");
    toAnimationIndexL=new QLabel("Animation:");
    toFrameIndexL=new QLabel("Frame:");
    toAnimationsIndex=new QSpinBox();
    toFrameIndex=new QSpinBox();
    box->addWidget(toL);
    box->addWidget(toAnimationIndexL);
    box->addWidget(toAnimationsIndex);
    box->addWidget(toFrameIndexL);
    box->addWidget(toFrameIndex);
    BoxFrameAnimation->addLayout(box);
    FrameAnimationControl->setLayout(BoxFrameAnimation);
    FrameAnimationControl->setMaximumHeight(120);
    MainBox->addWidget(FrameAnimationControl);

    BoxFrameAnimation=new QVBoxLayout;
    FrameAnimationControl=new QWidget;
    FrameAnimationControl->setObjectName("Box");
    FrameIndex=new QSpinBox();
    FrameIndex->setEnabled(false);

    FrameIndexL=new QLabel("Frame:");
    AddFrame=new ButtonPlay("add");
    RemoveFrame=new ButtonRemove("Remove");
    connect(AddFrame,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));
    connect(RemoveFrame,SIGNAL(clickButton(QPushButton*)),this,SLOT(ClikedButton(QPushButton*)));

    box=new QHBoxLayout();
    BoxFrameAnimation->addWidget(FrameIndexL);
    box->addWidget(FrameIndex);
    box->addWidget(AddFrame);
    box->addWidget(RemoveFrame);
    BoxFrameAnimation->addLayout(box);
    FrameAnimationControl->setLayout(BoxFrameAnimation);
    FrameAnimationControl->setMaximumHeight(70);
    MainBox->addWidget(FrameAnimationControl);

    VBoxWidget=new QWidget();
    VBoxWidget->setLayout(MainBox);
    this->addQtWidget(VBoxWidget,EKord(0.70,0.1),EKord(0.30,0.90));
}
void SpriteEditor::RenderFrameFunction(){
    ObjectRender->rennderDamageFrame(ESprite((*Projectpatch)+"/"+SPRITE_DIR+"/"+ListRenderSprite->currentText(),Edit_Mode),RenderValue->value());
}
void SpriteEditor::SpriteListChanged(QString s){
    if(!s.isEmpty()){
        VBoxWidget->setEnabled(true);
        OpenSprite(s);
        updateAnimationsList();
    }
    else{
        VBoxWidget->setEnabled(false);
    }
}
void SpriteEditor::CreateSprite(){
    camera->Off();
    Core->clear();
    QUrl createname=QFileDialog::getSaveFileUrl(SpaceEngineEvents,"Selected Sprite",QUrl::fromLocalFile((*Projectpatch)+"/"+SPRITE_DIR),"*.spr");
    if(createname.isEmpty())
        return;
    QString tempPatch= createname.path();
#ifdef Q_OS_WIN
    tempPatch=tempPatch.right(tempPatch.size()-1);
#endif
    ESprite *temp=new ESprite(createname.path(),Edit_Mode);
    temp->save();
    delete temp;
    if(ObjectRender!=NULL){
        this->removeObject(ObjectRender);
    }
    ObjectRender=new EObject("",EKord(100,100),EKord(0),tempPatch,Edit_Mode);
    ESprite::connectProgress(ObjectRender,log);
    ObjectRender->newEmptyAnimation("System1");
    ObjectRender->save();
    this->addObject(ObjectRender,getMapsList()->front());
    OnAll();
    SpriteListChanged(tempPatch);
    updateAnimationsList();
    camera->On();
}
void SpriteEditor::ClikedButton(QPushButton *b){
    if(b==create){
        CreateSprite();
    }
    if(b==AddAnimation&&ObjectRender!=NULL){
        QString name=QFileDialog::getOpenFileName(SpaceEngineEvents,"Select Gif Animation","","*.gif");
        if(name!=""){
            ObjectRender->Append(name,"newAnimation");
            updateAnimationsList();
        }
    }
    if(b==PlayAnimation&&ObjectRender!=NULL&&AnimationsIndex->count()){
        ObjectRender->Play(AnimationsIndex->currentIndex());
    }
    if(b==ClearAnimation&&ObjectRender!=NULL){
        ObjectRender->Replay();
    }
    if(b==Save&&ObjectRender!=NULL){
        ObjectRender->save();
    }
    if(b==RenameAnimation&&ObjectRender!=NULL&&AnimationsIndex->count()){
        ObjectRender->renameAnimation(AnimationsIndex->currentIndex(),QInputDialog::getText(this->getMain(),"new Name animation","Write new Name curent animation"));
        updateAnimationsList();
    }
    if(b==RemoveAnimation&&ObjectRender!=NULL&&AnimationsIndex->count()){
        ObjectRender->Remove_Animation(AnimationsIndex->currentIndex());
        shortKey=presed_none;
        updateAnimationsList();
    }
    if(b==AddFrame&&ObjectRender!=NULL&&AnimationsIndex->count()){
        QStringList temp= QFileDialog::getOpenFileNames(this->getMain(),"Select image fles");
        int tem=0;
        log->setmax(temp.size(),"Add frmes");
        for(QString i:temp){
            ObjectRender->Append(AnimationsIndex->currentIndex(),i,FrameIndex->value()+tem++);
            log->progress(tem);
        }
        log->progress(-1);
        shortKey=presed_none;
        updateFrameList(AnimationsIndex->currentIndex());
    }
    if(b==RemoveFrame&&ObjectRender!=NULL&&AnimationsIndex->count()&&
            ListFrame->selectedRanges().size()){
        int left= ListFrame->selectedRanges().front().leftColumn();
        int right= ListFrame->selectedRanges().front().rightColumn();
        while(left<=right){
            ObjectRender->Remove_Frame(AnimationsIndex->currentIndex(),left);
            right--;
        }
        shortKey=presed_none;
        updateFrameList(AnimationsIndex->currentIndex());
    }
    if(b==addEmpty&&ObjectRender!=NULL&&AnimationsIndex->count()){
        ObjectRender->newEmptyAnimation(QInputDialog::getText(this->getMain(),"Name animation","Write Name created animation"));
        updateAnimationsList();
    }
    if(b==RenderFrame&&ObjectRender!=NULL&&AnimationsIndex->count()){
        RenderFrameFunction();
        shortKey=presed_none;
        updateFrameList(AnimationsIndex->currentIndex());
    }
    if(b==compress&&ObjectRender!=NULL&&AnimationsIndex->count()){
        CompressMenu *compressM=new CompressMenu(getMain());
        connect(compressM,SIGNAL(ok(int,int)),SLOT(compressOk(int,int)));
        compressM->show();
        shortKey=presed_none;
    }
    if(b==Delete&&ObjectRender!=NULL&&AnimationsIndex->count()){
        int temp = QMessageBox::question(getMain(), "Warning","delete this Sprite?",
                                      QMessageBox::No|QMessageBox::Yes);
        if(temp== QMessageBox::Yes){
            QString temp=ObjectRender->getPatch();
            this->removeObject(ObjectRender);
            QFile(temp).remove();
            updateAnimationsList();
            shortKey=presed_none;
            SpriteListChanged("");
        }
    }
    if(b==MoveFrame&&ObjectRender!=NULL&&AnimationsIndex->count()&&toAnimationsIndex->value()<AnimationsIndex->count()){
        ObjectRender->moveFrame(ofAnimationsIndex->value(),toAnimationsIndex->value(),
                                ofFrameIndex->value(),toFrameIndex->value());
        AnimationsIndex->setCurrentIndex(toAnimationsIndex->value());
        shortKey=presed_none;
        updateFrameList(AnimationsIndex->currentIndex());
    }
    if(b==CopyFrame&&ObjectRender!=NULL&&AnimationsIndex->count()&&toAnimationsIndex->value()<AnimationsIndex->count()){
        ObjectRender->copyFrame(ofAnimationsIndex->value(),toAnimationsIndex->value(),
                                ofFrameIndex->value(),toFrameIndex->value());
        AnimationsIndex->setCurrentIndex(toAnimationsIndex->value());
        shortKey=presed_none;
        updateFrameList(AnimationsIndex->currentIndex());
    }
    if(b==Bcolor&&ObjectRender!=NULL&&AnimationsIndex->count()){
        QColor temp=QColorDialog::getColor(Qt::black,getMain());
        camera->setBackgroundColor(temp);
    }
    if(b==OpenSpriteButton){
        QString tempPatch= QFileDialog::getOpenFileUrl(SpaceEngineEvents,"Selected Sprite",QUrl::fromLocalFile((*Projectpatch)+"/"+SPRITE_DIR),"*.spr").path();
#ifdef Q_OS_WIN
    tempPatch=tempPatch.right(tempPatch.size()-1);
#endif
       SpriteListChanged(tempPatch);
    }
}
void SpriteEditor::compressOk(int sec, int frame){
    ObjectRender->Compress(AnimationsIndex->currentIndex(),frame,sec);
    updateFrameList(AnimationsIndex->currentIndex());
}
void SpriteEditor::updateAnimationsList(){
    if(ObjectRender!=NULL){
        AnimationsIndex->clear();
        for(int i=0;i<ObjectRender->getValueSprite();i++){
            AnimationsIndex->addItem(ObjectRender->getNameAnimation(i));
        }
        FrameIndex->setValue(0);
        ListRenderSprite->clear();
        ListRenderSprite->addItems(readProject());
    }
}
void SpriteEditor::updateFrameList(int i){//утечка памяти не удаляються лейблы из листа кадров
    if(i<0||ObjectRender->getLongSprite(i)<=0){
        RemoveFrame->setEnabled(false);
        ListFrame->setEnabled(false);
        FrameIndex->setValue(0);
    }else{
        RemoveFrame->setEnabled(true);
        ListFrame->setEnabled(true);
        FrameIndex->setMinimum(0);
        FrameIndex->setMaximum(ObjectRender->getLongSprite(i)-1);
        ofAnimationsIndex->setValue(i);
        FrameIndex->setValue(0);
        ListFrame->setRowCount(2);
        ListFrame->setColumnCount(ObjectRender->getLongSprite(i));
        ListFrame->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
        ListFrame->horizontalHeader()->sectionResizeMode(QHeaderView::Fixed);
        ListFrame->horizontalHeader()->setMaximumSectionSize(70);
        ListFrame->horizontalHeader()->setMinimumSectionSize(70);
        ListFrame->horizontalHeader()->setDefaultSectionSize(70);
        ListFrame->setRowHeight(0,80);
        ListFrame->setRowHeight(1,20);
        QLabel *tempLabel;
        QList<QImage*> *temp=ObjectRender->getSource();
        for(int i=0;i<ObjectRender->getLongSprite(AnimationsIndex->currentIndex());i++){
            tempLabel=new QLabel();
            tempLabel->setPixmap(QPixmap::fromImage(*(temp->operator [](i+ObjectRender->getBeginIndexAnimation(AnimationsIndex->currentIndex())))).scaled(80,70));
            ListFrame->setCellWidget(0,i,tempLabel);
            QLineEdit *edit=new QLineEdit(QString::number(ObjectRender->getLongFrame(AnimationsIndex->currentIndex(),i)));
            edit->setEnabled(false);
            connect(edit,SIGNAL(editingFinished()),SLOT(LongAQnimationChanged()));
            ListFrame->setCellWidget(1,i,edit);
            memorylist.push_back(tempLabel);
        }
    }
}
void SpriteEditor::LongAQnimationChanged(){
    ui temp=((QLineEdit*)ListFrame->cellWidget(1,ListFrame->currentColumn()))->text().toUInt();
    if(temp!=0){
        ObjectRender->Edit(AnimationsIndex->currentIndex(),ListFrame->currentColumn(),temp);
    }
    updateFrameList(AnimationsIndex->currentIndex());
}
void SpriteEditor::FrameChanged(int, int i){
    FrameIndex->setValue(i);
    ofFrameIndex->setValue(i);
    ListFrame->cellWidget(1,i)->setEnabled(true);
    ObjectRender->setCurentFrame(AnimationsIndex->currentIndex(),i);
    if(OldCurentFrame<ListFrame->columnCount())
        ListFrame->cellWidget(1,OldCurentFrame)->setEnabled(false);
    OldCurentFrame=i;
}
void SpriteEditor::createHorizontalListFrame(){
    QHBoxLayout *mainBox=new QHBoxLayout();
    ListFrame=new QTableWidget();
    ListFrame->setMaximumHeight(137);
    ListFrame->setMinimumHeight(137);
    connect(ListFrame,SIGNAL(cellClicked(int,int)),SLOT(FrameChanged(int,int)));
    mainBox->addWidget(ListFrame);
      QWidget *pane=new QWidget;
      pane->setObjectName("Box");
      pane->setLayout(mainBox);
      this->addQtWidget(pane,EKord(0,0.75),EKord(0.70,0.25));
}
void SpriteEditor::animationIndexApp(){
}
void SpriteEditor::OpenSprite(const QString& patch){
    camera->Off();
    Core->clear();
    if(ObjectRender!=NULL){
        this->removeObject(ObjectRender);
    }
    ObjectRender=new EObject("",EKord(100,100),EKord(0),patch,Edit_Mode);
    ESprite::connectProgress(ObjectRender,log);
    this->addObject(ObjectRender,getMapsList()->front());
    camera->On();
}
void SpriteEditor::AnimationChanged(QString str){
    if(str.size()>0){
        PlayAnimation->setEnabled(true);
    }
    else
        PlayAnimation->setEnabled(false);
}
void SpriteEditor::LoadSprite(){

}
SpriteEditor::~SpriteEditor(){
  /*  for(QLabel* i:memorylist)
        delete i;
    memorylist.clear();*/
}
