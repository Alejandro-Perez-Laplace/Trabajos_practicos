import socket

# Definir la dirección y el puerto del servidor
HOST = '0.0.0.0'  # Escucha en todas las interfaces de red disponibles
PORT = 8080       # Puerto en el que se ejecutará el servidor

# Crear el socket para el servidor
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))  # Asociar la dirección y el puerto al socket
    s.listen(1)           # Habilitar el servidor para aceptar conexiones
    print(f"Servidor web escuchando en http://{HOST}:{PORT}")
    
    while True:
        conn, addr = s.accept()  # Esperar la conexión de un cliente
        with conn:
            print(f"Conectado por {addr}")
            request = conn.recv(1024).decode()  # Recibir la solicitud del cliente
            print(f"Solicitud recibida: {request}")
            
            # Respuesta HTTP simple con un "Hola Mundo"
            http_response = """\
HTTP/1.1 200 OK

<html>
    <head><title>Hola Mundo</title></head>
    <body><h1>Hola Mundo</h1></body>
</html>
"""
            conn.sendall(http_response.encode())  # Enviar la respuesta al cliente

