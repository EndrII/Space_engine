#ifndef ECONFIG
#define ECONFIG
#include "EKord.h"
#include <fstream>
#include <QString>
#include <QFile>
#include <list>
#include "EDefkey.h"
using namespace std;
class EConfig//  class yavlayetsya interfeisom megdu failam nastroyak i prozessom dvigka
{
private:
    bool test;//proverka na nalichie putya k failu

protected:
    int seek;//posiziya chteniya iz faila
    short kol_vo;//kol-vo klavish v igre
    void write(char*object,const short& byte,const short& _long=1);//zapis polya v konez faila nugno dlya peregruzki update i sync
    void read(char*object,const short &byte);//chteni iz faila polya
    void delet();//udalaet fail nastroek nugno dkya novoi zapisi faila;
public:
    EConfig(const char*,const short&);
    EConfig(const EConfig&);
    virtual bool isConnect();//proverit sushestvuet li fail nastroek
    EConfig& operator=(const EConfig&);
    virtual const short& getLength();//vernyot dlinu massiva klavish
    char* name;//imya faila s nastroikami
    EKord windows_skrinn;//razreshenie ekrana
    Qt::Key *keys;//nabor klavish ii ih sootvetztvii
    virtual void Default();//nastroiki po umolchaniyu
    virtual void Update();// obnovlayae sodergimoe nastroek
    virtual void sync();// sinhraniziruet novie nastriiki s failom konfigurazii
    virtual ~EConfig();
};

#endif // ECONFIG

