import csv
import math
import multiprocessing
from multiprocessing import Pipe


def read_gps_data(filename):
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            latitude = float(row[0])
            longitude = float(row[1])
            yield latitude, longitude


def haversine_distance(lat1, lon1, lat2, lon2):
    R = 6371.0  # Radio de la Tierra en kilómetros

    lat1_rad = math.radians(lat1)
    lon1_rad = math.radians(lon1)
    lat2_rad = math.radians(lat2)
    lon2_rad = math.radians(lon2)

    dlon = lon2_rad - lon1_rad
    dlat = lat2_rad - lat1_rad

    a = math.sin(dlat / 2)**2 + math.cos(lat1_rad) * math.cos(lat2_rad) * math.sin(dlon / 2)**2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))

    distance = R * c
    return distance


def calculate_distance(conn, gps_data):
    total_distance = 0
    previous_lat = None
    previous_lon = None

    for lat, lon in gps_data:
        if previous_lat is not None and previous_lon is not None:
            distance = haversine_distance(previous_lat, previous_lon, lat, lon)
            total_distance += distance
            conn.send(distance)

        previous_lat = lat
        previous_lon = lon

    conn.send(total_distance)
    conn.close()


if __name__ == '__main__':
    gps_data = list(read_gps_data('gps_data.csv'))
    parent_conn, child_conn = Pipe()

    p = multiprocessing.Process(target=calculate_distance, args=(child_conn, gps_data))
    p.start()

    while True:
        try:
            distance = parent_conn.recv()
            print(f"Distancia: {distance:.2f} km")
        except EOFError:
            break

    total_distance = parent_conn.recv()
    print(f"Distancia total recorrida: {total_distance:.2f} km")

    p.join()
