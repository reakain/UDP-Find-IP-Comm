from udp_socket import UDPClient

if __name__ == "__main__":
    # This initialization of the UDP client handles also finding the correct remote machine
    # the number 4210 is the port to send data to on the remote machine
    udp_client = UDPClient(4210)

    while True:
        # If we have a new packet from our remote machine to read
        if udp_client.have_new_data():
            # then we get it from the class
            new_data = udp_client.packet
            # then do w/e you want with the data
