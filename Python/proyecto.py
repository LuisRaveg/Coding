import random
def generacion(obst,agua,filas,columnas):
    print(f"Agua: {agua}")
    print(f"Obstaculos: {obst}")
    a=[[str(random.randint(0,5)) for i in range(columnas)] for j in range(filas)]  # Generación del array de arrays, que representa una matriz con elementos aleatorios entre 0 y 5
    a[random.randint(0,filas -1)][random.randint(0,columnas-1)]="D"  #Selección de un elemento aleatorio para colocar la nave
    for n in range(obst):  #Colocar obst constáculos
        b=random.randint(0,filas -1) #numero de fila
        c=random.randint(0,columnas-1) #numero de columna
        if (a[b][c]!="D"): #Asegura que el elemento a[b][c] no sea la nave D
            a[b][c]="*" #Se colocan los obstáculos
    for n in range(agua): #Colocar agua
        b=random.randint(0,filas-1) #numero de fila
        c=random.randint(0,columnas-1)  #numero de columna
        if (a[b][c]!="D"): #Asegura que el elemento a[b][c] no sea la nave D
            a[b][c]="-"  #Se coloca el agua
    borde = "#" * (columnas + 2)   #String con  longitud de columnas + 2, con "#" en cada lugar
    print(borde)  # Se imprime el primer nivel
    for fila in a:
        print("#" + "".join(map(str, fila)) + "#")   #En cada fila se une un "# " al inicio y al final
    print(borde) # Se imprime el ultimo nivel 
    return a
generacion(42,28,5,10)
