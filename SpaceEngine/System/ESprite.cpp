#include "ESprite.h"
ESprite::ESprite(const QString &patch,draw_mode mode_,QObject*ptr):
    QObject(ptr)
{
    QString tempPatch=patch;
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
   // stopedFlag=false;
    if(patch!="none"){
        generateID();
        if(!file->exists())
            WriteToFile();
        else
            ReadInFile();
    }
}
us ESprite::getIdFile(){
    return ID_fileSprite;
}
us ESprite::getAnimationStackValue(){
    return animationStack.size();
}
void ESprite::generateID(){
    GLOBALLIST
    ID_fileSprite=0;
    while(LOADED_FILE_SPRITE.size()!=ID_fileSprite&&LOADED_FILE_SPRITE[ID_fileSprite]!=file->fileName()){
        ID_fileSprite++;
    }
    if(ID_fileSprite==LOADED_FILE_SPRITE.size())
        LOADED_FILE_SPRITE.push_back(file->fileName());
}
void ESprite::WriteToFile(){
    if(mode==Edit_Mode){
        file->open(QIODevice::ReadWrite|QIODevice::Truncate);
        stream->device()->seek(0);
        (*stream)<<(us)longAnimationsVector.size();
        bool temp=StartHaviProcess(longAnimationsVector.size(),"Write");
        for(unsigned int i=0;i<longAnimationsVector.size();i++){
               (*stream)<<(us)longAnimationsVector[i];
               for(int j=IndexBeginAnimationsVector[i];j<(longAnimationsVector[i]+IndexBeginAnimationsVector[i]);j++){
                   (*stream)<<*SourceVector[j]<<longFrame[j];
               }
               LoadProcess(i,temp);
        }
        *stream<<(us)AnimationsName.size();
        for(QString str:AnimationsName){
            (*stream)<<str;
        }
        EndHaviProcess(temp);
    }else{
        throw EError("sprite mode = Game Mode","void ESprite::WriteToFile(const QString &patch)");
    }
}
void ESprite::Clear(){
    SourceClear();
    base.clear();
    longFrame.clear();
    nameAdress.clear();
    AnimationsName.clear();
    longAnimationsVector.clear();
    IndexBeginAnimationsVector.clear();
}
void ESprite::SourceClear(){
    if(mode==Edit_Mode){
        for(QImage* i:SourceVector){
            delete i;
        }
        SourceVector.clear();
    }
}
QString ESprite::getPatch() const{
    return file->fileName();
}
void ESprite::setPatch(const QString &str){
    stopedFlag=true;
    if(file->isOpen())file->close();
    file->setFileName(str);
    if(!file->exists())
        WriteToFile();
    else
        ReadInFile();
    generateID();
    DrawFrame=0;
    animationStack.clear();
    CurentFrame=0;
    stopedFlag=false;
}
void ESprite::ReadInFile(){
    this->Clear();
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
        while(Long>longAnimationsVector.size()){
            *stream>>temp;
            longAnimationsVector.push_back(temp);
            IndexBeginAnimationsVector.push_back(SourceVector.size());
            for(temp;temp>0;temp--){
                if(mode==Edit_Mode)tempI=new QImage;
                nameAdress.push_back(stream->device()->pos());
                *stream>>*tempI;
                *stream>>tempL;
                if(mode==Edit_Mode)SourceVector.push_back(tempI);
                longFrame.push_back(tempL);
                base.push_back(LASTFRAMEPOOLINDEX);
            }
             LoadProcess(longAnimationsVector.size(),resolution);
        }
        us longNames;
        *stream>>longNames;
        QString tempString;
        for(ui i =0;i<longNames;i++){
            (*stream)>>tempString;
            AnimationsName.push_back(tempString);
        }
        if(mode==Game_mode)
            delete tempI;
        EndHaviProcess(resolution);
    }
}
QOpenGLTexture* ESprite::Read_(const ui &addres){
    if(mode==Edit_Mode){
        return new QOpenGLTexture(*(SourceVector[DrawFrame]));
    }else{
        QImage temp;
        stream->device()->seek(addres);
        *stream>>temp;
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
    if(indexAnimatoin>longAnimationsVector.size()||position>longAnimationsVector[indexAnimatoin])
        return -1;
    ui tempAdress=0;
    if(nameAdress.size())
        tempAdress=nameAdress.back()++;
    if(position<0){

        nameAdress.insert(nameAdress.begin()+IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin],tempAdress);
        SourceVector.insert(SourceVector.begin()+IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin],new QImage(img));
        base.insert(base.begin()+IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin],LASTFRAMEPOOLINDEX);
        longFrame.insert(longFrame.begin()+IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin],1000);
        longAnimationsVector[indexAnimatoin]++;
        refreshIndexBeginAnimations(indexAnimatoin,1);
        return IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin];
    }
    else{
        nameAdress.insert(nameAdress.begin()+IndexBeginAnimationsVector[indexAnimatoin]+position,tempAdress);
        SourceVector.insert(SourceVector.begin()+IndexBeginAnimationsVector[indexAnimatoin]+position,new QImage(img));
        base.insert(base.begin()+IndexBeginAnimationsVector[indexAnimatoin]+position,LASTFRAMEPOOLINDEX);
        longFrame.insert(longFrame.begin()+IndexBeginAnimationsVector[indexAnimatoin]+position,1000);
        longAnimationsVector[indexAnimatoin]++;
        refreshIndexBeginAnimations(indexAnimatoin,1);
        return IndexBeginAnimationsVector[indexAnimatoin]+position;
    }
}
void ESprite::newEmptyAnimation(const QString &name){
    if(name=="")return;
    longAnimationsVector.push_back(0);
    IndexBeginAnimationsVector.push_back(longFrame.size());
    if(longAnimationsVector.size()<=1)
        AnimationsName.push_back("System");
    else
        AnimationsName.push_back(name);
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
        longAnimationsVector.push_back(temp.frameCount());
        IndexBeginAnimationsVector.push_back(longFrame.size());
        bool resolution= StartHaviProcess(temp.frameCount(),"Append");
        for(int i=0;i<temp.frameCount();i++){
            SourceVector.push_back(new QImage(temp.currentImage()));
            longFrame.push_back(temp.nextFrameDelay());
            nameAdress.push_back(0);
            base.push_back(LASTFRAMEPOOLINDEX);
            temp.jumpToNextFrame();
            LoadProcess(i,resolution);
        }
        EndHaviProcess(resolution);
    }
    if(name.isEmpty()){
        if(AnimationsName.size())
            AnimationsName.push_back(temp.fileName());
        else
            AnimationsName.push_back("System");
    }
    else{
        if(AnimationsName.size())
            AnimationsName.push_back(name);
        else
            AnimationsName.push_back("System");
    }
    return longAnimationsVector.size()-1;
}
void ESprite::Edit(const us &index, const us &time){
    if(this->mode==Game_mode){
        throw EError("Sprite mode = Game","void ESprite::Edit(const us &index, const us &time)");
        return;
    }
    us temp=IndexBeginAnimationsVector[index];
    for(int i=temp;i<longAnimationsVector[index];i++)
        longFrame[i]=time;
}
void ESprite::Edit(const us &index, const us &frame, const us &time){
    if(this->mode==Game_mode){
        throw EError("Sprite mode = Game","void ESprite::Edit(const us &index, const us &frame, const us &time)");
        return;
    }
    longFrame[IndexBeginAnimationsVector[index]+frame]=time;
}
void ESprite::Edit(const us &time){
    if(this->mode==Game_mode){
        throw EError("Sprite mode = Game","void ESprite::Edit(const us &time)");
        return;
    }
    for(unsigned int i=0;i<longFrame.size();i++){
        longFrame[i]=time;
    }
}
ui ESprite::getLongFrame(const us &index, const us &frame){
    if(playMode)
        return staticTimeLongFrameAnimation;
    else
        return longFrame[IndexBeginAnimationsVector[index]+frame];
}
void ESprite::Remove_Frame(const ui &AnimationIndex, const ui &indexFrame){
    if(IndexBeginAnimationsVector.size()>AnimationIndex&&longAnimationsVector[AnimationIndex]){
        stopedFlag=true;
        Replay();
        if(mode==Game_mode){
            throw EError("animation \'"+file->fileName().toStdString()+"\' not open for Edit!","void ESprite::Remove_Animation(const int &index)");
            return;
        }
        longFrame.erase(longFrame.begin()+IndexBeginAnimationsVector[AnimationIndex]+indexFrame);
        nameAdress.erase(nameAdress.begin()+IndexBeginAnimationsVector[AnimationIndex]+indexFrame);
        base.erase(base.begin()+IndexBeginAnimationsVector[AnimationIndex]+indexFrame);
        delete SourceVector[indexFrame+IndexBeginAnimationsVector[AnimationIndex]];
        SourceVector.erase(SourceVector.begin()+IndexBeginAnimationsVector[AnimationIndex]+indexFrame);
        refreshIndexBeginAnimations(AnimationIndex,-1);
        longAnimationsVector[AnimationIndex]--;
        stopedFlag=false;
    }
}
void ESprite::Remove_Frame(const ui &FrameIndex){
    ui temp=IndexBeginAnimationsVector.size()-1;
    while(IndexBeginAnimationsVector[temp]>FrameIndex){
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
    if(longFrame.size()<=index||index==0)
        return;
    if(mode==Game_mode){
        throw EError("animation \'"+file->fileName().toStdString()+"\' not open for Edit!","void ESprite::Remove_Animation(const int &index)");
        return;
    }
    else{// утечка памяти по адреску image Source vector
        nameAdress.erase(nameAdress.begin()+IndexBeginAnimationsVector[index],nameAdress.begin()+IndexBeginAnimationsVector[index]+longAnimationsVector[index]);
        AnimationsName.erase(AnimationsName.begin()+index);
        longFrame.erase(longFrame.begin()+IndexBeginAnimationsVector[index],longFrame.begin()+IndexBeginAnimationsVector[index]+longAnimationsVector[index]);
        for(int i=0;i<longAnimationsVector[index];i++)
            delete SourceVector[i+IndexBeginAnimationsVector[index]];
        SourceVector.erase(SourceVector.begin()+IndexBeginAnimationsVector[index],SourceVector.begin()+IndexBeginAnimationsVector[index]+longAnimationsVector[index]);
        base.erase(base.begin()+IndexBeginAnimationsVector[index],base.begin()+IndexBeginAnimationsVector[index]+longAnimationsVector[index]);
        IndexBeginAnimationsVector.erase(IndexBeginAnimationsVector.begin()+index);
        for(std::vector<us>::iterator i=IndexBeginAnimationsVector.begin()+index;i!=IndexBeginAnimationsVector.end();i++){
            (*i)=(*i)-=longAnimationsVector[index];
        }
        longAnimationsVector.erase(longAnimationsVector.begin()+index);
    }
    stopedFlag=false;
}
void ESprite::Play(const int &index, const PlayMode &playMode){
    switch(playMode){
    case instantly:{
        CurentAnimationIndex=index;
        DrawFrame=IndexBeginAnimationsVector[index];
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
        if(timer_.elapsed()>((playMode)?staticTimeLongFrameAnimation:longFrame[DrawFrame])){
            timer_.restart();
            if(switcher){
                CurentAnimationIndex=animationStack.front();
                DrawFrame=IndexBeginAnimationsVector[CurentAnimationIndex];
                switcher=false;
            }
            if(++DrawFrame>=IndexBeginAnimationsVector[CurentAnimationIndex]+longAnimationsVector[CurentAnimationIndex]){
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
    CurentFrame=frame%base.size();
}
void ESprite::setCurentFrame(us animation,ui frame){
    frame+=IndexBeginAnimationsVector[animation];
    CurentFrame=frame%base.size();
}
std::vector<ui>* ESprite::getBase(){
    return &base;
}
std::vector<QImage *> *ESprite::getSource(){
    return &SourceVector;
}
ui ESprite::getBeginIndexAnimation(ui i){
    return IndexBeginAnimationsVector[i];
}
int ESprite::getFrame(){
    if(base.empty())
        return -1;
    else
        return base[DrawFrame];
}
bool ESprite::newAdresFromFrame(const int&u_i){
    if(u_i<0)
        return false;
    else{
        base[DrawFrame]=u_i;
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
        base[DrawFrame]=VideoAdressFrame;
        if(mode!=Edit_Mode)
            return Read_(nameAdress[DrawFrame]);
        else
            return Read_(0);
}
QString& ESprite::getNameAnimation(const int &indexAnimation){
    return AnimationsName[indexAnimation];
}
ui ESprite::getIdFrame(){
    return nameAdress[DrawFrame]+ID_fileSprite;
}
void ESprite::save(){
    if(mode==Edit_Mode){
        if(file->fileName().mid(file->fileName().size()-3)!="spr"){
            this->setPatch(file->fileName()+".spr");
        }
        this->WriteToFile();
        file->close();
        file->open(QIODevice::ReadWrite);
    }
}
us ESprite::getLongSprite()const{
    return base.size();
}
us ESprite::getLongSprite(us indexAnimation)const{
    return longAnimationsVector[indexAnimation];
}
us ESprite::getValueSprite()const{
    return IndexBeginAnimationsVector.size();
}
bool ESprite::renameAnimation(const ui &indexAnimation,const QString &newName){
    if(indexAnimation==0||indexAnimation>=AnimationsName.size()||newName==""){
        return false;
    }else{
        AnimationsName[indexAnimation]=newName;
        return true;
    }
}
bool ESprite::moveFrame(const ui&indexAnimation,const ui &indexPasteAnimation,const ui& indexFrame,const ui& indexPasteFrame){
    if(mode!=Edit_Mode)
        throw EError("sprite mode = Game Mode","void ESprite::WriteToFile(const QString &patch)");
    if(indexAnimation>=IndexBeginAnimationsVector.size()||indexPasteAnimation>=IndexBeginAnimationsVector.size()||
            indexFrame>=longAnimationsVector[indexAnimation]||indexPasteFrame>=longAnimationsVector[indexPasteAnimation]){
        return false;
    }else{
        QImage* temp=SourceVector[IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        ui temp1=base[IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        us temp2=longFrame[IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        ui temp3=nameAdress[IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        SourceVector.erase(SourceVector.begin()+IndexBeginAnimationsVector[indexAnimation]+indexFrame);
        base.erase(base.begin()+IndexBeginAnimationsVector[indexAnimation]+indexFrame);
        longFrame.erase(longFrame.begin()+IndexBeginAnimationsVector[indexAnimation]+indexFrame);
        nameAdress.erase(nameAdress.begin()+IndexBeginAnimationsVector[indexAnimation]+indexFrame);
        longAnimationsVector[indexAnimation]--;
        refreshIndexBeginAnimations(indexAnimation,-1);
        SourceVector.insert(SourceVector.begin()+IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp);
        base.insert(base.begin()+IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp1);
        longFrame.insert(longFrame.begin()+IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp2);
        nameAdress.insert(nameAdress.begin()+IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp3);
        refreshIndexBeginAnimations(indexPasteAnimation,1);
        longAnimationsVector[indexPasteAnimation]++;
        return true;
    }
}

bool ESprite::moveFrame(const ui&indexAnimation,const ui& indexFrame,const ui& indexPasteFrame){
    return moveFrame(indexAnimation,indexAnimation,indexFrame,indexPasteFrame);
}
bool ESprite::copyFrame(const ui&indexAnimation,const ui &indexPasteAnimation,const ui& indexFrame,const ui& indexPasteFrame){
    if(mode!=Edit_Mode)
        throw EError("sprite mode = Game Mode","void ESprite::WriteToFile(const QString &patch)");
    if(indexAnimation>=IndexBeginAnimationsVector.size()||indexPasteAnimation>=IndexBeginAnimationsVector.size()||
            indexFrame>=longAnimationsVector[indexAnimation]||indexPasteFrame>=longAnimationsVector[indexPasteAnimation]){
        return false;
    }else{
        QImage* temp=new QImage(*SourceVector[IndexBeginAnimationsVector[indexAnimation]+indexFrame]);
        ui temp1=base[IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        us temp2=longFrame[IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        ui temp3=nameAdress[IndexBeginAnimationsVector[indexAnimation]+indexFrame];
        SourceVector.insert(SourceVector.begin()+IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp);
        base.insert(base.begin()+IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp1);
        longFrame.insert(longFrame.begin()+IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp2);
        nameAdress.insert(nameAdress.begin()+IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp3);
        refreshIndexBeginAnimations(indexPasteAnimation,1);
        longAnimationsVector[indexPasteAnimation]++;
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
        QImage *temp= SourceVector[longAnimationsVector[0]-1];
        ui tempIndex=baseSprite.IndexBeginAnimationsVector.size()*i/longAnimationsVector[0];
        if(!FrameRender(*temp,*(baseSprite.SourceVector[baseSprite.IndexBeginAnimationsVector[tempIndex]+rand()%(baseSprite.getLongSprite(tempIndex))])))
            break;
        Append(0,*temp);
        LoadProcess(++tempProgres,resolution);
    }
    EndHaviProcess(resolution);
}
void ESprite::refreshIndexBeginAnimations(ui index, int mov){
    for(ui i=index+1;i<IndexBeginAnimationsVector.size();i++){
        IndexBeginAnimationsVector[i]+=mov;
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
ESprite::~ESprite(){
    delete stream;
    file->close();
    delete file;
    this->Clear();
}
