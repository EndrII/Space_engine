#ifndef LANGUAGEEDITOR_H
#define LANGUAGEEDITOR_H

#include <QWidget>
#include <QComboBox>
#include <QTextEdit>
#include <Buttons.h>
#include <QDir>
#include <QTextStream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <SpaceEngine/System/ELanguage.h>
class LanguageEditor : public QWidget
{
    Q_OBJECT
private:
    ButtonRegulyar *saveA,*saveB;
    QTextEdit *textA,*textB;
    QString fA,fB;
    QComboBox *boxA,*boxB;
    void write(QComboBox*);
private slots:
    void click(QPushButton*);
    void FileChangedA(QString);
    void FileChangedB(QString);

public:
    explicit LanguageEditor(QWidget *parent = 0);
    ~LanguageEditor();
signals:

public slots:
};

#endif // LANGUAGEEDITOR_H
