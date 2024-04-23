def main():
    
    principal = int(input("Ingrese el principal: ")) # Solicitud de datos al usuario
    tasa_interes_anual = float(input("Ingrese la tasa de interés anual (en %): "))
    veces_capitalizacion_anual = int(input("Ingrese el número de veces que se capitaliza el interés al año: "))
    años_inversion = int(input("Ingrese el número de años que permanecerá la inversión: "))

    # Convertir la tasa de interés anual de porcentaje a decimal
    tasa_interes_decimal = tasa_interes_anual / 100

    # Calcular el monto de interés compuesto
    monto_acumulado = principal * (1 + tasa_interes_decimal / veces_capitalizacion_anual) ** (veces_capitalizacion_anual * años_inversion)

    # Imprimir el monto acumulado después de t años con dos decimales
    print("El monto acumulado después de {} años es: {:.2f}".format(años_inversion, monto_acumulado))


if __name__ == "__main__":
    main()
