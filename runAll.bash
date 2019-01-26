#!/bin/bash

echo "--> Started to run CpFM data analysis.";

echo "--> Compilation.";
#make clean; make -j2;
echo "--> Convertation of the data.";

#protons 2016_10_18
#./convert_wf /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2016_10_18/CpFM_Local_Data/ filelist_wf_2016_10_18.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_10_18.root;
#./convert_pr /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2016_10_18/CpFM_Local_Data/ filelist_pr_2016_10_18.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2016_10_18.root;
#./convert_rt /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2016_10_18/CpFM_Local_Data/ filelist_rt_2016_10_18.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_rt_2016_10_18.root;

#ions 2016_11_23
#./convert_wf /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2016_11_23/CpFM_Local_Data/ filelist_wf_2016_11_23.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_11_23.root;
#./convert_pr /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2016_11_23/CpFM_Local_Data/ filelist_pr_2016_11_23.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2016_11_23.root;

echo "--> Visualisation of the data.";
#protons 2016_10_18
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_10_18.root 235437 2;
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_10_18.root 244357 2;
#ions 2016_11_23
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_11_23.root 93808 2; # R1
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_11_23.root 237346 2; # R2
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_11_23.root 223680 2; # R5

echo "--> Getting Waveform parameters"
#protons 2016_10_18
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_10_18.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2016_10_18.root;
#ions 2016_11_23
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_11_23.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2016_11_23.root;

echo "--> Getting Motor LVDT position"
#make convert_ps;
#./convert_ps cpfm_linear_scan_1.dat cpfm_linear_scan_1.root

echo "--> Running Calibration"
#ions 2016_11_23
#./runAna_calibration_wf /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2016_11_23.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output3_wf_2016_11_23.root
#./runAna_calibration_pr /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2016_11_23.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output3_pr_2016_11_23.root

echo "--> Running Data Analysis"
make runAna_pr;
#protons 2016_10_18
#./runAna_pr 2
./runAna_pr 3

echo "--> Finished."


