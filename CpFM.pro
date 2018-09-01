TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "/home/andrii/root/include"
#INCLUDEPATH += "/home/gred/root_v5.34.34/root/include"

LIBS += -L/home/andrii/root/lib -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread

SOURCES += \
    convertor.cc \
    src/Tree.C \
    runAna_ions.cc \
    runAna_protons.cc \
    getParam.cc \
    visWaveform.cc \
    plotHisto.C \
    convert_wf.cc \
    convert_pr.cc \
    get_position.cc \
    convert_pr.cc \
    convert_wf.cc \
    getParam.cc \
    get_position.cc \
    plotHisto.C \
    runAna_ions.cc \
    runAna_protons.cc \
    visWaveform.cc

HEADERS += \
    include/Constants.hh \
    runAll.bash \
    src/Tree.h

DISTFILES += \
    filelist.txt \
    runAll.bash \
    README.md \
    filelist_pr.txt \
    filelist_pr_ions.txt \
    filelist_wf.txt \
    filelist_wf_ions.txt
