ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
EXTRALIBS += $(shell $(ROOTSYS)/bin/root-config --libs)
LDLIBS += $(shell $(ROOTSYS)/bin/root-config --libs)

#ROOTCFLAGS    = $(shell /usr/bin/root-config --cflags)
#ROOTLIBS      = $(shell /usr/bin/root-config --libs)
#ROOTGLIBS     = $(shell /usr/bin/root-config --glibs)

CXX           = g++
CXXFLAGS      = -g -Wall -fPIC -Wno-deprecated

NGLIBS         = $(ROOTGLIBS) 
NGLIBS        += -lMinuit

CXXFLAGS      += $(ROOTCFLAGS)
CXX           += -I./
LIBS           = $(ROOTLIBS) 

GLIBS          = $(filter-out -lNew, $(NGLIBS))

CXX	      += -I./obj/
OUTLIB	      = ./obj/
.SUFFIXES: .cc,.C
.PREFIXES: ./obj/

#----------------------------------------------------#

all: get_position convert_wf convert_pr getParam runAna_calibration_wf runAna_calibration_pr visWaveform

get_position: get_position.cc

convert_wf: convert_wf.cc

convert_pr: convert_pr.cc

runAna_calibration_wf: runAna_calibration_wf.cc

runAna_calibration_pr: runAna_calibration_pr.cc

getParam: getParam.cc obj/Tree.o  obj/Tree.o
	$(CXX) $(CXXFLAGS) -o getParam $(OUTLIB)/*.o $(GLIBS) $<

visWaveform: visWaveform.cc obj/Tree.o  obj/Tree.o
	$(CXX) $(CXXFLAGS) -o visWaveform $(OUTLIB)/*.o $(GLIBS) $<

obj/Tree.o: src/Tree.C src/Tree.h 
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)CpFMclass.o $<

clean:
	rm -f *~
	rm -f $(OUTLIB)*.o
	rm -f get_position
	rm -f convert_wf
	rm -f convert_pr
	rm -f getParam
	rm -f visWaveform
	rm -r runAna_calibration_wf
	rm -r runAna_calibration_pr