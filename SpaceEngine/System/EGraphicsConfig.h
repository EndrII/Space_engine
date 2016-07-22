#ifndef EGRAPHICSCONFIG_H
#define EGRAPHICSCONFIG_H

enum Quality{Conf_Ultra,Conf_High,Conf_Medium,Conf_Low,Conf_Max_Performance};
class EGraphicsConfig
{
public:
   Quality Particles;
   EGraphicsConfig();
   void Default();//po umolchaniyu
   void setQuality(const Quality& Q);//ustonovit vsyo fraficu na Q
   virtual ~EGraphicsConfig();
};

#endif // EGRAPHICSCONFIG_H
