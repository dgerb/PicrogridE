
# Communication Protocol

This folder contains Python files that act as a communication bridge between an HTTP server and the atverter board through a Raspberry Pi.


## Setting Up the Server

Your HTTP server will most likely be your desktop or laptop computer, for example a Mac. 

Make sure you know the IP address of your server machine. You can do this by opening your command line or terminal and typing: 
    - ifconfig (for Linux) 
    - ipconfig(for Windows) 
and looking under en0: inet. If on Mac, you can also navigate to System Preferences – Network and find the IP Address there.

If using ethernet and disconnected from WiFi, your machine auto-generates an IP address by ethernet connection. Use this IP address to run sample_server.py.

## Setting Up the Raspberry Pi
Enable serial communication in your Raspberry Pi. This can be done inside the terminal:
    - sudo raspi-config
    - You will be redirected to a menu. Navigate to Interface Options (3) and hit enter.
    - Navigate to Serial Port (I6) and hit enter.
    - Select No for "Would you like a login shell to be accessible over serial?"
    - Select Yes for "Would you like the serial port hardware to be enabled?"
    - You may have to reboot the system in order for the changes to take effect. Open a terminal and type sudo reboot.
    
Inside of the terminal, install the serial and requests libraries with: 
    - pip install requests
    - pip install pyserial

Inside rpi_signal_conversion.py, change the serial port to whatever you need to connect to. In order to find which one:
    - Open terminal, and type: 
        - ls /dev/tty*
    - Look at the shown options that don't look like a numbered list (for example, not /dev/tty55)
    - Unplug your desired USB connection from the Raspberry Pi and repeat the terminal command.
    - Whichever connection disappeared is the connection you want to put into the python file.

From setting up the server, take the wifi or ethernet IP address and use those as the address elements of wifiurl and ethurl.

## Setting up the Atverter
Open serial_testing.ino. Under the navigation menu, select Tools. Make sure that Board is set to "Arduino Uno" and Port is set to whatever /dev/tty* identifier you found when setting up your Raspberry Pi.
