from http.server import HTTPServer, BaseHTTPRequestHandler
import requests
import json

#change based on which connection you want
#keep in mind if wifi off, ethernet IP Address changes
ethhost = "169.254.211.11"
#wifihost = "198.128.205.144"


port = 8000
class testHTTP(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "application/json")
        self.end_headers()
        command = -3
        self.wfile.write(bytes('{"Command": "' + str(command) + '"}', "utf-8"))
        
    def do_POST(self):
        self.send_response(200)
        self.send_header("Content-type", "application/json")
        self.end_headers()
        content_length = int(self.headers['Content-Length'])
        response = self.rfile.read(content_length)
        response = response.decode('utf-8')
        response = json.loads(response)
        print("Battery State of Charge:", response["State"])
        print("Battery Charging Rate:", response["Rate"])
       
        
server = HTTPServer((ethhost, port), testHTTP)
#server = HTTPServer((wifihost, port), testHTTP)
print("Server now running")
server.serve_forever()
server.server_close()
print ("Server stopped")
