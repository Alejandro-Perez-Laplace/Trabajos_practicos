import csv

with open('gps_data.csv', 'r') as archivo:
    lector_csv = csv.reader(archivo)

    # Iteramos sobre las filas del archivo CSV
    for fila in lector_csv:
        # Imprimimos cada celda de la fila
        for celda in fila:
            print(celda)

