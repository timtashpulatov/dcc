EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Power_Management:BTN8982TA Q1
U 1 1 5E38FF50
P 6000 2225
F 0 "Q1" H 5875 2725 50  0000 L CNN
F 1 "BTN8982TA" H 5575 2625 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:TO-263-7_TabPin8" H 5800 2675 50  0001 C CNN
F 3 "https://www.infineon.com/dgdl/Infineon-BTN8982TA-DS-v01_00-EN.pdf?fileId=db3a30433fa9412f013fbe32289b7c17" H 5950 2235 50  0001 C CNN
	1    6000 2225
	1    0    0    -1  
$EndComp
$Comp
L Power_Management:BTN8982TA Q2
U 1 1 5E391511
P 7475 2225
F 0 "Q2" H 7450 2700 50  0000 C CNN
F 1 "BTN8982TA" H 7300 2600 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:TO-263-7_TabPin8" H 7275 2675 50  0001 C CNN
F 3 "https://www.infineon.com/dgdl/Infineon-BTN8982TA-DS-v01_00-EN.pdf?fileId=db3a30433fa9412f013fbe32289b7c17" H 7425 2235 50  0001 C CNN
	1    7475 2225
	-1   0    0    -1  
$EndComp
$Comp
L 74xx:74HC04 U1
U 1 1 5E3935E7
P 4825 2975
F 0 "U1" H 4825 3325 50  0000 C CNN
F 1 "74HC04" H 4825 3250 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" H 4825 2725 50  0000 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT04.pdf" H 4825 2975 50  0001 C CNN
	1    4825 2975
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC04 U1
U 7 1 5E3955A9
P 1500 6825
F 0 "U1" H 1730 6871 50  0000 L CNN
F 1 "74HC04" H 1730 6780 50  0000 L CNN
F 2 "" H 1500 6825 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT04.pdf" H 1500 6825 50  0001 C CNN
	7    1500 6825
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 5E396A7C
P 9350 975
F 0 "J1" H 9430 1012 50  0000 L CNN
F 1 "Conn_01x06" H 9430 921 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-6_P5.08mm" H 9430 830 50  0000 L CNN
F 3 "~" H 9350 975 50  0001 C CNN
	1    9350 975 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 775  8675 775 
Wire Wire Line
	9150 875  8675 875 
Text GLabel 8675 775  0    50   Output ~ 0
VCC
$Comp
L power:GND #PWR0101
U 1 1 5E397AB3
P 8675 875
F 0 "#PWR0101" H 8675 625 50  0001 C CNN
F 1 "GND" H 8680 702 50  0001 C CNN
F 2 "" H 8675 875 50  0001 C CNN
F 3 "" H 8675 875 50  0001 C CNN
	1    8675 875 
	1    0    0    -1  
$EndComp
Text GLabel 9150 975  0    50   Input ~ 0
MAIN1
Text GLabel 9150 1075 0    50   Input ~ 0
MAIN2
Text GLabel 6300 2225 2    50   Output ~ 0
MAIN1
Text GLabel 7175 2225 0    50   Output ~ 0
MAIN2
Wire Wire Line
	6100 2625 6100 2700
Wire Wire Line
	6100 2700 6750 2700
Wire Wire Line
	7375 2700 7375 2625
$Comp
L power:GND #PWR0102
U 1 1 5E39949D
P 6750 2700
F 0 "#PWR0102" H 6750 2450 50  0001 C CNN
F 1 "GND" H 6755 2527 50  0001 C CNN
F 2 "" H 6750 2700 50  0001 C CNN
F 3 "" H 6750 2700 50  0001 C CNN
	1    6750 2700
	1    0    0    -1  
$EndComp
Connection ~ 6750 2700
Wire Wire Line
	6750 2700 7375 2700
Wire Wire Line
	6100 1825 6100 1500
Wire Wire Line
	6100 1500 6750 1500
Wire Wire Line
	7375 1500 7375 1825
Wire Wire Line
	6750 1500 6750 1250
Wire Wire Line
	6750 1250 7000 1250
Connection ~ 6750 1500
Wire Wire Line
	6750 1500 7375 1500
Text GLabel 7000 1250 2    50   Input ~ 0
VCC
$Comp
L Driver_Motor:A4953_LJ U2
U 1 1 5E39CF39
P 6500 5250
F 0 "U2" H 6275 5925 50  0000 C CNN
F 1 "A4953_LJ" H 6250 5850 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-8-1EP_3.9x4.9mm_Pitch1.27mm" H 6500 4675 50  0000 C CNN
F 3 "www.allegromicro.com/~/media/Files/Datasheets/A4952-3-Datasheet.ashx?la=en" H 6200 5600 50  0001 C CNN
	1    6500 5250
	1    0    0    -1  
$EndComp
Text GLabel 9150 1175 0    50   Input ~ 0
PROG1
Text GLabel 9150 1275 0    50   Input ~ 0
PROG2
Text GLabel 6900 5150 2    50   Input ~ 0
PROG1
Text GLabel 6900 5050 2    50   Input ~ 0
PROG2
Wire Wire Line
	6500 4850 6500 4500
Wire Wire Line
	6500 4500 7000 4500
Text GLabel 7425 4500 2    50   Input ~ 0
VCC
$Comp
L power:GND #PWR0103
U 1 1 5E39F2B0
P 6500 5650
F 0 "#PWR0103" H 6500 5400 50  0001 C CNN
F 1 "GND" H 6505 5477 50  0001 C CNN
F 2 "" H 6500 5650 50  0001 C CNN
F 3 "" H 6500 5650 50  0001 C CNN
	1    6500 5650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5E39F7AA
P 6600 5650
F 0 "#PWR0104" H 6600 5400 50  0001 C CNN
F 1 "GND" H 6605 5477 50  0001 C CNN
F 2 "" H 6600 5650 50  0001 C CNN
F 3 "" H 6600 5650 50  0001 C CNN
	1    6600 5650
	1    0    0    -1  
$EndComp
$Comp
L Bridges:R Rs1
U 1 1 5E3A4F5B
P 7000 5450
F 0 "Rs1" H 7070 5541 50  0000 L CNN
F 1 "0R25 1% 1W" H 7070 5450 50  0000 L CNN
F 2 "Resistors_SMD:R_2512" H 7070 5359 50  0000 L CNN
F 3 "" H 7000 5450 50  0001 C CNN
	1    7000 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 5250 7000 5250
Wire Wire Line
	7000 5250 7000 5300
$Comp
L power:GND #PWR0105
U 1 1 5E3A5749
P 7000 5600
F 0 "#PWR0105" H 7000 5350 50  0001 C CNN
F 1 "GND" H 7005 5427 50  0001 C CNN
F 2 "" H 7000 5600 50  0001 C CNN
F 3 "" H 7000 5600 50  0001 C CNN
	1    7000 5600
	1    0    0    -1  
$EndComp
Text GLabel 3875 900  2    50   Output ~ 0
+5V
$Comp
L 74xx:74HC04 U1
U 2 1 5E3A88F7
P 4800 5450
F 0 "U1" H 4800 5857 50  0000 C CNN
F 1 "74HC04" H 4800 5766 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" H 4800 5675 50  0000 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT04.pdf" H 4800 5450 50  0001 C CNN
	2    4800 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7075 3475 8225 3475
Wire Wire Line
	8225 3475 8225 2125
Wire Wire Line
	8225 2125 7775 2125
Wire Wire Line
	6475 3475 5175 3475
Wire Wire Line
	5175 3475 5175 2125
Wire Wire Line
	5175 2125 5700 2125
Wire Wire Line
	7775 2025 8000 2025
Wire Wire Line
	8000 2025 8000 2975
Wire Wire Line
	8000 2975 5250 2975
Wire Wire Line
	5250 2975 5250 2025
Wire Wire Line
	5250 2025 5700 2025
Connection ~ 5250 2975
Connection ~ 5175 3475
Wire Wire Line
	5100 5450 5250 5450
Wire Wire Line
	5250 5450 5250 5150
Wire Wire Line
	5250 5150 6100 5150
Wire Wire Line
	6100 5050 4375 5050
Wire Wire Line
	4500 5450 4375 5450
Wire Wire Line
	4375 5450 4375 5050
Connection ~ 4375 5050
Wire Wire Line
	4375 5050 3850 5050
Text GLabel 5650 5350 0    50   Input ~ 0
+5V
$Comp
L Amplifier_Operational:LM358 U3
U 1 1 5E3BC457
P 9550 3900
F 0 "U3" H 9550 4267 50  0000 C CNN
F 1 "LM358" H 9550 4176 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 9550 3650 50  0000 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 9550 3900 50  0001 C CNN
	1    9550 3900
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM358 U3
U 2 1 5E3BF2DF
P 8550 5350
F 0 "U3" H 8550 5717 50  0000 C CNN
F 1 "LM358" H 8550 5626 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 9525 5575 50  0000 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 8550 5350 50  0001 C CNN
	2    8550 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 5250 8250 5250
Connection ~ 7000 5250
Wire Wire Line
	3375 1850 3375 900 
Wire Wire Line
	3375 900  3875 900 
$Comp
L power:GND #PWR0106
U 1 1 5E3CD4ED
P 1500 7325
F 0 "#PWR0106" H 1500 7075 50  0001 C CNN
F 1 "GND" H 1505 7152 50  0001 C CNN
F 2 "" H 1500 7325 50  0001 C CNN
F 3 "" H 1500 7325 50  0001 C CNN
	1    1500 7325
	1    0    0    -1  
$EndComp
Text GLabel 4525 6325 2    50   Output ~ 0
+5V
Text Notes 7500 5200 0    50   ~ 0
+/- 500mV ?
Text Notes 7300 4925 0    50   ~ 0
0R25 for Vref=5V and Imax=2A
$Comp
L Bridges:R R4
U 1 1 5E3D5889
P 5700 2575
F 0 "R4" H 5900 2550 50  0000 R CNN
F 1 "1K" H 5950 2625 50  0000 R CNN
F 2 "Resistors_SMD:R_0805" V 5630 2575 50  0001 C CNN
F 3 "" H 5700 2575 50  0001 C CNN
	1    5700 2575
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5E3D6EA9
P 5700 2725
F 0 "#PWR0107" H 5700 2475 50  0001 C CNN
F 1 "GND" H 5705 2552 50  0001 C CNN
F 2 "" H 5700 2725 50  0001 C CNN
F 3 "" H 5700 2725 50  0001 C CNN
	1    5700 2725
	1    0    0    -1  
$EndComp
$Comp
L Bridges:R R5
U 1 1 5E3D732F
P 7775 2575
F 0 "R5" H 7705 2529 50  0000 R CNN
F 1 "1K" H 7705 2620 50  0000 R CNN
F 2 "Resistors_SMD:R_0805" V 7705 2575 50  0001 C CNN
F 3 "" H 7775 2575 50  0001 C CNN
	1    7775 2575
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5E3D7339
P 7775 2725
F 0 "#PWR0108" H 7775 2475 50  0001 C CNN
F 1 "GND" H 7780 2552 50  0001 C CNN
F 2 "" H 7775 2725 50  0001 C CNN
F 3 "" H 7775 2725 50  0001 C CNN
	1    7775 2725
	1    0    0    -1  
$EndComp
$Comp
L Bridges:R R7
U 1 1 5E3D8B55
P 8600 2550
F 0 "R7" H 8530 2504 50  0000 R CNN
F 1 "TBD" H 8530 2595 50  0000 R CNN
F 2 "Resistors_SMD:R_0805" V 8530 2550 50  0001 C CNN
F 3 "" H 8600 2550 50  0001 C CNN
	1    8600 2550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5E3D8B5F
P 8600 2700
F 0 "#PWR0109" H 8600 2450 50  0001 C CNN
F 1 "GND" H 8605 2527 50  0001 C CNN
F 2 "" H 8600 2700 50  0001 C CNN
F 3 "" H 8600 2700 50  0001 C CNN
	1    8600 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 2325 5450 2325
Wire Wire Line
	5450 2325 5450 3800
Wire Wire Line
	8600 2325 8600 2400
$Comp
L 74xx:74HC04 U1
U 3 1 5E3E9EA5
P 6775 3475
F 0 "U1" H 6775 3825 50  0000 C CNN
F 1 "74HC04" H 6775 3750 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" H 6775 3225 50  0000 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT04.pdf" H 6775 3475 50  0001 C CNN
	3    6775 3475
	1    0    0    -1  
$EndComp
Text Label 3375 2975 0    50   ~ 0
ENABLE_MAIN
Connection ~ 3375 900 
$Comp
L power:GND #PWR0110
U 1 1 5E3CCF82
P 2250 6925
F 0 "#PWR0110" H 2250 6675 50  0001 C CNN
F 1 "GND" H 2255 6752 50  0001 C CNN
F 2 "" H 2250 6925 50  0001 C CNN
F 3 "" H 2250 6925 50  0001 C CNN
	1    2250 6925
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5E3CBEAB
P 2825 3150
F 0 "#PWR0111" H 2825 2900 50  0001 C CNN
F 1 "GND" H 2830 2977 50  0001 C CNN
F 2 "" H 2825 3150 50  0001 C CNN
F 3 "" H 2825 3150 50  0001 C CNN
	1    2825 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5E3CBCC4
P 2725 3150
F 0 "#PWR0112" H 2725 2900 50  0001 C CNN
F 1 "GND" H 2730 2977 50  0001 C CNN
F 2 "" H 2725 3150 50  0001 C CNN
F 3 "" H 2725 3150 50  0001 C CNN
	1    2725 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5E3CB802
P 2625 3150
F 0 "#PWR0113" H 2625 2900 50  0001 C CNN
F 1 "GND" H 2630 2977 50  0001 C CNN
F 2 "" H 2625 3150 50  0001 C CNN
F 3 "" H 2625 3150 50  0001 C CNN
	1    2625 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3225 1850 3375 1850
$Comp
L Amplifier_Operational:LM358 U3
U 3 1 5E3C2076
P 2350 6625
F 0 "U3" H 2308 6671 50  0000 L CNN
F 1 "LM358" H 2308 6580 50  0000 L CNN
F 2 "" H 2350 6625 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 2350 6625 50  0001 C CNN
	3    2350 6625
	1    0    0    -1  
$EndComp
Wire Wire Line
	2925 900  3375 900 
Wire Wire Line
	2925 1050 2925 900 
$Comp
L MCU_Module:Arduino_UNO_R3 A1
U 1 1 5E38E585
P 2725 2050
F 0 "A1" H 2725 3500 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 2725 3425 50  0000 C CNN
F 2 "Modules:Arduino_UNO_R3_WithMountingHoles" H 2725 3350 50  0000 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 2725 2050 50  0001 C CNN
	1    2725 2050
	1    0    0    -1  
$EndComp
Text Label 3375 3475 0    50   ~ 0
DCC_SIGNAL_MAIN
Text Label 2750 5050 0    50   ~ 0
DCC_SIGNAL_PROG
$Comp
L Bridges:R R2
U 1 1 5E3D389B
P 1950 2450
F 0 "R2" V 1743 2450 50  0000 C CNN
F 1 "10K" V 1834 2450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1880 2450 50  0001 C CNN
F 3 "" H 1950 2450 50  0001 C CNN
	1    1950 2450
	0    1    1    0   
$EndComp
$Comp
L Bridges:R R1
U 1 1 5E3D427F
P 4225 2975
F 0 "R1" V 4018 2975 50  0000 C CNN
F 1 "10K" V 4109 2975 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 4155 2975 50  0001 C CNN
F 3 "" H 4225 2975 50  0001 C CNN
	1    4225 2975
	0    1    1    0   
$EndComp
$Comp
L Bridges:R R8
U 1 1 5E33BB43
P 8600 5775
F 0 "R8" V 8393 5775 50  0000 C CNN
F 1 "10K" V 8484 5775 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 8530 5775 50  0001 C CNN
F 3 "" H 8600 5775 50  0001 C CNN
	1    8600 5775
	0    1    1    0   
$EndComp
$Comp
L Bridges:R R6
U 1 1 5E33BF23
P 8250 6000
F 0 "R6" H 8125 5975 50  0000 C CNN
F 1 "1K" H 8100 6075 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 8180 6000 50  0001 C CNN
F 3 "" H 8250 6000 50  0001 C CNN
	1    8250 6000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5E33C3EE
P 8250 6150
F 0 "#PWR0114" H 8250 5900 50  0001 C CNN
F 1 "GND" H 8255 5977 50  0001 C CNN
F 2 "" H 8250 6150 50  0001 C CNN
F 3 "" H 8250 6150 50  0001 C CNN
	1    8250 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 5450 8250 5775
Wire Wire Line
	8450 5775 8250 5775
Connection ~ 8250 5775
Wire Wire Line
	8250 5775 8250 5850
Wire Wire Line
	8750 5775 8850 5775
Wire Wire Line
	8850 5775 8850 5350
Wire Wire Line
	8850 5350 9250 5350
Connection ~ 8850 5350
Text Notes 8550 6025 0    50   ~ 0
TBD
Wire Wire Line
	5125 2975 5250 2975
Wire Wire Line
	4375 2975 4525 2975
Wire Wire Line
	4075 2975 3375 2975
$Comp
L Bridges:R R3
U 1 1 5E34FD15
P 3700 5050
F 0 "R3" V 3493 5050 50  0000 C CNN
F 1 "10K" V 3584 5050 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3630 5050 50  0001 C CNN
F 3 "" H 3700 5050 50  0001 C CNN
	1    3700 5050
	0    1    1    0   
$EndComp
Wire Wire Line
	3550 5050 2750 5050
Text Notes 4250 4675 0    50   ~ 0
ENABLE PROG ???
Text Label 3225 2050 0    50   ~ 0
A0
Text Label 3225 2150 0    50   ~ 0
A1
Text Label 10075 3900 0    50   ~ 0
A0
Text Label 9250 5350 0    50   ~ 0
A1
$Comp
L Bridges:R R10
U 1 1 5E35866A
P 9600 4325
F 0 "R10" V 9393 4325 50  0000 C CNN
F 1 "10K" V 9484 4325 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 9530 4325 50  0001 C CNN
F 3 "" H 9600 4325 50  0001 C CNN
	1    9600 4325
	0    1    1    0   
$EndComp
$Comp
L Bridges:R R9
U 1 1 5E358674
P 9250 4550
F 0 "R9" H 9125 4525 50  0000 C CNN
F 1 "1K" H 9100 4625 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 9180 4550 50  0001 C CNN
F 3 "" H 9250 4550 50  0001 C CNN
	1    9250 4550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5E35867E
P 9250 4700
F 0 "#PWR0115" H 9250 4450 50  0001 C CNN
F 1 "GND" H 9255 4527 50  0001 C CNN
F 2 "" H 9250 4700 50  0001 C CNN
F 3 "" H 9250 4700 50  0001 C CNN
	1    9250 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 4000 9250 4325
Wire Wire Line
	9450 4325 9250 4325
Connection ~ 9250 4325
Wire Wire Line
	9250 4325 9250 4400
Wire Wire Line
	9750 4325 9850 4325
Wire Wire Line
	9850 4325 9850 3900
Text Notes 9550 4575 0    50   ~ 0
TBD
Wire Wire Line
	8425 3800 9250 3800
Wire Wire Line
	9850 3900 10075 3900
Connection ~ 9850 3900
Text Label 2225 1750 2    50   ~ 0
ENABLE_MAIN
Text Label 1625 2450 2    50   ~ 0
DCC_SIGNAL_MAIN
Text Label 1275 1950 2    50   ~ 0
DCC_SIGNAL_PROG
Wire Wire Line
	2225 2650 2075 2650
$Comp
L Bridges:R R12
U 1 1 5E36F49C
P 1925 2650
F 0 "R12" V 2025 2650 50  0000 C CNN
F 1 "DNF" V 2100 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1855 2650 50  0001 C CNN
F 3 "" H 1925 2650 50  0001 C CNN
	1    1925 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	1625 2450 1725 2450
Wire Wire Line
	1775 2650 1725 2650
Wire Wire Line
	1725 2650 1725 2450
Wire Wire Line
	2225 1650 1700 1650
$Comp
L Bridges:R R11
U 1 1 5E3736A4
P 1550 1650
F 0 "R11" V 1343 1650 50  0000 C CNN
F 1 "DNF" V 1434 1650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1480 1650 50  0001 C CNN
F 3 "" H 1550 1650 50  0001 C CNN
	1    1550 1650
	0    1    -1   0   
$EndComp
Wire Wire Line
	1400 1650 1350 1650
Wire Wire Line
	1350 1650 1350 1950
Wire Wire Line
	2225 1950 1350 1950
Connection ~ 1350 1950
Wire Wire Line
	1350 1950 1275 1950
$Comp
L Bridges:C C1
U 1 1 5E3D2AED
P 2850 6650
F 0 "C1" H 2965 6741 50  0000 L CNN
F 1 "100nF" H 2965 6650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2400 6350 50  0000 L CNN
F 3 "" H 2850 6650 50  0001 C CNN
	1    2850 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 6500 2850 6325
Wire Wire Line
	2850 6325 2250 6325
Wire Wire Line
	1500 6325 2250 6325
Connection ~ 2250 6325
Wire Wire Line
	2850 6325 3500 6325
Connection ~ 2850 6325
$Comp
L power:GND #PWR0116
U 1 1 5E3DE3FD
P 2850 6800
F 0 "#PWR0116" H 2850 6550 50  0001 C CNN
F 1 "GND" H 2855 6627 50  0001 C CNN
F 2 "" H 2850 6800 50  0001 C CNN
F 3 "" H 2850 6800 50  0001 C CNN
	1    2850 6800
	1    0    0    -1  
$EndComp
$Comp
L Bridges:C C2
U 1 1 5E3E0ED9
P 3500 6650
F 0 "C2" H 3615 6741 50  0000 L CNN
F 1 "100nF" H 3615 6650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3615 6559 50  0000 L CNN
F 3 "" H 3500 6650 50  0001 C CNN
	1    3500 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 6500 3500 6325
$Comp
L power:GND #PWR0117
U 1 1 5E3E0EE4
P 3500 6800
F 0 "#PWR0117" H 3500 6550 50  0001 C CNN
F 1 "GND" H 3505 6627 50  0001 C CNN
F 2 "" H 3500 6800 50  0001 C CNN
F 3 "" H 3500 6800 50  0001 C CNN
	1    3500 6800
	1    0    0    -1  
$EndComp
Connection ~ 3500 6325
Wire Wire Line
	3500 6325 4525 6325
$Comp
L Bridges:C C4
U 1 1 5E3F3358
P 7000 4650
F 0 "C4" H 7115 4741 50  0000 L CNN
F 1 "100nF" H 7115 4650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7115 4559 50  0000 L CNN
F 3 "" H 7000 4650 50  0001 C CNN
	1    7000 4650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 5E3F3362
P 7000 4800
F 0 "#PWR0118" H 7000 4550 50  0001 C CNN
F 1 "GND" H 7005 4627 50  0001 C CNN
F 2 "" H 7000 4800 50  0001 C CNN
F 3 "" H 7000 4800 50  0001 C CNN
	1    7000 4800
	1    0    0    -1  
$EndComp
Connection ~ 7000 4500
Wire Wire Line
	7000 4500 7425 4500
Wire Wire Line
	5650 5350 5725 5350
$Comp
L Bridges:C C3
U 1 1 5E3FE578
P 5725 5500
F 0 "C3" H 5840 5591 50  0000 L CNN
F 1 "100nF" H 5840 5500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4825 5400 50  0000 L CNN
F 3 "" H 5725 5500 50  0001 C CNN
	1    5725 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 5E3FE582
P 5725 5650
F 0 "#PWR0119" H 5725 5400 50  0001 C CNN
F 1 "GND" H 5730 5477 50  0001 C CNN
F 2 "" H 5725 5650 50  0001 C CNN
F 3 "" H 5725 5650 50  0001 C CNN
	1    5725 5650
	1    0    0    -1  
$EndComp
Connection ~ 5725 5350
Wire Wire Line
	5725 5350 6100 5350
Wire Wire Line
	5450 3800 8425 3800
$Comp
L Bridges:R R13
U 1 1 5E41702A
P 5450 4025
F 0 "R13" H 5380 3979 50  0000 R CNN
F 1 "TBD" H 5380 4070 50  0000 R CNN
F 2 "Resistors_SMD:R_0805" V 5380 4025 50  0001 C CNN
F 3 "" H 5450 4025 50  0001 C CNN
	1    5450 4025
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 5E417034
P 5450 4175
F 0 "#PWR0120" H 5450 3925 50  0001 C CNN
F 1 "GND" H 5455 4002 50  0001 C CNN
F 2 "" H 5450 4175 50  0001 C CNN
F 3 "" H 5450 4175 50  0001 C CNN
	1    5450 4175
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3800 5450 3875
Connection ~ 5450 3800
$Comp
L Bridges:R R14
U 1 1 5E41AD43
P 8425 3375
F 0 "R14" V 8525 3425 50  0000 R CNN
F 1 "DNF" V 8300 3450 50  0000 R CNN
F 2 "Resistors_SMD:R_0805" V 8355 3375 50  0001 C CNN
F 3 "" H 8425 3375 50  0001 C CNN
	1    8425 3375
	-1   0    0    1   
$EndComp
$Comp
L Bridges:C C5
U 1 1 5E41E57C
P 8425 3950
F 0 "C5" H 8540 4041 50  0000 L CNN
F 1 "DNF" H 8540 3950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7475 3825 50  0000 L CNN
F 3 "" H 8425 3950 50  0001 C CNN
	1    8425 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 5E41E586
P 8425 4100
F 0 "#PWR0121" H 8425 3850 50  0001 C CNN
F 1 "GND" H 8430 3927 50  0001 C CNN
F 2 "" H 8425 4100 50  0001 C CNN
F 3 "" H 8425 4100 50  0001 C CNN
	1    8425 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7775 2325 8425 2325
Connection ~ 8425 3800
Wire Wire Line
	8425 3525 8425 3800
Wire Wire Line
	8425 3225 8425 2325
Connection ~ 8425 2325
Wire Wire Line
	8425 2325 8600 2325
$Comp
L Device:CP1 C6
U 1 1 5E44E46C
P 6750 1750
F 0 "C6" H 6865 1841 50  0000 L CNN
F 1 "100uF 50V" H 6865 1750 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_6.3x5.3" H 6800 2075 50  0000 L CNN
F 3 "~" H 6750 1750 50  0001 C CNN
	1    6750 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 1600 6750 1500
Wire Wire Line
	6750 2700 6750 1900
Wire Wire Line
	3375 3475 5175 3475
Wire Wire Line
	1800 2450 1725 2450
Connection ~ 1725 2450
Wire Wire Line
	2100 2450 2225 2450
$Comp
L Device:Ferrite_Bead_Small FB1
U 1 1 5E3E685D
P 3400 4025
F 0 "FB1" V 3073 4025 50  0000 C CNN
F 1 "Ferrite_Bead_Small" V 3164 4025 50  0000 C CNN
F 2 "Inductors_SMD:L_0805_HandSoldering" V 3255 4025 50  0000 C CNN
F 3 "~" H 3400 4025 50  0001 C CNN
	1    3400 4025
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 5E3E774A
P 3300 4025
F 0 "#PWR0122" H 3300 3775 50  0001 C CNN
F 1 "GND" H 3305 3852 50  0001 C CNN
F 2 "" H 3300 4025 50  0001 C CNN
F 3 "" H 3300 4025 50  0001 C CNN
	1    3300 4025
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 5E3E7E28
P 3500 4025
F 0 "#PWR0123" H 3500 3775 50  0001 C CNN
F 1 "GND" H 3505 3852 50  0001 C CNN
F 2 "" H 3500 4025 50  0001 C CNN
F 3 "" H 3500 4025 50  0001 C CNN
	1    3500 4025
	1    0    0    -1  
$EndComp
$EndSCHEMATC
