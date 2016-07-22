#include <QApplication>
#include <QMediaPlayer>
int main( int argv,char** args)
{
   // try {
    QApplication app(argv,args);
    return app.exec();
    //}catch(EError r){std::cout<<r.What()<<std::endl;
   // }
}
