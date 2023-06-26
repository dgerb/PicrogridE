#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jun 22 15:23:29 2023

@author: Brandon Ng
"""
#given DC power, we'll have a DC load (purely resistive)
#max current output 5A (using 4 for safety buffer)
#max voltage 46V, using 36 for safety buffer)
#sim file approximating the function of the system, up to battery push

from time import sleep
import json

#batterystart = input("What voltage should the battery be set to? 0-36V:  ")
#loadattach = input ("Pick a resistance of our load:  ")

#constants, will vary with the actual data inputted, these are all tests
minprice = 0
maxprice = 1
mincurrent = -4
maxcurrent = 4
minbinary = 0
maxbinary = 63

#mimicking a get from the OpenADR value interface, so the data is read into the Pi
with open ("powerdata.json") as file:
    data = json.load(file)
dailydata = data.get("intervals")[0].get("payloads")[0].get("values")


#mapping one value to another, based off arduino map() function
def map_to_value (input_value, input_min, input_max, output_min, output_max):
    val1 = ((input_value-input_min)/(input_max-input_min))
    #(current-mincurrent)/maxcurrent-mincurrent)
    output_value = (val1*(output_max-output_min)) + output_min
    return output_value

#def map_to_current(price):
    #current = map_to_value(price, minprice, maxprice, mincurrent, maxcurrent) 
    #return current

#theory: the battery is bidirectional, but only one at a time.
#so if at any point charging is more economical, charge the battery (rate?)
#if battery power is better, then supply battery power based on algorithm

#convert any value to its closest 6 bit binary number
#these act as the RPi output voltages
def map_to_binary (input_val):
    #binary = map_to_value(input_val, mincurrent, maxcurrent, minbinary, maxbinary)
    binary = map_to_value(input_val, minprice, maxprice, minbinary, maxbinary)
    binary_string = (bin(round(binary)))[2:]  
    return binary_string.zfill(6)

#separate the binary into lists of one character strings
def convert_to_push(pricelist):
    binary_code_list = []
    for price in pricelist:
        #newcurrent = map_to_current(price)        
        #pushcode = (list(map_to_binary(newcurrent)))
        pushcode = (list(map_to_binary(price)))
        binary_code_list.append(pushcode)        
    return binary_code_list    

#use delays to mimic the RPi sending out voltage bits, now as integers
def rpi_output(list_of_lists):
    for price in list_of_lists:
        for bit in price:
            print(int(bit))
            sleep(1)
        sleep(5)    

#print(convert_to_push(dailydata))
data = convert_to_push(dailydata)
rpi_output(data)

