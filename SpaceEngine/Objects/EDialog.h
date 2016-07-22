#ifndef EDIALOG_H
#define EDIALOG_H
#include "EImage.h"
#include "EButton.h"
#include <QVBoxLayout>
#include "QList"
#include "SpaceEngine/System/EKord.h"
class EDialog: public QWidget
{
    Q_OBJECT
private:
    EImage*img,*Fon;
    QLabel text;

    QVBoxLayout *main;
    QVector<EButton*> *answers;
private slots:
    void _select(QWidget*);
public:
    EDialog(QWidget *ptr, const QString&FonUrl, const QString& Text,
            const QList<QString>&,
            const QString& ImgUrl="",EKord siz=EKord(100,100));
    static void Information(QWidget *ptr, const QString text, const QString &UrlImag="", const EKord &siz=EKord(100,100));
    void resize();
    ~EDialog();
signals:
    void selected(int);//siganl s vibronnim variantom otveta
};

#endif // EDIALOG_H
