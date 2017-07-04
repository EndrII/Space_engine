#include "widget.h"

Widget::Widget(int argc, char *argv[], QWidget *parent)
    : QMainWindow(parent)
{
    //qDebug()<<"second="<<listIncludeFileSprite;
    ELanguage::selectedLang()=LANG_ENG;
    setMinimumSize(1100,680);
    QWidget *CenterWidget =new QWidget();
    CenterWidget->setObjectName("Main");
    ModuleDescript=new QLabel("Project not opened",CenterWidget);
    ModuleDescript->setAlignment(Qt::AlignCenter);
    ModuleDescript->setObjectName("StateBar");
    tabs=new QTabWidget(CenterWidget);
    tabs->setObjectName("tab");
    connect(tabs,SIGNAL(currentChanged(int)),SLOT(TabChangedElement(int)));
    CSS::ReadCss(this,":Resurses/StyleProgramm.css");
    createMenu();

    this->setCentralWidget(CenterWidget);


    if(argc>1){
        OpenModule(argv[1]);
    }else{
        QFile fio("./temp");
        if(fio.open(QIODevice::ReadOnly)){
            QDataStream stream(&fio);
            stream>>projectFuulPatch;
            OpenModule(projectFuulPatch);
            fio.close();
        }else{
            PrjectPatch=".";
        }
    }
}
void Widget::resizeEvent(QResizeEvent *){
    ModuleDescript->setGeometry(0*this->width(),0*this->height(),1*this->width(),0.04*this->height());
    tabs->setGeometry(0*this->width(),0.04*this->height(),1*this->width(),0.96*this->height());
}
void Widget::createMenu(){
    this->setMenuBar(new QMenuBar);
    exit=new QAction("Exit",this);
    exit->setShortcut(QKeySequence::Close);
    connect(exit,SIGNAL(triggered(bool)),SLOT(ExitClick(bool)));
    createModule=new QAction("Create Module",this);
    moduleInformation=new QAction("Module Information",this);
    defaultLanguage=new QAction("Set Default Language",this);
    moduleInformation->setEnabled(false);
    openModule=new QAction("Open Module",this);
    connect(createModule,SIGNAL(triggered(bool)),SLOT(createClick(bool)));
    connect(moduleInformation,SIGNAL(triggered(bool)),SLOT(InformationClick(bool)));
    connect(openModule,SIGNAL(triggered(bool)),SLOT(OpenClick(bool)));
    connect(defaultLanguage,SIGNAL(triggered(bool)),this,SLOT(defaultLang(bool)));
    QMenu *module=new QMenu("Module");
    module->addAction(createModule);
    module->addAction(openModule);
    module->addAction(defaultLanguage);
    module->addAction(moduleInformation);

    menuBar()->addMenu(module);
    menuBar()->addAction(exit);
}
void Widget::InformationClick(bool){
    ModuleInformation *info=new ModuleInformation(&ProjectTitle,&Description,this);
    info->show();
}
void Widget::defaultLang(bool){
    ELanguage::setLanguage(QFileDialog::getOpenFileUrl(this,"select language file",PrjectPatch));;
}
void Widget::createClick(bool){
    QString temp= QFileDialog::getSaveFileName(this,"Project","","*.modpro");
    if(temp.size()){
        if(temp.mid(temp.size()-7).compare(".modpro",Qt::CaseInsensitive))
            temp+=".modpro";
        QFile f(temp);
        f.open(QIODevice::WriteOnly|QIODevice::Truncate);
        QDataStream stream(&f);
        ProjectTitle="No name project";
        stream<<ProjectTitle<<Description;
        f.close();
        QDir dir(temp.left(temp.lastIndexOf('/')));
        dir.mkdir(SPRITE_DIR);
        dir.mkdir(OBJECT_DIR);
        dir.mkdir(GAME_OBJECT_DIR);
        dir.mkdir(SONG_DIR);
        dir.mkdir(LANGUAGE);
        projectFuulPatch=dir.path()+"/"+temp;
        PrjectPatch=dir.path();
        moduleInformation->setEnabled(true);
        tabs->setEnabled(true);
        EResursePack::ResursePackDir()=PrjectPatch+"/Resurses.res";
        initializeTabs();
    }
}
void Widget::OpenClick(bool){
    QString temp= QFileDialog::getOpenFileName(this,"Project","","*.modpro");
    OpenModule(temp);
}
void Widget::SaveProject(){
    QFile f(projectFuulPatch);
    if(f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QDataStream stream(&f);
        stream<<ProjectTitle<<Description;
        f.close();
    }
}
void Widget::initializeTabs(){
    if(!tabs->count()){
        spr=new SpriteEditor(&PrjectPatch,NULL);
        objEdit=new ObjectEditor(&PrjectPatch,NULL);
        langEdit=new LanguageEditor();
        tabs->addTab(spr->getMain(),"Sprite Editor");
        tabs->addTab(objEdit->getMain(),"Object Editor");
        tabs->addTab(langEdit,"Language Editor");
    }
}
void Widget::OpenModule( QString patch){
#ifdef Q_OS_WIN
    patch.replace('\\','/');
#endif
    if(patch.size()){
        QFile f(patch);
        f.open(QIODevice::ReadOnly);
        QDataStream stream(&f);
        stream>>ProjectTitle;
        stream>>Description;
        ModuleDescript->setText(ProjectTitle);
        f.close();
        projectFuulPatch=patch;
        PrjectPatch=patch.left(patch.lastIndexOf('/'));
        moduleInformation->setEnabled(true);
        tabs->setEnabled(true);

        EResursePack::ResursePackDir()=PrjectPatch+"/Resurses.res";
        ELanguage::selectedLang()=PrjectPatch+LANG_ENG;
        initializeTabs();
    }
    QFile f("./temp");
    if(f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QDataStream stream(&f);
        stream<<projectFuulPatch;
        f.close();
    }
}
void Widget::TabChangedElement(int s){
    spr->cashClear();
    objEdit->cashClear();
    switch (s) {
    case SPRITE_EDITOR:
        spr->OnAll();
        break;
    case OBJECT_EDITOR:
        objEdit->OnAll();
        break;
    default:
        break;
    }
    tabs->repaint();
}
void Widget::ExitClick(bool){
    this->close();
}
void Widget::closeEvent(QCloseEvent *){
    SaveProject();
}
Widget::~Widget()
{
    disconnect(tabs,0,0,0);
    delete spr;
    delete objEdit;
}
