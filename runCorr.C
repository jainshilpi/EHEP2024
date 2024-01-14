#include <iostream>
#include <regex>
#include <string>
#include <cstdlib>

#include "applyCorrection.C"

//#include <bits/stdc++.h>

void runCorr(){

  string str;
  
  ifstream is("files_forcorr.list");
  applyCorrection t;
  
  while(getline(is, str))
    {
      cout<<""<<endl;
      string corrName;
      string fname;
      is >> fname >> corrName;
      int fstr = fname.find("#",0);
      if(fstr!=string::npos)
        {
          continue;
        }
      cout<<str<<endl;
      cout<<"corrName fname "<<corrName<<" "<<fname<<endl;

      t.Loop(fname, corrName);
    }//while(getline(is, str))  
  
  
}
