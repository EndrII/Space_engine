#include "EGraphicsConfig.h"

EGraphicsConfig::EGraphicsConfig()
{
    Default();
}
void EGraphicsConfig::Default()
{
    Particles=Conf_Medium;
}
void EGraphicsConfig::setQuality(const Quality &Q)
{
    Particles=Q;
}
EGraphicsConfig::~EGraphicsConfig()
{

}

