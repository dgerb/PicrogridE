from http.server import HTTPServer, BaseHTTPRequestHandler
import json

#change based on which connection you want
#keep in mind if wifi off, use ethernet IP address
#example IP addresses here, use the one matched to your device
eth_host = "169.254.211.11"
#wifi_host = "198.128.205.144"
port = 8000


class serverHTTP(BaseHTTPRequestHandler):
    #GET command sends charge command to RPi in json format
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "application/json")
        self.end_headers()
        command = -3
        self.wfile.write(bytes('{"Command": "' + str(command) + '"}', "utf-8"))
        
    def do_POST(self):
        #POST command reads state and rate of charge from battery in json format
        self.send_response(200)
        self.send_header("Content-type", "application/json")
        self.end_headers()
        content_length = int(self.headers['Content-Length'])
        response = self.rfile.read(content_length)
        response = response.decode('utf-8')
        response = json.loads(response)
        #prints are just checks to ensure communication, actual server will do manipulation
        print("Battery State of Charge:", response["State"])
        print("Battery Charging Rate:", response["Rate"])
       
        
server = HTTPServer((eth_host, port), serverHTTP)
#server = HTTPServer((wifi_host, port), serverHTTP)


print("Server now running")
server.serve_forever()
server.server_close()
print ("Server stopped")
