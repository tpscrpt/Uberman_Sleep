EESchema Schematic File Version 4
LIBS:project-cache
EELAYER 26 0
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
L project-rescue:MAX30102EFD+-2019-12-14_17-30-25 U?
U 1 1 5DF51DA7
P 2050 5750
F 0 "U?" H 3350 6337 60  0000 C CNN
F 1 "MAX30102EFD+" H 3350 6231 60  0000 C CNN
F 2 "21-0880B" H 3350 6290 60  0001 C CNN
F 3 "" H 2050 5750 60  0000 C CNN
	1    2050 5750
	1    0    0    -1  
$EndComp
$Comp
L MCU_MAX32652GWE:MAX32652GWE+ U?
U 2 1 5DF5A9D4
P 8750 2900
F 0 "U?" H 9750 3287 60  0000 C CNN
F 1 "MAX32652GWE+" H 9750 3181 60  0000 C CNN
F 2 "21-100219C_W1404A4+1" H 9750 3140 60  0001 C CNN
F 3 "" H 8750 2900 60  0000 C CNN
	2    8750 2900
	1    0    0    -1  
$EndComp
$Comp
L PMU_MAX20345AEWN:MAX20345AEWN+ U?
U 1 1 5DF5AD3E
P 5700 3050
F 0 "U?" H 6700 3437 60  0000 C CNN
F 1 "MAX20345AEWN+" H 6700 3331 60  0000 C CNN
F 2 "21-100260A_W563H3+1" H 6700 3290 60  0001 C CNN
F 3 "" H 5700 3050 60  0000 C CNN
	1    5700 3050
	1    0    0    -1  
$EndComp
$Comp
L dk_Memory-Connectors-PC-Card-Sockets:2908-05WB-MG J?
U 1 1 5DF5B38D
P 1350 3600
F 0 "J?" H 1978 3628 60  0000 L CNN
F 1 "2908-05WB-MG" H 1978 3522 60  0000 L CNN
F 2 "digikey-footprints:MicroSD_2908-05WB-MG" H 1550 3800 60  0001 L CNN
F 3 "http://multimedia.3m.com/mws/media/416257O/3mtm-card-connector-microsdtm-2900-series-ts2197.pdf" H 1550 3900 60  0001 L CNN
F 4 "3M5607CT-ND" H 1550 4000 60  0001 L CNN "Digi-Key_PN"
F 5 "2908-05WB-MG" H 1550 4100 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 1550 4200 60  0001 L CNN "Category"
F 7 "Memory Connectors - PC Card Sockets" H 1550 4300 60  0001 L CNN "Family"
F 8 "http://multimedia.3m.com/mws/media/416257O/3mtm-card-connector-microsdtm-2900-series-ts2197.pdf" H 1550 4400 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/3m/2908-05WB-MG/3M5607CT-ND/1242498" H 1550 4500 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN MICRO SD CARD PUSH-PUSH R/A" H 1550 4600 60  0001 L CNN "Description"
F 11 "3M" H 1550 4700 60  0001 L CNN "Manufacturer"
F 12 "Active" H 1550 4800 60  0001 L CNN "Status"
	1    1350 3600
	1    0    0    -1  
$EndComp
$Comp
L dk_USB-DVI-HDMI-Connectors:0473460001 J?
U 1 1 5DF5B73C
P 1100 1300
F 0 "J?" H 1163 2023 50  0000 C CNN
F 1 "0473460001" H 1163 1932 50  0000 C CNN
F 2 "digikey-footprints:USB_Micro_B_Female_0473460001" H 1300 1500 60  0001 L CNN
F 3 "https://www.molex.com/pdm_docs/sd/473460001_sd.pdf" H 1300 1600 60  0001 L CNN
F 4 "WM17141CT-ND" H 1300 1700 60  0001 L CNN "Digi-Key_PN"
F 5 "0473460001" H 1300 1800 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 1300 1900 60  0001 L CNN "Category"
F 7 "USB, DVI, HDMI Connectors" H 1300 2000 60  0001 L CNN "Family"
F 8 "https://www.molex.com/pdm_docs/sd/473460001_sd.pdf" H 1300 2100 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/molex/0473460001/WM17141CT-ND/1782474" H 1300 2200 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN RCPT USB2.0 MICRO B SMD R/A" H 1300 2300 60  0001 L CNN "Description"
F 11 "Molex" H 1300 2400 60  0001 L CNN "Manufacturer"
F 12 "Active" H 1300 2500 60  0001 L CNN "Status"
	1    1100 1300
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC M?
U 1 1 5DF5BC31
P 7000 900
F 0 "M?" H 7158 896 50  0000 L CNN
F 1 "Motor_DC" H 7158 805 50  0000 L CNN
F 2 "" H 7000 810 50  0001 C CNN
F 3 "~" H 7000 810 50  0001 C CNN
	1    7000 900 
	1    0    0    -1  
$EndComp
$Comp
L dk_Alarms-Buzzers-and-Sirens:PKMCS0909E4000-R1 BZ?
U 1 1 5DF5BDE3
P 4850 1050
F 0 "BZ?" H 5190 1158 60  0000 L CNN
F 1 "PKMCS0909E4000-R1" H 5190 1052 60  0000 L CNN
F 2 "digikey-footprints:Piezo_9x9mm_PKMCS0909E4000-R1" H 5050 1250 60  0001 L CNN
F 3 "https://www.murata.com/~/media/webrenewal/products/sound/sounder/vppt-buzj083-d.ashx" H 5050 1350 60  0001 L CNN
F 4 "490-9647-1-ND" H 5050 1450 60  0001 L CNN "Digi-Key_PN"
F 5 "PKMCS0909E4000-R1" H 5050 1550 60  0001 L CNN "MPN"
F 6 "Audio Products" H 5050 1650 60  0001 L CNN "Category"
F 7 "Alarms, Buzzers, and Sirens" H 5050 1750 60  0001 L CNN "Family"
F 8 "https://www.murata.com/~/media/webrenewal/products/sound/sounder/vppt-buzj083-d.ashx" H 5050 1850 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/murata-electronics-north-america/PKMCS0909E4000-R1/490-9647-1-ND/4878401" H 5050 1950 60  0001 L CNN "DK_Detail_Page"
F 10 "AUDIO PIEZO TRANSDUCER 12.5V SMD" H 5050 2050 60  0001 L CNN "Description"
F 11 "Murata Electronics North America" H 5050 2150 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5050 2250 60  0001 L CNN "Status"
	1    4850 1050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5DF5C430
P 8900 1100
F 0 "SW?" H 8900 1385 50  0000 C CNN
F 1 "SW_Push" H 8900 1294 50  0000 C CNN
F 2 "" H 8900 1300 50  0001 C CNN
F 3 "" H 8900 1300 50  0001 C CNN
	1    8900 1100
	1    0    0    -1  
$EndComp
$Comp
L Battery_Management:MAX1811 U?
U 1 1 5DF5CD35
P 2300 1150
F 0 "U?" H 2350 1617 50  0000 C CNN
F 1 "MAX1811" H 2350 1526 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 2550 800 50  0001 L CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX1811.pdf" H 2300 450 50  0001 C CNN
	1    2300 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT?
U 1 1 5DF5CFE8
P 3700 1000
F 0 "BT?" H 3818 1096 50  0000 L CNN
F 1 "Battery_Cell" H 3818 1005 50  0000 L CNN
F 2 "" V 3700 1060 50  0001 C CNN
F 3 "~" V 3700 1060 50  0001 C CNN
	1    3700 1000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
