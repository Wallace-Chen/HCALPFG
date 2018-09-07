#://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCRAB3Tutorial  #**Up-to-date**
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3ConfigurationFile #
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3CheatSheet        #
#
# Environment setup:
#    cmsenv
#    source /cvmfs/cms.cern.ch/crab3/crab.sh
# To submit:
#    crab submit -c crabConfig_noiseAnalysis_CollisionData_RECO_cfg.py
# To check status:
#    crab status -d <CRAB-project-directory> [--jobids <comma-separated-list-of-jobs-and/or-job-ranges>]
# To kill jobs:
#    crab kill -d <CRAB-project-directory> [--jobids <comma-separated-list-of-jobs-and/or-job-ranges>]
# To retrieve output:
#    crab getoutput -d <CRAB-project-directory> [--jobids <comma-separated-list-of-jobs-and/or-job-ranges>]
# -----------------------------------------------------------------------------------------------------------------------------
from CRABClient.UserUtilities import config
from CRABClient.UserUtilities import getUsernameFromSiteDB


# Select dataset to crab over
number = 0 # starting at 0

# List of datasets
datasetnames = [
#'/NoBPTX/Commissioning2016-PromptReco-v1/RECO',
#'/MinimumBias/Commissioning2016-PromptReco-v1/RECO',
#'/HcalHPDNoise/Commissioning2016-PromptReco-v1/RECO',
#'/HcalNZS/Commissioning2016-PromptReco-v1/RECO',
#'/Cosmics/Commissioning2016-PromptReco-v1/RECO'
#'/JetHT/Run2017A-v1/RAW'
#'/HLTPhysics1/Run2017A-v1/RAW'
#'/MET/Run2017B-v1/RAW'
#'/JetHT/Run2017B-v1/RAW'
#'/ZeroBias/Commissioning2018-v1/RAW',
#'/ZeroBias/Run2018A-v1/RAW',
#'/IsolatedBunch/Run2018A-v1/RAW',
#'/IsolatedBunch/Run2018B-v1/RAW',
#'/IsolatedBunch/Run2018C-v1/RAW',
#'/IsolatedBunch/Run2018D-v1/RAW',
#'/MinimumBias/Commissioning2018-v1/RAW'
#'/JetHT/Run2018A-v1/RAW',
#'/JetHT/Run2018B-v1/RAW'
#'/JetHT/Run2018C-v1/RAW'
'/JetHT/Run2018D-v1/RAW'
]

# Storage path for output files - EOS specific
#storagepath = '/store/user/'+getUsernameFromSiteDB()+'/HCALnoise2016'
#storagepath = '/store/group/dpg_hcal/comm_hcal/Noise/2017/' # DO NOT USE
storagepath = '/eos/cms/store/user/yuanc/'
# cmsRun file
#psetname = './pfg_Global_RAW_cfg.py'
#psetname = './pfg_Global_Isolated_QIE10.py'
#psetname = 'pfg_Global_Isolated_HBHE_QIE10.py'
#psetname = './pfg_Global_Isolated_HBHE.py'
psetname = './pfg_Global_Isolated_HBHE_M0.py'

# Output filename
OutputFilename = 'results.root'

# Storage site of output files
storageSite = 'T2_CH_CERN'
#storageSite = 'T2_US_UCSD' 

# White list sites
whiteList = ['T2_CH_CERN','T2_US_Caltech','T2_US_Florida', 'T2_US_MIT', 'T2_US_Nebraska', 'T2_US_Purdue', 'T2_US_UCSD', 'T2_US_Vanderbilt', 'T2_US_Wisconsin', 'T1_US_FNAL','T2_US_MIT']
#whiteList = ['T1_UK_RAL_Disk','T2_CH_CERN']
# ['T2_US_UCSD']

# Black list sites
blackList = ['']

# -----------------------------------------------------------------------------------------------------------------------------
# No modifications below this line are necessary

import datetime
timestamp = datetime.datetime.now().strftime("_%Y%m%d_%H%M%S")


dataset = filter(None, datasetnames[number].split('/'))

config = config()

config.General.workArea        = "out_crab"
#config.General.instance = 'preprod'
config.General.requestName     = dataset[0]+'_'+dataset[1]+'_'+dataset[2]+timestamp
config.General.transferOutputs = True
config.General.transferLogs    = True

config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = psetname
config.JobType.outputFiles = [OutputFilename]
config.JobType.pyCfgParams = ['outputFile='+OutputFilename]
config.JobType.inputFiles = ['bx.json']


# DATA specific:
config.Data.inputDataset     = datasetnames[number]
config.Data.inputDBS         = 'global'
#config.Data.splitting       = 'FileBased'
#config.Data.unitsPerJob     = 5
config.Data.splitting        = 'LumiBased'
#config.Data.splitting        = 'Automatic'
config.Data.unitsPerJob      = 10
config.Data.ignoreLocality   = True
#config.Data.outLFNDirBase    = storagepath
config.Data.publication      = False
config.Data.outputDatasetTag = dataset[1]+'_'+dataset[2]+timestamp
#config.Data.lumiMask         = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/13TeV/Reprocessing/Cert_13TeV_16Dec2015ReReco_Collisions15_25ns_JSON.txt'
#config.Data.runRange         = '254231-260627'
#config.Data.runRange        = '260577-260578' #for test
#config.Data.lumiMask        = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/13TeV/Reprocessing/Cert_13TeV_16Dec2015ReReco_Collisions15_50ns_JSON.txt'
#config.Data.runRange        = '295606-295606'
#config.Data.runRange        = '295436-296174'

#config.Data.lumiMask        = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PromptReco/Cert_294927-297723_13TeV_PromptReco_Collisions17_JSON.txt'
#config.Data.lumiMask         = './my_lumi_mask.json'
#config.Data.lumiMask         = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/PromptReco/Cert_314472-317696_13TeV_PromptReco_Collisions18_JSON.txt'
config.Data.lumiMask         = './lumimask.txt'
#config.Data.lumiMask         = './lumi_test.txt'
#config.Data.runRange        = '316361-316363,316377-316380,316441,316455-316457,316469-316470,316472,316613-316615'
#config.Data.runRange        = '317279-317279' #Fill 67**
#config.Data.runRange        = '315420-315420' #Fill 67**
#config.Data.runRange        = '315646-315646'
#config.Data.runRange        = '318828-318828'
config.Data.runRange        = '322118-322118'

#config.Data.runRange        =  '315149-315173'#'314470-314505'

#config.Data.runRange         =  '315322,315339,315357,315361,315366,315420,315488,315489,315510,315512,315543,315555,315557,315644,315645,315646,315689,315690,316361-316363,316377-316380,316441,316455-316457,316469-316470,316472,316613-316615,316559,317279'
#config.Data.runRange         =  '315322,315339,315357,315361,315366,315420,315488,315489,315510,315512,315543,315555,315557,315644,315645,315646,315689,315690,316361-316363,316377-316380,316441,316455-316457,316469-316470,316472,316613-316615,316559'
#config.Data.runRange         =  '317279-317279'

# -----------------------------------------------------------------------------------------------------------------------------
# JSON files are available at: /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/
# -----------------------------------------------------------------------------------------------------------------------------

config.Site.storageSite = storageSite

#if not whiteList:
config.Site.whitelist = whiteList
#config.Site.whitelist = ["T2_US_UCSD"]

#if not blackList:
#            config.Site.blacklist = blackListptions.LoadFromFile('filelist','filelist.txt')
