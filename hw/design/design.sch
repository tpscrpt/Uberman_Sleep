EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 1950 1250 700  550 
U 5E0A3409
F0 "HR Sensor" 50
F1 "HR_SENSOR.sch" 50
F2 "HRSDA" B R 2650 1400 50 
F3 "HRSCL" I R 2650 1500 50 
F4 "HRINT" O R 2650 1600 50 
$EndSheet
Wire Wire Line
	2650 1400 4100 1400
Wire Wire Line
	4100 1500 2650 1500
Wire Wire Line
	2650 1600 4100 1600
$Sheet
S 4100 1300 950  1700
U 5E117560
F0 "MCU GPIO" 50
F1 "MCU_GPIO.sch" 50
F2 "HRINT" I L 4100 1600 50 
F3 "SDA_I2C" B L 4100 1400 50 
F4 "SCL_I2C" O L 4100 1500 50 
$EndSheet
$Sheet
S 5500 1300 900  1450
U 5E15CBF8
F0 "MCU Power" 50
F1 "MCU_V.sch" 50
$EndSheet
$Sheet
S 6800 1300 700  750 
U 5E17C70B
F0 "MCU Peripherals" 50
F1 "MCU_Peripherals.sch" 50
$EndSheet
$EndSCHEMATC
