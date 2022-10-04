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
L MCU_Microchip_ATmega:ATmega328P-PU MCU?
U 1 1 62C4D2E9
P 1850 2500
F 0 "MCU?" H 1206 2591 50  0000 R BNN
F 1 "ATmega328P-PU" H 1206 2500 50  0000 R BNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 1206 2409 50  0001 R BIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 1850 2500 50  0001 C BNN
	1    1850 2500
	1    0    0    -1  
$EndComp
$Comp
L Driver_FET:IR2302 GateDriver?
U 1 1 62C5028E
P 4300 6600
F 0 "GateDriver?" H 4300 7371 50  0000 C CNN
F 1 "IR2302" H 4300 7280 50  0000 C CNN
F 2 "digikey-footprints:DIP-8_W7.62mm" H 4300 7189 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/ir2302.pdf?fileId=5546d462533600a4015355c988b216de" H 4300 6600 50  0001 C CNN
	1    4300 6600
	1    0    0    -1  
$EndComp
$Comp
L Diode:BAT46 DBoot?
U 1 1 62C52409
P 4650 6050
F 0 "DBoot?" H 4650 6267 50  0000 C CNN
F 1 "BAT46" H 4650 6176 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4650 5875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85662/bat46.pdf" H 4650 6050 50  0001 C CNN
	1    4650 6050
	-1   0    0    1   
$EndComp
$Comp
L Connector:Raspberry_Pi_2_3 PiConnector?
U 1 1 62C535BF
P 1450 5950
F 0 "PiConnector?" H 1450 7431 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 1450 7340 50  0000 C CNN
F 2 "Module:Raspberry_Pi_Zero_Socketed_THT_FaceDown_MountingHoles" H 1450 5950 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 1450 5950 50  0001 C CNN
	1    1450 5950
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7805_TO220 Supply5V?
U 1 1 62C69105
P 8050 2500
F 0 "Supply5V?" H 8050 2833 50  0000 C CNN
F 1 "LM7805_TO220" H 8050 2742 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 8050 2651 50  0001 C CIN
F 3 "https://www.onsemi.cn/PowerSolutions/document/MC7800-D.PDF" H 8050 2450 50  0001 C CNN
	1    8050 2500
	1    0    0    -1  
$EndComp
$Comp
L dk_Transistors-FETs-MOSFETs-Single:IRF540NPBF MosfetH?
U 1 1 62C6C9ED
P 8050 4300
F 0 "MosfetH?" H 8158 4406 60  0000 L CNN
F 1 "IRF540NPBF" H 8158 4300 60  0000 L CNN
F 2 "digikey-footprints:TO-220-3" H 8158 4194 60  0001 L CNN
F 3 "https://www.infineon.com/dgdl/irf540npbf.pdf?fileId=5546d462533600a4015355e39f0d19a1" H 8250 4600 60  0001 L CNN
F 4 "IRF540NPBF-ND" H 8250 4700 60  0001 L CNN "Digi-Key_PN"
F 5 "IRF540NPBF" H 8250 4800 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8250 4900 60  0001 L CNN "Category"
F 7 "Transistors - FETs, MOSFETs - Single" H 8250 5000 60  0001 L CNN "Family"
F 8 "https://www.infineon.com/dgdl/irf540npbf.pdf?fileId=5546d462533600a4015355e39f0d19a1" H 8250 5100 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/infineon-technologies/IRF540NPBF/IRF540NPBF-ND/811869" H 8250 5200 60  0001 L CNN "DK_Detail_Page"
F 10 "MOSFET N-CH 100V 33A TO-220AB" H 8250 5300 60  0001 L CNN "Description"
F 11 "Infineon Technologies" H 8250 5400 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8250 5500 60  0001 L CNN "Status"
	1    8050 4300
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Current:ACS724xLCTR-10AB ISenH?
U 1 1 62C746F6
P 4900 4450
F 0 "ISenH?" H 4900 5121 50  0000 C CNN
F 1 "ACS724xLCTR-10AB" H 4900 5030 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4900 4939 50  0001 C CIN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS724-Datasheet.ashx?la=en" H 4900 4450 50  0001 C CNN
	1    4900 4450
	0    -1   1    0   
$EndComp
$Comp
L Sensor_Current:ACS724xLCTR-10AB ISenL?
U 1 1 62C77C61
P 10450 4450
F 0 "ISenL?" H 10450 5121 50  0000 C CNN
F 1 "ACS724xLCTR-10AB" H 10450 5030 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 10450 4939 50  0001 C CIN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS724-Datasheet.ashx?la=en" H 10450 4450 50  0001 C CNN
	1    10450 4450
	0    1    1    0   
$EndComp
$Comp
L dk_Transistors-FETs-MOSFETs-Single:IRF540NPBF MosfetL?
U 1 1 62C7B2F5
P 8050 4800
F 0 "MosfetL?" H 8158 4906 60  0000 L CNN
F 1 "IRF540NPBF" H 8158 4800 60  0000 L CNN
F 2 "digikey-footprints:TO-220-3" H 8158 4694 60  0001 L CNN
F 3 "https://www.infineon.com/dgdl/irf540npbf.pdf?fileId=5546d462533600a4015355e39f0d19a1" H 8250 5100 60  0001 L CNN
F 4 "IRF540NPBF-ND" H 8250 5200 60  0001 L CNN "Digi-Key_PN"
F 5 "IRF540NPBF" H 8250 5300 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8250 5400 60  0001 L CNN "Category"
F 7 "Transistors - FETs, MOSFETs - Single" H 8250 5500 60  0001 L CNN "Family"
F 8 "https://www.infineon.com/dgdl/irf540npbf.pdf?fileId=5546d462533600a4015355e39f0d19a1" H 8250 5600 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/infineon-technologies/IRF540NPBF/IRF540NPBF-ND/811869" H 8250 5700 60  0001 L CNN "DK_Detail_Page"
F 10 "MOSFET N-CH 100V 33A TO-220AB" H 8250 5800 60  0001 L CNN "Description"
F 11 "Infineon Technologies" H 8250 5900 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8250 6000 60  0001 L CNN "Status"
	1    8050 4800
	1    0    0    -1  
$EndComp
$Comp
L Diode:BAT46 DSupplyH?
U 1 1 62C7F1B0
P 7500 3350
F 0 "DSupplyH?" H 7500 3567 50  0000 C CNN
F 1 "BAT46" H 7500 3476 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 7500 3175 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85662/bat46.pdf" H 7500 3350 50  0001 C CNN
	1    7500 3350
	-1   0    0    1   
$EndComp
$Comp
L Diode:BAT46 DSupplyL?
U 1 1 62C7F8C0
P 8000 3350
F 0 "DSupplyL?" H 8000 3567 50  0000 C CNN
F 1 "BAT46" H 8000 3476 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8000 3175 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85662/bat46.pdf" H 8000 3350 50  0001 C CNN
	1    8000 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:L L?
U 1 1 62C4CCC2
P 8450 4550
F 0 "L?" H 8503 4596 50  0000 L CNN
F 1 "390uH, 5A" H 8503 4505 50  0000 L CNN
F 2 "Inductor_THT:L_Toroid_Horizontal_D32.5mm_P30.00mm_Bourns_2300" H 8502 4459 50  0001 L CNN
F 3 "~" H 8450 4550 50  0001 C CNN
	1    8450 4550
	0    -1   -1   0   
$EndComp
$Comp
L Device:R RVSenTopH?
U 1 1 62C5D799
P 5600 4300
F 0 "RVSenTopH?" H 5670 4346 50  0000 L CNN
F 1 "110k, 1%, 0.5W" H 5670 4255 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5530 4300 50  0001 C CNN
F 3 "~" H 5600 4300 50  0001 C CNN
	1    5600 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:R RVSenTopL?
U 1 1 62C6436F
P 9700 4250
F 0 "RVSenTopL?" H 9770 4296 50  0000 L CNN
F 1 "110k, 1%, 0.5W" H 9770 4205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 9630 4250 50  0001 C CNN
F 3 "~" H 9700 4250 50  0001 C CNN
	1    9700 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R RVSenBotH?
U 1 1 62C64D62
P 5600 4800
F 0 "RVSenBotH?" H 5670 4846 50  0000 L CNN
F 1 "10k, 1%, 0.5W" H 5670 4755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5530 4800 50  0001 C CNN
F 3 "~" H 5600 4800 50  0001 C CNN
	1    5600 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R RVSenBotL?
U 1 1 62C64D68
P 9700 4650
F 0 "RVSenBotL?" H 9770 4696 50  0000 L CNN
F 1 "10k, 1%, 0.5W" H 9770 4605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 9630 4650 50  0001 C CNN
F 3 "~" H 9700 4650 50  0001 C CNN
	1    9700 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R RBleedH?
U 1 1 62C66B42
P 6300 4800
F 0 "RBleedH?" H 6370 4846 50  0000 L CNN
F 1 "110k" H 6370 4755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6230 4800 50  0001 C CNN
F 3 "~" H 6300 4800 50  0001 C CNN
	1    6300 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:C CL?
U 1 1 62C67CA7
P 9000 4350
F 0 "CL?" H 9178 4396 50  0000 L CNN
F 1 "330uF, 100V" H 9178 4305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D18.0mm_P7.50mm" H 9000 4350 50  0001 C CNN
F 3 "~" H 9000 4350 50  0001 C CNN
	1    9000 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:R RBleedL?
U 1 1 62C67CAD
P 9350 4650
F 0 "RBleedL?" H 9420 4696 50  0000 L CNN
F 1 "110k" H 9420 4605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 9280 4650 50  0001 C CNN
F 3 "~" H 9350 4650 50  0001 C CNN
	1    9350 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R RGateH?
U 1 1 62C6C21D
P 7250 5350
F 0 "RGateH?" H 7320 5396 50  0000 L CNN
F 1 "0" H 7320 5305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7180 5350 50  0001 C CNN
F 3 "~" H 7250 5350 50  0001 C CNN
	1    7250 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:R RGateL?
U 1 1 62C6CFAC
P 7600 5350
F 0 "RGateL?" H 7670 5396 50  0000 L CNN
F 1 "0" H 7670 5305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7530 5350 50  0001 C CNN
F 3 "~" H 7600 5350 50  0001 C CNN
	1    7600 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:C CBoot?
U 1 1 62C6EC98
P 4900 6650
F 0 "CBoot?" H 5015 6696 50  0000 L CNN
F 1 "0.1uF" H 5015 6605 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.2mm_W5.5mm_P5.00mm_FKS2_FKP2_MKS2_MKP2" H 4938 6500 50  0001 C CNN
F 3 "~" H 4900 6650 50  0001 C CNN
	1    4900 6650
	1    0    0    -1  
$EndComp
$Comp
L Device:C CSup?
U 1 1 62C7155C
P 7050 1450
F 0 "CSup?" H 7165 1496 50  0000 L CNN
F 1 "0.1uF" H 7165 1405 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.2mm_W5.5mm_P5.00mm_FKS2_FKP2_MKS2_MKP2" H 7088 1300 50  0001 C CNN
F 3 "~" H 7050 1450 50  0001 C CNN
	1    7050 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C CH?
U 1 1 62C73957
P 6950 4800
F 0 "CH?" H 7065 4846 50  0000 L CNN
F 1 "0.1uF, 100V" H 7065 4755 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.2mm_W5.5mm_P5.00mm_FKS2_FKP2_MKS2_MKP2" H 6988 4650 50  0001 C CNN
F 3 "~" H 6950 4800 50  0001 C CNN
	1    6950 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 4500 8050 4550
Wire Wire Line
	5100 4050 5600 4050
Wire Wire Line
	5600 4050 5600 4150
Wire Wire Line
	5600 4450 5600 4550
Wire Wire Line
	5300 5050 5600 5050
Wire Wire Line
	10050 5050 9700 5050
Wire Wire Line
	10250 4050 9700 4050
Wire Wire Line
	9700 4050 9700 4100
Wire Wire Line
	9700 4400 9700 4450
Wire Wire Line
	6650 4050 6650 4350
$Comp
L Device:C CH?
U 1 1 62C519A9
P 6650 4500
F 0 "CH?" H 6828 4546 50  0000 L CNN
F 1 "330uF, 100V" H 6828 4455 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D18.0mm_P7.50mm" H 6650 4500 50  0001 C CNN
F 3 "~" H 6650 4500 50  0001 C CNN
	1    6650 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 4650 6300 4050
Wire Wire Line
	5600 5050 6300 5050
Connection ~ 5600 5050
Wire Wire Line
	5600 4050 5950 4050
Connection ~ 5600 4050
Connection ~ 6300 4050
Connection ~ 6300 5050
Wire Wire Line
	6300 4050 6650 4050
Connection ~ 6650 4050
Wire Wire Line
	9000 4200 9000 4050
Wire Wire Line
	9350 4050 9350 4500
Connection ~ 9700 4050
Wire Wire Line
	9350 5050 9700 5050
Connection ~ 9700 5050
Wire Wire Line
	9000 5050 9350 5050
Connection ~ 9350 5050
Wire Wire Line
	9000 4050 9350 4050
Connection ~ 9350 4050
Wire Wire Line
	9350 4050 9500 4050
Wire Wire Line
	6300 5050 6650 5050
Wire Wire Line
	6300 4950 6300 5050
Wire Wire Line
	6650 4650 6650 5050
Connection ~ 6650 5050
Wire Wire Line
	6650 5050 6950 5050
Wire Wire Line
	6950 4950 6950 5050
Wire Wire Line
	5600 4950 5600 5050
Wire Wire Line
	5300 4450 5300 5050
Wire Wire Line
	8050 5000 8050 5050
Connection ~ 6950 5050
Wire Wire Line
	8050 4050 8050 4100
Wire Wire Line
	10050 4450 10050 5050
Wire Wire Line
	9700 4800 9700 5050
Wire Wire Line
	9350 4800 9350 5050
Wire Wire Line
	9000 4500 9000 5050
Wire Wire Line
	9000 5050 8550 5050
Connection ~ 9000 5050
Wire Wire Line
	6950 5050 8050 5050
Connection ~ 8050 5050
Wire Wire Line
	7750 4900 7600 4900
Wire Wire Line
	7250 4400 7750 4400
Wire Wire Line
	7250 4400 7250 5200
Wire Wire Line
	7600 4900 7600 5200
Wire Wire Line
	8300 4550 8200 4550
Connection ~ 8050 4550
Wire Wire Line
	8050 4550 8050 4600
Wire Wire Line
	8600 4550 8750 4550
Wire Wire Line
	8750 4550 8750 4050
Wire Wire Line
	8750 4050 9000 4050
Connection ~ 9000 4050
Wire Wire Line
	6650 4050 6950 4050
$Comp
L Device:R RCH?
U 1 1 62CF08FF
P 6950 4300
F 0 "RCH?" H 7020 4346 50  0000 L CNN
F 1 "0" H 7020 4255 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6880 4300 50  0001 C CNN
F 3 "~" H 6950 4300 50  0001 C CNN
	1    6950 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 4150 6950 4050
Connection ~ 6950 4050
Wire Wire Line
	6950 4050 8050 4050
Wire Wire Line
	6950 4450 6950 4650
$Comp
L Device:C CDTR?
U 1 1 62CF62C1
P 3900 1500
F 0 "CDTR?" H 4015 1546 50  0000 L CNN
F 1 "0.1uF" H 4015 1455 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.2mm_W5.5mm_P5.00mm_FKS2_FKP2_MKS2_MKP2" H 3938 1350 50  0001 C CNN
F 3 "~" H 3900 1500 50  0001 C CNN
	1    3900 1500
	0    1    1    0   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62CFA2C4
P 7050 1100
F 0 "#PWR?" H 7050 950 50  0001 C CNN
F 1 "VCC" H 7065 1273 50  0000 C CNN
F 2 "" H 7050 1100 50  0001 C CNN
F 3 "" H 7050 1100 50  0001 C CNN
	1    7050 1100
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62CFC3ED
P 3950 6050
F 0 "#PWR?" H 3950 5900 50  0001 C CNN
F 1 "VCC" H 3965 6223 50  0000 C CNN
F 2 "" H 3950 6050 50  0001 C CNN
F 3 "" H 3950 6050 50  0001 C CNN
	1    3950 6050
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62CFD84F
P 4450 4350
F 0 "#PWR?" H 4450 4200 50  0001 C CNN
F 1 "VCC" H 4465 4523 50  0000 C CNN
F 2 "" H 4450 4350 50  0001 C CNN
F 3 "" H 4450 4350 50  0001 C CNN
	1    4450 4350
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62CFEB3B
P 10900 4350
F 0 "#PWR?" H 10900 4200 50  0001 C CNN
F 1 "VCC" H 10915 4523 50  0000 C CNN
F 2 "" H 10900 4350 50  0001 C CNN
F 3 "" H 10900 4350 50  0001 C CNN
	1    10900 4350
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62D0144F
P 1850 900
F 0 "#PWR?" H 1850 750 50  0001 C CNN
F 1 "VCC" H 1865 1073 50  0000 C CNN
F 2 "" H 1850 900 50  0001 C CNN
F 3 "" H 1850 900 50  0001 C CNN
	1    1850 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 1200 7050 1100
Wire Wire Line
	7050 1200 7050 1300
Connection ~ 7050 1200
Wire Wire Line
	4450 4350 4450 4450
Wire Wire Line
	4450 4450 4500 4450
Wire Wire Line
	10900 4350 10900 4450
Wire Wire Line
	10900 4450 10850 4450
$Comp
L power:GND #PWR?
U 1 1 62D249D0
P 8550 5150
F 0 "#PWR?" H 8550 4900 50  0001 C CNN
F 1 "GND" H 8555 4977 50  0000 C CNN
F 2 "" H 8550 5150 50  0001 C CNN
F 3 "" H 8550 5150 50  0001 C CNN
	1    8550 5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62D258C3
P 8050 2850
F 0 "#PWR?" H 8050 2600 50  0001 C CNN
F 1 "GND" H 8055 2677 50  0000 C CNN
F 2 "" H 8050 2850 50  0001 C CNN
F 3 "" H 8050 2850 50  0001 C CNN
	1    8050 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62D26FB9
P 4300 7150
F 0 "#PWR?" H 4300 6900 50  0001 C CNN
F 1 "GND" H 4305 6977 50  0000 C CNN
F 2 "" H 4300 7150 50  0001 C CNN
F 3 "" H 4300 7150 50  0001 C CNN
	1    4300 7150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62D28A77
P 1850 4050
F 0 "#PWR?" H 1850 3800 50  0001 C CNN
F 1 "GND" H 1855 3877 50  0000 C CNN
F 2 "" H 1850 4050 50  0001 C CNN
F 3 "" H 1850 4050 50  0001 C CNN
	1    1850 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62D2A3CC
P 1450 7300
F 0 "#PWR?" H 1450 7050 50  0001 C CNN
F 1 "GND" H 1455 7127 50  0000 C CNN
F 2 "" H 1450 7300 50  0001 C CNN
F 3 "" H 1450 7300 50  0001 C CNN
	1    1450 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 7300 1450 7250
Wire Wire Line
	1450 7250 1350 7250
Connection ~ 1450 7250
Wire Wire Line
	1350 7250 1250 7250
Connection ~ 1350 7250
Wire Wire Line
	1250 7250 1150 7250
Connection ~ 1250 7250
Wire Wire Line
	1150 7250 1050 7250
Connection ~ 1150 7250
Wire Wire Line
	1450 7250 1550 7250
Wire Wire Line
	1550 7250 1650 7250
Connection ~ 1550 7250
Wire Wire Line
	1650 7250 1750 7250
Connection ~ 1650 7250
Wire Wire Line
	1850 4050 1850 4000
Wire Wire Line
	4300 7150 4300 7100
Wire Wire Line
	8550 5150 8550 5050
Connection ~ 8550 5050
Wire Wire Line
	8550 5050 8050 5050
Wire Wire Line
	3950 6050 4300 6050
$Comp
L Connector:Conn_01x06_Male HeaderFTDI?
U 1 1 62D4D121
P 4550 1200
F 0 "HeaderFTDI?" H 4522 1174 50  0000 R CNN
F 1 "Conn_01x06_Male" H 4522 1083 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 4550 1200 50  0001 C CNN
F 3 "~" H 4550 1200 50  0001 C CNN
	1    4550 1200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1850 900  1850 950 
Wire Wire Line
	4350 1000 4250 1000
$Comp
L power:GND #PWR?
U 1 1 62D72B29
P 4150 850
F 0 "#PWR?" H 4150 600 50  0001 C CNN
F 1 "GND" V 4155 722 50  0000 R CNN
F 2 "" H 4150 850 50  0001 C CNN
F 3 "" H 4150 850 50  0001 C CNN
	1    4150 850 
	0    1    1    0   
$EndComp
Text Notes 4600 1000 0    50   ~ 0
GND
Text Notes 4600 1200 0    50   ~ 0
VCC
Text Notes 4600 1100 0    50   ~ 0
CTS
Text Notes 4600 1300 0    50   ~ 0
TX0
Text Notes 4600 1500 0    50   ~ 0
DTR
Text Notes 4600 1400 0    50   ~ 0
RXI
Wire Wire Line
	4350 1100 4250 1100
Wire Wire Line
	4250 1100 4250 1000
Wire Wire Line
	4250 850  4150 850 
$Comp
L Connector:Conn_01x01_Male TestPiVCC?
U 1 1 62D8981D
P 800 4600
F 0 "TestPiVCC?" H 908 4781 50  0000 C CNN
F 1 "Conn_01x01_Male" H 908 4690 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 800 4600 50  0001 C CNN
F 3 "~" H 800 4600 50  0001 C CNN
	1    800  4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 4600 1250 4600
Wire Wire Line
	1250 4600 1250 4650
Wire Wire Line
	1250 4600 1350 4600
Wire Wire Line
	1350 4600 1350 4650
Connection ~ 1250 4600
$Comp
L Connector:Conn_01x01_Male TestVCC?
U 1 1 62D9045C
P 7450 1200
F 0 "TestVCC?" H 7422 1132 50  0000 R CNN
F 1 "Conn_01x01_Male" H 7422 1223 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 7450 1200 50  0001 C CNN
F 3 "~" H 7450 1200 50  0001 C CNN
	1    7450 1200
	-1   0    0    1   
$EndComp
Wire Wire Line
	7250 1200 7050 1200
Wire Wire Line
	4250 850  4250 1000
Connection ~ 4250 1000
Text Label 4050 1300 0    50   ~ 0
MCURXI
Wire Wire Line
	4050 1300 4350 1300
Wire Wire Line
	4050 1400 4350 1400
Text Label 4050 1400 0    50   ~ 0
MCUTXO
Wire Wire Line
	3500 1150 3500 1200
$Comp
L power:VCC #PWR?
U 1 1 62D85792
P 3500 1150
F 0 "#PWR?" H 3500 1000 50  0001 C CNN
F 1 "VCC" H 3515 1323 50  0000 C CNN
F 2 "" H 3500 1150 50  0001 C CNN
F 3 "" H 3500 1150 50  0001 C CNN
	1    3500 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:R RDTR?
U 1 1 62CF7F93
P 3500 1350
F 0 "RDTR?" H 3570 1396 50  0000 L CNN
F 1 "10k, 1%, 0.5W" H 3570 1305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3430 1350 50  0001 C CNN
F 3 "~" H 3500 1350 50  0001 C CNN
	1    3500 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 1500 4350 1500
Wire Wire Line
	3750 1500 3500 1500
Wire Wire Line
	3500 1850 3500 1500
Connection ~ 3500 1500
Text Label 4050 1500 0    50   ~ 0
DTR
Text Label 2450 2800 0    50   ~ 0
!RESET
Wire Wire Line
	2450 3000 2750 3000
Wire Wire Line
	2450 3100 2750 3100
Text Label 2450 3000 0    50   ~ 0
MCURXI
Text Label 2450 3100 0    50   ~ 0
MCUTXO
Wire Wire Line
	7750 2500 7750 3350
Wire Wire Line
	7750 3350 7850 3350
Wire Wire Line
	7650 3350 7750 3350
Connection ~ 7750 3350
Wire Wire Line
	8150 3350 10650 3350
Wire Wire Line
	10650 3350 10650 4050
Wire Wire Line
	7350 3350 4700 3350
Wire Wire Line
	4700 3350 4700 4050
$Comp
L Connector:Screw_Terminal_01x02 TermH?
U 1 1 62EC05F7
P 4700 3000
F 0 "TermH?" H 4618 3217 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 4618 3126 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 4700 3000 50  0001 C CNN
F 3 "~" H 4700 3000 50  0001 C CNN
	1    4700 3000
	0    1    -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62EC534F
P 4600 3350
F 0 "#PWR?" H 4600 3100 50  0001 C CNN
F 1 "GND" H 4605 3177 50  0000 C CNN
F 2 "" H 4600 3350 50  0001 C CNN
F 3 "" H 4600 3350 50  0001 C CNN
	1    4600 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3350 4600 3200
$Comp
L Connector:Screw_Terminal_01x02 TermH?
U 1 1 62ECC7F7
P 10650 3000
F 0 "TermH?" H 10568 3217 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 10568 3126 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 10650 3000 50  0001 C CNN
F 3 "~" H 10650 3000 50  0001 C CNN
	1    10650 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10650 3200 10650 3350
Connection ~ 10650 3350
$Comp
L power:GND #PWR?
U 1 1 62EDF266
P 10750 3400
F 0 "#PWR?" H 10750 3150 50  0001 C CNN
F 1 "GND" H 10755 3227 50  0000 C CNN
F 2 "" H 10750 3400 50  0001 C CNN
F 3 "" H 10750 3400 50  0001 C CNN
	1    10750 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10750 3200 10750 3400
Wire Wire Line
	4700 3200 4700 3350
Connection ~ 4700 3350
Connection ~ 5600 4550
Wire Wire Line
	5600 4550 5600 4650
Wire Wire Line
	5450 4550 5450 5150
Wire Wire Line
	5450 5150 3000 5150
Wire Wire Line
	3000 5150 3000 2200
Wire Wire Line
	3000 2200 2450 2200
Wire Wire Line
	5450 4550 5600 4550
Wire Wire Line
	9700 4450 9850 4450
Wire Wire Line
	9850 4450 9850 5600
Wire Wire Line
	9850 5600 5450 5600
Wire Wire Line
	5450 5600 5450 5250
Wire Wire Line
	5450 5250 2950 5250
Wire Wire Line
	2950 5250 2950 2300
Wire Wire Line
	2950 2300 2450 2300
Connection ~ 9700 4450
Wire Wire Line
	9700 4450 9700 4500
Wire Wire Line
	4900 4850 4900 5350
Wire Wire Line
	4900 5350 2900 5350
Wire Wire Line
	2900 5350 2900 2400
Wire Wire Line
	2900 2400 2450 2400
Wire Wire Line
	10450 4850 10450 5650
Wire Wire Line
	10450 5650 5400 5650
Wire Wire Line
	5400 5650 5400 5450
Wire Wire Line
	5400 5450 2850 5450
Wire Wire Line
	2850 5450 2850 2500
Wire Wire Line
	2850 2500 2450 2500
Text Label 2500 2200 0    50   ~ 0
VH
Text Label 2500 2300 0    50   ~ 0
VL
Text Label 2500 2400 0    50   ~ 0
IH
Text Label 2500 2500 0    50   ~ 0
IL
Wire Wire Line
	4600 6800 4900 6800
Wire Wire Line
	4900 6500 4900 6300
Wire Wire Line
	4900 6300 4600 6300
Wire Wire Line
	4900 6300 4900 6050
Wire Wire Line
	4900 6050 4800 6050
Connection ~ 4900 6300
Wire Wire Line
	4500 6050 4300 6050
Connection ~ 4300 6050
Wire Wire Line
	4300 6050 4300 6100
Wire Wire Line
	2450 2800 3400 2800
Wire Wire Line
	1950 1000 1950 950 
Wire Wire Line
	1950 950  1850 950 
Connection ~ 1850 950 
Wire Wire Line
	1850 950  1850 1000
Wire Wire Line
	2450 1400 3100 1400
Wire Wire Line
	3100 1400 3100 6600
Wire Wire Line
	3100 6600 4000 6600
Text Label 2500 1400 0    50   ~ 0
PWM
Wire Wire Line
	4600 6400 5450 6400
Wire Wire Line
	6200 6400 6200 6000
Wire Wire Line
	6200 6000 7250 6000
Wire Wire Line
	7250 6000 7250 5500
Wire Wire Line
	4600 6900 5450 6900
Wire Wire Line
	6300 6900 6300 6100
Wire Wire Line
	6300 6100 7600 6100
Wire Wire Line
	7600 6100 7600 5500
Wire Wire Line
	4900 6800 6400 6800
Wire Wire Line
	6400 6800 6400 6200
Wire Wire Line
	6400 6200 8200 6200
Wire Wire Line
	8200 6200 8200 4550
Connection ~ 4900 6800
Connection ~ 8200 4550
Wire Wire Line
	8200 4550 8050 4550
Wire Wire Line
	4000 6700 2750 6700
Wire Wire Line
	2750 6700 2750 3400
Wire Wire Line
	2450 3400 2750 3400
Text Label 2450 3400 0    50   ~ 0
!SD
Wire Wire Line
	3500 1850 3400 1850
Wire Wire Line
	2250 5650 3400 5650
$Comp
L Connector:Conn_01x03_Male JRST?
U 1 1 62E11019
P 3600 2800
F 0 "JRST?" H 3572 2824 50  0000 R CNN
F 1 "Conn_01x03_Male" H 3572 2733 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3600 2800 50  0001 C CNN
F 3 "~" H 3600 2800 50  0001 C CNN
	1    3600 2800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3400 1850 3400 2700
Wire Wire Line
	3400 2900 3400 5650
$Comp
L Connector:Conn_01x01_Male TestGND?
U 1 1 63072EC5
P 3800 2250
F 0 "TestGND?" H 3772 2274 50  0000 R CNN
F 1 "Conn_01x01_Male" H 3772 2183 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3800 2250 50  0001 C CNN
F 3 "~" H 3800 2250 50  0001 C CNN
	1    3800 2250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 630755DF
P 3600 2350
F 0 "#PWR?" H 3600 2100 50  0001 C CNN
F 1 "GND" H 3605 2177 50  0000 C CNN
F 2 "" H 3600 2350 50  0001 C CNN
F 3 "" H 3600 2350 50  0001 C CNN
	1    3600 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2350 3600 2250
Wire Wire Line
	2250 6450 3350 6450
Wire Wire Line
	3350 6450 3350 1800
Wire Wire Line
	3350 1800 2450 1800
Wire Wire Line
	2250 6350 3300 6350
Wire Wire Line
	3300 6350 3300 1600
Wire Wire Line
	3300 1600 2450 1600
Wire Wire Line
	2250 6250 3250 6250
Wire Wire Line
	3250 6250 3250 1700
Wire Wire Line
	3250 1700 2450 1700
Text Label 2500 1600 0    50   ~ 0
MOSI
Text Label 2500 1700 0    50   ~ 0
MISO
Text Label 2500 1800 0    50   ~ 0
SCLK
$Comp
L Connector:Conn_01x01_Male TestStatus?
U 1 1 630A5635
P 2750 1050
F 0 "TestStatus?" H 2722 1074 50  0000 R CNN
F 1 "Conn_01x01_Male" H 2722 983 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 2750 1050 50  0001 C CNN
F 3 "~" H 2750 1050 50  0001 C CNN
	1    2750 1050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2550 1050 2550 1300
Wire Wire Line
	2550 1300 2450 1300
$Comp
L Connector:Conn_01x01_Male TestH?
U 1 1 630B04B0
P 6150 3850
F 0 "TestH?" H 6122 3874 50  0000 R CNN
F 1 "Conn_01x01_Male" H 6122 3783 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 6150 3850 50  0001 C CNN
F 3 "~" H 6150 3850 50  0001 C CNN
	1    6150 3850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5950 3850 5950 4050
Connection ~ 5950 4050
Wire Wire Line
	5950 4050 6300 4050
$Comp
L Connector:Conn_01x01_Male TestL?
U 1 1 630BB59E
P 9700 3850
F 0 "TestL?" H 9672 3874 50  0000 R CNN
F 1 "Conn_01x01_Male" H 9672 3783 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 9700 3850 50  0001 C CNN
F 3 "~" H 9700 3850 50  0001 C CNN
	1    9700 3850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9500 3850 9500 4050
Connection ~ 9500 4050
Wire Wire Line
	9500 4050 9700 4050
$Comp
L Connector:Conn_01x01_Male TestSW?
U 1 1 630C6AA0
P 8400 3900
F 0 "TestSW?" H 8372 3924 50  0000 R CNN
F 1 "Conn_01x01_Male" H 8372 3833 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8400 3900 50  0001 C CNN
F 3 "~" H 8400 3900 50  0001 C CNN
	1    8400 3900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8200 3900 8200 4550
$Comp
L Connector:Conn_01x01_Male TestGH?
U 1 1 630D2321
P 5650 6250
F 0 "TestGH?" H 5622 6274 50  0000 R CNN
F 1 "Conn_01x01_Male" H 5622 6183 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 5650 6250 50  0001 C CNN
F 3 "~" H 5650 6250 50  0001 C CNN
	1    5650 6250
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male TestGL?
U 1 1 630D3487
P 5650 7050
F 0 "TestGL?" H 5622 7074 50  0000 R CNN
F 1 "Conn_01x01_Male" H 5622 6983 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 5650 7050 50  0001 C CNN
F 3 "~" H 5650 7050 50  0001 C CNN
	1    5650 7050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5450 7050 5450 6900
Connection ~ 5450 6900
Wire Wire Line
	5450 6900 6300 6900
Wire Wire Line
	5450 6250 5450 6400
Connection ~ 5450 6400
Wire Wire Line
	5450 6400 6200 6400
Wire Wire Line
	4350 1200 4050 1200
Text Label 4050 1200 0    50   ~ 0
VCCTTL
Text Label 1000 4600 0    50   ~ 0
VCCPi
Wire Wire Line
	8350 2500 8600 2500
Text Label 8350 2500 0    50   ~ 0
VCCSupply
$Comp
L Connector_Generic:Conn_02x03_Odd_Even JPower?
U 1 1 63140350
P 6350 1200
F 0 "JPower?" H 6400 1517 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 6400 1426 50  0000 C CNN
F 2 "" H 6350 1200 50  0001 C CNN
F 3 "~" H 6350 1200 50  0001 C CNN
	1    6350 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6316CA1D
P 7050 1750
F 0 "#PWR?" H 7050 1500 50  0001 C CNN
F 1 "GND" H 7055 1577 50  0000 C CNN
F 2 "" H 7050 1750 50  0001 C CNN
F 3 "" H 7050 1750 50  0001 C CNN
	1    7050 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 1600 7050 1750
Wire Wire Line
	8050 2800 8050 2850
Wire Wire Line
	6650 1100 6700 1100
Wire Wire Line
	6700 1100 6700 1200
Wire Wire Line
	6700 1200 6650 1200
Wire Wire Line
	6650 1300 6700 1300
Wire Wire Line
	6700 1300 6700 1200
Connection ~ 6700 1200
Wire Wire Line
	6700 1200 7050 1200
Wire Wire Line
	6150 1100 5800 1100
Wire Wire Line
	6150 1200 5800 1200
Wire Wire Line
	6150 1300 5800 1300
Text Label 5800 1100 0    50   ~ 0
VCCTTL
Text Label 5800 1200 0    50   ~ 0
VCCPi
Text Label 5800 1300 0    50   ~ 0
VCCSupply
$EndSCHEMATC
