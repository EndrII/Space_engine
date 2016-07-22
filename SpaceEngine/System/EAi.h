#ifndef EAI
#define EAI
#include "./SpaceEngine/Objects/EObject.h"
#define INSTINCT_AI 49
//#define TUAREL_AI 88
#define PILOT_AI 505
#define PLANET_AI 3003
#define CONTROLL_AI 6006
#define FRACTION_AI 30008
class EAi:public EObject
{
    Q_OBJECT
private:
    void render();
protected:
    int AiType;//tip Ai
public:
    explicit EAi();
    virtual void setAiType(const int&);//ustonovit tip AI
    virtual int getAiType();//vernyot tip ai
    virtual bool setObject(EObject*);//ustonovit object
    virtual void startAI();//zapusk obrobotki AI
    ~EAi();
};
#endif // EAI

