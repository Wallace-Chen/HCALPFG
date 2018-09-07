Credits to: https://github.com/HCALPFG/HcalTupleMaker/tree/PFG-CMSSW_9_0_X
Has been modified based on the version above.
Can be used combined with https://github.com/Wallace-Chen/CMSHCALTiming.

# HcalTupleMaker
EDM analyzer for making ntuples from HCAL DIGIs and RecHits

## To build
```
# setup environment  
export SCRAM_ARCH=slc6_amd64_gcc530  

# setup cmssw release  
cmsrel CMSSW_9_0_0  
cd CMSSW_9_0_0/src  
cmsenv    

# clone repository  
mkdir HCALPFG  
cd HCALPFG  
git clone -b PFG-CMSSW_9_0_X  git@github.com:HCALPFG/HcalTupleMaker.git  

# compile code  
cd HcalTupleMaker  
scram b -j 8
```

## To run
```
# setup cmssw environment  
cd HCALPFG/HcalTupleMaker/test  
cmsenv  

# obtain grid proxy (optional)  
voms-proxy-init -voms cms -rfc  

# local runs  
cmsRun pfg_Local_RAW_cfg.py

# global runs  
cmsRun pfg_Global_RAW_cfg.py
```

## Local runs

1. Local runs can be found on the HCAL DPG eos space  
    * /eos/cms/store/group/dpg_hcal/comm_hcal/USC/runXXXXXX/USC_XXXXXX.root

2. Access this space using the `root://eoscms.cern.ch/` redirector  
    * root://eoscms.cern.ch//eos/cms/store/group/dpg_hcal/comm_hcal/USC/runXXXXXX/USC_XXXXXX.root

3. If you wish to browse this space, do an `eosmount` on lxplus

4. Copy a file locally using `xrdcp`

## Global runs

1. Choose the correct global tag  
    * https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions

2. Run information:  
    * https://cmswbm.cern.ch/

---------------
Maintained by HCAL PFG  
Original author: Edmund Berry <Edmund.A.Berry(at)CERN.CH>
