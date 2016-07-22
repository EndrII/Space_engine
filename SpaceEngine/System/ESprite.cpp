#include "ESprite.h"
ESprite::ESprite(const QString &patch,draw_mode mode_)
{
    if(patch!="none"){
        if(patch.mid(patch.size()-3)!="spr")
            throw EError("is not sprite","ESprite::ESprite(const QString &patch,draw_mode mode_)");
    }
    file=new QFile(patch);
    stream=new QDataStream(file);
    mode =mode_;
    ID_fileSprite=-1;
    callTime=allTime=0;
    isBindet=false;
    playMode=DefaultAni;
    staticTimeLongFrameAnimation=1000;
    timer_.start();
    CurentFrame=0;
    switcher=true;
    stopedFlag=false;
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
        for(unsigned int i=0;i<longAnimationsVector.size();i++){
               (*stream)<<(us)longAnimationsVector[i];
               for(int j=IndexBeginAnimationsVector[i];j<(longAnimationsVector[i]+IndexBeginAnimationsVector[i]);j++){
                   (*stream)<<*SourceVector[j]<<longFrame[j];
               }
        }
    }else{
        throw EError("sprite mode = Game Mode","void ESprite::WriteToFile(const QString &patch)");
    }
}
void ESprite::Clear(){
    SourceClear();
    base.clear();
    longFrame.clear();
    nameAdress.clear();
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
                base.push_back(0);
            }
        }
        if(mode==Game_mode)
            delete tempI;
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
int ESprite::Append(const ui &indexAnimatoin, const QString &img, const ui position){
   /* if(this->mode==Game_mode){
        throw EError("Sprite mode = Game","void ESprite::Append(const QString &gif_img)");
        return -1;
    }
    if(indexAnimatoin>longAnimationsVector.size()||position>longAnimationsVector[indexAnimation])
        return -1;
    if(position<0){
        SourceVector.insert(SourceVector.begin()+IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin],new QImage(img));
        base.insert(SourceVector.begin()+IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin],LASTFRAMEPOOLINDEX);
        return IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin];
    }
    else{
        SourceVector.insert(SourceVector.begin()+IndexBeginAnimationsVector[indexAnimatoin]+position,new QImage(img));
        base.insert(SourceVector.begin()+IndexBeginAnimationsVector[indexAnimatoin]+position,LASTFRAMEPOOLINDEX);
        return IndexBeginAnimationsVector[indexAnimatoin]+position;
    }*/
       return Append(indexAnimatoin,QImage(img),position);
}
int ESprite::Append(const ui &indexAnimatoin, const QImage &img, const ui position){
    if(this->mode==Game_mode){
        throw EError("Sprite mode = Game","void ESprite::Append(const QString &gif_img)");
        return -1;
    }
    if(indexAnimatoin>longAnimationsVector.size()||position>longAnimationsVector[indexAnimatoin])
        return -1;
    if(!position){
        nameAdress.insert(nameAdress.begin()+IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin],0);
        SourceVector.insert(SourceVector.begin()+IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin],new QImage(img));
        base.insert(base.begin()+IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin],LASTFRAMEPOOLINDEX);
        longFrame.insert(longFrame.begin()+IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin],1000);
        refreshIndexBeginAnimations(indexAnimatoin,1);
        return IndexBeginAnimationsVector[indexAnimatoin]+longAnimationsVector[indexAnimatoin];
    }
    else{
        nameAdress.insert(nameAdress.begin()+IndexBeginAnimationsVector[indexAnimatoin]+position,0);
        SourceVector.insert(SourceVector.begin()+IndexBeginAnimationsVector[indexAnimatoin]+position,new QImage(img));
        base.insert(base.begin()+IndexBeginAnimationsVector[indexAnimatoin]+position,LASTFRAMEPOOLINDEX);
        longFrame.insert(longFrame.begin()+IndexBeginAnimationsVector[indexAnimatoin]+position,1000);
        refreshIndexBeginAnimations(indexAnimatoin,1);
        return IndexBeginAnimationsVector[indexAnimatoin]+position;
    }
}
int ESprite::Append(const QString &gif_img){
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
        for(int i=0;i<temp.frameCount();i++){
            SourceVector.push_back(new QImage(temp.currentImage()));
            longFrame.push_back(temp.nextFrameDelay());
            nameAdress.push_back(0);
            base.push_back(LASTFRAMEPOOLINDEX);
            temp.jumpToNextFrame();
        }
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
void ESprite::Remove_Frame(const ui &AnimationIndex, const ui &indexFrame){
    stopedFlag=true;
    Replay();
    if(mode==Game_mode){
        throw EError("animation \'"+file->fileName().toStdString()+"\' not open for Edit!","void ESprite::Remove_Animation(const int &index)");
        return;
    }
    longFrame.erase(longFrame.begin()+IndexBeginAnimationsVector[AnimationIndex]+indexFrame);
    nameAdress.erase(base.begin()+IndexBeginAnimationsVector[AnimationIndex]+indexFrame);
    base.erase(base.begin()+IndexBeginAnimationsVector[AnimationIndex]+indexFrame);
    delete SourceVector[indexFrame];
    SourceVector.erase(SourceVector.begin()+IndexBeginAnimationsVector[AnimationIndex]+indexFrame);
    refreshIndexBeginAnimations(AnimationIndex,-1);
    stopedFlag=false;
}
void ESprite::Remove_Frame(const ui &FrameIndex){
    stopedFlag=true;
    Replay();
    if(mode==Game_mode){
        throw EError("animation \'"+file->fileName().toStdString()+"\' not open for Edit!","void ESprite::Remove_Animation(const int &index)");
        return;
    }
    nameAdress.erase(nameAdress.begin()+FrameIndex);
    longFrame.erase(longFrame.begin()+FrameIndex);
    base.erase(base.begin()+FrameIndex);
    delete SourceVector[FrameIndex];
    SourceVector.erase(SourceVector.begin()+FrameIndex);
    ui temp=IndexBeginAnimationsVector.size()-1;
    while(IndexBeginAnimationsVector[temp]>FrameIndex){
        temp--;
    }
    refreshIndexBeginAnimations(temp,-1);
    stopedFlag=false;
}
void ESprite::Remove_Animation(const ui &index){
    stopedFlag=true;
    Replay();
    if(longFrame.size()>=index)
        return;
    if(mode==Game_mode){
        throw EError("animation \'"+file->fileName().toStdString()+"\' not open for Edit!","void ESprite::Remove_Animation(const int &index)");
        return;
    }
    else{// утечка памяти по адреску image Source vector
        nameAdress.erase(nameAdress.begin()+IndexBeginAnimationsVector[index],nameAdress.begin()+IndexBeginAnimationsVector[index]+longAnimationsVector[index]);
        longFrame.erase(longFrame.begin()+IndexBeginAnimationsVector[index],longFrame.begin()+IndexBeginAnimationsVector[index]+longAnimationsVector[index]);
        SourceVector.erase(SourceVector.begin()+IndexBeginAnimationsVector[index],SourceVector.begin()+IndexBeginAnimationsVector[index]+longAnimationsVector[index]);
        for(int i=0;i<longAnimationsVector[index];i++)
            delete SourceVector[i+IndexBeginAnimationsVector[index]];
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
        switcher=false;
        animationStack.pop_front();
        break;
    }
    case toBegin:{
        animationStack.push_front(index);
        switcher=false;
        break;
    }
    case toEnd:{
        animationStack.push_back(index);
        switcher=false;
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
    callTime=allTime+timer_.elapsed();
    if(stopedFlag) return;
    if(switcher)
        DrawFrame=CurentFrame;
    else{
        if(playMode==DefaultAni){
            if(timer_.elapsed()>longFrame[DrawFrame]){
                allTime+=timer_.elapsed();
                timer_.restart();
                if(++DrawFrame>=longAnimationsVector[CurentAnimationIndex]){
                    CurentAnimationIndex=animationStack.front();
                    animationStack.pop_front();
                    if(animationStack.empty())
                        switcher=true;
                }
            }
        }else{
            if(timer_.elapsed()>staticTimeLongFrameAnimation){
                allTime+=timer_.elapsed();
                timer_.restart();
                if(++DrawFrame>=longAnimationsVector[CurentAnimationIndex]){
                    CurentAnimationIndex=animationStack.front();
                    animationStack.pop_front();
                    if(animationStack.empty())
                        switcher=true;
                }
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
void ESprite::setCurentFrame(us frame){
    CurentFrame=frame%base.size();
}
std::vector<ui>* ESprite::getBase(){
    return &base;
}
std::vector<QImage *> *ESprite::getSource(){
    return &SourceVector;
}
ui ESprite::getFrame(){
    return base[DrawFrame];
}
bool ESprite::newAdresFromFrame(const ui&u_i){
    if(!u_i)
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
        SourceVector.erase(SourceVector.begin()+IndexBeginAnimationsVector[indexAnimation]+indexFrame);
        base.erase(base.begin()+IndexBeginAnimationsVector[indexAnimation]+indexFrame);
        longFrame.erase(longFrame.begin()+IndexBeginAnimationsVector[indexAnimation]+indexFrame);
        refreshIndexBeginAnimations(indexAnimation,-1);
        SourceVector.insert(SourceVector.begin()+IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp);
        base.insert(base.begin()+IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp1);
        longFrame.insert(longFrame.begin()+IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame,temp2);
        refreshIndexBeginAnimations(indexPasteAnimation,1);

        /*if(IndexBeginAnimationsVector[indexPasteAnimation]+indexPasteFrame>IndexBeginAnimationsVector[indexAnimation]+indexFrame){
        }else{
            refreshIndexBeginAnimations();
        }*/
        return true;
    }
}
bool ESprite::moveFrame(const ui&indexAnimation,const ui& indexFrame,const ui& indexPasteFrame){
    return moveFrame(indexAnimation,indexAnimation,indexFrame,indexPasteFrame);
}
void ESprite::rennderDamageFrame(const ESprite &baseSprite, const ui &frameValue){
    srand(time(0));
    for(ui i=0;i<frameValue;i++){
        QImage *temp= SourceVector[longAnimationsVector[0]];
        ui tempIndex=baseSprite.IndexBeginAnimationsVector.size()*i/longAnimationsVector[0];
        if(!FrameRender(*temp,*(baseSprite.SourceVector[baseSprite.IndexBeginAnimationsVector[tempIndex]+rand()%(baseSprite.getLongSprite(tempIndex))])))
            break;
        Append(0,*temp);
    }
}
void ESprite::refreshIndexBeginAnimations(ui index, ui mov){
    for(ui i=index;i<IndexBeginAnimationsVector.size();i++){
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
                QColor temp=B.pixelColor(i,j);
                temp.setAlpha(A.pixelColor(i,j).alpha());
                A.setPixelColor(i,j,temp);
            }
        }
        return true;
    }else{
        return false;
    }
}
ESprite::~ESprite(){
    delete stream;
    file->close();
    delete file;
    this->Clear();
}
