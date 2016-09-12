#ifndef EFON
#define EFON
#include "EObject.h"
#define SLOI_FON 0.000001
#define FIRST_FON -0.000005
#define SECOND_FON -0.000004
#define THRID_FON -0.000003
class EFon: public EObject//klass predstovlyaet soboi fonovoe izobrogenie
{
    Q_OBJECT
private:
    //float size_;//razmer fona (viberaetsa menishee znachenie)
    float Max;//koofizent razmera fona (dolgen bit >1)
protected:
public:
    explicit EFon(const QString &urlSprite, const float &kf,const float&sloi=FIRST_FON);//konstruktor
    explicit EFon();
    float getMax()const;//vernyot koofizient rzmera fona;
    //float getminsize();
    void setMax(const float &max);//ustanovit kooficent razmera fona
    friend QDataStream& operator >>(QDataStream&,EFon&);
    friend QDataStream& operator <<(QDataStream&,EFon&);
    void render();//otrenderit izobragenie
    ~EFon();
};
#endif // EFON
