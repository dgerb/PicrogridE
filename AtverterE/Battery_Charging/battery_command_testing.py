from time import sleep
import serial

#change serial port based on how you are connecting to Atverter
serial_port = '/dev/tty.usbserial-AB6ZRVKI'
ser = serial.Serial(serial_port, 9600, timeout = 1.0)
sleep(3)
ser.reset_input_buffer()

while True:
    try:
        current = input("What current would you like? Charge is positive in mA, -3500 to 1500:  ")
        ser.write((current + '\n').encode('utf-8'))
        sleep(0.1)
        
        if ser.in_waiting > 0:
        #eventually, will receive commands from atverter once specifics are determined
            command = ser.readline().decode('utf-8')
            print(command)
    except KeyBoardInterrupt:
        ser.close()
