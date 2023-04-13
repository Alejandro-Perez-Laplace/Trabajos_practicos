from math import radians, sin, cos, sqrt, atan2
import csv
import os
from multiprocessing import Process, Pipe


def haversine(lat1, lon1, lat2, lon2): 
    R = 6371.0 # Radio de la Tierra en km
    dLat = radians(lat2 - lat1)
    dLon = radians(lon2 - lon1)
    lat1 = radians(lat1)
    lat2 = radians(lat2)
    a = sin(dLat / 2)**2 + cos(lat1) * cos(lat2) * sin(dLon / 2)**2
    c = 2 * atan2(sqrt(a), sqrt(1 - a))
    return R * c

 
def calcular_distancias(proceso_hijo_pipe): 
   
    lat1, lon1 = proceso_hijo_pipe.recv()
    dist_total = 0
    
    while True:
       
        try:
            lat2, lon2 = proceso_hijo_pipe.recv()
        except EOFError:
            
            break
        
        dist_tramo = haversine(lat1, lon1, lat2, lon2)
        
        dist_total += dist_tramo
       
        print("Distancia del tramo:",dist_tramo," km")
       
        lat1, lon1 = lat2, lon2
    
    print("Distancia total recorrida:",dist_total," km")

if __name__ == '__main__':
    ruta_archivo = os.path.abspath("gps_data.csv")
    padre_pipe, hijo_pipe = Pipe()
    proceso_hijo = Process(target=calcular_distancias, args=(hijo_pipe,))
    proceso_hijo.start()
    with open(ruta_archivo, "r") as archivo_csv:
        lector_csv = csv.reader(archivo_csv)
        lat_idx = 0
        lon_idx = 1
        alt_idx = 2
        for fila in lector_csv:
            lat = float(fila[lat_idx])
            lon = float(fila[lon_idx])
            padre_pipe.send((lat, lon))
    padre_pipe.close()  
    proceso_hijo.join()
