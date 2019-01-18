EESchema Schematic File Version 4
LIBS:hall-effect-v2-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Hall Effect Bricklet"
Date "2018-06-27"
Rev "2.0"
Comp "Tinkerforge GmbH"
Comment1 "Licensed under CERN OHL v.1.1"
Comment2 "Copyright (©) 2018, L.Lauer <lukas@tinkerforge.com>"
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 600  7650 0    40   ~ 0
Copyright Tinkerforge GmbH 2018.\nThis documentation describes Open Hardware and is licensed under the\nCERN OHL v. 1.1.\nYou may redistribute and modify this documentation under the terms of the\nCERN OHL v.1.1. (http://ohwr.org/cernohl). This documentation is distributed\nWITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF\nMERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A\nPARTICULAR PURPOSE. Please see the CERN OHL v.1.1 for applicable\nconditions\n
$Comp
L tinkerforge:DRILL U4
U 1 1 4C692B9B
P 10600 6350
F 0 "U4" H 10650 6400 60  0001 C CNN
F 1 "DRILL" H 10600 6350 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 10600 6350 60  0001 C CNN
F 3 "" H 10600 6350 60  0001 C CNN
	1    10600 6350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DRILL U3
U 1 1 4C692B9A
P 10600 6150
F 0 "U3" H 10650 6200 60  0001 C CNN
F 1 "DRILL" H 10600 6150 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 10600 6150 60  0001 C CNN
F 3 "" H 10600 6150 60  0001 C CNN
	1    10600 6150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DRILL U5
U 1 1 4C692B98
P 10900 6150
F 0 "U5" H 10950 6200 60  0001 C CNN
F 1 "DRILL" H 10900 6150 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 10900 6150 60  0001 C CNN
F 3 "" H 10900 6150 60  0001 C CNN
	1    10900 6150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DRILL U6
U 1 1 4C692B94
P 10900 6350
F 0 "U6" H 10950 6400 60  0001 C CNN
F 1 "DRILL" H 10900 6350 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 10900 6350 60  0001 C CNN
F 3 "" H 10900 6350 60  0001 C CNN
	1    10900 6350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:VCC #PWR03
U 1 1 4C5FCFB4
P 2600 1100
F 0 "#PWR03" H 2600 1200 30  0001 C CNN
F 1 "VCC" H 2600 1150 30  0000 C CNN
F 2 "" H 2600 1100 60  0001 C CNN
F 3 "" H 2600 1100 60  0001 C CNN
	1    2600 1100
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR02
U 1 1 4C5FCF5E
P 1900 2650
F 0 "#PWR02" H 1900 2650 30  0001 C CNN
F 1 "GND" H 1900 2580 30  0001 C CNN
F 2 "" H 1900 2650 60  0001 C CNN
F 3 "" H 1900 2650 60  0001 C CNN
	1    1900 2650
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR04
U 1 1 4C5FCF4F
P 2600 1700
F 0 "#PWR04" H 2600 1700 30  0001 C CNN
F 1 "GND" H 2600 1630 30  0001 C CNN
F 2 "" H 2600 1700 60  0001 C CNN
F 3 "" H 2600 1700 60  0001 C CNN
	1    2600 1700
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:CON-SENSOR2 P1
U 1 1 5B2CB98D
P 1350 1850
F 0 "P1" H 1200 2250 60  0000 C CNN
F 1 "CON-SENSOR2" V 1500 1850 60  0000 C CNN
F 2 "kicad-libraries:CON-SENSOR2" H 1450 1700 60  0001 C CNN
F 3 "" H 1450 1700 60  0000 C CNN
	1    1350 1850
	-1   0    0    -1  
$EndComp
$Comp
L tinkerforge:C C2
U 1 1 5B2CBB5E
P 2100 1400
F 0 "C2" H 2150 1500 50  0000 L CNN
F 1 "10uF" H 2150 1300 50  0000 L CNN
F 2 "kicad-libraries:C0805" H 2100 1400 60  0001 C CNN
F 3 "" H 2100 1400 60  0000 C CNN
	1    2100 1400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C3
U 1 1 5B2CBBA9
P 2600 1400
F 0 "C3" H 2650 1500 50  0000 L CNN
F 1 "1uF" H 2650 1300 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 2600 1400 60  0001 C CNN
F 3 "" H 2600 1400 60  0000 C CNN
	1    2600 1400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:R_PACK4 RP1
U 1 1 5B2CC204
P 2300 2200
F 0 "RP1" H 2300 2650 50  0000 C CNN
F 1 "82" H 2300 2150 50  0000 C CNN
F 2 "kicad-libraries:4X0402" H 2300 2200 50  0001 C CNN
F 3 "" H 2300 2200 50  0000 C CNN
	1    2300 2200
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C1
U 1 1 5B2CC36D
P 1900 2400
F 0 "C1" H 1950 2500 50  0000 L CNN
F 1 "220pF" H 1950 2300 50  0000 L CNN
F 2 "kicad-libraries:C0402F" H 1900 2400 60  0001 C CNN
F 3 "" H 1900 2400 60  0000 C CNN
	1    1900 2400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR01
U 1 1 5B2CC5E8
P 1350 2650
F 0 "#PWR01" H 1350 2650 30  0001 C CNN
F 1 "GND" H 1350 2580 30  0001 C CNN
F 2 "" H 1350 2650 60  0001 C CNN
F 3 "" H 1350 2650 60  0001 C CNN
	1    1350 2650
	1    0    0    -1  
$EndComp
Text GLabel 2850 1850 2    47   Output ~ 0
S-CS
Text GLabel 2850 1950 2    47   Output ~ 0
S-CLK
Text GLabel 2850 2050 2    47   Output ~ 0
S-MOSI
Text GLabel 2850 2150 2    47   Input ~ 0
S-MISO
Wire Wire Line
	1350 2650 1350 2300
Wire Wire Line
	1900 2650 1900 2600
Wire Wire Line
	1700 2150 1900 2150
Wire Wire Line
	1700 2050 2100 2050
Wire Wire Line
	1700 1950 2100 1950
Wire Wire Line
	2100 1850 1700 1850
Wire Wire Line
	2500 1850 2850 1850
Wire Wire Line
	2850 1950 2500 1950
Wire Wire Line
	2500 2050 2850 2050
Wire Wire Line
	2850 2150 2500 2150
Wire Wire Line
	1900 2200 1900 2150
Connection ~ 1900 2150
Wire Wire Line
	1700 1750 1900 1750
Wire Wire Line
	1900 1750 1900 1150
Wire Wire Line
	1900 1150 2100 1150
Wire Wire Line
	2600 1100 2600 1150
Connection ~ 2600 1150
Wire Wire Line
	2100 1200 2100 1150
Connection ~ 2100 1150
Wire Wire Line
	1700 1650 2100 1650
Wire Wire Line
	2600 1600 2600 1650
Connection ~ 2600 1650
Wire Wire Line
	2100 1600 2100 1650
Connection ~ 2100 1650
NoConn ~ 1700 1550
$Comp
L tinkerforge:XMC1XXX24 U1
U 1 1 5B2CDB5D
P 4900 6900
F 0 "U1" H 4750 7300 60  0000 C CNN
F 1 "XMC1XXX24" H 4900 6500 60  0000 C CNN
F 2 "kicad-libraries:QFN24-4x4mm-0.5mm" H 5050 7650 60  0001 C CNN
F 3 "" H 5050 7650 60  0000 C CNN
	1    4900 6900
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:XMC1XXX24 U1
U 2 1 5B2CDBCA
P 4900 3450
F 0 "U1" H 4750 4000 60  0000 C CNN
F 1 "XMC1XXX24" H 4900 2900 60  0000 C CNN
F 2 "kicad-libraries:QFN24-4x4mm-0.5mm" H 5050 4200 60  0001 C CNN
F 3 "" H 5050 4200 60  0000 C CNN
	2    4900 3450
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:XMC1XXX24 U1
U 3 1 5B2CDC17
P 4900 4650
F 0 "U1" H 4750 4900 60  0000 C CNN
F 1 "XMC1XXX24" H 4900 4400 60  0000 C CNN
F 2 "kicad-libraries:QFN24-4x4mm-0.5mm" H 5050 5400 60  0001 C CNN
F 3 "" H 5050 5400 60  0000 C CNN
	3    4900 4650
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C6
U 1 1 5B2CE6DB
P 4350 6850
F 0 "C6" H 4400 6950 50  0000 L CNN
F 1 "100nF" H 4400 6750 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 4350 6850 60  0001 C CNN
F 3 "" H 4350 6850 60  0000 C CNN
	1    4350 6850
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:VCC #PWR09
U 1 1 5B2CE789
P 4350 6550
F 0 "#PWR09" H 4350 6650 30  0001 C CNN
F 1 "VCC" H 4350 6650 30  0000 C CNN
F 2 "" H 4350 6550 60  0001 C CNN
F 3 "" H 4350 6550 60  0001 C CNN
	1    4350 6550
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR010
U 1 1 5B2CE7BE
P 4350 7250
F 0 "#PWR010" H 4350 7250 30  0001 C CNN
F 1 "GND" H 4350 7180 30  0001 C CNN
F 2 "" H 4350 7250 60  0001 C CNN
F 3 "" H 4350 7250 60  0001 C CNN
	1    4350 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 6650 4350 6600
Wire Wire Line
	4350 6600 4550 6600
Connection ~ 4350 6600
Wire Wire Line
	4350 7050 4350 7100
Wire Wire Line
	4550 7100 4350 7100
Connection ~ 4350 7100
Wire Wire Line
	4550 7200 4350 7200
Connection ~ 4350 7200
NoConn ~ 4550 4800
$Comp
L tinkerforge:CONN_01X01 P3
U 1 1 5B2CF777
P 3850 3600
F 0 "P3" H 3850 3700 50  0000 C CNN
F 1 "DEBUG" V 3950 3600 50  0000 C CNN
F 2 "kicad-libraries:DEBUG_PAD" H 3850 3600 50  0001 C CNN
F 3 "" H 3850 3600 50  0000 C CNN
	1    3850 3600
	-1   0    0    1   
$EndComp
Text GLabel 4300 3700 0    47   Input ~ 0
S-CS
Text GLabel 4300 3800 0    47   Input ~ 0
S-CLK
Text GLabel 4300 3900 0    47   Input ~ 0
S-MOSI
Text GLabel 4300 5400 0    47   Output ~ 0
S-MISO
Text Notes 5350 3900 0    39   ~ 0
SPI Slave/CH0\nP0.13 : USIC0_CH0-DX2F : SEL\nP0.14 : USIC0_CH0-DX1A : CLK\nP0.15 : USIC0_CH0-DX0B : MOSI\nP2.0 : USIC0_CH0-DOUT0 : MISO
Wire Wire Line
	4300 3700 4550 3700
Wire Wire Line
	4550 3800 4300 3800
Wire Wire Line
	4300 3900 4550 3900
NoConn ~ 4550 3500
NoConn ~ 4550 3100
$Comp
L tinkerforge:CONN_01X02 P2
U 1 1 5B2D13A2
P 3350 3450
F 0 "P2" H 3350 3600 50  0000 C CNN
F 1 "BOOT" V 3450 3450 50  0000 C CNN
F 2 "kicad-libraries:SolderJumper" H 3350 3450 50  0001 C CNN
F 3 "" H 3350 3450 50  0000 C CNN
	1    3350 3450
	-1   0    0    1   
$EndComp
$Comp
L tinkerforge:R R3
U 1 1 5B2D1966
P 4200 6000
F 0 "R3" V 4200 6100 50  0000 C CNN
F 1 "1k" V 4200 5900 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 4200 6000 60  0001 C CNN
F 3 "" H 4200 6000 60  0000 C CNN
	1    4200 6000
	0    1    1    0   
$EndComp
$Comp
L tinkerforge:LED D1
U 1 1 5B2D1B30
P 3650 6000
F 0 "D1" H 3650 6100 50  0000 C CNN
F 1 "blue" H 3650 5900 50  0000 C CNN
F 2 "kicad-libraries:D0603F" H 3650 6000 50  0001 C CNN
F 3 "" H 3650 6000 50  0000 C CNN
	1    3650 6000
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:VCC #PWR06
U 1 1 5B2D1E1D
P 3400 5950
F 0 "#PWR06" H 3400 6050 30  0001 C CNN
F 1 "VCC" H 3400 6000 30  0000 C CNN
F 2 "" H 3400 5950 60  0001 C CNN
F 3 "" H 3400 5950 60  0001 C CNN
	1    3400 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 5400 4550 5400
$Comp
L tinkerforge:VCC #PWR012
U 1 1 5B2CD13F
P 9000 3750
F 0 "#PWR012" H 9000 3850 30  0001 C CNN
F 1 "VCC" H 9000 3850 30  0000 C CNN
F 2 "" H 9000 3750 60  0001 C CNN
F 3 "" H 9000 3750 60  0001 C CNN
	1    9000 3750
	1    0    0    -1  
$EndComp
NoConn ~ 4550 3300
$Comp
L tinkerforge:XMC1XXX24 U1
U 4 1 5B2CDC65
P 4900 5750
F 0 "U1" H 4750 6200 60  0000 C CNN
F 1 "XMC1XXX24" H 4900 5300 60  0000 C CNN
F 2 "kicad-libraries:QFN24-4x4mm-0.5mm" H 5050 6500 60  0001 C CNN
F 3 "" H 5050 6500 60  0000 C CNN
	4    4900 5750
	1    0    0    -1  
$EndComp
NoConn ~ 4550 6100
NoConn ~ 4550 3200
$Comp
L tinkerforge:GND #PWR05
U 1 1 5B33D683
P 3600 3550
F 0 "#PWR05" H 3600 3550 30  0001 C CNN
F 1 "GND" H 3600 3480 30  0001 C CNN
F 2 "" H 3600 3550 60  0001 C CNN
F 3 "" H 3600 3550 60  0001 C CNN
	1    3600 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 3500 3600 3500
Wire Wire Line
	3600 3500 3600 3550
$Comp
L tinkerforge:DRV023 U2
U 1 1 5B339060
P 8600 4600
F 0 "U2" H 8450 4850 60  0000 C CNN
F 1 "DRV5053" H 8600 4350 60  0000 C CNN
F 2 "kicad-libraries:SOT23-3" H 9400 4350 60  0001 C CNN
F 3 "" H 9400 4350 60  0000 C CNN
	1    8600 4600
	1    0    0    -1  
$EndComp
Text GLabel 9700 4500 2    47   Output ~ 0
OUT
$Comp
L tinkerforge:GND #PWR013
U 1 1 5B33987B
P 9000 5400
F 0 "#PWR013" H 9000 5400 30  0001 C CNN
F 1 "GND" H 9000 5330 30  0001 C CNN
F 2 "" H 9000 5400 60  0001 C CNN
F 3 "" H 9000 5400 60  0001 C CNN
	1    9000 5400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C7
U 1 1 5B33A501
P 9000 5150
F 0 "C7" H 9050 5250 50  0000 L CNN
F 1 "100nF" H 9050 5050 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 9000 5150 60  0001 C CNN
F 3 "" H 9000 5150 60  0000 C CNN
	1    9000 5150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR011
U 1 1 5B33AC4F
P 8150 5400
F 0 "#PWR011" H 8150 5400 30  0001 C CNN
F 1 "GND" H 8150 5330 30  0001 C CNN
F 2 "" H 8150 5400 60  0001 C CNN
F 3 "" H 8150 5400 60  0001 C CNN
	1    8150 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 4600 8150 4600
Wire Wire Line
	8150 4600 8150 5400
Wire Wire Line
	9000 4700 8950 4700
Wire Wire Line
	9000 5350 9000 5400
Connection ~ 9000 4700
Wire Wire Line
	9000 3750 9000 4700
NoConn ~ 4550 4700
Wire Wire Line
	4550 6000 4450 6000
Wire Wire Line
	3950 6000 3850 6000
Wire Wire Line
	3450 6000 3400 6000
Wire Wire Line
	3400 6000 3400 5950
Wire Wire Line
	4550 3600 4050 3600
Wire Wire Line
	1900 2150 2100 2150
Wire Wire Line
	2600 1150 2600 1200
Wire Wire Line
	2100 1150 2600 1150
Wire Wire Line
	2600 1650 2600 1700
Wire Wire Line
	2100 1650 2600 1650
Wire Wire Line
	4350 6600 4350 6550
Wire Wire Line
	4350 7100 4350 7200
Wire Wire Line
	4350 7200 4350 7250
Wire Wire Line
	9000 4700 9000 4950
$Comp
L tinkerforge:R R1
U 1 1 5C41BEF8
P 4150 4500
F 0 "R1" V 4150 4600 50  0000 C CNN
F 1 "1k" V 4150 4400 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 4150 4500 60  0001 C CNN
F 3 "" H 4150 4500 60  0000 C CNN
	1    4150 4500
	0    1    1    0   
$EndComp
$Comp
L tinkerforge:C C4
U 1 1 5C41C02B
P 3500 4950
F 0 "C4" H 3550 5050 50  0000 L CNN
F 1 "100nF" H 3550 4850 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 3500 4950 60  0001 C CNN
F 3 "" H 3500 4950 60  0000 C CNN
	1    3500 4950
	1    0    0    -1  
$EndComp
Text GLabel 4400 5900 0    47   Input ~ 0
OUT
$Comp
L tinkerforge:R R2
U 1 1 5C41DFEB
P 4150 4600
F 0 "R2" V 4150 4700 50  0000 C CNN
F 1 "1k" V 4150 4500 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 4150 4600 60  0001 C CNN
F 3 "" H 4150 4600 60  0000 C CNN
	1    4150 4600
	0    1    1    0   
$EndComp
$Comp
L tinkerforge:C C5
U 1 1 5C41E031
P 3800 4950
F 0 "C5" H 3850 5050 50  0000 L CNN
F 1 "100nF" H 3850 4850 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 3800 4950 60  0001 C CNN
F 3 "" H 3800 4950 60  0000 C CNN
	1    3800 4950
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR07
U 1 1 5C41E10B
P 3500 5200
F 0 "#PWR07" H 3500 5200 30  0001 C CNN
F 1 "GND" H 3500 5130 30  0001 C CNN
F 2 "" H 3500 5200 60  0001 C CNN
F 3 "" H 3500 5200 60  0001 C CNN
	1    3500 5200
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR08
U 1 1 5C41E1B0
P 3800 5200
F 0 "#PWR08" H 3800 5200 30  0001 C CNN
F 1 "GND" H 3800 5130 30  0001 C CNN
F 2 "" H 3800 5200 60  0001 C CNN
F 3 "" H 3800 5200 60  0001 C CNN
	1    3800 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 5200 3800 5150
Wire Wire Line
	3500 5200 3500 5150
Wire Wire Line
	3900 4600 3800 4600
Wire Wire Line
	3800 4600 3800 4750
Wire Wire Line
	4400 4600 4550 4600
Wire Wire Line
	4550 4500 4400 4500
Wire Wire Line
	3900 4500 3500 4500
Wire Wire Line
	3500 4500 3500 4750
Text GLabel 3400 4600 0    47   Output ~ 0
VOUT0
Text GLabel 3400 4500 0    47   Output ~ 0
VOUT1
Wire Wire Line
	3800 4600 3400 4600
Connection ~ 3800 4600
Wire Wire Line
	3500 4500 3400 4500
Connection ~ 3500 4500
Text GLabel 4400 5800 0    47   Input ~ 0
VOUT1
Text GLabel 4400 5600 0    47   Input ~ 0
VOUT0
Text GLabel 4400 5500 0    47   Input ~ 0
OUT
NoConn ~ 4550 5700
Wire Wire Line
	4550 5900 4400 5900
Wire Wire Line
	4400 5800 4550 5800
Wire Wire Line
	4550 5600 4400 5600
Wire Wire Line
	4400 5500 4550 5500
Text Notes 9800 5150 0    39   ~ 0
(optional)
Wire Wire Line
	9150 4500 8950 4500
$Comp
L tinkerforge:C C8
U 1 1 5C42F137
P 9650 5150
F 0 "C8" H 9700 5250 50  0000 L CNN
F 1 "100nF" H 9700 5050 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 9650 5150 60  0001 C CNN
F 3 "" H 9650 5150 60  0000 C CNN
	1    9650 5150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR014
U 1 1 5C42F18D
P 9650 5400
F 0 "#PWR014" H 9650 5400 30  0001 C CNN
F 1 "GND" H 9650 5330 30  0001 C CNN
F 2 "" H 9650 5400 60  0001 C CNN
F 3 "" H 9650 5400 60  0001 C CNN
	1    9650 5400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:R R4
U 1 1 5C42F35A
P 9400 4500
F 0 "R4" V 9400 4600 50  0000 C CNN
F 1 "100" V 9400 4450 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 9400 4500 60  0001 C CNN
F 3 "" H 9400 4500 60  0000 C CNN
	1    9400 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	9700 4500 9650 4500
Wire Wire Line
	9650 4950 9650 4500
Connection ~ 9650 4500
Wire Wire Line
	9650 5400 9650 5350
NoConn ~ 4550 3000
Wire Wire Line
	4550 3400 3550 3400
$EndSCHEMATC
