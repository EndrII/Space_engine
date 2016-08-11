#ifndef EERROR_H
#define EERROR_H
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;
class EError //klass oshibok
{
    private:
      int i;//index polomki
      string s,file_; //stroka pod zapis
      void What_();//chto sluchilos
    public:
      EError(const string&I,const string &file);
      EError(const int &I,const string &file);
      std::string What();//chto sluchilos
      int getID();
      void clear();//otchistka log faila
};

#endif // EERROR_H
