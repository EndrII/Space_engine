#include "ERandom.h"

ERandom::ERandom()
{
    srand(time(0));
}
double ERandom::Next() //+++++
{
    return sin(rand());
}
int ERandom::RanBit() //++++++
{
    return rand()%2;
}
int ERandom::Next(const int & range)//+++++
{
    if(range==0) return 0;
    return rand()%range*((range<0)?-1:1);
}
int ERandom::Next(const int& rangeA, const int& rangeB)//+++++
{
    if(rangeA==rangeB)
        return rangeA;
    return rand()%abs(rangeB-rangeA)+((rangeB<rangeA)?rangeB:rangeA);
}
ERandom::~ERandom()
{

}
