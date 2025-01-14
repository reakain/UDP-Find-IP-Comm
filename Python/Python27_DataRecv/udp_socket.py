import socket
import json
import time
import select

class UDPClient(object):
    """
    A class to handle udp socket events.
    """

    def __init__(self, serverIPAddress, ComputerPort):
        #msgFromClient       = "Hello UDP Server"
        #bytesToSend         = str.encode(msgFromClient)
        #self.serverIPAddress     = socket.gethostbyname(ComputerName)
        self.computerPort        = ComputerPort
        self.serverIPAddress     = serverIPAddress
        self.serverAddressPort   = (self.serverIPAddress, self.computerPort)
        self.bufferSize          = 2048

        # Create a UDP socket at client side
        self.UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
        self.UDPClientSocket.bind(('', self.computerPort))
    
    # This version will find the ip address on its own by communicating with the server
    def __init__(self, ComputerPort):
        self.computerPort        = ComputerPort+1
        self.bufferSize          = 2048

        # Create a UDP socket at client side
        self.UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
        #self.UDPClientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
        #self.UDPClientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        self.UDPClientSocket.bind(('0.0.0.0', self.computerPort))

        self.serverIPAddress     = self.get_server_ip(ComputerPort)
        self.serverAddressPort   = (self.serverIPAddress, self.computerPort)
        #self.UDPClientSocket.close()
        #self.UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
        #self.UDPClientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
        #self.UDPClientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        #self.UDPClientSocket.bind((self.serverIPAddress, self.computerPort))

    def close_client(self):
        self.UDPClientSocket.close()

    def get_message(self):
        recievedData = self.UDPClientSocket.recvfrom(self.bufferSize)
        #message = recievedData[0].decode()
        msg = "Message from Server: {}".format(recievedData)
        return recievedData

    def have_new_data(self):
        readables, writables, errors=select.select([self.UDPClientSocket],[],[], 1)
        for read_socket in readables:
            data = self.get_message()
            if data[1][0] == self.serverIPAddress:
                self.packet = data[0].decode()
                return True
            return False
        return False
        
    def get_json_packet(self):
        return json.loads(self.packet)

    def get_server_ip(self, comm_port):
        hello_request = "hello?"
        while True:
            # Send the request to the server
            self.broadcast_send(hello_request, comm_port)
            # wait a lil bit so we don't just slam the server
            time.sleep(2)
            readables, writables, errors=select.select([self.UDPClientSocket],[],[], 1)
            for read_socket in readables:
                data = self.get_message()
                returnMsg = data[0].decode('utf_8','strict')
                if returnMsg == "hello!":
                    return data[1][0]

    def broadcast_send(self, message, comm_port):
        msg = message.encode('utf_8','strict')
        #sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        sock = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
        #sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        sock.sendto(msg, ("255.255.255.255", comm_port))
        sock.close()
        # interfaces = socket.getaddrinfo(socket.gethostbyname(socket.gethostname()), None, socket.AF_INET)
        # allips = [ip[-1][0] for ip in interfaces]

        # msg = message.encode('utf_8','strict')
        # for ip in allips:
        #     print 'sending on {}'.format(ip)
        #     sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)  # UDP
        #     sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        #     sock.bind((ip,0))
        #     sock.sendto(msg, ("255.255.255.255", comm_port))
        #     sock.close()


# # Send to server using created UDP socket
# #UDPClientSocket.sendto(bytesToSend, serverAddressPort)

# msgFromServer = UDPClientSocket.recvfrom(bufferSize)

# msg = "Message from Server {}".format(msgFromServer[0])
# print(msg)