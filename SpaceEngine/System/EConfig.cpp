#include "EConfig.h"
EConfig::EConfig(const char*s, const short &i)
{
    seek=0;
    name=new char[255];
    name=(char*)(s);
    if(i<=_Key_value)
    {
        keys=new Qt::Key[i];
        kol_vo=i;
    }else
    {
        keys=new Qt::Key[_Key_value];
        kol_vo=_Key_value;
    }
}
EConfig::EConfig(const EConfig &cfg)
{
    seek=cfg.seek;
    name=new char[255];
    name=cfg.name;
    if(cfg.kol_vo<=_Key_value)
    {
        keys=new Qt::Key[cfg.kol_vo];
        *keys=*cfg.keys;
        kol_vo=cfg.kol_vo;
    }else
    {
        keys=new Qt::Key[_Key_value];
        kol_vo=_Key_value;
    }
    windows_skrinn=cfg.windows_skrinn;
}
bool EConfig::isConnect()
{
    return  QFile(name).exists();
}
void EConfig::Default()
{
    windows_skrinn=QSize(640,480);
    keys[_up]=Qt::Key_Up;
    keys[_left]=Qt::Key_Left;
    keys[_down]=Qt::Key_Down;
    keys[_right]=Qt::Key_Right;
    for(int i(4);i<kol_vo;i++)
    {
        keys[i]=Qt::Key_F35;
    }
}
const short &EConfig::getLength()
{
    return kol_vo;
}
void EConfig::delet()
{
    fstream f;
    f.open(name,ios_base::binary|ios_base::out);
    f.close();
    seek=0;
}
void EConfig::read(char *object, const short &byte)
{
    ifstream f;
    f.open(name,ios_base::binary);
        short a;
        f.seekg(seek);
        f.read((char*)&a,sizeof(a));
        seek+=sizeof(a);
        f.read(object,byte*a);
        seek+=byte*a;
    f.close();
}
void EConfig::write(char *object,const short &byte,const short &_long)
{
    ofstream f;
    f.open(name,ios_base::binary|ios_base::app);
        f.write((char*)&_long,sizeof(_long));
        f.write(object,byte*_long);
    f.close();
}
void EConfig::Update()
{
   read((char*)&kol_vo,sizeof(kol_vo));
   read((char*)&windows_skrinn,sizeof(windows_skrinn));
   read((char*)keys,sizeof(*keys));
   seek=0;
}
void EConfig::sync()
{
   delet();
   write((char*)&kol_vo,sizeof(kol_vo),1);
   write((char*)&windows_skrinn,sizeof(windows_skrinn),1);
   write((char*)keys,sizeof(*keys),kol_vo);
}
 EConfig& EConfig::operator =(const EConfig& n)
{
    this->name=n.name;
    this->kol_vo=n.kol_vo;
    this->windows_skrinn=n.windows_skrinn;
    this->seek=n.seek;
    delete[] keys;
    this->keys=new Qt::Key[kol_vo];
    for(int i(0);i<kol_vo;i++)
    this->keys[i]=n.keys[i];
    return *this;
}
EConfig::~EConfig()
{
    delete[] keys;
}
