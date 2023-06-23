from time import sleep

#gpio setup
import RPi.GPIO as gpio
gpio.setmode(gpio.BOARD)
gpiopin = 11
gpio.setup(gpiopin, gpio.OUT)


#actual program
minprice = 0
maxprice = 25
minbinary = 0
maxbinary = 63

dailydata = [1, 2]

def map_to_value(input_value, input_min, input_max, output_min, output_max):
	val1 = ((input_value - input_min)/(input_max - input_min))
	output_value = (val1 * (output_max - output_min)) + output_min
	return output_value

def map_to_binary(input_val):
	binary = map_to_value(input_val, minprice, maxprice, minbinary, maxbinary)
	binary_string = (bin(round(binary)))[2:]
	return binary_string.zfill(6)

def convert_to_push(pricelist):
	binary_code_list = []
	for price in pricelist:
		pushcode = (list(map_to_binary(price)))
		binary_code_list.append(pushcode)
	return binary_code_list

def rpi_output(list_of_lists):
	for price in list_of_lists:
		for bit in price:
			if int(bit) == 1:
				gpio.output(gpiopin, True)
				sleep(1)
			else:
				gpio.output(gpiopin, False)
				sleep(1)
		sleep(5)

data = convert_to_push(dailydata)
rpi_output(data)

gpio.cleanup()

