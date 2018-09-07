from WMCore.DataStructs.LumiList import LumiList

lumiList = LumiList(filename='my_original_lumi_mask.json')
lumiList.selectRuns([x for x in range(190645,191271+1)])
lumiList.writeJSON('my_lumi_mask.json')

