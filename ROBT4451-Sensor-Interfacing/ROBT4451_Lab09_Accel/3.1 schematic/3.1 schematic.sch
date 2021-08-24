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
Text GLabel 3650 5550 0    50   Input ~ 0
Vouty
$Comp
L 3.1-schematic-rescue:R_US-Device R15
U 1 1 607AF7D1
P 4200 5550
F 0 "R15" H 4268 5596 50  0000 L CNN
F 1 "100k" H 4268 5505 50  0000 L CNN
F 2 "" V 4240 5540 50  0001 C CNN
F 3 "~" H 4200 5550 50  0001 C CNN
	1    4200 5550
	0    1    -1   0   
$EndComp
$Comp
L 3.1-schematic-rescue:R_US-Device R16
U 1 1 607B4835
P 5050 5100
F 0 "R16" H 5118 5146 50  0000 L CNN
F 1 "100k" H 5118 5055 50  0000 L CNN
F 2 "" V 5090 5090 50  0001 C CNN
F 3 "~" H 5050 5100 50  0001 C CNN
	1    5050 5100
	0    1    -1   0   
$EndComp
$Comp
L 3.1-schematic-rescue:R_US-Device R19
U 1 1 607B4E7E
P 7650 5200
F 0 "R19" H 7718 5246 50  0000 L CNN
F 1 "100k" H 7718 5155 50  0000 L CNN
F 2 "" V 7690 5190 50  0001 C CNN
F 3 "~" H 7650 5200 50  0001 C CNN
	1    7650 5200
	0    1    -1   0   
$EndComp
Wire Wire Line
	3650 5550 4050 5550
Wire Wire Line
	4350 5550 4750 5550
Wire Wire Line
	5350 5650 5750 5650
Wire Wire Line
	6050 5650 6050 5800
Wire Wire Line
	6050 5800 6600 5800
Wire Wire Line
	4750 5750 4750 5950
$Comp
L 3.1-schematic-rescue:GND-power #PWR?
U 1 1 607C89E7
P 4750 5950
F 0 "#PWR?" H 4750 5700 50  0001 C CNN
F 1 "GND" H 4755 5777 50  0000 C CNN
F 2 "" H 4750 5950 50  0001 C CNN
F 3 "" H 4750 5950 50  0001 C CNN
	1    4750 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 5850 7350 6050
$Comp
L 3.1-schematic-rescue:GND-power #PWR?
U 1 1 607C91CA
P 7350 6050
F 0 "#PWR?" H 7350 5800 50  0001 C CNN
F 1 "GND" H 7355 5877 50  0000 C CNN
F 2 "" H 7350 6050 50  0001 C CNN
F 3 "" H 7350 6050 50  0001 C CNN
	1    7350 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5650 5350 5100
Wire Wire Line
	5350 5100 5200 5100
Connection ~ 5350 5650
Wire Wire Line
	4750 5550 4750 5100
Wire Wire Line
	4750 5100 4900 5100
Connection ~ 4750 5550
Wire Wire Line
	7350 5650 7350 5200
Wire Wire Line
	7350 5200 7500 5200
Connection ~ 7350 5650
Wire Wire Line
	7950 5750 7950 5200
Wire Wire Line
	7950 5200 7800 5200
Wire Wire Line
	7950 5750 8350 5750
Connection ~ 7950 5750
$Comp
L 3.1-schematic-rescue:R_US-Device R17
U 1 1 607B1D0D
P 5900 5650
F 0 "R17" H 5968 5696 50  0000 L CNN
F 1 "1k" H 5968 5605 50  0000 L CNN
F 2 "" V 5940 5640 50  0001 C CNN
F 3 "~" H 5900 5650 50  0001 C CNN
	1    5900 5650
	0    1    -1   0   
$EndComp
$Comp
L 3.1-schematic-rescue:R_POT_US-Device R18
U 1 1 607B2764
P 6600 5650
F 0 "R18" H 6532 5600 50  0000 R CNN
F 1 "15.8k" H 6532 5700 50  0000 R CNN
F 2 "" H 6600 5650 50  0001 C CNN
F 3 "~" H 6600 5650 50  0001 C CNN
	1    6600 5650
	0    -1   1    0   
$EndComp
$Comp
L 3.1-schematic-rescue:TL084-Amplifier_Operational U1
U 2 1 607AED61
P 7650 5750
F 0 "U1" H 7650 5383 50  0000 C CNN
F 1 "TL084" H 7650 5474 50  0000 C CNN
F 2 "" H 7600 5850 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 7700 5950 50  0001 C CNN
	2    7650 5750
	1    0    0    1   
$EndComp
$Comp
L 3.1-schematic-rescue:TL084-Amplifier_Operational U1
U 1 1 607ACCC9
P 5050 5650
F 0 "U1" H 5050 5283 50  0000 C CNN
F 1 "TL084" H 5050 5374 50  0000 C CNN
F 2 "" H 5000 5750 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 5100 5850 50  0001 C CNN
	1    5050 5650
	1    0    0    1   
$EndComp
$Comp
L 3.1-schematic-rescue:TL084-Amplifier_Operational U1
U 5 1 607CB49E
P 950 1500
F 0 "U1" H 950 1133 50  0000 C CNN
F 1 "TL084" H 950 1224 50  0000 C CNN
F 2 "" H 900 1600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 1000 1700 50  0001 C CNN
	5    950  1500
	1    0    0    -1  
$EndComp
$Comp
L 3.1-schematic-rescue:C-Device C1
U 1 1 607E7D95
P 1200 1500
F 0 "C1" H 1315 1546 50  0000 L CNN
F 1 "0.1u" H 1315 1455 50  0000 L CNN
F 2 "" H 1238 1350 50  0001 C CNN
F 3 "~" H 1200 1500 50  0001 C CNN
	1    1200 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  1800 850  2400
Wire Wire Line
	1200 1800 850  1800
Wire Wire Line
	1200 1800 1200 1650
Wire Wire Line
	1200 1350 1200 1200
Wire Wire Line
	1200 1200 850  1200
Wire Wire Line
	850  850  850  1200
Text Notes 9200 1100 0    50   ~ 0
Notes:
Text Notes 9300 1200 0    50   ~ 0
1) Tie unused inputs
$Comp
L 3.1-schematic-rescue:R_POT_US-Device R6
U 1 1 607D69D2
P 6600 2550
F 0 "R6" H 6532 2500 50  0000 R CNN
F 1 "4.2463k" H 6532 2600 50  0000 R CNN
F 2 "" H 6600 2550 50  0001 C CNN
F 3 "~" H 6600 2550 50  0001 C CNN
	1    6600 2550
	0    -1   1    0   
$EndComp
Wire Wire Line
	6750 2550 7050 2550
Wire Wire Line
	6050 2700 6600 2700
Wire Wire Line
	6050 2550 6050 2700
Wire Wire Line
	3650 2550 5450 2550
$Comp
L 3.1-schematic-rescue:R_US-Device R5
U 1 1 607B12D0
P 5900 2550
F 0 "R5" H 5968 2596 50  0000 L CNN
F 1 "3.9k" H 5968 2505 50  0000 L CNN
F 2 "" V 5940 2540 50  0001 C CNN
F 3 "~" H 5900 2550 50  0001 C CNN
	1    5900 2550
	0    1    -1   0   
$EndComp
Text GLabel 3650 2550 0    50   Input ~ 0
Vbias
$Comp
L DAC_Lab:IO_Pin P6.1(A1)
U 1 2 607E7306
P 8450 5750
F 0 "P6.1(A1)" H 8900 5750 50  0000 C CNN
F 1 "IO_Pin" H 8450 5950 50  0001 C CNN
F 2 "" H 8400 5750 50  0001 C CNN
F 3 "" H 8400 5750 50  0001 C CNN
	1    8450 5750
	1    0    0    -1  
$EndComp
$Comp
L DAC_Lab:IO_Pin P6.0(A0)
U 1 2 607E6D38
P 8450 3700
F 0 "P6.0(A0)" H 8900 3700 50  0000 C CNN
F 1 "IO_Pin" H 8450 3900 50  0001 C CNN
F 2 "" H 8400 3700 50  0001 C CNN
F 3 "" H 8400 3700 50  0001 C CNN
	1    8450 3700
	1    0    0    -1  
$EndComp
Text GLabel 3650 3500 0    50   Input ~ 0
Voutx
$Comp
L 3.1-schematic-rescue:R_US-Device R7
U 1 1 6099D6F0
P 4200 3500
F 0 "R7" H 4268 3546 50  0000 L CNN
F 1 "100k" H 4268 3455 50  0000 L CNN
F 2 "" V 4240 3490 50  0001 C CNN
F 3 "~" H 4200 3500 50  0001 C CNN
	1    4200 3500
	0    1    -1   0   
$EndComp
$Comp
L 3.1-schematic-rescue:R_US-Device R8
U 1 1 6099D6FA
P 5050 3050
F 0 "R8" H 5118 3096 50  0000 L CNN
F 1 "100k" H 5118 3005 50  0000 L CNN
F 2 "" V 5090 3040 50  0001 C CNN
F 3 "~" H 5050 3050 50  0001 C CNN
	1    5050 3050
	0    1    -1   0   
$EndComp
$Comp
L 3.1-schematic-rescue:R_US-Device R11
U 1 1 6099D704
P 7650 3150
F 0 "R11" H 7718 3196 50  0000 L CNN
F 1 "100k" H 7718 3105 50  0000 L CNN
F 2 "" V 7690 3140 50  0001 C CNN
F 3 "~" H 7650 3150 50  0001 C CNN
	1    7650 3150
	0    1    -1   0   
$EndComp
Wire Wire Line
	3650 3500 4050 3500
Wire Wire Line
	4350 3500 4750 3500
Wire Wire Line
	5350 3600 5750 3600
Wire Wire Line
	6050 3600 6050 3750
Wire Wire Line
	6050 3750 6600 3750
Wire Wire Line
	4750 3700 4750 3900
$Comp
L 3.1-schematic-rescue:GND-power #PWR?
U 1 1 6099D717
P 4750 3900
F 0 "#PWR?" H 4750 3650 50  0001 C CNN
F 1 "GND" H 4755 3727 50  0000 C CNN
F 2 "" H 4750 3900 50  0001 C CNN
F 3 "" H 4750 3900 50  0001 C CNN
	1    4750 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 3800 7350 4000
$Comp
L 3.1-schematic-rescue:GND-power #PWR?
U 1 1 6099D722
P 7350 4000
F 0 "#PWR?" H 7350 3750 50  0001 C CNN
F 1 "GND" H 7355 3827 50  0000 C CNN
F 2 "" H 7350 4000 50  0001 C CNN
F 3 "" H 7350 4000 50  0001 C CNN
	1    7350 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3600 5350 3050
Wire Wire Line
	5350 3050 5200 3050
Connection ~ 5350 3600
Wire Wire Line
	4750 3500 4750 3050
Wire Wire Line
	4750 3050 4900 3050
Connection ~ 4750 3500
Wire Wire Line
	7350 3600 7350 3150
Wire Wire Line
	7350 3150 7500 3150
Connection ~ 7350 3600
Wire Wire Line
	7950 3700 7950 3150
Wire Wire Line
	7950 3150 7800 3150
Wire Wire Line
	7950 3700 8350 3700
$Comp
L 3.1-schematic-rescue:R_US-Device R9
U 1 1 6099D739
P 5900 3600
F 0 "R9" H 5968 3646 50  0000 L CNN
F 1 "1k" H 5968 3555 50  0000 L CNN
F 2 "" V 5940 3590 50  0001 C CNN
F 3 "~" H 5900 3600 50  0001 C CNN
	1    5900 3600
	0    1    -1   0   
$EndComp
$Comp
L 3.1-schematic-rescue:R_POT_US-Device R10
U 1 1 6099D743
P 6600 3600
F 0 "R10" H 6532 3550 50  0000 R CNN
F 1 "32.6k" H 6532 3650 50  0000 R CNN
F 2 "" H 6600 3600 50  0001 C CNN
F 3 "~" H 6600 3600 50  0001 C CNN
	1    6600 3600
	0    -1   1    0   
$EndComp
$Comp
L 3.1-schematic-rescue:TL084-Amplifier_Operational U1
U 3 1 6099D74E
P 7650 3700
F 0 "U1" H 7650 3333 50  0000 C CNN
F 1 "TL084" H 7650 3424 50  0000 C CNN
F 2 "" H 7600 3800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 7700 3900 50  0001 C CNN
	3    7650 3700
	1    0    0    1   
$EndComp
$Comp
L 3.1-schematic-rescue:TL084-Amplifier_Operational U1
U 4 1 6099D758
P 5050 3600
F 0 "U1" H 5050 3233 50  0000 C CNN
F 1 "TL084" H 5050 3324 50  0000 C CNN
F 2 "" H 5000 3700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 5100 3800 50  0001 C CNN
	4    5050 3600
	1    0    0    1   
$EndComp
Wire Wire Line
	6750 3600 7050 3600
Wire Wire Line
	7050 2550 7050 3600
Connection ~ 7050 3600
Wire Wire Line
	7050 3600 7350 3600
$Comp
L 3.1-schematic-rescue:R_US-Device R4
U 1 1 609D2853
P 5600 2550
F 0 "R4" H 5668 2596 50  0000 L CNN
F 1 "82k" H 5668 2505 50  0000 L CNN
F 2 "" V 5640 2540 50  0001 C CNN
F 3 "~" H 5600 2550 50  0001 C CNN
	1    5600 2550
	0    1    -1   0   
$EndComp
$Comp
L 3.1-schematic-rescue:+5V-power #PWR?
U 1 1 60A04711
P 850 850
F 0 "#PWR?" H 850 700 50  0001 C CNN
F 1 "+5V" H 865 1023 50  0000 C CNN
F 2 "" H 850 850 50  0001 C CNN
F 3 "" H 850 850 50  0001 C CNN
	1    850  850 
	1    0    0    -1  
$EndComp
Text Label 8100 3700 0    50   ~ 0
Vadcx
Text Label 8100 5750 0    50   ~ 0
Vadcy
Connection ~ 7950 3700
$Comp
L 3.1-schematic-rescue:GND-power #PWR?
U 1 1 60A2D0A7
P 2700 2200
F 0 "#PWR?" H 2700 1950 50  0001 C CNN
F 1 "GND" H 2705 2027 50  0000 C CNN
F 2 "" H 2700 2200 50  0001 C CNN
F 3 "" H 2700 2200 50  0001 C CNN
	1    2700 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 1815 2700 2200
Wire Wire Line
	2700 850  2700 1200
$Comp
L DAC_Lab:DE-ACCM2G U4
U 1 1 60A2C451
P 2700 1500
F 0 "U4" H 2373 1539 50  0000 R CNN
F 1 "DE-ACCM2G" H 2373 1448 50  0000 R CNN
F 2 "" H 2370 1785 50  0001 C CNN
F 3 "" H 2370 1785 50  0001 C CNN
	1    2700 1500
	1    0    0    -1  
$EndComp
Text GLabel 3400 1400 2    50   Input ~ 0
Voutx
Wire Wire Line
	3100 1400 3400 1400
Text GLabel 3400 1600 2    50   Input ~ 0
Vouty
Wire Wire Line
	3100 1600 3400 1600
Wire Wire Line
	6750 5650 7050 5650
$Comp
L 3.1-schematic-rescue:R_POT_US-Device R14
U 1 1 609A9F0E
P 6600 4600
F 0 "R14" H 6532 4550 50  0000 R CNN
F 1 "4.5k" H 6532 4650 50  0000 R CNN
F 2 "" H 6600 4600 50  0001 C CNN
F 3 "~" H 6600 4600 50  0001 C CNN
	1    6600 4600
	0    -1   1    0   
$EndComp
Wire Wire Line
	6750 4600 7050 4600
Wire Wire Line
	6050 4750 6600 4750
Wire Wire Line
	6050 4600 6050 4750
Wire Wire Line
	3650 4600 5450 4600
$Comp
L 3.1-schematic-rescue:R_US-Device R13
U 1 1 609A9F18
P 5900 4600
F 0 "R13" H 5968 4646 50  0000 L CNN
F 1 "1k" H 5968 4555 50  0000 L CNN
F 2 "" V 5940 4590 50  0001 C CNN
F 3 "~" H 5900 4600 50  0001 C CNN
	1    5900 4600
	0    1    -1   0   
$EndComp
Text GLabel 3650 4600 0    50   Input ~ 0
Vbias
Wire Wire Line
	7050 4600 7050 5650
$Comp
L 3.1-schematic-rescue:R_US-Device R12
U 1 1 609A9F20
P 5600 4600
F 0 "R12" H 5668 4646 50  0000 L CNN
F 1 "33k" H 5668 4555 50  0000 L CNN
F 2 "" V 5640 4590 50  0001 C CNN
F 3 "~" H 5600 4600 50  0001 C CNN
	1    5600 4600
	0    1    -1   0   
$EndComp
Connection ~ 850  1200
Connection ~ 850  1800
$Comp
L power:-5V #PWR?
U 1 1 609B75E2
P 850 2400
F 0 "#PWR?" H 850 2500 50  0001 C CNN
F 1 "-5V" H 865 2573 50  0000 C CNN
F 2 "" H 850 2400 50  0001 C CNN
F 3 "" H 850 2400 50  0001 C CNN
	1    850  2400
	1    0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 609B9526
P 2700 850
F 0 "#PWR?" H 2700 700 50  0001 C CNN
F 1 "+3.3V" H 2715 1023 50  0000 C CNN
F 2 "" H 2700 850 50  0001 C CNN
F 3 "" H 2700 850 50  0001 C CNN
	1    2700 850 
	1    0    0    -1  
$EndComp
Connection ~ 7050 5650
Wire Wire Line
	7050 5650 7350 5650
$Comp
L power:+3.3V #PWR?
U 1 1 60A0AE67
P 4150 850
F 0 "#PWR?" H 4150 700 50  0001 C CNN
F 1 "+3.3V" H 4165 1023 50  0000 C CNN
F 2 "" H 4150 850 50  0001 C CNN
F 3 "" H 4150 850 50  0001 C CNN
	1    4150 850 
	1    0    0    -1  
$EndComp
Text GLabel 4300 1400 2    50   Input ~ 0
Vbias
Wire Wire Line
	4150 850  4150 1400
Wire Wire Line
	4150 1400 4300 1400
$EndSCHEMATC
