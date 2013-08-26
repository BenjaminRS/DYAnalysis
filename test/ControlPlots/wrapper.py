#!/usr/bin/env python

from subprocess import Popen

print "Clean up the output folder"

#Popen("rm ./runfolder/*root",shell=True).wait()

Popen("python analyseYield_p1.py",shell=True).wait()
#Popen("python analyseYield_p2.py",shell=True).wait()
Popen("python analyseYield_p3.py",shell=True).wait()
#Popen("python analyseYield_p4.py",shell=True).wait()
