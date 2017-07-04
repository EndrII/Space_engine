#include "widget.h"
#include <QApplication>
//vector<ESpriteBase*>* listIncludeFileSprite;
CORE_DECLARE

int main(int argc, char *argv[])
{
    CORE_INITIALIZE
    QApplication a(argc, argv);
   // listIncludeFileSprite =new vector<ESpriteBase*>();
    //qDebug()<<listIncludeFileSprite;
    Widget w( argc, argv);
    w.show();

    return a.exec();
}
