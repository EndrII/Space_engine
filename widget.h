#ifndef WIDGET_H
#define WIDGET_H

#include <QLineEdit>
#include <QMenuBar>
#include <QTabWidget>
#include <QMainWindow>
#include "SpaceEngine/SpaceEngine.h"
#include "SpriteEditor.h"
#include "ObjectEditor.h"
#include "LanguageEditor.h"
#include "ModuleInformation.h"
#define SPRITE_EDITOR 0
#define OBJECT_EDITOR 1
//extern vector<ESpriteBase*>* listIncludeFileSprite;
class Widget : public QMainWindow
{
    Q_OBJECT
private:
    QAction *exit,*createModule,*openModule,*moduleInformation,*defaultLanguage;
    QLabel *ModuleDescript;
    SpriteEditor *spr;
    ObjectEditor *objEdit;
    LanguageEditor *langEdit;
    QString ProjectTitle,Description;
    void createMenu();
    QString PrjectPatch,projectFuulPatch;
    QTabWidget *tabs;
    void OpenModule(QString patch);
    void initializeTabs();
private slots:
    void resizeEvent(QResizeEvent *);
    void TabChangedElement(int);
    void ExitClick(bool);
    void InformationClick(bool);
    void createClick(bool);
    void defaultLang(bool);
    void OpenClick(bool);
    void closeEvent(QCloseEvent*);
    void SaveProject();
public:
    Widget(int argc, char *argv[],QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
