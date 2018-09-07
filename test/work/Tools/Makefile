CXX=`root-config --cxx`
CXXFLAGS=`root-config --cflags`
LDFLAGS=`root-config --ldflags`
LDLIBS=`root-config --glibs`
#ROOTLIBS='-lRooFit -lHtml -lMinuit -lRooFitCore -lRooStats -lHistFactory'


# Assumes that the script is in MyScript.C
# # and it must contain a main() function
#
all: HcalPfgStudies

% : %.C
	g++ -g -Wall `root-config --cflags --libs` -L $(ROOTSYS)/lib $(ROOTLIBS) $? -o $@

