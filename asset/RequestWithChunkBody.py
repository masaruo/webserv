#!/usr/bin/env python3
import socket

def send_chunked():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('localhost', 8888))
    
    request = (
        b'POST /cgi-bin/echo.py/path/info HTTP/1.1\r\n'
        b'Host: localhost:8888\r\n'
        b'Content-Type: application/x-www-form-urlencoded\r\n'
        b'Transfer-Encoding: chunked\r\n'
        b'\r\n'
        b'A\r\n'
        b'name=masar\r\n'
        b'A\r\n'
        b'u&message=\r\n'
        b'B\r\n'
        b'this_is_fro\r\n'
        b'6\r\n'
        b'm_post\r\n'
        b'0\r\n\r\n'
    )
    
    sock.send(request)
    response = sock.recv(4096)
    print(response.decode())
    sock.close()

if __name__ == '__main__':
    send_chunked()
