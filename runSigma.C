#include <iostream>
#include <regex>
#include <string>
#include <cstdlib>

#include "plotSigma.C"

//#include <bits/stdc++.h>

void runSigma(){

  
  ifstream is("files_forsigma.list");
  string str;
  plotSigma t;
  vector<double> rms;
  vector<double> nsigma;
  vector<double> noise;

  TFile *fout = new TFile("rms.root","RECREATE");
  
  while(getline(is, str))
    {
      cout<<""<<endl;
      float genE;
      string fname;
      is >> fname >> genE;
      int fstr = fname.find("#",0);
      if(fstr!=string::npos)
        {
          continue;
        }
      cout<<str<<endl;
      cout<<"genE fname "<<genE<<" "<<fname<<endl;

      ///get Nsigma and noise
      // Find the position of "sigma" and "noise" in the string
      size_t sigmaPos = fname.find("sigma");
      size_t noisePos = fname.find("noise");
      cout<<"sigmaPos : noisePos "<<sigmaPos<<" "<<noisePos<<endl;
      cout<<"length of string "<<fname.length()<<endl;
      // Extract the substring between "noise" and "sigma"
      std::string noiseValueStr = fname.substr(noisePos + 5, fname.length()-(noisePos+6));

      // Convert the substring to a float
      std::istringstream sstream(noiseValueStr);
      float noiseValue;
      sstream >> noiseValue;
      
      
      std::string sigmaValueStr = fname.substr(sigmaPos-3,3);

      sstream = sigmaValueStr;
      float sigmaValue;
      sstream >> sigmaValue;
      


      
      // Print the result
      std::cout << "Sigma Value : Noise Val " << sigmaValue << " "<<noiseValue<<std::endl;
      
      rms.push_back(t.Loop(genE, fname, fout));
      nsigma.push_back(sigmaValue);
      noise.push_back(noiseValue);
      
    }//while(getline(is, str))  
  
  int nrms = rms.size();
  

  TGraph *grms = new TGraph(nrms, &(nsigma[0]), &(rms[0]) );
  grms->SetName("rms");
  grms->SetMarkerStyle(20);
  grms->GetXaxis()->SetTitle("Number of #sigma");
  grms->GetYaxis()->SetTitle("#DeltaE/E (%)");
  grms->Write();
  fout->Write();
  
  
}
