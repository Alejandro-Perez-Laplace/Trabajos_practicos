import socket
import json

# Dato simulado del sensor
sensor_data = {"sensor_value": "776655"}

# Configuración del servidor
HOST = '0.0.0.0'  # Escuchar en todas las interfaces disponibles
PORT = 8080       # Puerto en el que escucha el servidor

# Crear el socket para el servidor
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))  # Asociar la dirección y el puerto al socket
    s.listen(1)           # Escuchar conexiones
    print(f"Servidor del sensor escuchando en http://{HOST}:{PORT}")
    
    while True:
        conn, addr = s.accept()  # Aceptar una conexión de cliente
        with conn:
            print(f"Conectado por {addr}")
            request = conn.recv(1024).decode()  # Recibir la solicitud del cliente
            print(f"Solicitud recibida: {request}")
            
            # Verificar que la solicitud sea un GET
            if "GET" in request:
                # Convertir el dato del sensor a JSON
                json_response = json.dumps(sensor_data)
                
                # Formato de la respuesta HTTP
                http_response = f"""\
HTTP/1.1 200 OK
Content-Type: application/json

{json_response}
"""
                conn.sendall(http_response.encode())  # Enviar la respuesta



import socket

# Configuración del cliente
HOST = '127.0.0.1'  # Dirección del servidor (en este caso, localhost)
PORT = 8080         # Puerto al que se conecta el cliente

# Crear el socket para el cliente
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))  # Conectar al servidor
    
    # Enviar solicitud GET
    request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n"
    s.sendall(request.encode())
    
    # Recibir la respuesta del servidor
    response = s.recv(1024).decode()
    
    # Imprimir la respuesta completa del servidor
    print("Respuesta del servidor:")
    print(response)
    
    # Extraer el contenido JSON de la respuesta
    response_lines = response.split("\r\n\r\n")
    if len(response_lines) > 1:
        json_data = response_lines[1]
        print(f"Datos del sensor en JSON: {json_data}")