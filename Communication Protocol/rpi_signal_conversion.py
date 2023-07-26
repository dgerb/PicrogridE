import requests
import json
from time import sleep
from requests.structures import CaseInsensitiveDict
import serial

#these exist as an initial to prevent ValueErrors
state = None
rate = None

#initialize serial communication

#change the serial port to whatever your connection is
serial_port = '/dev/ttyUSB0'
ser = serial.Serial(serial_port, 9600, timeout = 1.0)
sleep(3)
ser.reset_input_buffer()

#initialize http client

#replace with your correct urls
#'http://<ipaddress>:8000'
wifiurl = 'http://198.128.205.144:8000'
ethurl =  'http://169.254.175.245:8000'
headers = CaseInsensitiveDict()
headers["Accept"] = "application/json"
headers["Content-type"] = "application/json"



while True:
    #receive from server
    #request = requests.get(wifiurl)
    request = requests.get(ethurl)
    response = request.json()
    command = response["Command"]
    
    #send to serial
    try:
        ser.write((command + '\n').encode('utf-8'))
        sleep(0.1)
        
    #receive from serial        
        if ser.in_waiting > 0:
            state = ser.readline().decode('utf-8')
            rate = ser.readline().decode('utf-8')
    except KeyboardInterrupt:
        ser.close()
    
    #send to server
    data = {"State": state, "Rate": rate}
    data = json.dumps(data)
    #resp = requests.post(wifiurl, headers = headers, data = data) 
    resp = requests.post(ethurl, headers = headers, data = data)
    print(resp.status_code)
    sleep(1)
