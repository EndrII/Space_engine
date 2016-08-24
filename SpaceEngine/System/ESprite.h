#ifndef ESPARAIT_H
#define ESPARAIT_H
#include <QImage>
#include <QMovie>
#include <QTime>
#include "EError.h"
#include "./SpaceEngine/Objects/ELoadScreen.h"
#include <ctime>
#include <QDataStream>
#include <QFile>
#include <stack>
#include <algorithm>
//#include "EPictureCore.h"
#include <QOpenGLTexture>
#define minFrameTime 16
#define LASTFRAMEPOOLINDEX 2114125312
#define GLOBALLIST static vector<QString> listIncludeFileSprite;
#define LOADED_FILE_SPRITE listIncludeFileSprite
//enum sprite_mod{live,fait,death,custom_1,custom_2,
//               custom_3,custom_4};
//typedef std::stack<sprite_mod> AniStack;
typedef unsigned short us;
typedef unsigned int ui;
/**
 * @brief The PlayMode enum
 * instantly моментальная, однократная прорисовка анимации
 * toBegin дождёться заверщения текущей анимации
 * toEnd дождёться заверщения всех анимаций
 */
enum PlayMode{instantly,toBegin,toEnd};
/**
 * @brief The draw_mode enum
 * Edit_mode - режим для редактирования спрайта (Source не удаляеться)
 * Game_mode - режим для рисовки игры в этом случае source удаляеться после импорта GL
 */
enum draw_mode{Edit_Mode,Game_mode};
/**
 * @brief The modeAnimation enum
 * Default- в стандартном режиме
 * Static- в статическом
 */
enum modeAnimation{DefaultAni,StaticAni};
/**
 * @brief The ESprite class
 * Структура - Спрайт
 * количество анимаций,
 *  длина n анимации,
 * кадр QImage,
 * длина кадра,
 * длина n+1 анимации
 * базовая графическая состовляющая Space Engine
 */

class ESprite:public QObject //klass spraitov s vipolneniem vseh animazii
{
    Q_OBJECT
private:
    bool switcher;//perecluschtel
    bool isBindet;//
    us ID_fileSprite;// unikalinii adree faila spraita vidovaemii sistemoi
    void generateID();
    QFile *file;
    void refreshIndexBeginAnimations(ui index, int mov);//
    bool FrameRender(QImage& A,const QImage&B);//nalogen texturu B na A v zavisimosti ot alpha kanala
    QDataStream *stream;//stream zapisi
    long long int callTime, allTime; //vremya poslednego vizova i vremya ot momenta smeni animazii (nugno dlya nakopleniya)
    QTime timer_; //vnitreni schochik vremeni dlya animazii
    modeAnimation playMode;//regim vosproizvedeniya animazii
    draw_mode mode;//regim risowki
    us CurentAnimationIndex; //индеус выранной анимации
    us CurentFrame,DrawFrame,tempDrawFrame;   // CurentFrame кадр отображаемый в случаи отсуцтвия анимации
                                //DrawFrame рисуемы в данный момент кадр
    std::list<us> animationStack;//ocheredi animazii
    void Clear();
    QOpenGLTexture* Read_(const ui& addres);//chteniye izobrageniy po adresu vernyot uge hotovuyu teksturu.
    bool stopedFlag;// flag ostonovki
    int staticTimeLongFrameAnimation;// dlina animazii v statichiskom regime
    std::vector<QString> AnimationsName;//imena animazii
    std::vector<QImage*> SourceVector;// izobragenie i dlina kadra
    std::vector<ui> nameAdress;// adresa kadrov v faile
    std::vector<us> longFrame;//dlina proigrovaniya kagdogo kadra
    std::vector<ui> base;// basa izobragenii
    std::vector<us> longAnimationsVector;// vector dlin anomazii
    std::vector<us> IndexBeginAnimationsVector;// indxi nachal animazii
    bool loading_test;//test na proverku zanyatosti ekrana zagruski
protected:
    /**
     * @brief getAnimationStackValue
     * @return вернет количество анимаций в стаке
     */
    us getAnimationStackValue();
    /**
     * @brief ReadInFile : читает из файла
     */
    void ReadInFile();//   chtenie iz fail
    /**
     * @brief setPatch
     * изменит файл ресурсов
     */
    void setPatch(const QString&);
    /**
     * @brief WriteToFile : пишет в файл
     */
    void WriteToFile(); // zapis v faila
    /**
     * @brief StartHaviProcess начнет процесс загрузки (начнет показ экрана загруски)
     * @param long_prcess количество выплняемых работ
     * @param nameProzess название выполняемой работы
     */
    bool StartHaviProcess(int long_prcess,const QString&nameProzess);
    /**
     * @brief EndHaviProcess завершит процесс загрузки (прекратит показ экрана загруски)
     */
    void EndHaviProcess(bool);
    /**
     * @brief LoadProcess покажет текушую степень завершения выполняемого процесса
     * @param value номер выполненной работы
     */
    void LoadProcess(ui value, bool test);
public:
    /**
     * @brief ESprite
     * @param patch - путь к файлу спрайта
     * @param mode_ - режим рисовки по умолчаню Game_mode
     */
    explicit ESprite(const QString &patch="none", draw_mode mode_=draw_mode::Game_mode, QObject *ptr=0);
    /**
     * @brief getPatch
     * @return место расположения файла спрайта
     */
    QString getPatch()const;
    /**
     * @brief SourceClear отчистить спрайт нужно для удаления старых изображений
     */
    void SourceClear();
    /**
     * @brief Append - добавит анимацию в спрайт
     * @param gif_img - имя гиф анимации
     * @return вернёт индекс добавленной анимации.
     * -1 если анимация не была добавленна
     */
    int Append(const QString &gif_img , const QString &name="");
    /**
     * @brief Append добавит в анимацию кадр
     * @param indexAnimatoin индекс анимации куда будет добавлен кадр
     * @param img путь к картинке
     * @param position позиция куда добовлять
     * @return вернет позицию куда юыл бобален кадр (если position= -1 вернет размер анимации, если в
     * в кадр бобавить е удалось вернет -1)
     */
    int Append(const ui& indexAnimatoin, const QString& img, const int position=-1);
    /**
     * @brief Append сделанно для удобства
     * @param indexAnimatoin
     * @param img
     * @param position
     * @return
     */
    int Append(const ui& indexAnimatoin, const QImage& img, const int position=-1);
    /**
     * @brief newEmptyAnimation добавит новую пустую анимацию
     * @param name имя новой анимации
     */
    void newEmptyAnimation(const QString& name);
    /**
     * @brief Edit редактирует время длительности анимации
     * @param index индекс анимации
     * @param time время между кадрами анимации в мс
     */
    void Edit(const us &index, const us &time);
    /**
     * @brief Edit редактирует время длительности анимации
     * @param index индекс анимации
     * @param time время между кадрами анимации
     * @param frame редактируемый кадр
     */
    void Edit(const us &index, const us &frame, const us &time);
    /**
     * @brief Edit  редактирует время длительности анимации　всей анимации
     * @param time  время между кадрами анимации в мс
     */
    void Edit(const us &time);
    /**
     * @brief getLongFrame вернет длину воспроизведения выбранного кадра
     * @param index индекс анимации
     * @param frame индекс кадра
     * @return вернет длину воспроизведения выбранного кадра
     */
    ui getLongFrame(const us &index, const us &frame);

    /**
    * @brief Remove_Animation удалит анимацию
    * @param index индекс удаляемой анимации
    */
    void Remove_Animation(const ui &index);
    /**
     * @brief Compress изменит размер длительности анимации
     * может сократить количество кадров в зависимости от пораметров
     * @param animation индекс анимации над которой будет выполняться действие
     * @param frame_sec количество кадров в секунду в анимации
     * @param time_ml_sec длительность анимации
     */
    void Compress(const ui &animation, const ui& frame_sec, const ui time_ml_sec);
    /**
     * @brief Remove_Frame удалит кадр
     * @param AnimationIndex индекс анимации в которой находиться удаемы кадр
     * @param indexFrame номер удаляемого кадра
     */

    void Remove_Frame(const ui& AnimationIndex,const ui&indexFrame);
    /**
     * @brief Remove_Frame то же самое
     * @param FrameIndex индекс удоляемого кадра
     */
    void Remove_Frame(const ui& FrameIndex);
    /**
     * @brief Play запустить анимацию
     * @param index индекс анимации
     * @param PlayMode режим воспроизведения анимации
     */
    void Play(const int& index, const PlayMode &playMode=toBegin);
    /**
     * @brief Replay сбросить все анимации
     */
    void Replay();
    /**
     * @brief setMode режим запуска анимации
     * @param mod режим
     * @param staticTime время для статического режима поумолчанию 0
     */
    void setMode(const modeAnimation&mod,const int &staticTime=0);
    /**
     * @brief getMode
     * @return вернет текущий режим
     */
    modeAnimation getMode();
    /**
     * @brief setCurentFrame установит кадр по умолчанию
     * @param frame индекс кадра
     */
    void setCurentFrame(us frame);
    /**
     * @brief setCurentFrame  установит кадр по умолчанию
     * @param animation  индекс анимации
     * @param frame  индекс кадра
     */
    void setCurentFrame(us animation,ui frame);
    /**
     * @brief render
     * обработка анимации
     */
    void render_sprite();
    /**
     * @brief getBase
     * @return OpenGl список текстур в анимации
     */
    std::vector<ui> *getBase();
    /**
     * @brief getSource
     * @return  вернёт вектор обьектов (кадров не подготовленных для текстурирования)
     */
    std::vector<QImage*>* getSource();
    /**
     * @brief getBeginIndexAnimation
     * @param i индекс анимации
     * @return вернет индекс начала выбронной анимации i
     */
    ui getBeginIndexAnimation(ui i);
    /**
     * @brief getFrame
     * @return вернёт ресуемый кадр
     */
    int getFrame();
    /**
     * @brief newAdresFromFrame установит новый адрес в памяти для текущего рисуемого кадра перед вызовом этого метода нужно вызывать метод start_stop
     * @param ui новый адресс памяти
     * @return вернёт false если в качестве пораметра был принят не верный адресс
     */
    bool newAdresFromFrame(const int &);
    /**
     * @brief stop_start　остановит или запускает все анимации
     * по усолчанию анимации запущены
     */

    void stop(bool);
    /**
     * @brief save перезапишет файл спрайта
     */
    void save();
    /**
     * @brief getCallTimeRender
     * @return время которое отображает сколько данный обьект бездействует
     */
    int getCallTimeRender();
    /**
     * @brief Bind подгрузит из файла необходимые кадры для анимации
     * @param VideoAdressFrame - адресс ячейки для хронения кадра в пулле
     * @return вернет указвтель на QOpenGLTexture которая будет содержать кадр
     */
    QOpenGLTexture* Bind(ui VideoAdressFrame);
    /**
     * @brief getNameAnimation вернет имя анимации
     * @param indexAnimation индекс анимации для которого запрашиваеться имя
     * @return вернет строку с именем анимации
     */
    QString& getNameAnimation(const int&indexAnimation);
    /**
     * @brief getIdFrame
     * @return вернет уникальный адресс рисуемого кадра
     */
    ui getIdFrame();
    /**
     * @brief getIdFile
     * @return  вкрнет уникальный адресс файла спрайта
     */
    us getIdFile();
    /**
     * @brief getLongSprite
     * @return вернёт количество кадров в спрайте
     */
    us getLongSprite()const;
    /**
     * @brief getLongSprite
     * @return вернёт количество кадров в спрайте
     */
    us getLongSprite(us indexAnimation)const;
    /**
     * @brief getValueSprite
     * @return вернет количество анимаций в спрайтевф
     */
    us getValueSprite() const;
    /**
     * @brief renameAnimation перейменует анимацию
     * @param indexAnimation индекс анимации которая будет перейменована
     * @return  вернет true в случее успеха или false правала.
     */
    bool renameAnimation(const ui &indexAnimation, const QString&newName);
    /**
     * @brief moveFrame передвинет кадр
     * @param indexAnimation индекс анимации
     * @param IndexFrame индекс перемещаемого  кадра
     * @param IndexPasteFrame индекс куда кадр будет перемещён
     */
    bool moveFrame(const ui&indexAnimation,const ui& IndexFrame,const ui& IndexPasteFrame);
    /**

     * @brief moveFrame передвинет кадр
     * @param indexAnimation индекс анимации
     * @param IndexPasteAnimation индекс анимации куда будет вставлен кадр
     * @param IndexFrame индекс перемещаемого  кадра
     * @param IndexPasteFrame индекс куда кадр будет перемещён
     */
    bool moveFrame(const ui&indexAnimation,const ui& IndexPasteAnimation,const ui& IndexFrame,const ui& IndexPasteFrame);
    /**
     * @brief rerndre дорисует определённое количество кадров для системной анимации.
     * @param baseSprite основа для повреждений
     */
    void rennderDamageFrame(const ESprite &baseSprite,const ui&frameValue);
    /**
     * @brief copyFrame копирует кадр
     * @param indexAnimation индекс анимации
     * @param IndexFrame индекс копируемого  кадра
     * @param IndexPasteFrame индекс куда кадр будет скопирован
     */
    bool copyFrame(const ui&indexAnimation,const ui& IndexFrame,const ui& IndexPasteFrame);
    /**
     * @brief moveFrame копирует кадр
     * @param indexAnimation индекс анимации
     * @param IndexPasteAnimation индекс анимации куда будет вставлен кадр
     * @param IndexFrame индекс копируемого  кадра
     * @param IndexPasteFrame индекс куда кадр будет скопирован
     */
    bool copyFrame(const ui&indexAnimation,const ui& IndexPasteAnimation,const ui& IndexFrame,const ui& IndexPasteFrame);
    /**
     * @brief connectProgress статический метод подключения обьекта к прогресс бару
     * @param connectObject обьект за которым будет вестись слежка
     * @param bar бар который будет отслеживать выбранный обьект
     */
    static void connectProgress(ESprite *connectObject, ELoadScreen *bar);
    /**
     * @brief disconnectProgress отоеденит процесс и экран загруски
     * @param connectObject обьект за которым будет вестись слежка
     * @param bar  бар который будет отслеживать выбранный обьект
     */
    static void disconnectProgress(ESprite *connectObject, ELoadScreen *bar);
    ~ESprite();
signals:
    void progress(int);
    void progressMaximumChanged(int,QString);
};
#endif // ESPARAIT_H

