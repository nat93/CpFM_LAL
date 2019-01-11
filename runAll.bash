#!/bin/bash

echo "--> Started to run CpFM data analysis.";

echo "--> Compilation.";
make clean; make -j2;

echo "--> Convertation of the data.";
#protons 2016
#./convert_wf /home/andrii/gred/Downloads/cern_data/MD_2016_10_18/Detectors_old_format/CpFM/ filelist_wf.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1.root;
#./convert_pr /home/andrii/gred/Downloads/cern_data/MD_2016_10_18/Detectors_old_format/CpFM/ filelist_pr.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output4.root;
#ions 2016
#./convert_wf /home/andrii/gred/Downloads/cern_data/MD_2016_11_23/Detectors_old_format/CpFM/ filelist_wf_ions.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_ions.root;
#./convert_pr /home/andrii/gred/Downloads/cern_data/MD_2016_11_23/Detectors_old_format/CpFM/ filelist_pr_ions.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output4_ions.root;

echo "--> Visualisation of the data.";
#protons 2016
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1.root 235437 2;
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1.root 244357 2;
#ions 2016
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_ions.root 93808 2; # R1
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_ions.root 237346 2; # R2
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_ions.root 223680 2; # R5

echo "--> Getting Waveform parameters"
#protons 2016
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2.root;
#ions 2016
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_ions.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_ions.root;

echo "--> Getting Motor LVDT position"
#./get_position ./root_files/2016_10_18_sps_full.root 1476741600000000 ./root_files/output2.root position_wf.root;
#./get_position ./root_files/2016_10_18_nobctfr.root 1476741600000000 ./root_files/output4.root ./root_files/position_pr.root;

echo "--> Running analysis"
#protons 2016
#./runAna_protons ./root_files/output2.root ./root_files/output3.root ./root_files/position_wf.root;
#./runAna_protons ./root_files/output4.root ./root_files/output5.root ./root_files/position_pr.root;
#ions 2016
#./runAna_calibration_wf /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_ions.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output3_ions.root
#./runAna_calibration_pr /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output4_ions.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output5_ions.root

echo "--> Finished."


