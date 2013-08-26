#!/usr/bin/env python

from subprocess import Popen
import sys

#histos = ['CosAngle','invm','chi2dof','trackerHits','pixelHits','muonHits','nMatches','dxyBS','relPFisoNoEGamma','vtxTrkProb','trigMatches','pT','eta']

use_specific_hist = "" #"_invm_"

#merge files
def stringer(inp_list):
    out_string = ''
    for item in inp_list:
        out_string += item+' '
    return out_string

def populator(folder,marker):
    #print glob.glob(folder+marker+'*'+'invm_RunAB.root')
    for file in glob.glob(folder+marker+'*'+'invm_RunAB.root'):
        Popen('cp '+file+' '+file[:-7]+'C.root',shell=True).wait()
        Popen('cp '+file+' '+file[:-7]+'D.root',shell=True).wait()
 
import os
import glob
folder = './runfolder/'
#FIXME disabled
#POSTFIX_THIS = "this"
#POSTFIX_THIS = str(sys.argv[1])
TYPE = [str(sys.argv[1]),str(sys.argv[2])]

print "Hadd the main root files" 

#FIXME this is temporary, but make RunC
populator(folder,"DY")
populator(folder,"t")
populator(folder,"ZZ")
populator(folder,"WZ")
populator(folder,"WW")
populator(folder,"QCD")
populator(folder,"WJ")

#print stringer(EWKs)
included_eras = ['RunAB','RunC','RunD']
for run in included_eras:
    DATAs = glob.glob(folder+'DATA*'+use_specific_hist+run+'.root')
    DYMs = glob.glob(folder+'DYM*'+use_specific_hist+run+'.root')
    TTs = glob.glob(folder+'t*'+use_specific_hist+run+'.root')
    TAUs = glob.glob(folder+'DYtautau*'+use_specific_hist+run+'.root')
    EWKs = glob.glob(folder+'WJ*'+use_specific_hist+run+'.root')
    QCDs = glob.glob(folder+'QCD*'+use_specific_hist+run+'.root')
    ZZs = glob.glob(folder+'ZZ*'+use_specific_hist+run+'.root')
    WZs = glob.glob(folder+'WZ*'+use_specific_hist+run+'.root')
    WWs = glob.glob(folder+'WW*'+use_specific_hist+run+'.root')

    #print "DATA ", stringer(DATAs)
    #print "DYM ", stringer(DYMs)
    #print "TT ",stringer(TTs)
    #print "TAU ", stringer(TAUs)
    #print "EWK ",stringer(EWKs)
    #print "QCD ",stringer(QCDs)
    #print "WW ",stringer(WWs)
    #print "WZ ",stringer(WZs)
    #print "ZZ ",stringer(ZZs)

    os.system("hadd -f "+folder+"DATA"+use_specific_hist+run+"CP.root "+stringer(DATAs))
    os.system("hadd -f "+folder+"DYM"+use_specific_hist+run+"CP.root "+stringer(DYMs))
    os.system("hadd -f "+folder+"TT"+use_specific_hist+run+"CP.root "+stringer(TTs))
    os.system("hadd -f "+folder+"TAU"+use_specific_hist+run+"CP.root "+stringer(TAUs))
    os.system("hadd -f "+folder+"EWK"+use_specific_hist+run+"CP.root "+stringer(EWKs))
    os.system("hadd -f "+folder+"QCD"+use_specific_hist+run+"CP.root "+stringer(QCDs))
    os.system("hadd -f "+folder+"DIBOSON"+use_specific_hist+run+"CP.root "+stringer(WWs)+' '+stringer(WZs)+' '+stringer(ZZs))

os.system("hadd -f "+folder+"DATA_CP.root "+folder+"DATA"+use_specific_hist+"Run*CP.root")
os.system("hadd -f "+folder+"DYM_CP.root "+folder+"DYM"+use_specific_hist+"Run*CP.root")
os.system("hadd -f "+folder+"DIBOSON_CP.root "+folder+"DIBOSON"+use_specific_hist+"Run*CP.root")
os.system("hadd -f "+folder+"EWK_CP.root "+folder+"EWK"+use_specific_hist+"Run*CP.root")
os.system("hadd -f "+folder+"TT_CP.root "+folder+"TT"+use_specific_hist+"Run*CP.root")
os.system("hadd -f "+folder+"TAU_CP.root "+folder+"TAU"+use_specific_hist+"Run*CP.root")
os.system("hadd -f "+folder+"QCD_CP.root "+folder+"QCD"+use_specific_hist+"Run*CP.root")


print "Convert the ABCD root file to appropriate format. Assume ABCD root file is copied manually"

Popen('root -b -l -q \'convert.C()\'',shell=True).wait()
Popen('root -b -l -q \'convert_2D.C()\'',shell=True).wait()
#
print "Parse all into one root file"

eras = ['RunAB','RunC','RunD'] #hgere '_' denotes combined run range

for run in eras:
    Popen('root -b -l -q \'parser.C(\"'+run+'\",\"'+'invm'+TYPE[0]+'\")\'',shell=True).wait()
    Popen('root -b -l -q \'parser_2D.C(\"'+run+'\",\"'+'rap'+'\",\"'+TYPE[1]+'\")\'',shell=True).wait()
    #underflow and overflow
    #Popen('root -b -l -q \'parser_2D.C(\"'+run+'\",\"'+'rap24'+TYPE[1]+'\")\'',shell=True).wait()
    #Popen('root -b -l -q \'parser_2D.C(\"'+run+'\",\"'+'rap12'+TYPE[1]+'\")\'',shell=True).wait()

    #Popen('hadd -f  ./runfolder/stack4fit_analyserap'+TYPE[1]+run+'OU.root ./runfolder/stack4fit_analyserap'+TYPE[1]+run+'CP.root ./runfolder/stack4fit_analyserap24'+TYPE[1]+run+'CP.root ./runfolder/stack4fit_analyse'+'rap12'+TYPE[1]+run+'CP.root',shell=True).wait()

#make combined run range
Popen('hadd -f  ./runfolder/stack4fit_analyserap'+TYPE[1]+'CP.root ./runfolder/stack4fit_analyserap'+TYPE[1]+'RunAB'+'CP.root ./runfolder/stack4fit_analyserap'+TYPE[1]+'RunC'+'CP.root ./runfolder/stack4fit_analyse'+'rap'+TYPE[1]+'RunD'+'CP.root',shell=True).wait()

#FIXME disabled
##Popen('mkdir storefolder_'+POSTFIX_THIS,shell=True).wait()
##Popen('cp -r ./runfolder/*root storefolder_'+POSTFIX_THIS,shell=True).wait()
print "Copying to ../Inputs"
for run in eras:
    Popen('cp ./runfolder/stack4fit_analyse'+'invm'+TYPE[0]+run+'CP.root ../Inputs/rawYield/DYspectrum_uncorr_2013'+run+'tmp.root',shell=True).wait()
    Popen('cp ./runfolder/stack4fit_analyse'+'rap'+TYPE[1]+run+'CP.root ../Inputs/rawYield/DYspectrum_Rap_uncorr_2013'+run+'tmp.root',shell=True).wait()
#copy the combined
Popen('cp ./runfolder/stack4fit_analyse'+'rap'+TYPE[1]+'CP.root ../Inputs/rawYield/DYspectrum_Rap_uncorr_2013_tmp.root',shell=True).wait()
