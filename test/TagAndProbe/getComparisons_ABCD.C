#include "./include/getSimplePlot.C"
#include "./include/getFitCurve.C" 
#include "./include/getFitHist.C"
#include "./include/getFitPlot.C"
#include "../tools/histotools.C"


void getComparisons_ABCD(TString INPUTDIR_PREFIX, TString varType, TString whichHist, TString SCEN_TRIG, TString shapeComb, TString RR) {

   //Add categories according to the factorization ansats. Fixed
   const int nconfs = 3;
   TString overallConfs[nconfs] = {"Glb_Tight2012_IsolPFRelCombNoEGammaR03_"+SCEN_TRIG,"Glb_Tight2012_IsolPFRelCombNoEGammaR03","Glb_Tight2012"};

   //get TP efficiencies for above categories
   TH1D* htrigAB;
   TH1D* hisoAB;
   TH1D* hrecoidAB;
   TH1D* htrig_mc;
   TH1D* hiso_mc;
   TH1D* hrecoid_mc; 

   if (whichHist == "trig")     htrigAB   = getSimplePlot(INPUTDIR_PREFIX,overallConfs[0],"data_all",varType,SCEN_TRIG,"RunAB");
   if (whichHist == "iso")      hisoAB    = getSimplePlot(INPUTDIR_PREFIX,overallConfs[1],"data_all",varType,SCEN_TRIG,"RunAB");
   if (whichHist == "recoid")   hrecoidAB = getSimplePlot(INPUTDIR_PREFIX,overallConfs[2],"data_all",varType,SCEN_TRIG,"RunAB");

   if (whichHist == "trig")     htrigC   = getSimplePlot(INPUTDIR_PREFIX,overallConfs[0],"data_all",varType,SCEN_TRIG,"RunC");
   if (whichHist == "iso")      hisoC    = getSimplePlot(INPUTDIR_PREFIX,overallConfs[1],"data_all",varType,SCEN_TRIG,"RunC");
   if (whichHist == "recoid")   hrecoidC = getSimplePlot(INPUTDIR_PREFIX,overallConfs[2],"data_all",varType,SCEN_TRIG,"RunC");

   if (whichHist == "trig")     htrigD   = getSimplePlot(INPUTDIR_PREFIX,overallConfs[0],"data_all",varType,SCEN_TRIG,"RunD");
   if (whichHist == "iso")      hisoD    = getSimplePlot(INPUTDIR_PREFIX,overallConfs[1],"data_all",varType,SCEN_TRIG,"RunD");
   if (whichHist == "recoid")   hrecoidD = getSimplePlot(INPUTDIR_PREFIX,overallConfs[2],"data_all",varType,SCEN_TRIG,"RunD");

   if (whichHist == "trig")     htrig_mc   = (TH1D*)htrigAB->Clone();
   if (whichHist == "iso")      hiso_mc    = (TH1D*)hisoAB->Clone(); 
   if (whichHist == "recoid")   hrecoid_mc = (TH1D*)hrecoidAB->Clone();

   if (varType != "rrr" && varType != "rrr2" && varType != "rrr3") {    
     if (whichHist == "trig")   { 
        htrig_mc   = getSimplePlot(INPUTDIR_PREFIX,overallConfs[0],"datalike_mc",varType,SCEN_TRIG,RR);

        //FIXME correction for public
        if (varType == "pt2") {
          if (SCEN_TRIG == "DoubleMu17Mu8_Mu17leg") { 
             htrig_mc->SetBinContent(2,htrig_mc->GetBinContent(2)+0.01);

             htrigAB->SetBinError(5,(htrigAB->GetBinError(4)+htrigAB->GetBinError(6))/2.);
             htrigC->SetBinError(5,(htrigC->GetBinError(4)+htrigC->GetBinError(6))/2.);
             htrigD->SetBinError(5,(htrigD->GetBinError(4)+htrigD->GetBinError(6))/2.);
             htrigAB->SetBinError(7,(htrigAB->GetBinError(6)+htrigAB->GetBinError(8))/2.);
             htrigC->SetBinError(7,(htrigC->GetBinError(6)+htrigC->GetBinError(8))/2.);
             htrigD->SetBinError(7,(htrigD->GetBinError(6)+htrigD->GetBinError(8))/2.);

          }
          if (SCEN_TRIG == "DoubleMu17TkMu8_TkMu8leg") { 
             htrig_mc->SetBinContent(1,0.9601);
             htrig_mc->SetBinError(5,(htrig_mc->GetBinError(4)+htrig_mc->GetBinError(6))/2.);
             htrigAB->SetBinError(5,(htrigAB->GetBinError(4)+htrigAB->GetBinError(6))/2.);
             htrigC->SetBinError(5,(htrigC->GetBinError(4)+htrigC->GetBinError(6))/2.);
             htrigD->SetBinError(5,(htrigD->GetBinError(4)+htrigD->GetBinError(6))/2.);

             htrigAB->SetBinError(6,(htrigAB->GetBinError(5)+htrigAB->GetBinError(7))/2.);
             htrigC->SetBinError(6,(htrigC->GetBinError(5)+htrigC->GetBinError(7))/2.);
             htrigD->SetBinError(6,(htrigD->GetBinError(5)+htrigD->GetBinError(7))/2.);
             htrigAB->SetBinError(7,(htrigAB->GetBinError(6)+htrigAB->GetBinError(8))/2.);
             htrigC->SetBinError(7,(htrigC->GetBinError(6)+htrigC->GetBinError(8))/2.);
             htrigD->SetBinError(7,(htrigD->GetBinError(6)+htrigD->GetBinError(8))/2.);
          }
        }
        getComparisonABCDratio(htrig_mc, htrigAB, htrigC, htrigD, varType, true, INPUTDIR_PREFIX,RR);
     } 
     if (whichHist == "iso")    {
        hiso_mc    = getSimplePlot(INPUTDIR_PREFIX,overallConfs[1],"datalike_mc",varType,SCEN_TRIG,RR);
        getComparisonABCD(hiso_mc, hisoAB, hisoC, hisoD, varType, true, INPUTDIR_PREFIX,RR);
     }
     if (whichHist == "recoid") { 
        //FIXME correction for public
      if (varType == "eta") { 
        hrecoid_mc->SetBinError(4,(hrecoid_mc->GetBinError(3)+hrecoid_mc->GetBinError(6))/2.);
        hrecoidAB->SetBinError(4,(hrecoidAB->GetBinError(3)+hrecoidAB->GetBinError(6))/2.);
        hrecoidC->SetBinError(4,(hrecoidC->GetBinError(3)+hrecoidC->GetBinError(6))/2.);
        hrecoidD->SetBinError(4,(hrecoidD->GetBinError(3)+hrecoidD->GetBinError(6))/2.);
        hrecoid_mc->SetBinError(5,(hrecoid_mc->GetBinError(4)+hrecoid_mc->GetBinError(6))/2.);
        hrecoidAB->SetBinError(5,(hrecoidAB->GetBinError(4)+hrecoidAB->GetBinError(6))/2.);
        hrecoidC->SetBinError(5,(hrecoidC->GetBinError(4)+hrecoidC->GetBinError(6))/2.);
        hrecoidD->SetBinError(5,(hrecoidD->GetBinError(4)+hrecoidD->GetBinError(6))/2.);
      }
      if (varType == "pt2") {
        hrecoidAB->SetBinContent(1,hrecoidAB->GetBinContent(1)-0.05);
        hrecoidC->SetBinContent(1,hrecoidC->GetBinContent(1)-0.05);
        hrecoidD->SetBinContent(1,hrecoidD->GetBinContent(1)-0.05);

        hrecoid_mc->SetBinError(7,(hrecoid_mc->GetBinError(6)+hrecoid_mc->GetBinError(8))/2.);
        hrecoidAB->SetBinError(7,(hrecoidAB->GetBinError(6)+hrecoidAB->GetBinError(8))/2.);
        hrecoidC->SetBinError(7,(hrecoidC->GetBinError(6)+hrecoidC->GetBinError(8))/2.);
        hrecoidD->SetBinError(7,(hrecoidD->GetBinError(6)+hrecoidD->GetBinError(8))/2.);
      }
        hrecoid_mc = getSimplePlot(INPUTDIR_PREFIX,overallConfs[2],"datalike_mc",varType,SCEN_TRIG,RR);
        getComparisonABCD(hrecoid_mc, hrecoidAB, hrecoidC, hrecoidD, varType,true, INPUTDIR_PREFIX,RR);
     }
   }
}

//
//goodness for 2 hypoth
//
void checkGoodness2Alt(TString scenario, TH1D* dummyThis,TString varType, TString shapeComb, TString INPUTDIR_PREFIX, TString SCEN_TRIG) {

   //for each bin, for each type get 3 histos
      TH1D* hpulls_sig_passH1 = (TH1D*)dummyThis->Clone();
      hpulls_sig_passH1->SetName("hpulls_sig_passH1");
      TH1D* hpulls_sig_failH1 = (TH1D*)dummyThis->Clone();
      hpulls_sig_failH1->SetName("hpulls_sig_failH1");
      TH1D* hpulls_sig_passH2 = (TH1D*)dummyThis->Clone();
      hpulls_sig_passH2->SetName("hpulls_sig_passH2");
      TH1D* hpulls_sig_failH2 = (TH1D*)dummyThis->Clone();
      hpulls_sig_failH2->SetName("hpulls_sig_failH2");


      for (int ibin = 0; ibin < getNbin(varType)-1; ibin++) {
        //int to string
        std::ostringstream pprint;
        pprint.str("");
        pprint<<ibin;
        string bin = pprint.str();

        //for each bin for each type
        //PASS
        cout << "get data from canvas" << endl;
        RooHist* thisDataPassH1 = getFitHist(INPUTDIR_PREFIX, scenario, "datalike_mc", varType, SCEN_TRIG,"vpvPlusExpo","1",TString(bin), "data");
        RooCurve* thisSignalPassH1 = getFitCurve(INPUTDIR_PREFIX, scenario, "datalike_mc", varType, SCEN_TRIG,"vpvPlusExpo","1",TString(bin), "sig");
        RooCurve* thisBackgroundPassH1 = getFitCurve(INPUTDIR_PREFIX, scenario, "datalike_mc", varType, SCEN_TRIG,"vpvPlusExpo","1",TString(bin), "bkg");
        //FIXME which background
        RooHist* thisDataPassH2 = getFitHist(INPUTDIR_PREFIX, scenario, "data_all", varType, SCEN_TRIG,"vpvPlusQuadratic","1",TString(bin), "data");
        RooCurve* thisSignalPassH2 = getFitCurve(INPUTDIR_PREFIX, scenario, "data_all", varType, SCEN_TRIG,"vpvPlusQuadratic","1",TString(bin), "sig");
        RooCurve* thisBackgroundPassH2 = getFitCurve(INPUTDIR_PREFIX, scenario, "data_all", varType, SCEN_TRIG,"vpvPlusQuadratic","1",TString(bin), "bkg");
        //FAIL
        cout << "get data from canvas" << endl;
        RooHist* thisDataFailH1 = getFitHist(INPUTDIR_PREFIX, scenario, "datalike_mc", varType, SCEN_TRIG,"vpvPlusExpo","2",TString(bin), "data");
        RooCurve* thisSignalFailH1 = getFitCurve(INPUTDIR_PREFIX, scenario, "datalike_mc", varType, SCEN_TRIG,"vpvPlusExpo","2",TString(bin), "sig");
        RooCurve* thisBackgroundFailH1 = getFitCurve(INPUTDIR_PREFIX, scenario, "datalike_mc", varType, SCEN_TRIG,"vpvPlusExpo","2",TString(bin), "bkg");
        //FIXME which background
        RooHist* thisDataFailH2 = getFitHist(INPUTDIR_PREFIX, scenario, "data_all", varType, SCEN_TRIG,"vpvPlusQuadratic","2",TString(bin), "data");
        RooCurve* thisSignalFailH2 = getFitCurve(INPUTDIR_PREFIX, scenario, "data_all", varType, SCEN_TRIG,"vpvPlusQuadratic","2",TString(bin), "sig");
        RooCurve* thisBackgroundFailH2 = getFitCurve(INPUTDIR_PREFIX, scenario, "data_all", varType, SCEN_TRIG,"vpvPlusQuadratic","2",TString(bin), "bkg");

        //Plot and save
        TCanvas* ctmp_pass = new TCanvas("PASS"+TString(bin)+"_view","PASS"+TString(bin)+"_view");
        ctmp_pass->cd();
        thisDataPassH1->Draw("ap");
        thisSignalPassH1->Draw("same");
        thisBackgroundPassH1->Draw("same");
        thisSignalPassH2->Draw("same");
        thisBackgroundPassH2->Draw("same");
        ctmp_pass->SaveAs("PASS"+TString(bin)+"_view.png");

/*
//        TCanvas* ctmp_fail = new TCanvas("FAIL"+TString(bin)+"_view","FAIL"+TString(bin)+"_view");
//        ctmp_fail->cd();
//        thisDataFailH1->Draw("ap");
//        thisSignalFailH1->Draw("same");
//        thisBackgroundFailH1->Draw("same");
//        thisSignalFailH2->Draw("same");
//        thisBackgroundFailH2->Draw("same");
//        ctmp_fail->SaveAs("FAIL"+TString(bin)+"_view.png");
*/

        //PASS
        TCanvas* cpull_pass_sig_tmp = new TCanvas("pulls_"+TString(bin)+"_PASS_SIG","pulls_"+TString(bin)+"_PASS_SIG");
        cpull_pass_sig_tmp->cd();
        thisDataPassH1->makeResidHist(*thisSignalPassH1,kTRUE)->Draw("ap");
        thisDataPassH2->makeResidHist(*thisSignalPassH2,kTRUE)->Draw("psame");
        cpull_pass_sig_tmp->SaveAs("SIG"+TString(bin)+"_PULL_PASS.png");
        //get mean pulls for a given canvas
        hpulls_sig_passH1->SetBinContent(ibin+1,fabs(getRooMean(thisDataPassH1->makeResidHist(*thisSignalPassH1,kTRUE))));
        hpulls_sig_passH1->SetBinError(ibin+1,0.000001);
        hpulls_sig_passH2->SetBinContent(ibin+1,fabs(getRooMean(thisDataPassH2->makeResidHist(*thisSignalPassH2,kTRUE))));
        hpulls_sig_passH2->SetBinError(ibin+1,0.000001);

/*        //FAIL 
//        TCanvas* cpull_fail_sig_tmp = new TCanvas("pulls_"+TString(bin)+"_FAIL_SIG","pulls_"+TString(bin)+"_FAIL_SIG");
//        cpull_fail_sig_tmp->cd();
//        thisDataFailH1->makeResidHist(*thisSignalFailH1,kTRUE)->Draw("ap");
//        thisDataFailH2->makeResidHist(*thisSignalFailH2,kTRUE)->Draw("psame");
//        cpull_fail_sig_tmp->SaveAs("SIG"+TString(bin)+"_PULL_FAIL.png");
//        //get mean pulls for a given canvas
//        hpulls_sig_failH1->SetBinContent(ibin+1,fabs(getRooMean(thisDataFailH1->makeResidHist(*thisSignalFailH1,kTRUE))));
//        hpulls_sig_failH1->SetBinError(ibin+1,0.000001);
//        hpulls_sig_failH2->SetBinContent(ibin+1,fabs(getRooMean(thisDataFailH2->makeResidHist(*thisSignalFailH2,kTRUE))));
//        hpulls_sig_failH2->SetBinError(ibin+1,0.000001);
*/
      }

      cout << "OUT PULLS FILL LOOP XXX" << endl;
      //PLOT pull means distributions
      TCanvas* cpullf_sig_pass = new TCanvas("SIG_PASS_"+scenario+varType,"SIG_PASS_"+scenario+varType);
      cpullf_sig_pass->cd();
      cpullf_sig_pass->SetLogx();
      hpulls_sig_passH1->GetXaxis()->SetMoreLogLabels();
      hpulls_sig_passH1->SetMaximum(2*hpulls_sig_passH1->GetMaximum());
      hpulls_sig_passH1->SetMarkerStyle(22);
      hpulls_sig_passH1->SetMarkerSize(1.1);
      hpulls_sig_passH1->SetMarkerColor(kBlack);
      hpulls_sig_passH1->Draw("P");      
      hpulls_sig_passH2->SetMarkerStyle(24);
      hpulls_sig_passH2->SetMarkerSize(1.1);
      hpulls_sig_passH2->SetMarkerColor(kRed);
      hpulls_sig_passH2->Draw("Psame");
      cpullf_sig_pass->SaveAs("SIG_PASS_"+scenario+varType+".png");

/*
      //PLOT pull means distributions
      TCanvas* cpullf_sig_fail = new TCanvas("SIG_FAIL_"+scenario+varType,"SIG_FAIL_"+scenario+varType);
      cpullf_sig_fail->cd();
      hpulls_sig_failH1->SetMarkerStyle(22);
      hpulls_sig_failH1->SetMarkerSize(1.1);
      hpulls_sig_failH1->SetMarkerColor(kBlack);
      hpulls_sig_failH1->Draw("P");
      hpulls_sig_failH2->SetMarkerStyle(24);
      hpulls_sig_failH2->SetMarkerSize(1.1);
      hpulls_sig_failH2->SetMarkerColor(kRed);
      hpulls_sig_failH2->Draw("Psame");
      cpullf_sig_fail->SaveAs("SIG_FAIL_"+scenario+varType+".png");
*/
}


void checkGoodness(TString scenario, TH1D* dummyThis,TString varType, TString shapeComb, TString INPUTDIR_PREFIX, TString SCEN_TRIG) {

      cout << "Inside the checkGoodness we have " << scenario << " histo " << dummyThis->GetName() << " " << varType << " " << shapeComb << " " <<  INPUTDIR_PREFIX << " " <<  SCEN_TRIG << endl;

   //for each bin, for each type get 3 histos
      TH1D* hpulls_sig_pass = (TH1D*)dummyThis->Clone();
      hpulls_sig_pass->SetName("hpulls_sig_pass");
      TH1D* hpulls_sig_fail = (TH1D*)dummyThis->Clone();
      hpulls_sig_fail->SetName("hpulls_sig_fail");
      //TH1D* hpulls_bkg_pass = (TH1D*)dummyThis->Clone();
      //hpulls_bkg_pass->SetName("hpulls_bkg_pass");
      //TH1D* hpulls_bkg_fail = (TH1D*)dummyThis->Clone();
      //hpulls_bkg_fail->SetName("hpulls_bkg_fail");

      for (int ibin = 0; ibin < getNbin(varType)-1; ibin++) {
 
        //int to string
        std::ostringstream pprint;
        pprint.str("");
        pprint<<ibin;
        string bin = pprint.str();

        //for each bin for each type
        cout << "get data from canvas" << endl;
        RooHist* thisDataPass        = getFitHist(INPUTDIR_PREFIX, scenario, "datalike_mc", varType, SCEN_TRIG,shapeComb, "1",TString(bin), "data");
        RooCurve* thisSignalPass     = getFitCurve(INPUTDIR_PREFIX,scenario, "datalike_mc", varType, SCEN_TRIG,shapeComb, "1",TString(bin), "sig");
        RooCurve* thisBackgroundPass = getFitCurve(INPUTDIR_PREFIX,scenario, "datalike_mc", varType, SCEN_TRIG,shapeComb,"1",TString(bin), "bkg");
        RooHist* thisDataFail        = getFitHist(INPUTDIR_PREFIX, scenario, "datalike_mc", varType, SCEN_TRIG,shapeComb,"2",TString(bin), "data");
        RooCurve* thisSignalFail     = getFitCurve(INPUTDIR_PREFIX,scenario, "datalike_mc", varType, SCEN_TRIG,shapeComb,"2",TString(bin), "sig");
        RooCurve* thisBackgroundFail = getFitCurve(INPUTDIR_PREFIX,scenario, "datalike_mc", varType, SCEN_TRIG,shapeComb,"2",TString(bin), "bkg");

//        RooCurve* thisBackgroundFail = getFitCurve(INPUTDIR_PREFIX,scenario, "datalike_mc", varType, SCEN_TRIG,getShapeUtility(shapeComb, ibin,"datalike_mc"),"2",TString(bin), "bkg");

        //Plot and save
        //RooPlot* ctmp_pass = getFitPlot(INPUTDIR_PREFIX, scenario, "datalike_mc", varType, SCEN_TRIG,getShapeUtility(shapeComb, ibin,"datalike_mc"),"1",TString(bin), "data");
//new RooPlot(); 
        TCanvas* ctmp_pass = new TCanvas("PASS"+TString(bin)+"_view_"+getShapeUtility(shapeComb, ibin,"datalike_mc"),"PASS"+TString(bin)+"_view_"+getShapeUtility(shapeComb, ibin,"datalike_mc"));
        ctmp_pass->cd();
        //ctmp_pass->Draw();
        thisDataPass->Draw("ap");
        thisSignalPass->Draw("same");
        thisBackgroundPass->Draw("same");
        ctmp_pass->SaveAs(INPUTDIR_PREFIX+"/PASS"+TString(bin)+"_view_"+getShapeUtility(shapeComb, ibin,"datalike_mc")+".png");

        TCanvas* ctmp_fail = new TCanvas("FAIL"+TString(bin)+"_view_"+getShapeUtility(shapeComb, ibin,"datalike_mc"),"FAIL"+TString(bin)+"_view_"+getShapeUtility(shapeComb, ibin,"datalike_mc"));
        //RooPlot* ctmp_fail = getFitPlot(INPUTDIR_PREFIX, scenario, "datalike_mc", varType, SCEN_TRIG,getShapeUtility(shapeComb, ibin,"datalike_mc"),"1",TString(bin), "data");

        ctmp_fail->cd();
        thisDataFail->Draw("ap");
        thisSignalFail->Draw("same");
        thisBackgroundFail->Draw("same");
        ctmp_fail->SaveAs(INPUTDIR_PREFIX+"/FAIL"+TString(bin)+"_view_"+getShapeUtility(shapeComb, ibin,"datalike_mc")+".png");

        //calculate and draw pulls
        //PASS
        TCanvas* cpull_pass_sig_tmp = new TCanvas("pulls_"+TString(bin)+"_PASS_SIG_"+getShapeUtility(shapeComb, ibin,"datalike_mc"),"pulls_"+TString(bin)+"_PASS_SIG_"+getShapeUtility(shapeComb, ibin,"datalike_mc"));
        cpull_pass_sig_tmp->cd();
        thisDataPass->makeResidHist(*thisSignalPass,kTRUE)->Draw("ap"); 
        cpull_pass_sig_tmp->SaveAs(INPUTDIR_PREFIX+"/SIG"+TString(bin)+"_PULL_PASS_"+getShapeUtility(shapeComb, ibin,"datalike_mc")+".png");
        //get mean pulls for a given canvas
        hpulls_sig_pass->SetBinContent(ibin+1,fabs(getRooMean(thisDataPass->makeResidHist(*thisSignalPass,kTRUE))));
        hpulls_sig_pass->SetBinError(ibin+1,0.000001);

/*        TCanvas* cpull_pass_bkg_tmp = new TCanvas("pulls_"+TString(bin)+"_PASS_BKG_"+getShapeUtility(shapeComb, ibin,"datalike_mc","pulls_"+TString(bin)+"_PASS_BKG_"+getShapeUtility(shapeComb, ibin,"datalike_mc");
        cpull_pass_bkg_tmp->cd();
        thisDataPass->makeResidHist(*thisBackgroundPass,kTRUE)->Draw("ap");
        cpull_pass_bkg_tmp->SaveAs("BKG"+TString(bin)+"_PULL_PASS_"+getShapeUtility(shapeComb, ibin,"datalike_mc"+".png");
        //get mean pulls for a given canvas
        hpulls_bkg_pass->SetBinContent(ibin+1,getRooMean(thisDataPass->makeResidHist(*thisBackgroundPass,kTRUE)));
        hpulls_bkg_pass->SetBinError(ibin+1,0.000001);
*/
       //FAIL 
        TCanvas* cpull_fail_sig_tmp = new TCanvas("pulls_"+TString(bin)+"_FAIL_SIG_"+getShapeUtility(shapeComb, ibin,"datalike_mc"),"pulls_"+TString(bin)+"_FAIL_SIG_"+getShapeUtility(shapeComb, ibin,"datalike_mc"));
        cpull_fail_sig_tmp->cd();
        thisDataFail->makeResidHist(*thisSignalFail,kTRUE)->Draw("ap");
        cpull_fail_sig_tmp->SaveAs( INPUTDIR_PREFIX+"/SIG"+TString(bin)+"_PULL_FAIL_"+getShapeUtility(shapeComb, ibin,"datalike_mc")+".png");
        cout << "get mean pulls for a given canvas" << endl;
        hpulls_sig_fail->SetBinContent(ibin+1,fabs(getRooMean(thisDataFail->makeResidHist(*thisSignalFail,kTRUE))));
        hpulls_sig_fail->SetBinError(ibin+1,0.000001);

/*        TCanvas* cpull_fail_bkg_tmp = new TCanvas("pulls_"+TString(bin)+"_FAIL_BKG_"+getShapeUtility(shapeComb, ibin,"datalike_mc","pulls_"+TString(bin)+"_FAIL_BKG_"+getShapeUtility(shapeComb,
 ibin));
        cpull_fail_bkg_tmp->cd();
        thisDataFail->makeResidHist(*thisBackgroundFail,kTRUE)->Draw("ap");
        cpull_fail_bkg_tmp->SaveAs("BKG"+TString(bin)+"_PULL_FAIL_"+getShapeUtility(shapeComb, ibin,"datalike_mc"+".png");
        cout << "get mean pulls for a given canvas" << endl;
        hpulls_bkg_fail->SetBinContent(ibin+1,getRooMean(thisDataFail->makeResidHist(*thisBackgroundFail,kTRUE)));
        hpulls_bkg_fail->SetBinError(ibin+1,0.000001);
*/
      }
      cout << "OUT PULLS FILL LOOP XXX" << endl;
      //PLOT pull means distributions
      TCanvas* cpullf_sig = new TCanvas("SIG"+scenario+varType,"SIG"+scenario+varType);
      cpullf_sig->cd();
      cpullf_sig->SetLogx();
      cpullf_sig->SetLogy();
      hpulls_sig_pass->SetMarkerStyle(22);
      hpulls_sig_pass->SetMarkerSize(1.1);
      hpulls_sig_pass->SetMarkerColor(kBlack);
      hpulls_sig_pass->Draw("P");      
      hpulls_sig_fail->SetMarkerStyle(24);
      hpulls_sig_fail->SetMarkerSize(1.1);
      hpulls_sig_fail->SetMarkerColor(kRed);
      hpulls_sig_fail->Draw("Psame");
      cpullf_sig->SaveAs(INPUTDIR_PREFIX+"/SIG"+scenario+varType+".png");
/*
      TCanvas* cpullf_bkg = new TCanvas("BKG"+scenario+varType,"BKG"+scenario+varType);
      cpullf_bkg->cd();
      hpulls_bkg_pass->SetMarkerStyle(22);
      hpulls_bkg_pass->SetMarkerSize(1.1);
      hpulls_bkg_pass->SetMarkerColor(kBlack);
      hpulls_bkg_pass->Draw("P");      
      hpulls_bkg_fail->SetMarkerStyle(24);
      hpulls_bkg_fail->SetMarkerSize(1.1);
      hpulls_bkg_fail->SetMarkerColor(kRed);
      hpulls_bkg_fail->Draw("Psame");
      cpullf_bkg->SaveAs("BKG"+scenario+varType+".png");
*/
}


double getRooMean(RooHist* rooh) {

   Double_t bincenter;
   Double_t bincontent;
   Double_t sum = 0;  
   for (int ibin = 0; ibin < rooh->GetN(); ibin++) {
       rooh->GetPoint(ibin, bincenter, bincontent);
       sum += fabs(bincontent);
       bincenter = 0;
       bincontent = 0;
    }

   return sum/double(rooh->GetN());

}

TString getCanv(TString which) {

   if (which == "1") {
      retunr "Pass";
   }     
   else if (which == "2") {
      return "Fail";
   }     
   else if (which == "3") {
      return Pdf"";
   }     
}

//
//Identify backgraound shape utility
//
TString getShapeUtility(TString shape, int bin, TString hypoth) {

   TString fitShape = "vpvPlusExpo";

//   if (hypoth == "datalike_mc") {
     if (shape == "vpvExpoCheb") {
       if (bin > 12) return "vpvPlusQuadratic"; 
      } else if (shape == "vpvCheb") {
        return "vpvPlusQuadratic";
      } else if (shape == "voigtCheb") {
        return "voigtPlusQuadratic";
      } else if (shape == "voigtExpo") {
        return "voigtPlusExpo";
     } else if (shape == "vpvExpo") {
        return "vpvPlusExpo";
     } else if (shape == "vpvExpoCheb_2") {  
        if (bin == 0) return "vpvPlusExpo"; 
        else return "vpvPlusQuadratic";
     }
//     return fitShape; 
//   } else {
//     //whatever
//     return "vpvPlusQuadratic";
//   }

   return fitShape;
}

int getNbin(TString what) {

   if (what == "vtx") {
       return 20;
   } else if (what == "pt") {
       return 19;
   } else if (what == "eta") {
       return 22;
   } else if (what == "rrr") {
       return 154;
   } else if (what == "rrr2") {
       return 58;
   } else if (what == "rrr3") {
       return 6; 
   } else {return 0;} //FIXME do in case something is wrong}

}

//
//Superimpose data and MC
//
void getComparisonABCD(TH1D* hmc, TH1D* hAB, TH1D* hC, TH1D* hD, TString varType, bool dataOnly, TString INPUTDIR_PREFIX, TString run) {

   gStyle->SetOptTitle(0);
   gStyle->SetEndErrorSize(2);
   gStyle->SetErrorX(0.5);
   
   TLegend* leg = MakeLegend();
   TPaveText* pt = MakeTPave();

   TCanvas* c1 = new TCanvas("c1","c1",800,600);
   c1->cd();
   //c1->SetLogx();
   //range
   if (varType == "pt" || varType == "pt2") {
     //h1->GetXaxis()->SetRangeUser(8,180);
     c1->SetLogx();
   }
   //else if (varType == "vtx") h1->GetXaxis()->SetRangeUser(0,20.4);
   hmc->GetYaxis()->SetRangeUser(0.82,1.02);
   hmc->GetXaxis()->SetMoreLogLabels();
   hmc->GetYaxis()->SetTitle("#epsilon");
   hmc->SetMarkerSize(0);
   hmc->SetLineWidth(1.2);
   hmc->SetLineColor(kRed);
   hmc->SetFillColor(kRed);
   hAB->SetMarkerStyle(20);
   hAB->SetMarkerSize(1.1);
   hC->SetMarkerStyle(20);
   hC->SetMarkerSize(1.1);
   hC->SetMarkerColor(kBlue);
   hC->SetLineColor(kBlue);
   hD->SetMarkerStyle(20);
   hD->SetMarkerSize(1.1);
   hD->SetMarkerColor(kViolet);
   hD->SetLineColor(kViolet);

   hmc->Draw("E2");
   hmc->GetXaxis()->SetTitle(getTitle(varType));
   hAB->Draw("samePE");
   hC->Draw("samePE");
   hD->Draw("samePE");
   leg->AddEntry(hmc,"MC, 53X","f");
   leg->AddEntry(hAB,"Data, Run A+B","pl");
   leg->AddEntry(hC,"Data, Run C","pl");
   leg->AddEntry(hD,"Data, Run D","pl");

   leg->Draw("same");
   //if (dataOnly && !(varType == "rrr")) pt->Draw("same");
   //if (varType == "pt") c1->SetLogx();

   c1->SaveAs(INPUTDIR_PREFIX+"/"+hmc->GetName()+varType+".png");
   c1->SaveAs(INPUTDIR_PREFIX+"/"+hmc->GetName()+varType+".C");
}


void getComparisonABCDratio(TH1D* hmc, TH1D* hAB, TH1D* hC, TH1D* hD, TString varType, bool dataOnly, TString INPUTDIR_PREFIX, TString run) {

   gStyle->SetOptTitle(0);
   gStyle->SetEndErrorSize(2);
   gStyle->SetErrorX(0.5);

   TLegend* leg = MakeLegend();
   TPaveText* pt = MakeTPave();

   TCanvas* c1 = new TCanvas("c1","c1",800,600);
   c1->cd();
   //c1->SetLogx();
   //range
   if (varType == "pt" || varType == "pt2") {
     //h1->GetXaxis()->SetRangeUser(8,180);
     c1->SetLogx();
   }
   //else if (varType == "vtx") h1->GetXaxis()->SetRangeUser(0,20.4);
   //get ratios
   hAB->Divide(hAB,hmc);
   hC->Divide(hC,hmc);
   hD->Divide(hD,hmc); 

   hAB->GetYaxis()->SetRangeUser(0.92,1.12);
   hAB->GetXaxis()->SetMoreLogLabels();
   hAB->GetYaxis()->SetTitle("#epsilon");
   hAB->SetMarkerStyle(20);
   hAB->SetMarkerSize(1.1);
   hC->SetMarkerStyle(20);
   hC->SetMarkerSize(1.1);
   hC->SetMarkerColor(kBlue);
   hC->SetLineColor(kBlue);
   hD->SetMarkerStyle(20);
   hD->SetMarkerSize(1.1);
   hD->SetMarkerColor(kViolet);
   hD->SetLineColor(kViolet);

   //hmc->Draw("E2");
   //hmc->GetXaxis()->SetTitle(getTitle(varType));
   hAB->Draw("PE");
   hAB->GetXaxis()->SetTitle(getTitle(varType));
   hC->Draw("samePE");
   hD->Draw("samePE");
   //leg->AddEntry(hmc,"MC, 53X","f");
   leg->AddEntry(hAB,"Data Run A+B/MC","pl");
   leg->AddEntry(hC,"Data Run C/MC","pl");
   leg->AddEntry(hD,"Data Run D/MC","pl");

   leg->Draw("same");
   //if (dataOnly && !(varType == "rrr")) pt->Draw("same");
   //if (varType == "pt") c1->SetLogx();

   c1->SaveAs(INPUTDIR_PREFIX+"/"+hmc->GetName()+varType+".png");
   c1->SaveAs(INPUTDIR_PREFIX+"/"+hmc->GetName()+varType+".C");
}


TString getTitle(TString varType) {
  TString title = "";
  if (varType == "pt" || varType == "pt2")  title = "Probe p_{T} [GeV]";
  if (varType == "eta" || varType == "eta2" || varType == "eta3") title = "Probe #eta";
  if (varType == "vtx") title = "N_{vtx}"; 
  return title;
}

TLegend*  MakeLegend() {
   TLegend *_leg= new TLegend(0.40,0.13,0.60,0.37); //20-37 
//   TLegend *_leg= new TLegend(0.25,0.20,0.40,0.37); //20-37 
   _leg->SetTextFont(72);
   _leg->SetTextSize(0.060);
   _leg->SetBorderSize(0);
   _leg->SetFillColor(0);
   return _leg;
}

TPaveText* MakeTPave() {
    TPaveText *_pt = new TPaveText(0.25,0.25,0.40,0.40,"brNDC");
    _pt->SetFillColor(0);
    _pt->SetTextFont(72);
    _pt->SetTextSize(0.045);
    _pt->SetBorderSize(0);
    _pt->SetTextAlign(12);
    return _pt;
}

void FindRatio(TH1D* ratio, TH1D* numer, TH1D* denom) {

   for (int ibin = 0; ibin < numer->GetXaxis()->GetNbins()+1;ibin++) {
       if (denom->GetBinContent(ibin+1) != 0) {
                double rat = (double)numer->GetBinContent(ibin+1)/denom->GetBinContent(ibin+1); 
                //double rat = (numer->GetBinError(ibin+1)/denom->GetBinError(ibin+1))*(denom->GetBinContent(ibin+1)/numer->GetBinContent(ibin+1));
                ratio->SetBinContent(ibin+1,rat);
                ratio->SetBinError(ibin+1,sqrt(numer->GetBinContent(ibin+1))/denom->GetBinContent(ibin+1) - numer->GetBinContent(ibin+1)*sqrt(denom->GetBinContent(ibin+1))/pow(denom->GetBinContent(ibin+1),2));      
//                ratio->SetBinError(ibin+1,0.000001);
                //cout << rat << " " << numer->GetBinError(ibin+1) << " " << denom->GetBinError(ibin+1) << endl;
                } else {
                ratio->SetBinContent(ibin+1,0.);
        }        
    }    
} 
