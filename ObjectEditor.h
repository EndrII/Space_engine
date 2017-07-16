#ifndef OBJECTEDITOR_H
#define OBJECTEDITOR_H
#include "projectdir.h"
#include "SpaceEngine/SpaceEngine.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include "./Modules/Modules.h"
#include <QColorDialog>
#include <QStackedWidget>
#include "Buttons.h"
class ObjectEditor: public SpaceEngine
{
    Q_OBJECT
private:
    ELanguage *lang;
    ELoadScreen *log;
    EResursePack *pack;
    QCheckBox *ConturEdit,*showHitBox;
    QComboBox *AnimationsIndex,*TypeObject;
    int ugol,lastX;
    bool ShiftPressd,ctrlPresed,alt;
    QLineEdit *ObjectName;
    ButtonRegulyar *OpenObjectButton,*PlayAnimation,*Save,
    *ClearAnimation,*Bcolor;
    ButtonPlay *create;
    QSpinBox *sizeX,*sizeY;
    QLabel *scrollSizeX,*scrollSizeY;
    //void* moduleSlot;
    QWidget * adventSettings;
    QHBoxLayout* ModuleLayout;

    /***********************************modules*************************************************/
    QStackedWidget *module;
    ModuleParalax * moduleParalax;
    ModuleResursObject * moduleResursObject;
    /***********************************endmodules*************************************************/

    ButtonRemove *Delete;
    QWidget* VBoxWidget;
    ECamera *camera;
    EObject * ObjectRender;
    QString *Projectpatch;
    QStringList readProject();
    EKord fromContur(const float &x,const float &y);
    void createVerticalMenu();
    void createHorizontalMenu();
    bool createObject(const QString &patch);
    void openObject(const QString &patch);
    void saveObject();
    void retype(EObjectNameClass type);
    void updateAnimationsList();//obnoviy list animazii
    bool patchTypes(const QString& patch);
private slots:
    void ObjectSizeXChanged(int);
    void ObjectSizeYChanged(int);
    void cameraSizeChanged(EKord&);
    void typeChanged(int);
    void cameraClick(EMouseEvent*);
    void conturShowChanged(int);
    void RenameObject();
    void MouseMove(QMouseEvent*);
    void press(QKeyEvent*);
    void release(QKeyEvent*);
    void ClikedButton(QPushButton*);

public:
    explicit ObjectEditor(QString *patchProject, ELanguage *lan, QWidget *parent=0);
    ~ObjectEditor();
};

#endif // OBJECTEDITOR_H
