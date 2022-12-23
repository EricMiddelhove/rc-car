import socket

def main():
    with socket.create_server(("", 50000)) as sock:
        while True:
            conn, addr = sock.accept()
            with conn:
                while True:
                    data = conn.recv(1)
                    if not data:
                        break
                    print(data.decode("utf-8"), end="")

if __name__ == "__main__":
    main()