#include "EObject.h"
EObject::EObject(QObject *)//:
    //ESprite("void")
{
    PreConstructor("",EKord(0),EKord(0));
}
EObject::EObject(const QString &str, QObject *)
{
    PreConstructor("",EKord(0),EKord(0));
     QFile f(str);
     if(!f.open(QIODevice::ReadOnly)){
         throw EError("file no detected!","EObject::EObject(const QString &str, QObject *ptr):");
     }
     QDataStream stream(&f);
     stream>>*this;
}
EObject::EObject(const QString& createPatch,const EKord& size, const EKord& kord_, const QString &str, draw_mode mode, QObject *ptr):
    ESprite(str,mode,ptr)
{
    PreConstructor(createPatch,size,kord_);
}
void EObject::PreConstructor(const QString& createPatch, const EKord& size, const EKord& kord_){
    keys=new bool[_Key_value];
    for(int i(0);i<_Key_value;i++)
        keys[i]=false;
    massa=1;
    _w=size.X;
    _h=size.Y;
    multiObject=false;
    mx= _x=kord_.X;
    my= _y=kord_.Y;
    _z=0;
    DrawContur=false;
    vertixArrayRefresh();
    contur=new EContur(&_x,&_y,&ugol);
    slave_=this;
    speed=0;
    ugol=0;
    _ugol=0;
    radius=0;
    ElepsedUgol=0;
    Rad=0;
    ratateMode=NoRotate;
    noDraw_flag=false;
    delete_flag=false;
    ignore_flag=false;
    forceRenderFlag=false;
    acceleration=accs;
    playerTarget=NULL;
    movmode=Standart;
    map=NULL;
    _name="No Name Object";
    Objectpatch=createPatch;
    feedback=inSlowRender;
    class_=EOBJECT;
}
void EObject::setAcceleration(const float &A)
{
    acceleration=A;
}
bool EObject::isDrawContur()const{
     return DrawContur;
}
void EObject::setDrawContur(bool b){
    DrawContur=b;
}
void EObject::setName(const QString &name){
    _name=name;
}
void EObject::setContur(EContur *c){
    contur=c;
    contur->setKord(&_x,&_y,&ugol);
}
void EObject::generateThisObject(EResurse *res){
    READ_THIS(res->url());
}
EContur* EObject::getContur()const{
    return contur;
}
void EObject::vertixArrayRefresh(){
    vertixArray[0][0]=-_w/2;
    vertixArray[0][1]=-_h/2;
    vertixArray[0][2]=_z;

    vertixArray[1][0]=+_w/2;
    vertixArray[1][1]=-_h/2;
    vertixArray[1][2]=_z;

    vertixArray[2][0]=+_w/2;
    vertixArray[2][1]=+_h/2;
    vertixArray[2][2]=_z;

    vertixArray[3][0]=-_w/2;
    vertixArray[3][1]=+_h/2;
    vertixArray[3][2]=_z;
}
QDataStream& operator>>(QDataStream&stream,EObject&obj){
    QString temp;
    stream>>temp;
    obj.setPatch(temp);
    short tempEnum;
    stream>>tempEnum;obj.class_=(EObjectNameClass)tempEnum;
    if(obj.contur!=NULL){
        delete obj.contur;
    }
    obj.contur=new EContur();
    stream>>*obj.contur;
    obj.contur->setKord(&obj._x,&obj._y,&obj.ugol);
    stream>>obj.Rad;
    stream>>obj.ElepsedUgol;
    stream>>tempEnum;obj.ratateMode=(Rotate)tempEnum;
    stream>>tempEnum;obj.movmode=(MovMode)tempEnum;
    stream>>obj.massa;
    stream>>obj.speed;
    stream>>obj._x;
    stream>>obj._y;
    stream>>obj._z;
    stream>>obj._h;
    stream>>obj._w;
    stream>>obj.Objectpatch;
    stream>>obj._name;
    obj.vertixArrayRefresh();
    return stream;
}
QDataStream& operator<<(QDataStream&stream,const EObject&obj){
    stream<<obj.getPatch();
    stream<<(short)obj.class_;
    stream<<*obj.contur;
    stream<<obj.Rad;
    stream<<obj.ElepsedUgol;
    stream<<(short)obj.ratateMode;
    stream<<(short)obj.movmode;
    stream<<obj.massa;
    stream<<obj.speed;
    stream<<obj._x;
    stream<<obj._y;
    stream<<obj._z;
    stream<<obj._h;
    stream<<obj._w;
    stream<<obj.Objectpatch;
    stream<<obj._name;
    return stream;
}

void EObject::saveObject(QString patch){
    if(patch.isEmpty()) patch=Objectpatch;
    Objectpatch=patch;
    if(patch.mid(patch.size()-4)!="eobj")
        patch+=".eobj";
    QFile f(patch);
    QDataStream s(&f);
    if(f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        s<<*this;
        f.close();
    }else{
        throw EError("file no detected!","EObject::EObject(const QString &str, QObject *ptr):");
    }
}
EObject* EObject::getSlave() const
{
    return slave_;
}
void EObject::setUgol(const short &u)
{
    ugol=u;
}
void EObject::setSlave(EObject*obj)
{
    slave_=obj;
}
void EObject::setRotateUgol(const float &s)
{
    ElepsedUgol=s;
}
void EObject::setPlayerTaraget(void *p)
{
    playerTarget=p;
}
bool EObject::setMass(const short &m)
{
        massa=m;
        return true;
}
void EObject::setMap(void *m){
    map=m;
}
void EObject::setSpeed(const int &s)
{
    speed=s;
}
void EObject::setKord(const EKord &k)
{
    _x=k.X;
    _y=k.Y;
    mx=k.X;
    my=k.Y;
}
void EObject::setSize(const EKord & s)
{
    _w=s.X;
    _h=s.Y;
    vertixArrayRefresh();
}
void  EObject::setMovMode(const MovMode &m)
{
    movmode=m;
}
void EObject::setFeedBack(const Feedback &f)
{
    feedback=f;
}
float ** EObject::getMatrix(){
    return (float**)vertixArray;
}
void EObject::copy(EObject *obj){
    *this->contur=*obj->contur;
    contur->setKord(&_x,&_y,&ugol);
    this->ElepsedCenter_X=obj->ElepsedCenter_X;
    this->ElepsedCenter_Y=obj->ElepsedCenter_Y;
    this->Rad=obj->Rad;
    this->DrawContur=obj->DrawContur;
    this->ElepsedUgol=obj->ElepsedUgol;
    this->ratateMode=obj->ratateMode;
    this->movmode=obj->movmode;
    this->Objectpatch=obj->Objectpatch;
    this->_name=obj->_name;
    this->acceleration=obj->acceleration;
    this->ugol=obj->ugol;
    this->massa=obj->massa;
    this->radius=obj->radius;
    this->speed=obj->speed;
    this->_x=obj->_x;
    this->_y=obj->_y;
    this->_z=obj->_z;
    this->mx=obj->mx;
    this->my=obj->my;
    this->_w=obj->_w;
    this->_h=obj->_h;
    vertixArrayRefresh();
    this->setPatch(obj->getPatch());
}
void * EObject::getPlayerTarget()
{
    return playerTarget;
}
void EObject::click(Qt::MouseButton){

}
int* EObject::getSlowTime()
{
    return timeSync_slow;
}
int* EObject::getFastTime()
{
    return timeSync;
}
void* EObject::getMap(){
    return slave_->map;
}
Feedback EObject::getFeedBack()
{
    return feedback;
}
EObjectNameClass EObject::getEObjectNameClass()
{
    return class_;
}
MovMode EObject::getMovMode()
{
    return movmode;
}
float EObject::getSloi()const
{
    return _z;
}
int EObject::getMass()
{
    return massa;
}
int EObject::getSpeed()
{
    return speed;
}
EKord EObject::getSize()const{
    return EKord(_w,_h);
}
EKord EObject::getKord()const{
    return EKord(_x,_y);
}
bool EObject::isMultiObject()const{
    return multiObject;
}
float EObject::getUgol()
{
    if(slave_!=this)
        return slave_->ugol+ugol;
    else
        return ugol;
}
bool* EObject::getKeys()
{
    return keys;
}
void EObject::startElepsedMove(float *Center_X,float *Center_Y, const int &Radius, const Rotate rot)
{
    ElepsedCenter_X=Center_X;
    ElepsedCenter_Y=Center_Y;
    Rad=Radius;
    ratateMode=rot;
    this->setMovMode(MoveElepsed);
}
bool EObject::mov_to(const EKord &koordinati)
{
        if(movmode==Standart){
            mx=koordinati.X;
            my=koordinati.Y;
            return true;
        }else{
            return false;
        }

}
bool EObject::mov_to(const EKord &koordinati,const int& _speed)
{
    if(mov_to(koordinati)){
        speed=_speed;
        return true;
    }
    else{
        return false;
    }
}
void EObject::action_Begin(short naprovlenie)
{
    switch (naprovlenie) {
    case _up:{keys[_up]=true;break;}
    case _left:{keys[_left]=true;break;}
    case _down:{keys[_down]=true;break;}
    case _right:{keys[_right]=true;break;}
    default:
        break;
    }
}
void EObject::action_End(short naprovlenie)
{
    switch (naprovlenie) {
    case _up:{keys[_up]=false;break;}
    case _left:{keys[_left]=false;break;}
    case _down:{keys[_down]=false;break;}
    case _right:{keys[_right]=false;break;}
    default:
        break;
    }
}
void EObject::_keyRender()
{
    if(keys[_up])
    {
        radius-=acceleration*Tsync/1000;
        if(abs(radius)>speed) radius=0-speed;
    }
    if(keys[_down])
    {
        radius+=acceleration*Tsync/1000;
        if(abs(radius)>speed) radius=speed;
    }
    ugol-=keys[_left]*Tsync*acceleration/massa;
    ugol+=keys[_right]/massa*Tsync*acceleration;
    if(!keys[_up]&&!keys[_down])
    {
       if(abs(radius)<massa*Tsync/1000) radius=0;
       if(radius>0) radius-=Tsync*acceleration/massa;
       if(radius<0) radius+=Tsync*acceleration/massa;
    }
}
void EObject::_timeRender()
{
    if(slave_->feedback==inFastRender)Tsync=*timeSync;else Tsync=*timeSync_slow;
}
void EObject::render()
{
        _timeRender();
        _keyRender();
        _render();
}
void EObject::update(int *tsync, int *tsyncslow){
    timeSync=tsync;
    timeSync_slow=tsyncslow;
}
void EObject::NormalizeUgol()
{
    if(ugol>360)ugol-=360;
    if(ugol<0)ugol+=360;
    if(_ugol>360)_ugol-=360;
    if(_ugol<0)_ugol+=360;
}
void EObject::NoramlizeUgolSrlrct()
{
    if((ugol+180>_ugol&&ugol<_ugol)||(ugol+180>_ugol+360&&ugol<_ugol+360))
        _ugol+=optimalUgol(acceleration/massa/abs(radius)*Tsync*500);
    else
        _ugol-=optimalUgol(acceleration/massa/abs(radius)*Tsync*500);
}
void EObject::_render()
{
    switch (movmode) {
    case Standart:
    {
        if(slave_->feedback==inFastRender)
        {
            render_sprite();
        }
        _x+=(mx-_x)/1000*Tsync;
        _y+=(my-_y)/1000*Tsync;
        break;
    }
    case Key:
    {
        if(slave_->feedback==inFastRender)
        {
            NormalizeUgol();
            render_sprite();
            if(keys[_up]||keys[_down])
                NoramlizeUgolSrlrct();
        }else
        {
            _ugol=ugol-180;
        }
        mx=_x+radius*cos(_ugol*TO_RADIAN);
        my=_y+radius*sin(_ugol*TO_RADIAN);
        _x+=(mx-_x)/1000*Tsync;
        _y+=(my-_y)/1000*Tsync;
        break;
    }
    case NoMove:
    {
       if(slave_->feedback==inFastRender)
           render_sprite();
       break;
    }
    case NoMovePlus:
    {
        if(slave_->feedback==inFastRender)
        {
            ugol-=keys[_left]*Tsync*acceleration/massa;
            ugol+=keys[_right]/massa*Tsync*acceleration;
            NormalizeUgol();
            render_sprite();
            NoramlizeUgolSrlrct();
        }
       break;
    }
    case MoveElepsed:
    {
        if(slave_->feedback==inFastRender)
        {
            switch (ratateMode) {
            case RotateLeft:
                ugol-=Tsync*acceleration/massa;
                break;
            case RotateRight:
                ugol+=Tsync*acceleration/massa;
                break;
            default:
                break;
            }
            NormalizeUgol();
            render_sprite();
           NoramlizeUgolSrlrct();
        }else
        {
            _ugol=ugol-180;
        }
        ElepsedUgol+=(double)speed/Rad/40.0*Tsync;;
        _x=*ElepsedCenter_X+Rad*cos(ElepsedUgol*TO_RADIAN);
        _y=*ElepsedCenter_Y+Rad*sin(ElepsedUgol*TO_RADIAN);
       break;
    }
    default:
        break;
    }
}
float EObject::optimalUgol(  float u)
{
    if(u>30)u=30;
    return u;
}
float& EObject::x(){
    return _x;
}
float& EObject::y(){
    return _y;
}
float EObject::getW()const{
    return _w;
}
float EObject::getH()const{
    return _h;
}
QString EObject::getObjectPatch(){
    return Objectpatch;
}
QString EObject::getName(){
    return _name;
}
void EObject::setW(const float &w){
    _w=w;
    vertixArrayRefresh();
}
void EObject::setH(const float &h){
    _h=h;
    vertixArrayRefresh();
}
void EObject::setSloi(const float &s){
    _z=s;
    vertixArrayRefresh();
}
EObject::~EObject()
{
  if(keys!=NULL)
      delete[] keys;
  delete contur;
  emit destructed();
}
