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
L MCU_ST_STM32F0:STM32F030F4Px U1
U 1 1 5E650D5B
P 5650 3500
F 0 "U1" H 5325 4175 50  0000 C CNN
F 1 "STM32F030F4Px" H 6150 4175 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 5250 2800 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00088500.pdf" H 5650 3500 50  0001 C CNN
	1    5650 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5E6518CE
P 5650 4300
F 0 "#PWR0101" H 5650 4050 50  0001 C CNN
F 1 "GND" H 5655 4127 50  0001 C CNN
F 2 "" H 5650 4300 50  0001 C CNN
F 3 "" H 5650 4300 50  0001 C CNN
	1    5650 4300
	1    0    0    -1  
$EndComp
$Comp
L loco:NSR2030 D1
U 1 1 5E65250C
P 2500 2350
F 0 "D1" H 2500 2715 50  0000 C CNN
F 1 "NSR2030" H 2500 2624 50  0000 C CNN
F 2 "loco:NSR2030" H 2500 2533 50  0000 C CNN
F 3 "" H 2500 2350 50  0001 C CNN
	1    2500 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 2400 2900 2400
Wire Wire Line
	2900 2400 2900 2575
Wire Wire Line
	2900 2575 1975 2575
Wire Wire Line
	2250 2300 1975 2300
Text GLabel 1975 2300 0    50   Input ~ 0
RAIL1
Text GLabel 1975 2575 0    50   Input ~ 0
RAIL2
$Comp
L power:GND #PWR0102
U 1 1 5E652E8A
P 2875 2025
F 0 "#PWR0102" H 2875 1775 50  0001 C CNN
F 1 "GND" H 2880 1852 50  0001 C CNN
F 2 "" H 2875 2025 50  0001 C CNN
F 3 "" H 2875 2025 50  0001 C CNN
	1    2875 2025
	-1   0    0    1   
$EndComp
Wire Wire Line
	2875 2025 2875 2300
Wire Wire Line
	2875 2300 2750 2300
Wire Wire Line
	2250 2400 2175 2400
Wire Wire Line
	2175 2400 2175 2700
Wire Wire Line
	2175 2700 3175 2700
$Comp
L Driver_Motor:A4953_LJ U2
U 1 1 5E653C2B
P 3200 4325
F 0 "U2" H 3400 4800 50  0000 C CNN
F 1 "A4953_LJ" H 3425 4700 50  0000 C CNN
F 2 "Package_SO:SOIC-8-1EP_3.9x4.9mm_P1.27mm_EP2.41x3.3mm" H 3200 3775 50  0001 C CNN
F 3 "www.allegromicro.com/~/media/Files/Datasheets/A4952-3-Datasheet.ashx?la=en" H 2900 4675 50  0001 C CNN
	1    3200 4325
	1    0    0    -1  
$EndComp
Text Label 2850 2700 0    50   ~ 0
27V
Text Label 5150 3000 2    50   ~ 0
NRST
Text Label 5150 3200 2    50   ~ 0
BOOT0
Wire Wire Line
	5650 2800 5650 2700
Wire Wire Line
	5750 2800 5750 2700
Wire Wire Line
	5750 2700 5650 2700
Connection ~ 5650 2700
Wire Wire Line
	5650 2700 5650 2600
Text Label 5650 2600 0    50   ~ 0
+3V3
$Comp
L power:GND #PWR?
U 1 1 5E657AD9
P 3200 4825
F 0 "#PWR?" H 3200 4575 50  0001 C CNN
F 1 "GND" H 3205 4652 50  0001 C CNN
F 2 "" H 3200 4825 50  0001 C CNN
F 3 "" H 3200 4825 50  0001 C CNN
	1    3200 4825
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 4725 3200 4775
Wire Wire Line
	3300 4725 3300 4775
Wire Wire Line
	3300 4775 3200 4775
Connection ~ 3200 4775
Wire Wire Line
	3200 4775 3200 4825
Wire Wire Line
	3600 4125 3825 4125
Wire Wire Line
	3600 4225 3825 4225
Text Label 3825 4125 0    50   ~ 0
M1
Text Label 3825 4225 0    50   ~ 0
M2
Text Label 2800 4125 2    50   ~ 0
IN1
Text Label 2800 4225 2    50   ~ 0
IN2
Text Label 3200 3925 2    50   ~ 0
27V
$EndSCHEMATC
