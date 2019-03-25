#!/bin/bash

echo "--> Started to run CpFM data analysis.";

echo "--> Compilation.";
make clean; make -j2;
echo "--> Convertation of the data.";

#protons 2018_09_17
#./convert_pr /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2018_09_17/CpFM_Local_Data/ filelist_pr_2018_09_17.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2018_09_17.root;
#./convert_wf /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2018_09_17/CpFM_Local_Data/ filelist_wf_2018_09_17.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2018_09_17.root;

#protons 2016_10_18
#./convert_wf /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2016_10_18/CpFM_Local_Data/ filelist_wf_2016_10_18.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_10_18.root;
#./convert_pr /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2016_10_18/CpFM_Local_Data/ filelist_pr_2016_10_18.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2016_10_18.root;
#./convert_rt /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2016_10_18/CpFM_Local_Data/ filelist_rt_2016_10_18.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_rt_2016_10_18.root;

#ions 2016_11_23
#./convert_pr /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2016_11_23/CpFM_Local_Data/ filelist_pr_2016_11_23.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2016_11_23.root;
#./convert_wf /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2016_11_23/CpFM_Local_Data/ filelist_wf_2016_11_23.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_11_23.root;

#ions 2017_12_12
#./convert_pr /media/andrii/StorageUA9/MDs/MD_2017_12_12/CpFM_Local_Data/ filelist_pr_2017_12_12.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2017_12_12.root;
#./convert_wf /media/andrii/StorageUA9/MDs/MD_2017_12_12/CpFM_Local_Data/ filelist_wf_2017_12_12.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_12_12.root;

#proton 2017_05_30
#./convert_pr /media/andrii/StorageUA9/MDs/MD_2017_05_30/CpFM_Local_Data/ filelist_pr_2017_05_30.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2017_05_30.root;
#./convert_wf /media/andrii/StorageUA9/MDs/MD_2017_05_30/CpFM_Local_Data/ filelist_wf_2017_05_30.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_05_30.root;

#proton 2017_09_18
#./convert_pr /media/andrii/StorageUA9/MDs/MD_2017_09_18/CpFM_Local_Data/ filelist_pr_2017_09_18.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2017_09_18.root;
#./convert_wf /media/andrii/StorageUA9/MDs/MD_2017_09_18/CpFM_Local_Data/ filelist_wf_2017_09_18.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_09_18.root;

#protons 2018_11_07
#./convert_pr /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2018_11_07/CpFM_Local_Data/ filelist_pr_2018_11_07.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2018_11_07.root;
#./convert_wf /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2018_11_07/CpFM_Local_Data/ filelist_wf_2018_11_07.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2018_11_07.root;

#protons 2017_10_20
#./convert_wf_h8 /media/andrii/StorageUA9/H8_October_2017/Run_Scan_long_Pyramid2_Xfrom_moins15_to_140_Data_10_20_2017_Ascii/ filelist_wf_2017_10_20.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_10_20.root;
#./convert_wf_h8 /media/andrii/StorageUA9/H8_October_2017/Run_Scan_long_Pyramid2_Xfrom_moins15_to_140_v2_Data_10_20_2017_Ascii/ filelist_wf_2017_10_20_v2.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_10_20_v2.root;
#./convert_wf_h8 /media/andrii/StorageUA9/H8_October_2017/Run_scan_pyramid1_1mm_sec_from_X-5_to140_Data_10_20_2017_Ascii/ filelist_wf_2017_10_20_2.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_10_20_2.root;

#protons 2018_06_18
#./convert_pr /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2018_06_18/CpFM_Local_Data/ filelist_pr_2018_06_18.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2018_06_18.root;
#./convert_wf /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2018_06_18/CpFM_Local_Data/ filelist_wf_2018_06_18.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2018_06_18.root;
#./convert_rt /home/andrii/dfs/Experiments/UA9/Data_SPS_runs/MD_2018_06_18/CpFM_Local_Data/ filelist_rt_2018_06_18.txt /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_rt_2018_06_18.root;


echo "--> Visualisation of the data.";
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_10_18.root 235437 2;
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_10_18.root 244357 2;
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_11_23.root 93808 2; # R1
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_11_23.root 237346 2; # R2
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_11_23.root 223680 2; # R5
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_12_12.root 472 1;
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_10_20_2.root 472 0;
#./visWaveform /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_10_20_v2.root 472 0;

echo "--> Getting Waveform parameters"
#protons 2016_10_18
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_10_18.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2016_10_18.root;
#ions 2016_11_23
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2016_11_23.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2016_11_23.root;

#protons 2018_09_17
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2018_09_17.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2018_09_17.root;

#ions 2017_12_12
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_12_12.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_12_12.root;

#protons 2017_05_30
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_05_30.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_05_30.root;

#protons 2017_09_18
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_09_18.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_09_18.root;

#protons 2018_09_17
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2018_11_07.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2018_11_07.root;

#protons 2018_10_20
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_10_20.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_10_20.root;
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_10_20_v2.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_10_20_v2.root;
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2017_10_20_2.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_10_20_2.root;

#protons 2018_06_18
#./getParam /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output1_wf_2018_06_18.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2018_06_18.root;

echo "--> Getting Motor LVDT position"
#protons 2016_10_18
#./convert_ps cpfm_linear_scan_1.dat cpfm_linear_scan_1.root
#protons 2018_09_17
#./convert_ps cpfm_linear_scan_2018_09_17.dat cpfm_linear_scan_2018_09_17.root
#./convert_ps cpfm_linear_scan_2018_09_17_dch.dat cpfm_linear_scan_2018_09_17_dch.root
#protons 2018_11_07
#./convert_ps cpfm_linear_scan_2018_11_07_dch.dat cpfm_linear_scan_2018_11_07_dch.root
#protons 2018_06_18
#./convert_ps crystal1_angularscan_2018_06_18.dat crystal1_angularscan_2018_06_18.root
#protons 2017_12_12
#./convert_ps crystal4_angularscan_2017_12_12.dat crystal4_angularscan_2017_12_12.root
#./convert_ps blm_crystal4_angularscan_2017_12_12.dat blm_crystal4_angularscan_2017_12_12.root

echo "--> Running Calibration"
#ions 2016_11_23
#./runAna_calibration_wf /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2016_11_23.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output3_wf_2016_11_23.root
#./runAna_calibration_pr /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2016_11_23.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output3_pr_2016_11_23.root

#ions 2017_12_12
#./runAna_calibration_wf /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_wf_2017_12_12.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output3_wf_2017_12_12.root
#./runAna_calibration_pr /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output2_pr_2017_12_12.root /media/andrii/F492773C92770302/CpfmData/ROOT_FILES/output3_pr_2017_12_12.root

echo "--> Running Data Analysis"
#./runAna_pr 1
#./runAna_pr 2
#./runAna_pr 3
#./runAna_pr 4
#./runAna_pr 5
./runAna_pr 6
#./runAna_pr 7
#./runAna_pr 8
#./runAna_pr 9
#./runAna_pr 10

echo "--> Finished."


