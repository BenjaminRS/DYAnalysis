#!/usr/bin/env python

from subprocess import Popen
from ROOT import *
import glob

def populator(folder):
    print glob.glob(folder+'resMatrixProd_RunAB*.root')
    for file in glob.glob(folder+'resMatrixProd_RunAB*.root'):
        print 'cp '+file+' '+file[:-11]+'C_tmp.root'
        Popen('cp '+file+' '+file[:-11]+'C_tmp.root',shell=True).wait()
        Popen('cp '+file+' '+file[:-11]+'D_tmp.root',shell=True).wait()
        Popen('cp '+file+' '+file[:-8]+'POWHEG_tmp.root',shell=True).wait()

#FIXME they are all the same
eras = ['RunAB'] #,'RunC','RunD']
#analyzers
for run in eras:
    #response matrix is produced based on the MC, so the poinbt of the switch is the difference in mom scale correction
    #right now we have only one so no loop necessary 
    Popen('root -b -q -l \'ResMatrix.C(\"'+run+'\")\'',shell=True).wait() 

#postprocessing
Popen('hadd -f resMatrixProd_RunAB_tmp.root DY*RunAB.root',shell=True).wait()
#populate
#FIXME they are all the same
populator("./")
#copy to main
#for run in ['RunAB','RunC','RunD']:
#    Popen('cp resMatrixProd_'+run+'_tmp.root ../Inputs/unfold/',shell=True).wait()
