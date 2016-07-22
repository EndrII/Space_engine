#include "EError.h"
   EError:: EError(const int &I,const string &file)
    {
        i=I;
        What_();
        file_=file;
        fstream f;
        time_t t=time(0);
        f.open("./ErrorLog.txt",ios_base::app|ios_base::out);
        f<<asctime(localtime(&t))<<": \t"<<s<<"  in "<<"("<<file<<")"<<endl;
        f.close();
    }
   EError:: EError(const string &I,const string &file)
    {
        s=I;
        file_=file;
        fstream f;
        time_t t=time(0);
        f.open("./ErrorLog.txt",ios_base::app|ios_base::out);
        f<<asctime(localtime(&t))<<": \t"<<s<<"  in "<<"("<<file<<")"<<endl;
        f.close();
    }
  void EError::clear()
  {
        fstream f;
        f.open("./ErrorLog.txt",ios_base::trunc);
        f.close();
  }
  int EError::getID()
  {
      return i;
  }
  void EError:: What_()
    {
        switch (i) {
        case 0: {s="высота и ширина карты слишком малы они должны быть брльше 100";
            break;}
        case 1:{s="list=NULL";break;}
        case 2:{s="object ne soderget zvukov";break;}
        case 3:{s="object ne soderget zvuka s takim nomerom";break;}
        case 4:{s="object ne soderget zvuka s takim imenem";break;}
        case 5:{s="Map is not detected!";break;}
        case 6:{s="this object is not sprite!";break;}
        case 7:{s="this object is sprite!";break;}
        case 8:{s="in this thread, object is not detected";break;}
        case 9:{s="this pointer [EObject *Obj]=NUUL ";break;}
        case 10:{s="in this thread, object is detected";break;}
        case 11:{s="the camera is not for anyone to follow";;break;}
        case 12:{s="attempt to divide by 0"; break;}
        case 13:{s="is not sprait Object"; break;}
        case 14:{s="frames on sprite >60"; break;}
        case 15:{s="This camera is not here";break;}
        case 16:{s="that there is no camera or card";break;}
        case 17:{s="This map is not here";break;}
        case 18:{s="This map already contains this object";break;}
        case 19:{s="Do not use the camera a card with this object.";break;}
        case 20:{s="Error in Priority";break;}
        case 21:{s="It uses too much memory";break;}
        case 22:{s="the number in the sprite animations exceeds 7 or =0";break;}
        case 23:{s="picture in this object =NULL ";break;}
        case 24:{s="save sprite failed. ";break;}
        case 25:{s="Current file is not Sprite. ";break;}
        case 26:{s="this Effect no using. ";break;}
        case 27:{s="memoory core bot define in this effct ";break;}
        case 28:{s="this Object is not find in SpaceEngine";break;}
        case 29:{s="this Camera is not find in SpaceEngine";break;}
        case 30:{s="this AI been added";break;}
        case 31:{s="FPS<1";break;}
        case 32:{s="system folder is not detected ";break;}
        case 33:{s="in system folder wrong number of png files ";break;}
        case 34:{s="Language file is not detected";break;}
        case 35:{s="Random value \" Min\">Random value \" Max\"";break;}
        case 36:{s="Memory Eskolation (memory leak)";break;}
        case 37:{s="Player Ship=null";break;}
        default:
            break;
        }
    }
  std::string EError:: What()
    {
      return ": \t"+s+"  in ("+file_+")";
    }

