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
    getParam.cc \
    visWaveform.cc \
    convert_wf.cc \
    convert_pr.cc \
    convert_pr.cc \
    convert_wf.cc \
    getParam.cc \
    visWaveform.cc \
    runAna_calibration_wf.cc \
    runAna_calibration_pr.cc \
    convert_rt.cc \
    convert_ps.cc \
    runAna_pr.cc \
    convert_wf_h8.cc

HEADERS += \
    include/Constants.hh \
    src/Tree.h

DISTFILES += \
    filelist.txt \
    README.md \
    filelist_pr_2016_10_18.txt \
    filelist_pr_2016_11_23.txt \
    filelist_wf_2016_10_18.txt \
    filelist_wf_2016_11_23.txt \
    filelist_rt_2016_10_18.txt \
    filelist_pr_2018_09_17.txt \
    filelist_wf_2018_09_17.txt \
    runAll.bash \
    filelist_wf_2017_12_12.txt \
    filelist_pr_2017_12_12.txt \
    filelist_wf_2017_05_30.txt \
    filelist_pr_2017_05_30.txt \
    filelist_wf_2017_09_18.txt \
    filelist_pr_2017_09_18.txt \
    filelist_wf_2018_11_07.txt \
    filelist_pr_2018_11_07.txt \
    filelist_wf_2017_10_20.txt \
    filelist_wf_2017_10_20_2.txt \
    filelist_wf_2017_10_20_v2.txt \
    filelist_wf_2018_06_18.txt \
    filelist_pr_2018_06_18.txt \
    filelist_rt_2018_06_18.txt
