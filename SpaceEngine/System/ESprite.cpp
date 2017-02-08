#include "ESprite.h"
ESpriteBase* ESpriteBase::CopyThis(){
    value++;
    return this;
}
ESpriteBase::ESpriteBase(const QString& patch_){
    patch=patch_;
    value=0;
}
void ESpriteBase::clear(){
    for(QImage* i:SourceVector){
        delete i;
    }
    SourceVector.clear();
    base.clear();
    longFrame.clear();
    nameAdress.clear();
    AnimationsName.clear();
    longAnimationsVector.clear();
    IndexBeginAnimationsVector.clear();
}
bool ESpriteBase::DeleteThis(){
    if(!value--){
        delete this;
        return true;
    }else{
        return false;
    }
}
ESprite::ESprite(const QString &patch,draw_mode mode_,QObject*ptr):
    QObject(ptr)
{
    QString tempPatch=patch;
    GLOBALLIST globalIdData=LOADED_FILE_SPRITE;
    if(patch!="none"){
        if(patch.mid(patch.size()-3)!="spr")
            tempPatch+=".spr";
    }
    loading_test=true;
    file=new QFile(tempPatch);
    stream=new QDataStream(file);
    mode =mode_;
    ID_fileSprite=-1;
    callTime=allTime=0;
    isBindet=false;
    playMode=DefaultAni;
    staticTimeLongFrameAnimation=1000;
    timer_.start();
    loading_test=true;
    CurentAnimationIndex=DrawFrame=CurentFrame=0;
    switcher=true;
    tempDrawFrame=0;
    SpriteBase=NULL;
    if(patch!="none"){
        generateID();
    }
}
draw_mode ESprite::getDrawMode()const{
    return mode;
}
us ESprite::getIdFile(){
    return ID_fileSprite;
}
us ESprite::getAnimationStackValue(){
    return animationStack.size();
}
void ESprite::generateID(){ // в режиме редактирования не выдаються id файлам!
   // GLOBALLIST //this line have a error removies global data
    ID_fileSprite=0;
    while(globalIdData->size()!=ID_fileSprite&&globalIdData->data()[ID_fileSprite]->patch!=file->fileName()){
        ID_fileSprite++;
    }
    if(ID_fileSprite==globalIdData->size()){
        SpriteBase=new ESpriteBase(file->fileName());
        if(mode!=Edit_Mode)
            globalIdData->push_back(SpriteBase);
        if(!file->exists())
            WriteToFile();
        else
            ReadInFile();
    }
    else{
        if(mode!=Edit_Mode){
            SpriteBase=globalIdData->data()[ID_fileSprite]->CopyThis();
        }else{
            SpriteBase=new ESpriteBase(file->fileName());
        }
    }
}
void ESprite::WriteToFile(){
    if(mode==Edit_Mode){
        file->open(QIODevice::ReadWrite|QIODevice::Truncate);
        stream->device()->seek(0);
        (*stream)<<(us)SpriteBase->longAnimationsVector.size();
        bool temp=StartHaviProcess(SpriteBase->longAnimationsVector.size(),"Write");
        for(unsigned int i=0;i<SpriteBase->longAnimationsVector.size();i++){
               (*stream)<<(us)SpriteBase->longAnimationsVector[i];
               for(int j=SpriteBase->IndexBeginAnimationsVector[i];j<(SpriteBase->longAnimationsVector[i]+SpriteBase->IndexBeginAnimationsVector[i]);j++){
                   (*stream)<<*SpriteBase->SourceVector[j]<<SpriteBase->longFrame[j];
               }
               LoadProcess(i,temp);
        }
        *stream<<(us)SpriteBase->AnimationsName.size();
        for(QString str:SpriteBase->AnimationsName){
            (*stream)<<str;
        }
        EndHaviProcess(temp);
        file->close();
    }else{
        throw EError("sprite mode = Game Mode","void ESprite::WriteToFile(const QString &patch)");
    }
}
void ESprite::Clear(){
    if(mode==Edit_Mode)
        SpriteBase->clear();
}
void ESprite::SourceClear(){
    if(mode==Edit_Mode){
        for(QImage* i:SpriteBase->SourceVector){
            delete i;
        }
        SpriteBase->SourceVector.clear();
    }
}
QString ESprite::getPatch() const{
    return file->fileName();
}
void ESprite::setPatch(const QString &str){
    if(str=="none")return;
    stopedFlag=true;
    //if(file->isOpen())file->close();
    file->setFileName(str);
    generateID();
    DrawFrame=0;
    animationStack.clear();
    CurentFrame=0;
    stopedFlag=false;
}
void ESprite::ReadInFile(){
    this->Clear();// this line have a error, clear source images inn this sprite come to crashed programm
    if(!file->exists())
        throw EError("file \""+file->fileName().toStdString() +"\" is not detected","void ESprite::ReadInFile()");
    else{
        if(mode==Edit_Mode)
            file->open(QIODevice::ReadWrite);
        else
            file->open(QIODevice::ReadOnly);
        stream->device()->seek(0);
        us Long,temp,tempL;
        QImage *tempI;
        if(mode==Game_mode)
            tempI=new QImage;
        *stream>>Long;
        bool resolution= StartHaviProcess(Long,"Read Sprite "+file->fileName());
        while(Long>SpriteBase->longAnimationsVector.size()){
            *stream>>temp;
            SpriteBase->longAnimationsVector.push_back(temp);
            SpriteBase->IndexBeginAnimationsVector.push_back(SpriteBase->SourceVector.size());
            for(;temp>0;temp--){
                if(mode==Edit_Mode)tempI=new QImage;
                SpriteBase->nameAdress.push_back(stream->device()->pos());
                *stream>>*tempI;
                *stream>>tempL;
                if(mode==Edit_Mode)SpriteBase->SourceVector.push_back(tempI);
                SpriteBase->longFrame.push_back(tempL);
                SpriteBase->base.push_back(LASTFRAMEPOOLINDEX);
            }
             LoadProcess(SpriteBase->longAnimationsVector.size(),resolution);
        }
        us longNames;
        *stream>>longNames;
        QString tempString;
        for(ui i =0;i<longNames;i++){
            (*stream)>>tempString;
            SpriteBase->AnimationsName.push_back(tempString);
        }
        if(mode==Game_mode)
            delete tempI;
        EndHaviProcess(resolution);
        file->close();
    }
}
QOpenGLTexture* ESprite::Read_(const ui &addres){
    if(mode==Edit_Mode){
        return new QOpenGLTexture(*(SpriteBase->SourceVector[DrawFrame]));
    }else{
        QImage temp;
        file->open(QIODevice::ReadOnly);
        stream->device()->seek(addres);
        *stream>>temp;
        file->close();
        return new QOpenGLTexture(temp);
    }
}
int ESprite::Append(const ui &indexAnimatoin, const QString &img, const int position){
       return Append(indexAnimatoin,QImage(img),position);
}
int ESprite::Append(const ui &indexAnimatoin, const QImage &img, const int position){
    if(this->mode==Game_mode){
        throw EError("Sprite mode = Game","void ESprite::Append(const QString &gif_img)");
        return -1;
    }
    if(indexAnimatoin>SpriteBase->longAnimationsVector.size()||position>SpriteBase->longAnimationsVector[indexAnimatoin])
        return -1;
    ui tempAdress=0;
    while(find(SpriteBase->nameAdress.begin(),SpriteBase->nameAdress.end(),tempAdress)!=SpriteBase->nameAdress.end())
        tempAdress++;
    if(position<0){
        SpriteBase->nameAdress.insert(SpriteBase->nameAdress.begin()+SpriteBase->IndexBeginAnimationsVector[indexAnimatoin]+SpriteBase->longAnimationsVector[indexAnimatoin],tempAdress);
        SpriteBase->SourceVector.insert(SpriteBase->SourceVector.begin()+SpriteBase->IndexBeginAnimationsVector[indexAnimatoin]+SpriteBase->longAnimationsVector[indexAnimatoin],new QImage(img));
        SpriteBase->base.insert(SpriteBase->base.begin()+SpriteBase->IndexBeginAnimationsVector[indexAnimatoin]+SpriteBase->longAnimationsVector[indexAnimatoin],LASTFRAMEPOOLINDEX);
        SpriteBase->longFrame.insert(SpriteBase->longFrame.begin()+SpriteBase->IndexBeginAnimationsVector[indexAnimatoin]+SpriteBase->longAnimationsVector[indexAnimatoin],1000);
        SpriteBase->longAnimationsVector[indexAnimatoin]++;
        refreshIndexBeginAnimations(indexAnimatoin,1);
        return SpriteBase->IndexBeginAnimationsVector[indexAnimatoin]+SpriteBase->longAnimationsVector[indexAnimatoin];
    }
    else{
        SpriteBase->nameAdress.insert(SpriteBase->nameAdress.begin()+SpriteBase->IndexBeginAnimationsVector[indexAnimatoin]+position,tempAdress);
        SpriteBase->SourceVector.insert(SpriteBase->SourceVector.begin()+SpriteBase->IndexBeginAnimationsVector[indexAnimatoin]+position,new QImage(img));
        SpriteBase->base.insert(SpriteBase->base.begin()+SpriteBase->IndexBeginAnimationsVector[indexAnimatoin]+position,LASTFRAMEPOOLINDEX);
        SpriteBase->longFrame.insert(SpriteBase->longFrame.begin()+SpriteBase->IndexBeginAnimationsVector[indexAnimatoin]+position,1000);
        SpriteBase->longAnimationsVector[indexAnimatoin]++;
        refreshIndexBeginAnimations(indexAnimatoin,1);
        return SpriteBase->IndexBeginAnimationsVector[indexAnimatoin]+position;
    }
    emit FrameValueChanged(indexAnimatoin,SpriteBase->longAnimationsVector[indexAnimatoin]);
}
void ESprite::newEmptyAnimation(const QString &name){
    if(name=="")return;
    SpriteBase->longAnimationsVector.push_back(0);
    SpriteBase->IndexBeginAnimationsVector.push_back(SpriteBase->longFrame.size());
    if(SpriteBase->longAnimationsVector.size()<=1)
        SpriteBase->AnimationsName.push_back("System");
    else
        SpriteBase->AnimationsName.push_back(name);
}
int ESprite::Append(const QString &gif_img,const QString&name){
    if(this->mode==Game_mode){
        throw EError("Sprite mode = Game","void ESprite::Append(const QString &gif_img)");
        return -1;
    }
    if(!gif_img.mid(gif_img.size()-3).contains("gif",Qt::CaseInsensitive))
        throw EError("is not gif file","void ESprite::Append(const QString &gif_img)");
    QMovie temp(gif_img);
    temp.stop();
    temp.jumpToFrame(0);
    if(temp.currentFrameNumber()!=0){
        throw EError("number frame error first frame is: "+QString::number(temp.currentFrameNumber()).toStdString(),"void ESprite::Append(const QString &gif_img)");
    }else{
        SpriteBase->longAnimationsVector.push_back(temp.frameCount());
        SpriteBase->IndexBeginAnimationsVector.push_back(SpriteBase->longFrame.size());
        bool resolution= StartHaviProcess(temp.frameCount(),"Append");
        int tempAdress=0;
        for(int i=0;i<temp.frameCount();i++){
            SpriteBase->SourceVector.push_back(new QImage(temp.currentImage()));
            SpriteBase->longFrame.push_back(temp.nextFrameDelay());
            while(find(SpriteBase->nameAdress.begin(),SpriteBase->nameAdress.end(),tempAdress)!=SpriteBase->nameAdress.end())
                tempAdress++;
            SpriteBase->nameAdress.push_back(tempAdress);
            SpriteBase->base.push_back(LASTFRAMEPOOLINDEX);
            temp.jumpToNextFrame();
            LoadProcess(i,resolution);
        }
        EndHaviProcess(resolution);
    }
    if(name.isEmpty()){
        if(SpriteBase->AnimationsName.size())
            SpriteBase->AnimationsName.push_back(temp.fileName());
        else
            SpriteBase->AnimationsName.push_back("System");
    }
    else{
        if(SpriteBase->AnimationsName.size())
            SpriteBase->AnimationsName.push_back(name);
        else
            SpriteBase->AnimationsName.push_back("System");
    }
    emit FrameValueChanged(SpriteBase->longAnimationsVector.size()-1,SpriteBase->longAnimationsVector.back());
    return SpriteBase->longAnimationsVector.size()-1;
}
void ESprite::Edit(const us &index, const us &time){
    if(this->mode==Game_mode){
        throw EError("Sprite mode = Game","void ESprite::Edit(const us &index, const us &time)");
        return;
    }
    us temp=SpriteBase->IndexBeginAnimationsVector[index];
    for(int i=temp;i<SpriteBase->longAnimationsVector[index];i++)
        SpriteBase->longFrame[i]=time;
}
void ESprite::Edit(const us &index, const us &frame, const us &time){
    if(this->mode==Game_mode){
        throw EError("Sprite mode = Game","void ESprite::Edit(const us &index, const us &frame, const us &time)");
        return;
    }
    SpriteBase->longFrame[SpriteBase->IndexBeginAnimationsVector[index]+frame]=time;
}
void ESprite::Edit(const us &time){
    if(this->mode==Game_mode){
        throw EError("Sprite mode = Game","void ESprite::Edit(const us &time)");
        return;
    }
    for(unsigned int i=0;i<SpriteBase->longFrame.size();i++){
        SpriteBase->longFrame[i]=time;
    }
}
ui ESprite::getLongFrame(const us &index, const us &frame){
    if(playMode)
        return staticTimeLongFrameAnimation;
    else
        return SpriteBase->longFrame[SpriteBase->IndexBeginAnimationsVector[index]+frame];
}
void ESprite::Remove_Frame(const ui &AnimationIndex, const ui &indexFrame){
    if(SpriteBase->IndexBeginAnimationsVector.size()>AnimationIndex&&SpriteBase->longAnimationsVector[AnimationIndex]){
        stopedFlag=true;
        Replay();
        if(mode==Game_mode){
            throw EError("animation \'"+file->fileName().toStdString()+"\' not open for Edit!","void ESprite::Remove_Animation(const int &index)");
            return;
        }
        SpriteBase->longFrame.erase(SpriteBase->longFrame.begin()+SpriteBase->IndexBeginAnimationsVector[AnimationIndex]+indexFrame);
        SpriteBase->nameAdress.erase(SpriteBase->nameAdress.begin()+SpriteBase->IndexBeginAnimationsVector[AnimationIndex]+indexFrame);
        SpriteBase->base.erase(SpriteBase->base.begin()+SpriteBase->IndexBeginAnimationsVector[AnimationIndex]+indexFrame);
        delete SpriteBase->SourceVector[indexFrame+SpriteBase->IndexBeginAnimationsVector[AnimationIndex]];
        SpriteBase->SourceVector.erase(SpriteBase->SourceVector.begin()+SpriteBase->IndexBeginAnimationsVector[AnimationIndex]+indexFrame);
        refreshIndexBeginAnimations(AnimationIndex,-1);
        SpriteBase->longAnimationsVector[AnimationIndex]--;
        stopedFlag=false;
    }
}
void ESprite::Remove_Frame(const ui &FrameIndex){
    ui temp=SpriteBase->IndexBeginAnimationsVector.size()-1;
    while(SpriteBase->IndexBeginAnimationsVector[temp]>FrameIndex){
        temp--;
    }
    Remove_Frame(temp,FrameIndex-temp);
}
void ESprite::Compress(const ui& animation,const ui &frame_sec, const ui time_ml_sec){
    if(mode==Game_mode){
        throw EError("animation \'"+file->fileName().toStdString()+"\' not open for Edit!","void ESprite::Remove_Animation(const int &index)");
        return;
    }
    int frameValue=time_ml_sec*frame_sec/1000;
    if(frameValue<getLongSprite(animation)){
        float tempDeleteIndexFrame=1,
            plus=(float)getLongSprite(animation)/(getLongSprite(animation)-frameValue);
        while(frameValue!=getLongSprite(animation)){
            Remove_Frame(animation,tempDeleteIndexFrame);
            tempDeleteIndexFrame+=plus-1;
        }
    }
    int longFram=time_ml_sec/getLongSprite(animation);
    Edit(animation,longFram);
}
void ESprite::Remove_Animation(const ui &index){
    stopedFlag=true;
    Replay();
    if(SpriteBase->longFrame.size()<=index||index==0)
        return;
    if(mode==Game_mode){
        throw EError("animation \'"+file->fileName().toStdString()+"\' not open for Edit!","void ESprite::Remove_Animation(const int &index)");
        return;
    }
    else{// утечка памяти по адреску image Source vector
        SpriteBase->nameAdress.erase(SpriteBase->nameAdress.begin()+SpriteBase->IndexBeginAnimationsVector[index],SpriteBase->nameAdress.begin()+SpriteBase->IndexBeginAnimationsVector[index]+SpriteBase->longAnimationsVector[index]);
        SpriteBase->AnimationsName.erase(SpriteBase->AnimationsName.begin()+index);
        SpriteBase->longFrame.erase(SpriteBase->longFrame.begin()+SpriteBase->IndexBeginAnimationsVector[index],SpriteBase->longFrame.begin()+SpriteBase->IndexBeginAnimationsVector[index]+SpriteBase->longAnimationsVector[index]);
        for(int i=0;i<SpriteBase->longAnimationsVector[index];i++)
            delete SpriteBase->SourceVector[i+SpriteBase->IndexBeginAnimationsVector[index]];
        SpriteBase->SourceVector.erase(SpriteBase->SourceVector.begin()+SpriteBase->IndexBeginAnimationsVector[index],SpriteBase->SourceVector.begin()+SpriteBase->IndexBeginAnimationsVector[index]+SpriteBase->longAnimationsVector[index]);
        SpriteBase->base.erase(SpriteBase->base.begin()+SpriteBase->IndexBeginAnimationsVector[index],SpriteBase->base.begin()+SpriteBase->IndexBeginAnimationsVector[index]+SpriteBase->longAnimationsVector[index]);
        SpriteBase->IndexBeginAnimationsVector.erase(SpriteBase->IndexBeginAnimationsVector.begin()+index);
        for(std::vector<us>::iterator i=SpriteBase->IndexBeginAnimationsVector.begin()+index;i!=SpriteBase->IndexBeginAnimationsVector.end();i++){
            (*i)=(*i)-=SpriteBase->longAnimationsVector[index];
        }
        SpriteBase->longAnimationsVector.erase(SpriteBase->longAnimationsVector.begin()+index);
    }
    stopedFlag=false;
}
void ESprite::Play(const int &index, const PlayMode &playMode){
    switch(playMode){
    case instantly:{
        CurentAnimationIndex=index;
        DrawFrame=SpriteBase->IndexBeginAnimationsVector[index];
        switcher=true;
        animationStack.pop_front();
        break;
    }
    case toBegin:{
        animationStack.push_front(index);
     //   switcher=true;
        break;
    }
    case toEnd:{
        animationStack.push_back(index);
       // switcher=true;
        break;
    }
    default: throw EError("Play Animation Error, playMode is error mode!","void ESprite::Play(const int &index,const &playMode)");
    }
}
void ESprite::Replay(){
    animationStack.clear();
    switcher=true;
}
void ESprite::render_sprite(){
    if(stopedFlag) return;
    if(animationStack.empty())
        DrawFrame=CurentFrame;
    else{
        if(timer_.elapsed()>((playMode)?staticTimeLongFrameAnimation:SpriteBase->longFrame[DrawFrame])){
            timer_.restart();
            if(switcher){
                CurentAnimationIndex=animationStack.front();
                DrawFrame=SpriteBase->IndexBeginAnimationsVector[CurentAnimationIndex];
                switcher=false;
            }
            if(++DrawFrame>=SpriteBase->IndexBeginAnimationsVector[CurentAnimationIndex]+SpriteBase->longAnimationsVector[CurentAnimationIndex]){
                 DrawFrame--;
                 animationStack.pop_front();
                 switcher=true;
            }
        }
    }
}
int ESprite::getCallTimeRender(){
    return allTime+timer_.elapsed()-callTime;
}
void ESprite::setMode(const modeAnimation &mod, const int &staticTime){
        playMode=mod;
        if(staticTime>minFrameTime)
            staticTimeLongFrameAnimation=staticTime;
        else
            staticTimeLongFrameAnimation=minFrameTime;
}
modeAnimation ESprite::getMode(){
    return playMode;
}
void ESprite::setCurentFrame(us frame){
    CurentFrame=frame%SpriteBase->base.size();
}
void ESprite::setCurentFrame(us animation,ui frame){
    frame+=SpriteBase->IndexBeginAnimationsVector[animation];
    CurentFrame=frame%SpriteBase->base.size();
}
std::vector<ui>* ESprite::getBase(){
    return &SpriteBase->base;
}
std::vector<QImage *> *ESprite::getSource(){
    return &SpriteBase->SourceVector;
}
ui ESprite::getBeginIndexAnimation(ui i){
    return SpriteBase->IndexBeginAnimationsVector[i];
}
int ESprite::getFrame(){
    if(SpriteBase->base.empty())
        return -1;
    else
        return SpriteBase->base[DrawFrame];
}
bool ESprite::newAdresFromFrame(const int&u_i){
    if(u_i<0)
        return false;
    else{
        SpriteBase->base[DrawFrame]=u_i;
        return true;
    }
}
void ESprite::stop(bool b){
    stopedFlag=b;
}
/*bool ESprite::isBind(){
    return isBindet;
}*/
QOpenGLTexture* ESprite::Bind(ui VideoAdressFrame){
        SpriteBase->base[DrawFrame]=VideoAdressFrame;
        if(mode!=Edit_Mode)
            return Read_(SpriteBase->nameAdress[DrawFrame]);
        else
            return Read_(0);
}
QString& ESprite::getNameAnimation(const int &indexAnimation){
    return SpriteBase->AnimationsName[indexAnimation];
}
ui ESprite::getIdFrame(){
    return SpriteBase->nameAdress[DrawFrame]+ID_fileSprite;
}
void ESprite::save(){
    if(mode==Edit_Mode){
     //   file->open(QIODevice::ReadOnly);
        if(file->fileName().mid(file->fileName().size()-3)!="spr"){
            this->setPatch(file->fileName()+".spr");
        }
        this->WriteToFile();
    //    file->close();
        //file->open(QIODevice::ReadWrite);
    }
}
us ESprite::getLongSprite()const{
    return SpriteBase->base.size();
}
us ESprite::getLongSprite(us indexAnimation)const{
    return SpriteBase->longAnimationsVector[indexAnimation];
}
us ESprite::getValueSprite()const{
    return SpriteBase->IndexBeginAnimationsVector.size();
}
bool ESprite::renameAnimation(const ui &indexAnimation,const QString &newName){
    if(indexAnimation==0||indexAnimation>=SpriteBase->AnimationsName.size()||newName==""){
        return false;
    }
    SpriteBase->AnimationsName[indexAnimation]=newName;
    return true;
}
bool ESprite::moveFrame(const ui&indexAnimation,const ui &indexPasteAnimation,const ui& indexFrame,const ui& indexPasteFrame){
    if(mode!=Edit_Mode)
        throw EError("sprite mode = Game Mode","void ESprite::WriteToFile(const QString &patch)");
    if(indexAnimation>=SpriteBase->IndexBeginAnimationsVector.size()||indexPasteAnimation>=SpriteBase->IndexBeginAnimationsVector.size()||
            indexFrame>=SpriteBase->longAnimationsVector[indexAnimation]||indexPasteFrame>=SpriteBase->longAnimationsVector[indexPasteAnimation]){
        return false;
    }else{
        QImage* temp=SpriteBase->SourceVector[SpriteBase->IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        ui temp1=SpriteBase->base[SpriteBase->IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        us temp2=SpriteBase->longFrame[SpriteBase->IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        ui temp3=SpriteBase->nameAdress[SpriteBase->IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        SpriteBase->SourceVector.erase(SpriteBase->SourceVector.begin()+SpriteBase->IndexBeginAnimationsVector[indexAnimation]+indexFrame);
        SpriteBase->base.erase(SpriteBase->base.begin()+SpriteBase->IndexBeginAnimationsVector[indexAnimation]+indexFrame);
        SpriteBase->longFrame.erase(SpriteBase->longFrame.begin()+SpriteBase->IndexBeginAnimationsVector[indexAnimation]+indexFrame);
        SpriteBase->nameAdress.erase(SpriteBase->nameAdress.begin()+SpriteBase->IndexBeginAnimationsVector[indexAnimation]+indexFrame);
        SpriteBase->longAnimationsVector[indexAnimation]--;
        refreshIndexBeginAnimations(indexAnimation,-1);
        SpriteBase->SourceVector.insert(SpriteBase->SourceVector.begin()+SpriteBase->IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp);
        SpriteBase->base.insert(SpriteBase->base.begin()+SpriteBase->IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp1);
        SpriteBase->longFrame.insert(SpriteBase->longFrame.begin()+SpriteBase->IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp2);
        SpriteBase->nameAdress.insert(SpriteBase->nameAdress.begin()+SpriteBase->IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp3);
        refreshIndexBeginAnimations(indexPasteAnimation,1);
        SpriteBase->longAnimationsVector[indexPasteAnimation]++;
        return true;
    }
}

bool ESprite::moveFrame(const ui&indexAnimation,const ui& indexFrame,const ui& indexPasteFrame){
    return moveFrame(indexAnimation,indexAnimation,indexFrame,indexPasteFrame);
}
bool ESprite::copyFrame(const ui&indexAnimation,const ui &indexPasteAnimation,const ui& indexFrame,const ui& indexPasteFrame){
    if(mode!=Edit_Mode)
        throw EError("sprite mode = Game Mode","void ESprite::WriteToFile(const QString &patch)");
    if(indexAnimation>=SpriteBase->IndexBeginAnimationsVector.size()||indexPasteAnimation>=SpriteBase->IndexBeginAnimationsVector.size()||
            indexFrame>=SpriteBase->longAnimationsVector[indexAnimation]||indexPasteFrame>=SpriteBase->longAnimationsVector[indexPasteAnimation]){
        return false;
    }else{
        QImage* temp=new QImage(*SpriteBase->SourceVector[SpriteBase->IndexBeginAnimationsVector[indexAnimation]+indexFrame]);
        ui temp1=SpriteBase->base[SpriteBase->IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        us temp2=SpriteBase->longFrame[SpriteBase->IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        ui temp3=SpriteBase->nameAdress[SpriteBase->IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        SpriteBase->SourceVector.insert(SpriteBase->SourceVector.begin()+SpriteBase->IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp);
        SpriteBase->base.insert(SpriteBase->base.begin()+SpriteBase->IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp1);
        SpriteBase->longFrame.insert(SpriteBase->longFrame.begin()+SpriteBase->IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp2);
        SpriteBase->nameAdress.insert(SpriteBase->nameAdress.begin()+SpriteBase->IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp3);
        refreshIndexBeginAnimations(indexPasteAnimation,1);
        SpriteBase->longAnimationsVector[indexPasteAnimation]++;
        return true;
    }
}

bool ESprite::copyFrame(const ui&indexAnimation,const ui& indexFrame,const ui& indexPasteFrame){
    return copyFrame(indexAnimation,indexAnimation,indexFrame,indexPasteFrame);
}
void ESprite::rennderDamageFrame(const ESprite &baseSprite, const ui &frameValue){
    srand(time(0));
    bool resolution=StartHaviProcess(frameValue,"FrameRender");
    ui tempProgres=0;
    for(ui i=0;i<frameValue;i++){
        QImage *temp= SpriteBase->SourceVector[SpriteBase->longAnimationsVector[0]-1];
        ui tempIndex=baseSprite.SpriteBase->IndexBeginAnimationsVector.size()*i/SpriteBase->longAnimationsVector[0];
        if(!FrameRender(*temp,*(baseSprite.SpriteBase->SourceVector[baseSprite.SpriteBase->IndexBeginAnimationsVector[tempIndex]+rand()%(baseSprite.getLongSprite(tempIndex))])))
            break;
        Append(0,*temp);
        LoadProcess(++tempProgres,resolution);
    }
    EndHaviProcess(resolution);
}
void ESprite::refreshIndexBeginAnimations(ui index, int mov){
    for(ui i=index+1;i<SpriteBase->IndexBeginAnimationsVector.size();i++){
        SpriteBase->IndexBeginAnimationsVector[i]+=mov;
    }
}
bool ESprite::FrameRender(QImage &A, const QImage &B){
    if(A.size().height()>B.size().height()&&
            A.size().width()>B.size().width()){
        ui BeginX=rand()%(A.size().width()-B.size().width()+1);
        ui BeginY=rand()%(A.size().height()-B.size().height()+1);
        for(ui i=BeginX;i<B.size().width()+BeginX;i++){
            for(ui j=BeginY;j<B.size().height()+BeginY;j++){
                QColor temp=B.pixelColor(i-BeginX,j-BeginY);
                QColor AColor=A.pixelColor(i,j);
                if(temp.alpha()>100){
                    if(AColor.alphaF()<(1-temp.greenF())){
                        temp.setAlphaF(AColor.alphaF());
                    }else{
                        temp.setAlphaF(1-temp.greenF());
                    }
                    temp.setGreen(0);
                    A.setPixelColor(i,j,temp);
                }
            }
        }
        return true;
    }else{
        return false;
    }
}
bool ESprite::StartHaviProcess(int long_prcess,const QString&nameProzess){
    if(loading_test){
        emit progressMaximumChanged(long_prcess,nameProzess);
        loading_test=false;
        return true;
    }
    return false;
}
void ESprite::LoadProcess(ui value,bool test){
    if(test){
        emit progress(value);
    }
}
void ESprite::EndHaviProcess(bool test){
    if(test){
        loading_test=true;
        emit progress(-1);
    }
}
void ESprite::connectProgress(ESprite *connectObject,ELoadScreen *bar){
    connect(connectObject,SIGNAL(progress(int)),bar,SLOT(progress(int)));
    connect(connectObject,SIGNAL(progressMaximumChanged(int,QString)),bar,SLOT(setmax(int,QString)));
}
void ESprite::disconnectProgress(ESprite *connectObject,ELoadScreen *bar){
    disconnect(connectObject,SIGNAL(progress(int)),bar,SLOT(progress(int)));
    disconnect(connectObject,SIGNAL(progressMaximumChanged(int,QString)),bar,SLOT(setmax(int,QString)));
}
QImage* ESprite::getHeidImage(const QString &patch, const QSize &size){
    QFile f(patch);
    if(f.open(QIODevice::ReadOnly)){
        QDataStream stream_(&f);
        QImage * img_temp=new QImage;
        stream_.device()->seek(8);
        stream_>>*img_temp;
        f.close();
        img_temp->scaled(size);
        return img_temp;
    }
    return NULL;
}
ESprite::~ESprite(){
    delete stream;
   // file->close();
    delete file;
    if(mode==Edit_Mode)
        SpriteBase->clear();
    if(SpriteBase)
        SpriteBase->DeleteThis();
    //this->Clear();
}
