import os

read_pipe, write_pipe = os.pipe()# Creacion de pipe

child_pid = os.fork()# Creacion del proceso hijo

if child_pid == 0:
    # Proceso hijo
    os.close(write_pipe)#se cierra la tuberia de escritura desde el proceso hijo
    message = os.read(read_pipe, 1024)
    print(f'Received message in child process: {message.decode()}')
    os.close(read_pipe)#se cierra la tuberia de lectura desde el proceso hijo
    exit(0)
else:
    # Proceso padre
    os.close(read_pipe)#se cierra la tuberia de lectura desde el proceso padre
    #mensaje = b'Hello from parent process!'
    message = f'Hello from parent process {os.getpid()}!'
    #os.write(write_pipe, message)
    os.write(write_pipe, message.encode())
    os.close(write_pipe)#se cierra la tuberia de escritura desde el proceso padre
    pid, status = os.waitpid(child_pid, 0)
    print(f'Child process {child_pid} finished with status {status}')
