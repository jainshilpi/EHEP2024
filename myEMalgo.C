/// Adapted from Satyaki Bhattacharya's code

const int ncells = 60;
double xmax = 30;

void myEMalgo(){

  
  const int ntrials = 300;
  const int niter = 30;
  const int ngaus = 3;
  


  double sigma = 1.;
  
  //TF1 *f = new TF1("f","gaus",0,ncells);
  TF1 *f1 = new TF1("f1",myGaus,0,ncells,3);
  f1->SetParameter(0,1);
  f1->SetParameter(1,5);
  f1->SetParameter(2, sigma);

  TF1 *f2 = new TF1("f2",myGaus,0,ncells,3);
  f2->SetParameter(0,1);
  f2->SetParameter(1,8);
  f2->SetParameter(2, sigma);


  TF1 *f3 = new TF1("f3",myGaus,0,ncells,3);
  f3->SetParameter(0,1);
  f3->SetParameter(1,15);
  f3->SetParameter(2, sigma);
  

  TF1 *f_est[ngaus];
  int icol[] = {1,2,3,4,5,6,7,8,9,10};
  for(int igaus=0; igaus<ngaus; igaus++){
    f_est[igaus] = new TF1(Form("f%d_est",igaus),myGausWithBW,0,ncells,3);
    f_est[igaus]->SetLineColor(icol[igaus]);
  }


  //TH1F * h = new TH1F("h","",ncells,0,ncells);
  TH1F * h = new TH1F("h","",ncells,0,xmax);

  for(int itrial=0; itrial<ntrials; itrial++){
    
    
    h->Fill(f1->GetRandom());
    
    h->Fill(f2->GetRandom());
    h->Fill(f2->GetRandom());


    h->Fill(f3->GetRandom());
    h->Fill(f3->GetRandom());
    h->Fill(f3->GetRandom());
    
    
  }



}




Double_t myGaus(double *x, double *par){

  double root2pi = sqrt(2.*TMath::Pi());
  Double_t arg = 0;
  if (par[2] != 0) arg = (x[0] - par[1])/par[2];

  Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
  
  return fitval/root2pi;

}



Double_t myGausWithBW(double *x, double *par){

  double binwidth = xmax/ncells;
  double root2pi = sqrt(2.*TMath::Pi());
  Double_t arg = 0;
  if (par[2] != 0) arg = (x[0] - par[1])/par[2];

  Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
  
  return fitval*binwidth/root2pi;

}
