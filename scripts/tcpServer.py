import socket
import sys

# Super simple TCP server yoinked straight from google.com (http://pymotw.com/2/socket/tcp.html)

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

port = 3080
if len(sys.argv) == 3:
    port = int(sys.argv[2])

# Bind the socket to the port
server_address = (sys.argv[1], port)
print(f"Starting TCP Server with IP {server_address[0]} and Port {server_address[1]}.")
sock.bind(server_address)

# Listen for incoming connections
sock.listen(1)

while True:
    # Wait for a connection
    print('Waiting for Switch to Connect...')
    connection, client_address = sock.accept()
    try:
        print(f'Switch Connected! IP: {client_address[0]} Port: {client_address[1]}')
        while True:
            data = connection.recv(1024)

            if data:
                print(data.decode("utf-8"), end='', flush=True)
            else:
                print(f'Connection Terminated.')
                break

    except ConnectionResetError:
        print("Connection reset")

    finally:
        # Clean up the connection
        connection.close()

