# CpFM_Data_Analysis
The data analysis scripts for the CpFM detector.
1. Data format:

>>>>>> File name: measurement-2017-09-18T21.46.30.587254.dat -- USB-WaveCatcher parameter measuremets

=== DATA FILE SAVED WITH WAVECATCHERDIM DEV VERSION BUILT : Mar  2 2016 09:49:57 ===
=== ChannelNb ChannelName EventID MeasuredBaseline[Volts] Amplitude[Volts] PeakTime[ns] Charge[pC] LeadingEdgeTime[ns] TrailingEdgeTime[ns] Peaks[count] ===
=== Event 2520000 UnixTime = 1505763990587254 Timestamp = 2017-09-18T21.46.30.587254 TDC = 419822685922 ===
0 Trigger 2520000 -0.000381 -0.823119 148.125000 -107000.000000 169.562988 131.610107 2
2 CpFM1 2520000 1.135363 -0.086163 129.375000 -2935.000000 134.825439 125.556641 4
4 CpFM2 2520000 0.000076 -0.003126 313.750000 4194303.000000 314.074707 313.255615 0
=== Event 2520001 UnixTime = 1505763990610316 Timestamp = 2017-09-18T21.46.30.610316 TDC = 419827296784 ===
0 Trigger 2520001 0.000000 -0.823500 151.562500 -104997.000000 172.514648 134.604492 2
2 CpFM1 2520001 1.135248 -0.088450 131.875000 -3110.000000 137.939453 128.249512 5
4 CpFM2 2520001 0.000114 -0.003126 308.750000 4194303.000000 309.855957 307.161865 0

>>>>>> File name: waveform-2017-09-18T17.06.57.773551.dat -- WaveForms data

=== DATA FILE SAVED WITH WAVECATCHERDIM DEV VERSION BUILT : Mar  2 2016 09:50:02 ===
=== SampleRate = 3.2GHz ===
=== Event 1792500 UnixTime = 1505747217773551 Time = 2017-09-18T17.06.57.773551 TDC = 363840070364 ===
=== CH: 0 CHNAME: Trigger EVENTID: 1792500 Baseline: -0.000801 Amplitude: -0.825101 PeakTime: 148.750000 Charge: -105631.000000 RisingEdgeTime: 169.882813 FallingEdgeTime: 131.942139 Peaks: 2
-0.001200 -0.000645 -0.000799 -0.000459 ... (1024 points)
=== CH: 2 CHNAME: CpFM1 EVENTID: 1792500 Baseline: 1.135019 Amplitude: -0.008311 PeakTime: 129.375000 Charge: -282.000000 RisingEdgeTime: 133.292236 FallingEdgeTime: 126.611328 Peaks: 3
1.134333 1.135353 1.135138 1.133069 1.133657 ... (1024 points)
=== CH: 4 CHNAME: CpFM2 EVENTID: 1792500 Baseline: 0.000076 Amplitude: -0.002516 PeakTime: 157.187500 Charge: -22.000000 RisingEdgeTime: 157.554932 FallingEdgeTime: 156.926270 Peaks: 0
-0.000202 0.001180 0.000006 -0.000273 0.000918 ... (1024 points)

>>>>>> File name: rate-2017-09-18T12.24.03.122755.dat -- USB-WaveCatcher rate measurements

=== DATA FILE SAVED WITH WAVECATCHERDIM DEV VERSION BUILT : Mar  2 2016 09:50:00 ===
=== Rates [Hz] of: Trigger CpFM1 CpFM2 ===
=== Rates [Hz] of counter: 0:0 0:2 1:0 ===
=== Event 1062500 UnixTime = 1505730243122755 Timestamp = 2017-09-18T12.24.03.122755 TDC = 903315290287 ===
43.372658 174054.476058 0.000000
=== Event 1062501 UnixTime = 1505730243145730 Timestamp = 2017-09-18T12.24.03.145730 TDC = 903319901794 ===
43.372658 182772.380291 0.000000

2. Command line (runAll.bash):

filelistName.txt -- the list of the DAT file with a RAW data.

1) To convert USBWC parameters to a single ROOT file:
>> ./convert_pr /dataFilePath/ filelistName.txt outputFilesName2_pr.root;
2) To convert waveforms to a single ROOT file:
>> ./convert_wf /dataFilePath/ filelistName.txt outputFilesName1_wf.root;
3) To extract waveform parameters:
>> ./getParam outputFilesName1.root outputFilesName2_wf.root;
4) To visualize the waveform:
>> ./visWaveform outputFilesName1_wf.root eventID channelID;
5) For ion calibration:
(USBWC parameters)
>> ./runAna_calibration_pr outputFilesName2_pr.root outputFilesName3_pr.root
(Offline analysis parameters)
>> ./runAna_calibration_wf outputFilesName2_wf.root outputFilesName3_wf.root
5) For analysis:
>> ./runAna_pr runMode
