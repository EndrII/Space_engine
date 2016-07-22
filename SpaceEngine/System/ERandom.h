#ifndef ERANDOM_H
#define ERANDOM_H
#include <cstdlib>
#include <ctime>
#include <cmath>
class ERandom //generator sluchainih chisel
{
private:
public:
    explicit ERandom();
    int RanBit();// 0-1 int
    double Next(); // 0 - 1 double
    int Next(const int& range); // 0- range  range - neVkluchaetsya
    int Next(const int& rangeA, const int& rangeB); //rangeA-rangeB A- vkluchitelno B -net
    ~ERandom();
};

#endif // ERANDOM_H
