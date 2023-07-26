
# Communication Protocol

This folder contains Python files that act as a communication bridge between an HTTP server and the atverter board through a Raspberry Pi.


## Setting Up the Server

Your HTTP server will most likely be your desktop or laptop computer, for example a Mac. 

Make sure you know the IP address of your server machine. You can do this by opening your command line or terminal and typing ifconfig (for linux) or ipconfig(for windows) and looking under en0: inet. If on Mac, you can also navigate to System Preferences – Network and find the IP Address there.

If using ethernet and disconnected from WiFi, your machine auto-generates an IP address by ethernet connection. Use this IP address to run sample_server.py.
