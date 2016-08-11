#ifndef EBUTTON
#define EBUTTON
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
class EButton:public QPushButton//igrovaya klavicha
{
    Q_OBJECT
private:
    QPixmap  *Default_,*curent_; //izobrageniya nagatoi i obichnoi klavishi
    bool current;//nagata li klavisha
    QColor presed_;//
    QColor default_;
private slots:
    void presed();//vnutrenii slot dlya obrobotji nagatii klavishi
    void release();//vnutrenii slot dlya obrobotji nagatii klavishi
protected:
    void paintEvent(QPaintEvent*);//sobitie otrisovki
public:
    explicit EButton(const QString &Default, const QString &curent , QWidget*ptr=0);//konstruktor a
    explicit EButton(const QString &Default, const QString &curent, const QString &text ,
                     const QFont&F=QFont("Verdana",24), const QColor &def=QColor(239,199,102,195),
                     const QColor &select=QColor(74,0,38,195), QWidget*ptr=0);//konstruktor b
    ~EButton();
signals:
    void EClick(QWidget*);
};

#endif // EBUTTON

