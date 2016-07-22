#include "EAiControle.h"

AiControle::AiControle():
    QObject()
{
    forInstinct=new QTimer();
    forInstinct->setInterval(INSTINCT_AI);
    forPilot=new QTimer();
    forPilot->setInterval(PILOT_AI);
    forPlanet=new QTimer();
    forPlanet->setInterval(PLANET_AI);
    forControle=new QTimer();
    forControle->setInterval(CONTROLL_AI);
    forFraction=new QTimer();
    forFraction->setInterval(FRACTION_AI);
    connect(forInstinct,SIGNAL(timeout()),this,SLOT(_forInstinct()));
    connect(forPilot,SIGNAL(timeout()),this,SLOT(_forPilot()));
    connect(forPlanet,SIGNAL(timeout()),this,SLOT(_forPlanet()));
    connect(forControle,SIGNAL(timeout()),this,SLOT(_forControle()));
    connect(forFraction,SIGNAL(timeout()),this,SLOT(_forFraction()));
}
void AiControle::Off()
{
    forInstinct->stop();
    forPilot->stop();
    forPlanet->stop();
    forControle->stop();
    forFraction->stop();
}
void AiControle::On()
{
    forInstinct->start();
    forPilot->start();
    forPlanet->start();
    forControle->start();
    forFraction->start();
}
short AiControle::addAI(EAi *ai)
{
#ifdef QT_DEBUG
     std::vector<EAi*>::iterator temp=std::find(AIlist.begin(),AIlist.end(),ai);
     if(temp==AIlist.end())
     {
         switch (ai->getAiType()) {
         case INSTINCT_AI:{Instinctlist.push_back(ai); break;}
         case PILOT_AI:{Pilotlist.push_back(ai); break;}
         case PLANET_AI:{Planetlist.push_back(ai); break;}
         case CONTROLL_AI:{Controlelist.push_back(ai); break;}
         case FRACTION_AI:{Fractionlist.push_back(ai); break;}
         default:
             break;
         }
         AIlist.push_back(ai);
         return AIlist.size();
     }else
     {
         throw EError(30,"short AiControle::addAI(EAi *ai)");
     }
 #else

    switch (ai->getAiType()) {
    case INSTINCT_AI:{Instinctlist.push_back(ai); break;}
    case PILOT_AI:{Pilotlist.push_back(ai); break;}
    case PLANET_AI:{Planetlist.push_back(ai); break;}
    case CONTROLL_AI:{Controlelist.push_back(ai); break;}
    case FRACTION_AI:{Fractionlist.push_back(ai); break;}
    default:
        break;
    }
    AIlist.push_back(ai);
    return AIlist.size();
 #endif
}
void AiControle::_forInstinct()
{
    for(EAi *i:Instinctlist)
        i->startAI();
}
void AiControle::_forPilot()
{
    for(EAi *i:Pilotlist)
        i->startAI();
}
void AiControle::_forPlanet()
{
    for(EAi *i:Planetlist)
        i->startAI();
}
void AiControle::_forControle()
{
    for(EAi *i:Controlelist)
        i->startAI();
}
void AiControle::_forFraction()
{
    for(EAi *i:Fractionlist)
        i->startAI();
}
std::vector<EAi *> *AiControle::getAiList()
{
    return &AIlist;
}
AiControle::~AiControle()
{

}

