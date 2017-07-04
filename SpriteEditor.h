#ifndef SPRITEEDITOR_H
#include <QComboBox>
#include <QMessageBox>
#include <QLineEdit>
#include "projectdir.h"
#include "SpaceEngine/SpaceEngine.h"
#include <QFileDialog>
#include <QCheckBox>
#include <QTableWidget>
#include <QLineEdit>
#include <QInputDialog>
#include <QDir>
#include "CompressMenu.h"
#include <QHeaderView>
#include <QColorDialog>
#define SPRITEEDITOR_H
enum shortkey{presed_copy,presed_move,presed_none};
class SpriteEditor : public SpaceEngine
{
    Q_OBJECT
private:
    ELanguage *lang;
    ELoadScreen *log;
    bool ShiftPressd,ctrlPresed,alt;
    QCheckBox *modeTimeC;
    int ugol,lastX;
    int OldCurentFrame;
    QComboBox *ListRenderSprite,*AnimationsIndex;
    QSpinBox *FrameIndex;
    QSpinBox *ofAnimationsIndex,*ofFrameIndex;
    QSpinBox *toAnimationsIndex,*toFrameIndex,*TimeMode,*RenderValue;
    QLabel *AnimationIndexL,*FrameIndexL,*TimeModeL;
    QLabel *ofAnimationIndexL,*ofFrameIndexL,*ofL;
    QLabel *toAnimationIndexL,*toFrameIndexL,*toL;
    EObject * ObjectRender;
    std::list<QLabel*> memorylist;
    QTableWidget *ListFrame;
    ECamera* camera;
    ButtonRegulyar *OpenSpriteButton,*RenameAnimation,*PlayAnimation,*Save,*RenderFrame,
    *ClearAnimation,*MoveFrame,*CopyFrame,*compress,*Bcolor;
    ButtonPlay *AddAnimation,*create,*AddFrame,*addEmpty;
    ButtonRemove *Delete,*RemoveFrame,*RemoveAnimation;
    QWidget *HBoxWidget,*VBoxWidget;
    QString *Projectpatch;
    shortkey shortKey;
    short tempCopyAnimation,tempCopyIndex,tempPasteAnimation,tempPasteIndex;
    void createHorizontalListFrame();
    void createHorizontalMenu();
    void createVerticalMenu();
    void OpenSprite(const QString &patch);//otkroiet sprait iz faila;
    void updateAnimationsList();//obnoviy list animazii
    QStringList readProject();
private slots: 
    void MouseMove(QMouseEvent*);
    void press(QKeyEvent*);
    void release(QKeyEvent*);
    void compressOk(int,int);
    void TimeModeChanged(int);
    void RenderFrameFunction();
    void ModeChanged(int);
    void animationIndexApp();
    void LongAQnimationChanged();
    void updateFrameList(int i);
    void AnimationChanged(QString);
    void LoadSprite();
    void FrameChanged(int,int);
    void CreateSprite();
    void cameraClick(EMouseEvent*);
    void SpriteListChanged(QString s);
    void ClikedButton(QPushButton*);
public:
    explicit SpriteEditor(QString* patchProject, ELanguage *lan, QWidget *parent = 0);
   // void updateSpriteList();//obnovit spryait list
    ~SpriteEditor();
signals:
public slots:
};

#endif // SPRITEEDITOR_H
