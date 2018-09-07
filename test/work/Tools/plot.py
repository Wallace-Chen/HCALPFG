import ROOT as r
import sys
import commands
import time

start = time.clock()

r.gROOT.SetBatch()
r.gStyle.SetOptStat(0)

infile0 = sys.argv[1]

status,infile = commands.getstatusoutput("echo " + infile0 + " | sed 's/\.[^.]*$//'")

f1 = r.TFile(infile0)
if (f1.IsZombie() or (not f1.IsOpen())):
  print "Error: cannot open " + infile0 + " or the file is not valid,please check if filename is valid!"
  exit()
  
print "Open " + infile0 + " successfully, now plotting..." 

r.gStyle.SetTitleFontSize(.06)
r.gStyle.SetTitleXSize(.05)
r.gStyle.SetTitleYSize(.05)
#r.gStyle.SetPadBottomMargin(.13)
#r.gStyle.SetPadLeftMargin(.12)
r.gStyle.SetPadRightMargin(.18)
#r.gStyle.SetPadTopMargin(.1)
canvas = r.TCanvas()

outfile = infile + "_HF_timing.pdf"
canvas.SaveAs(outfile + '[')

####------------------------------------------------------------------------------------
#For this part, note that some early histogram root may not have those plots, thus need to be commented..
#qie10_tdc_depth_x_prefix = "qie10_tdc_depth_"
#for depth in range(1,5):
#  qie10_tdc_depth_x = qie10_tdc_depth_x_prefix + str(depth)
#  qie10_tdc_depth = f1.Get(qie10_tdc_depth_x)
#  qie10_tdc_depth.Draw("colz")
#  qie10_tdc_depth.SetTitle("Peak TDC depth " + str(depth) + ";iEta;iPhi")
#
#  canvas.SaveAs(outfile)

######--------------------------------------------------------------------------------------------
qie10_charge_fraction_TS2_depth_x_prefix = "qie10_charge_fraction_TS2_depth_"
for depth in range(1,5):
  qie10_charge_fraction_TS2_depth_x = qie10_charge_fraction_TS2_depth_x_prefix + str(depth)
  qie10_charge_fraction_TS2_depth = f1.Get(qie10_charge_fraction_TS2_depth_x)
  qie10_charge_fraction_TS2_depth.Draw("colz")
  qie10_charge_fraction_TS2_depth.SetTitle("TS2 charge fraction depth " + str(depth) + " ;iEta;iPhi")

  canvas.SaveAs(outfile)

####----------------------------------------------------------------------------------------------
hf_ieta_tdc_depth_x_ts_x_prefix0 = "hf_ieta_tdc_depth_"
for depth in range(1,5):
  hf_ieta_tdc_depth_x_ts_x_prefix = hf_ieta_tdc_depth_x_ts_x_prefix0 + str(depth) + "_ts_"
  canvas = r.TCanvas()
  canvas.Divide(3,1)
  for ts in range(0,3):
    canvas.cd(ts+1)
    hf_ieta_tdc_depth_x_ts_x = hf_ieta_tdc_depth_x_ts_x_prefix + str(ts)

    hf_ieta_tdc_depth_ts = f1.Get(hf_ieta_tdc_depth_x_ts_x)

    hf_ieta_tdc_depth_ts.Draw("colz")
    hf_ieta_tdc_depth_ts.SetTitle("depth "+str(depth)+", TS "+str(ts)+";iEta;TDC")
    
  canvas.SaveAs(outfile)
######-------------------------------------------------------------------------------------------
canvas = r.TCanvas()
r.gPad.SetLogy()
canvas.Update()
legend = r.TLegend(.75,.80,.95,.95)
hf_timing_all_channels_adc_x_prefix = "hf_timing_all_channels_adc_"
for cut in "0 30".split():
  draw = ""
    
  hf_timing_all_channels_adc_x = hf_timing_all_channels_adc_x_prefix + cut
  hf_timing_all_channels_adc = f1.Get(hf_timing_all_channels_adc_x)
  
  if cut != "0":
    draw = "same"
    hf_timing_all_channels_adc.SetLineColor(r.kRed) 
  hf_timing_all_channels_adc.Draw(draw)
  
  if cut == "0":
    hf_timing_all_channels_adc.SetTitle("all channels timing;timing(ns);Events")
  
  legend.AddEntry(hf_timing_all_channels_adc,"ADC > {}".format(cut))

legend.Draw("same")
canvas.SaveAs(outfile)
####--------------------------------------------------------------------------------------------
canvas.SaveAs(outfile + ']')

elapsed = time.clock() - start
print "All done, time used is: " + str(elapsed) + " secs..."
