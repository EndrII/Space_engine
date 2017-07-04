#include "LanguageEditor.h"

LanguageEditor::LanguageEditor(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *box=new QHBoxLayout;
    QVBoxLayout *left=new QVBoxLayout;
    QHBoxLayout *buttonBox=new QHBoxLayout;
    saveA=new ButtonRegulyar("Save");
    saveA->setShortcut(QKeySequence::Save);
    boxA=new QComboBox();
    buttonBox->addWidget(boxA);
    buttonBox->addWidget(saveA);
    connect(saveA,SIGNAL(clickButton(QPushButton*)),SLOT(click(QPushButton*)));
    connect(boxA,SIGNAL(currentIndexChanged(QString)),SLOT(FileChangedA(QString)));
    textA=new QTextEdit();
    left->addLayout(buttonBox);
    left->addWidget(textA);
    QVBoxLayout *right=new QVBoxLayout;
    buttonBox=new QHBoxLayout;
    saveB=new ButtonRegulyar("Save");
    saveB->setShortcut(QKeySequence::Save);
    boxB=new QComboBox();
    buttonBox->addWidget(boxB);
    buttonBox->addWidget(saveB);
    connect(saveB,SIGNAL(clickButton(QPushButton*)),SLOT(click(QPushButton*)));
    connect(boxB,SIGNAL(currentIndexChanged(QString)),SLOT(FileChangedB(QString)));
    textB=new QTextEdit();
    right->addLayout(buttonBox);
    right->addWidget(textB);
    box->addLayout(left);
    box->addLayout(right);
    this->setLayout(box);
    write(boxA);
    write(boxB);
}
void LanguageEditor::click(QPushButton* b){
    QFile fa(fA);
    if(saveA==b&&fa.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QTextStream stream(&fa);
        stream<<textA->toPlainText();
        fa.close();
    }
    QFile fb(fB);
    if(saveB==b&&fb.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QTextStream stream(&fb);
        stream<<textB->toPlainText();
        fb.close();
    }
}
void LanguageEditor::FileChangedA(QString name){
    QString patch=ELanguage::selectedLang();
    fA=patch.left(patch.lastIndexOf("/"))+"/"+name;
    QFile f(fA);
    if(f.open(QIODevice::ReadOnly)){
        QTextStream stream(&f);
        textA->setText(stream.readAll());
        f.close();
    }
}
void LanguageEditor::FileChangedB(QString name){
    QString patch=ELanguage::selectedLang();
    fB=patch.left(patch.lastIndexOf("/"))+"/"+name;
    QFile f(fB);
    if(f.open(QIODevice::ReadOnly)){
        QTextStream stream(&f);
        textB->setText(stream.readAll());
        f.close();
    }
}
void LanguageEditor::write(QComboBox*b){
    QString patch=ELanguage::selectedLang();
    QDir dir(patch.left(patch.lastIndexOf("/")));
    for(QFileInfo f:dir.entryInfoList(QDir::Files)){
        b->addItem(f.fileName());
    }
}
LanguageEditor::~LanguageEditor(){
}
