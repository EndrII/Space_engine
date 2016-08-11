#ifndef EAICONTROLE_H
#define EAICONTROLE_H
#include "EAi.h"
#include <QTimer>
class AiControle:QObject//klas uprovleniya vsemi AI
{
    Q_OBJECT
private:
    std::vector<EAi*> AIlist;//spisok obrobativoimih AI
    std::list<EAi*>
                    Instinctlist,//dlya instictov Ai
                    Pilotlist,//dlya pilotov
                    Planetlist,//dlya planet
                    Controlelist,//dlya uprovlyaushih AI
                    Fractionlist;//dlya fraczii
    QTimer *forInstinct,
           *forPilot,
           *forPlanet,
           *forControle,
           *forFraction;
    //spisok vseh potokov Ai raznih kotegorii
private slots:
               void _forInstinct();
               void _forPilot();
               void _forPlanet();
               void _forControle();
               void _forFraction();
protected:
public:
    explicit AiControle();
    short addAI(EAi*);//dobavit Ai i vernyot ego kodovoe imya (ID)
    std::vector<EAi*>* getAiList();//vernyot spisok AI
    void Off();//viclushit AI
    void On();//vkluchit AI
    ~AiControle();
};
#endif // EAICONTROLE_H
