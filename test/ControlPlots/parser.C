void parser(TString RUNRANGE, TString TYPE) {

   TString INPUT_PREFIX = "./runfolder/";
   bool norm2data = true;
   plot(TYPE,norm2data,INPUT_PREFIX,RUNRANGE);

}

void plot(char* h, bool norm2data, TString prefix, TString RR) {

    TFile f1(prefix+"DATA"+RR+"CP.root", "read");
    TH1D* hdata = (TH1D*)f1.Get(h);
    hdata->SetDirectory(0);
    
    TFile f2(prefix+"DYM_CP.root", "read");
    TH1D* hsignal = (TH1D*)f2.Get(TString(h));
    hsignal->SetDirectory(0);
    
    TFile f3(prefix+"QCD_CP_dd.root", "read");
    TH1D* hqcd = (TH1D*)f3.Get("hqcd");
    hqcd->SetDirectory(0);

    TFile f3_mc(prefix+"QCD_CP.root", "read");
    TH1D* hqcd_mc = (TH1D*)f3_mc.Get(h);
    hqcd_mc->SetDirectory(0);

    //FIXME    
    cout << "See the implementation in 2D case!" << endl;
    TFile f4(prefix+"TT_CP.root", "read");
    TH1D* httbar = (TH1D*)f4.Get(h); //"httbar");
    httbar->SetDirectory(0);

    TFile f4_mc(prefix+"TT_CP.root", "read");
    TH1D* httbar_mc = (TH1D*)f4_mc.Get(h);
    httbar_mc->SetDirectory(0);

    TFile f5(prefix+"TAU_CP.root", "read");
    TH1D* hZtautau = (TH1D*)f5.Get(h);
    hZtautau->SetDirectory(0);
    
    TFile f6(prefix+"EWK_CP.root", "read");
    TH1D* hWleptonnu = (TH1D*)f6.Get(h);
    hWleptonnu->SetDirectory(0);
    
    TFile f7(prefix+"DIBOSON_CP.root", "read");
    TH1D* hDibosons = (TH1D*)f7.Get(h);
    hDibosons->SetDirectory(0);
    
    gStyle->SetOptStat(0);
    gStyle->SetPalette(1);
    gROOT->ProcessLine(".L ../tools/setTDRStyle.C");
    setTDRStyle();
    gROOT->SetStyle("tdrStyle");
    gROOT->ForceStyle(true);
    
    // signal
    hsignal->SetLineColor(kOrange);
    hsignal->SetFillColor(kOrange);
    
    // qcd
    hqcd->SetLineColor(9);
    hqcd->SetFillColor(9);

    // tt
    httbar->SetLineColor(kRed+2);
    httbar->SetFillColor(kRed+2);

    // tau
    hZtautau->SetLineColor(kGreen);
    hZtautau->SetFillColor(kGreen);

    // EWK
    hWleptonnu->SetLineColor(38);
    hWleptonnu->SetFillColor(38);

    //hupsilon->SetLineColor(51);
    //hupsilon->SetFillColor(51);

    // diboson
    hDibosons->SetLineColor(40);
    hDibosons->SetFillColor(40);

    //
    //The histograms come properly weighted with priors
    //This would normalize to number of events in data
    //

    if (norm2data) {
	    const double ttbarNorm = httbar->Integral();
	    const double WleptonnuNorm = hWleptonnu->Integral();
	    const double ZtautauNorm = hZtautau->Integral();
	    const double qcdNorm = hqcd_mc->Integral();
 	    const double dibosonNorm = hDibosons->Integral();
	    const double signalNorm = hsignal->Integral();
 	    const double fullMCintegral = ttbarNorm+WleptonnuNorm+ZtautauNorm+qcdNorm+dibosonNorm+signalNorm;

	    httbar->Scale(hdata->Integral()/fullMCintegral);
	    hWleptonnu->Scale(hdata->Integral()/fullMCintegral);
	    hZtautau->Scale(hdata->Integral()/fullMCintegral);
	    hqcd_mc->Scale(hdata->Integral()/fullMCintegral);
	    hsignal->Scale(hdata->Integral()/fullMCintegral);
	    hDibosons->Scale(hdata->Integral()/fullMCintegral);
            normalizeToPeak(httbar, hWleptonnu, hqcd_mc, hZtautau, hsignal, hDibosons, hdata);

    } else {
           //Just do not normalize, for utility purposes, not for the analysis 
    }

    // mc
    TH1D* hmc = (TH1D*)hsignal->Clone();
    hmc->Add(hqcd_mc);
    //hmc->Add(hupsilon);
    hmc->Add(httbar);
    hmc->Add(hZtautau);
    hmc->Add(hWleptonnu);
    hmc->Add(hDibosons);

    //set up ratio check
    TH1D* hratio = (TH1D*)httbar->Clone();
    FindRatio(hratio,hdata,hmc);

    THStack* hstack = new THStack("hstack", "hstack");
    //hstack->Add(hupsilon);
    hstack->Add(hWleptonnu);
    hstack->Add(hDibosons);
    hstack->Add(httbar);
    hstack->Add(hZtautau);
    hstack->Add(hqcd_mc);
    hstack->Add(hsignal);

    std::ostringstream pprint;

    //add to stack
    TH1D* hstack4fit = (TH1D*)hsignal->Clone();
    //hstack->Add(hupsilon);
    hstack4fit->Add(hWleptonnu);
    hstack4fit->Add(hDibosons);
    hstack4fit->Add(httbar);
    hstack4fit->Add(hZtautau);
    hstack4fit->Add(hqcd_mc);

//save important histograms
    TFile* f = new TFile(prefix+"stack4fit_analyse"+TString(h)+RR+"CP.root","recreate");
    f->cd();
    //resetHisto(hstack4fit);
    hmc->SetName("hmc");
    hmc->Write();
    hstack4fit->SetName("stack4fit");
    hstack4fit->Write();
    //resetHisto(hsignal);
    hsignal->SetName("hsig_fewz");
    hsignal->SetTitle("hsig_fewz");
    hsignal->Write();
    //resetHisto(hqcd);
    hqcd->SetName("hqcd");
    hqcd->SetTitle("hqcd_dd");
    hqcd->Write();
    //resetHisto(hqcd_mc);
    hqcd_mc->SetName("hqcd_mc");
    hqcd_mc->SetTitle("hqcd_mc");
    hqcd_mc->Write();
    //resetHisto(hZtautau);
    hZtautau->SetName("hDYtautau");
    hZtautau->SetTitle("hDYtautau");
    hZtautau->Write();
    //resetHisto(hWleptonnu);
    cout << "hWleptonnu norm " << hWleptonnu->Integral() << endl;
    hWleptonnu->SetName("hWlepton");
    hWleptonnu->SetTitle("hWlepton");
    hWleptonnu->Write();
    //resetHisto(hDibosons);
    hDibosons->SetName("hdiboson");
    hDibosons->SetTitle("hdiboson");
    hDibosons->Write();
    //resetHisto(httbar);
    httbar->SetName("httbar");
    httbar->SetTitle("httbar_dd");
    httbar->Write();
    //resetHisto(httbar_mc);
    httbar_mc->SetName("httbar_mc");
    httbar_mc->SetTitle("httbar_mc");
    httbar_mc->Write();
    //resetHisto(hdata);
    hdata->SetName("hdata");
    hdata->SetTitle("hdata");
    hdata->Write();
    f->Close();
}

double Round(double d) {
    double nd = (double) floor(d*10.)/10.;
    return nd;
}

void FindRatio(TH1D* ratio, TH1D* numer, TH1D* denom) {
   for (int ibin = 0; ibin < numer->GetXaxis()->GetNbins()+1;ibin++) {
       if (denom->GetBinContent(ibin+1) != 0) {
                double rat = (double)(numer->GetBinContent(ibin+1)/denom->GetBinContent(ibin+1));
                ratio->SetBinContent(ibin+1,rat);
                ratio->SetBinError(ibin+1,sqrt(numer->GetBinContent(ibin+1))/denom->GetBinContent(ibin+1) - numer->GetBinContent(ibin+1)*sqrt(denom->GetBinContent(ibin+1))/pow(denom->GetBinContent(ibin+1),2));
        } else {
                ratio->SetBinContent(ibin+1,0.);
       }
  }
}


void resetHisto(TH1D* h) {

   for (int i = 0; i < h->GetXaxis()->GetNbins();i++) {
      h->SetBinContent(i+1,0.0);
      h->SetBinError(i+1,0.0);
   }

}

void normalizeToPeak(TH1D* hmc1, TH1D* hmc2, TH1D* hmc3, TH1D* hmc4, TH1D* hmc5, TH1D* hmc6, TH1D* hdata) {
   double this_mc = hmc1->Integral(10,22)+hmc2->Integral(10,22)+hmc3->Integral(10,22)+hmc4->Integral(10,22)+hmc5->Integral(10,22)+hmc6->Integral(10,22);
   double this_data = hdata->Integral(10,22);
   while(fabs(this_mc/this_data - 1.) > 0.000001) {
      cout << "Iter " << this_mc/this_data << endl;
      hmc1->Scale(this_data/this_mc);
      hmc2->Scale(this_data/this_mc);
      hmc3->Scale(this_data/this_mc);
      hmc4->Scale(this_data/this_mc);
      hmc5->Scale(this_data/this_mc);
      hmc6->Scale(this_data/this_mc);
      this_mc = hmc1->Integral(10,22)+hmc2->Integral(10,22)+hmc3->Integral(10,22)+hmc4->Integral(10,22)+hmc5->Integral(10,22)+hmc6->Integral(10,22);
   }
}

