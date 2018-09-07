from CRABClient.UserUtilities import config
from CRABClient.UserUtilities import getUsernameFromSiteDB
#import datetime

config = config()
#timestamp = datetime.datetime.now().strftime("_%Y%m%d_%H%M%S")
timestamp = 'MIDNIGHTJuly'

config.General.workArea        = "out_crab"
config.General.instance = 'preprod'
config.General.requestName     = 'JetHT_TEST'
config.General.transferOutputs = True
config.General.transferLogs    = True

config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = './pfg_Global_Isolated_HBHE_M0.py'
config.JobType.outputFiles = ['results.root']

config.Data.inputDataset = '/JetHT/Run2018B-v1/RAW'
config.Data.inputDBS         = 'global'
config.Data.splitting        = 'FileBased'
config.Data.unitsPerJob      = 3
config.Data.ignoreLocality   = True
#config.Data.publication      = False
#config.Data.outputDatasetTag = 'JetHT_Run2018B_'+timestamp
config.Data.lumiMask         = './lumimask.txt'
config.Data.runRange        = '317279-317279'

config.Site.storageSite = 'T2_CH_CERN'
config.Site.whitelist    = ['T2_CH_CERN','T2_US_Caltech','T2_US_Florida', 'T2_US_MIT', 'T2_US_Nebraska', 'T2_US_Purdue', 'T2_US_UCSD', 'T2_US_Vanderbilt', 'T2_US_Wisconsin', 'T1_US_FNAL','T2_US_MIT']
#config.Site.whitelist = ['T1_US_FNAL','T2_CH_CERN','T2_US_UCSD']
