void parser_2D(TString RUNRANGE, TString TYPE, TString POSTFIX) {

   TString INPUT_PREFIX = "./runfolder/";
   bool norm2data = true;
   plot(TYPE,norm2data,INPUT_PREFIX,RUNRANGE,POSTFIX);

}

void plot(char* h, bool norm2data, TString prefix, TString RR, TString POSTFIX) {

    TFile* f1 = new TFile(prefix+"DATA"+RR+"CP.root");
    f1->cd();
    TH1D* hdata0 = (TH1D*)gDirectory->Get(TString(h)+POSTFIX);
    TH1D* hdata24 = (TH1D*)gDirectory->Get(TString(h)+"24"+POSTFIX);
    
    TFile* f2 = new TFile(prefix+"DYM_CP.root", "read");
    f2->cd();
    TH1D* hsignal0 = (TH1D*)gDirectory->Get(TString(h)+POSTFIX);
    TH1D* hsignal24 = (TH1D*)gDirectory->Get(TString(h)+"24"+POSTFIX);
    
    TFile* f3 = new TFile(prefix+"QCD_CP_2D_dd.root", "read");
    f3->cd();
    TH1D* hqcd;
    hqcd0  = (TH1D*)gDirectory->Get("hqcd"); //h);
    hqcd24  = (TH1D*)gDirectory->Get("hqcd24"); //h);
    //hqcd24->Scale(1/2000.);

    TFile* f4 = new TFile(prefix+"TT_CP_2D_dd.root", "read");
    f4->cd();
    TH1D* httbar0 = (TH1D*)gDirectory->Get("httbar");
    TH1D* httbar24 = (TH1D*)gDirectory->Get("httbar24");

    TFile* f4_mc = new TFile(prefix+"TT_CP.root", "read");
    f4_mc->cd();
    TH1D* httbar_mc0 = (TH1D*)gDirectory->Get(TString(h)+POSTFIX);
    TH1D* httbar_mc24 = (TH1D*)gDirectory->Get(TString(h)+"24"+POSTFIX);

    TFile* f5 = new TFile(prefix+"TAU_CP.root", "read");
    f5->cd();
    TH1D* hZtautau0 = (TH1D*)gDirectory->Get(TString(h)+POSTFIX);
    TH1D* hZtautau24 = (TH1D*)gDirectory->Get(TString(h)+"24"+POSTFIX);
    
    TFile* f6 = new TFile(prefix+"EWK_CP.root", "read");
    f6->cd();
    TH1D* hWleptonnu0 = (TH1D*)gDirectory->Get(TString(h)+POSTFIX);
    TH1D* hWleptonnu24 = (TH1D*)gDirectory->Get(TString(h)+"24"+POSTFIX);
    
    TFile* f7 = new TFile(prefix+"DIBOSON_CP.root", "read");
    f7->cd();
    TH1D* hDibosons0 = (TH1D*)gDirectory->Get(TString(h)+POSTFIX);
    TH1D* hDibosons24 = (TH1D*)gDirectory->Get(TString(h)+"24"+POSTFIX);
   
    //INCLUDE UNDERFLOW 
    TH1D* hdata = rebinWithOU1_2D(hdata0,hdata24);
    TH1D* hsignal = rebinWithOU1_2D(hsignal0,hsignal24);
    TH1D* hqcd = rebinWithOU1_2D(hqcd0,hqcd24);
    TH1D* httbar = rebinWithOU1_2D(httbar0,httbar24);
    TH1D* httbar_mc = rebinWithOU1_2D(httbar_mc0,httbar_mc24);
    TH1D* hZtautau = rebinWithOU1_2D(hZtautau0,hZtautau24);
    TH1D* hWleptonnu = rebinWithOU1_2D(hWleptonnu0,hWleptonnu24);
    TH1D* hDibosons = rebinWithOU1_2D(hDibosons0,hDibosons24);

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
	    double ttbarNorm = httbar_mc->Integral();
	    const double WleptonnuNorm = hWleptonnu->Integral();
	    const double ZtautauNorm = hZtautau->Integral();
	    const double qcdNorm = hqcd->Integral();
 	    const double dibosonNorm = hDibosons->Integral();
	    const double signalNorm = hsignal->Integral();
 	    double fullMCintegral = ttbarNorm+WleptonnuNorm+ZtautauNorm+qcdNorm+dibosonNorm+signalNorm;

            //repeat the same buty using the data driven non-QCD.
            //Clone the histograms you dont want affected by this, the rest will be overriden
            TH1D* hWleptonnu_copy = (TH1D*)hWleptonnu->Clone();
            TH1D* hZtautau_copy = (TH1D*)hZtautau->Clone();
            TH1D* hDibosons_copy = (TH1D*)hDibosons->Clone();
            TH1D* hqcd_copy = (TH1D*)hqcd->Clone();
            TH1D* hsignal_copy = (TH1D*)hsignal->Clone();

	    httbar_mc->Scale(hdata->Integral()/fullMCintegral);
	    hWleptonnu->Scale(hdata->Integral()/fullMCintegral);
	    hZtautau->Scale(hdata->Integral()/fullMCintegral);
	    hqcd_copy->Scale(hdata->Integral()/fullMCintegral);
	    hsignal_copy->Scale(hdata->Integral()/fullMCintegral);
	    hDibosons->Scale(hdata->Integral()/fullMCintegral);
            normalizeToPeak(httbar_mc, hWleptonnu, hqcd_copy, hZtautau, hsignal_copy, hDibosons, hdata);

            //repeat the same but using the data driven non-QCD.
            ttbarNorm = httbar->Integral();
            fullMCintegral = ttbarNorm+qcdNorm+signalNorm;

            hWleptonnu_copy->Scale(0);
            hZtautau_copy->Scale(0);
            hDibosons_copy->Scale(0);
            hqcd->Scale(hdata->Integral()/fullMCintegral);
            hsignal->Scale(hdata->Integral()/fullMCintegral);
            httbar->Scale(hdata->Integral()/fullMCintegral);

            normalizeToPeak(httbar, hWleptonnu_copy, hqcd, hZtautau_copy, hsignal, hDibosons_copy, hdata);   
    } else {
            cout << "Normalize data to MC instead" << endl;
            const double ttbarNorm = httbar_mc->Integral();
            const double WleptonnuNorm = hWleptonnu->Integral();
            const double ZtautauNorm = hZtautau->Integral();
            const double qcdNorm = hqcd->Integral();
            const double dibosonNorm = hDibosons->Integral();
            const double signalNorm = hsignal->Integral();
            const double fullMCintegral = ttbarNorm+WleptonnuNorm+ZtautauNorm+qcdNorm+dibosonNorm+signalNorm;
            hdata->Scale(fullMCintegral/hdata->Integral());
    }

    //PERFORM  NORM FOR INIT HISTOS
    if (norm2data) {
            double ttbarNorm = httbar_mc0->Integral();
            const double WleptonnuNorm = hWleptonnu0->Integral();
            const double ZtautauNorm = hZtautau0->Integral();
            const double qcdNorm = hqcd0->Integral();
            const double dibosonNorm = hDibosons0->Integral();
            const double signalNorm = hsignal0->Integral();
            double fullMCintegral = ttbarNorm+WleptonnuNorm+ZtautauNorm+qcdNorm+dibosonNorm+signalNorm;

            //repeat the same buty using the data driven non-QCD.
            //Clone the histograms you dont want affected by this, the rest will be overriden
            TH1D* hWleptonnu_copy = (TH1D*)hWleptonnu0->Clone();
            TH1D* hZtautau_copy = (TH1D*)hZtautau0->Clone();
            TH1D* hDibosons_copy = (TH1D*)hDibosons0->Clone();
            TH1D* hqcd_copy = (TH1D*)hqcd0->Clone();
            TH1D* hsignal_copy = (TH1D*)hsignal0->Clone();

            httbar_mc0->Scale(hdata0->Integral()/fullMCintegral);
            hWleptonnu0->Scale(hdata0->Integral()/fullMCintegral);
            hZtautau0->Scale(hdata0->Integral()/fullMCintegral);
            hqcd_copy->Scale(hdata0->Integral()/fullMCintegral);
            hsignal_copy->Scale(hdata0->Integral()/fullMCintegral);
            hDibosons0->Scale(hdata0->Integral()/fullMCintegral);
            normalizeToPeak(httbar_mc0, hWleptonnu0, hqcd_copy, hZtautau0, hsignal_copy, hDibosons0, hdata0);

            //repeat the same but using the data driven non-QCD.
            ttbarNorm = httbar0->Integral();
            fullMCintegral = ttbarNorm+qcdNorm+signalNorm;

            hWleptonnu_copy->Scale(0);
            hZtautau_copy->Scale(0);
            hDibosons_copy->Scale(0);
            hqcd0->Scale(hdata0->Integral()/fullMCintegral);
            hsignal0->Scale(hdata0->Integral()/fullMCintegral);
            httbar0->Scale(hdata0->Integral()/fullMCintegral);

            normalizeToPeak(httbar0, hWleptonnu_copy, hqcd0, hZtautau_copy, hsignal0, hDibosons_copy, hdata0);
    } else {
            cout << "Normalize data to MC instead" << endl;
            const double ttbarNorm = httbar_mc0->Integral();
            const double WleptonnuNorm = hWleptonnu0->Integral();
            const double ZtautauNorm = hZtautau0->Integral();
            const double qcdNorm = hqcd0->Integral();
            const double dibosonNorm = hDibosons0->Integral();
            const double signalNorm = hsignal0->Integral();
            const double fullMCintegral = ttbarNorm+WleptonnuNorm+ZtautauNorm+qcdNorm+dibosonNorm+signalNorm;
            hdata0->Scale(fullMCintegral/hdata0->Integral());
    }

    //add to stack
    TH1D* hstack4fit = (TH1D*)hsignal->Clone();
    hstack4fit->Add(hWleptonnu);
    hstack4fit->Add(hDibosons);
    hstack4fit->Add(httbar);
    hstack4fit->Add(hZtautau);
    hstack4fit->Add(hqcd);

//save important histograms
    TFile* f = new TFile(prefix+"stack4fit_analyse"+TString(h)+POSTFIX+RR+"CP.root","recreate");
    f->cd();

    //resetHisto(hstack4fit);
    //hstack4fit->SetName("stack4fit");
    //hstack4fit->Write();
    //resetHisto(hsignal);
    hsignal0->SetName("hsig_fewz");
    hsignal0->SetTitle("hsig_fewz");
    hsignal0->Write();
    hsignal->SetName("hsig_fewz_r");
    hsignal->SetTitle("hsig_fewz_r");
    hsignal->Write();
    //resetHisto(hqcd);
    hqcd0->SetName("hqcd");
    hqcd0->SetTitle("hqcd_dd");
    hqcd0->Write();
    hqcd->SetName("hqcd_r");
    hqcd->SetTitle("hqcd_dd_r");
    hqcd->Write();
    //resetHisto(hqcd_mc);
    //resetHisto(hZtautau);
    hZtautau0->SetName("hDYtautau");
    hZtautau0->SetTitle("hDYtautau");
    hZtautau0->Write();
    hZtautau->SetName("hDYtautau_r");
    hZtautau->SetTitle("hDYtautau_r");
    hZtautau->Write();
    //resetHisto(hWleptonnu);
    hWleptonnu0->SetName("hWlepton");
    hWleptonnu0->SetTitle("hWlepton");
    hWleptonnu0->Write();
    hWleptonnu->SetName("hWlepton_r");
    hWleptonnu->SetTitle("hWlepton_r");
    hWleptonnu->Write();
    //resetHisto(hDibosons);
    hDibosons0->SetName("hdiboson");
    hDibosons0->SetTitle("hdiboson");
    hDibosons0->Write();
    hDibosons->SetName("hdiboson_r");
    hDibosons->SetTitle("hdiboson_r");
    hDibosons->Write();
    //resetHisto(httbar);
    httbar0->SetName("httbar");
    httbar0->SetTitle("httbar_dd");
    httbar0->Write();
    httbar->SetName("httbar_r");
    httbar->SetTitle("httbar_dd_r");
    httbar->Write();
    //resetHisto(httbar_mc);
    httbar_mc0->SetName("httbar_mc");
    httbar_mc0->SetTitle("httbar_mc");
    httbar_mc0->Write();
    httbar_mc->SetName("httbar_mc_r");
    httbar_mc->SetTitle("httbar_mc_r");
    httbar_mc->Write();
    //resetHisto(hdata);
    hdata0->SetName("hdata");
    hdata0->SetTitle("hdata");
    hdata0->Write();
    hdata->SetName("hdata_r");
    hdata->SetTitle("hdata_r");
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
   int from  = 73;
   int to = 96;
   if (hmc1==156) {
     from  = 73+24;
     to = 96+24;
   }
   double this_mc = hmc1->Integral(from,to)+hmc2->Integral(from,to)+hmc3->Integral(from,to)+hmc4->Integral(from,to)+hmc5->Integral(from,to)+hmc6->Integral(from,to);
   double this_data = hdata->Integral(from,to);
   while(fabs(this_mc/this_data - 1.) > 0.000001) {
      cout << "Iter " << this_mc/this_data << endl;
      hmc1->Scale(this_data/this_mc);
      hmc2->Scale(this_data/this_mc);
      hmc3->Scale(this_data/this_mc);
      hmc4->Scale(this_data/this_mc);
      hmc5->Scale(this_data/this_mc);
      hmc6->Scale(this_data/this_mc);
      this_mc = hmc1->Integral(from,to)+hmc2->Integral(from,to)+hmc3->Integral(from,to)+hmc4->Integral(from,to)+hmc5->Integral(from,to)+hmc6->Integral(from,to);
   }
}


// This replaces the 132 bin histogram with 168, adding 24 rapidity bins at low mass and 12 at high mass.
// It sets the initial 132 bin contents to the ones starting bin number #24
// Here underflow and overflow histograms simply 24 and 12 bin histos correspondingly which are filled for 0-20 GeV mass and 1500-10000 GeV mass
TH1D* rebinWithOU1_2D(TH1D* h_initial, TH1D* underflow) { //, TH1D* overflow) {
        //
        //switch to under-overlow inclusion will be provided by changing the matrix
        // 
        //FIXME right now the final binning is hard coded, and depends on the initial binning
        const int nbins = 156;
        TH1D* h_ou = new TH1D(h_initial->GetName(),h_initial->GetName(),nbins,0,nbins);
        //fill underflow
        for (int i = 0; i < underflow->GetXaxis()->GetNbins(); i++) {
             h_ou->SetBinContent(i+1,underflow->GetBinContent(i+1));
             h_ou->SetBinError(i+1,underflow->GetBinError(i+1));
        }       
        //fill main histogram
        for (int i = 0; i < h_initial->GetXaxis()->GetNbins(); i++) {
             h_ou->SetBinContent(i+1+24,h_initial->GetBinContent(i+1));
             h_ou->SetBinError(i+1+24,h_initial->GetBinError(i+1));
        }
        //fill underflow
        //for (int i = 0; i < overflow->GetXaxis()->GetNbins(); i++) {
        //     h_ou->SetBinContent(i+1+132+24,overflow->GetBinContent(i+1));
        //     h_ou->SetBinError(i+1+132+24,overflow->GetBinError(i+1));
        //}

        return h_ou;

}

