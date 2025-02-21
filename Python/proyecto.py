import random
def generacion(obst,agua,filas,columnas):
    print(f"Agua: {agua}")
    print(f"Obstaculos: {obst}")
    a=[[str(random.randint(0,5)) for i in range(columnas)] for j in range(filas)]
    a[random.randint(0,filas -1)][random.randint(0,columnas-1)]="D"
    for n in range(obst):
        b=random.randint(0,filas -1)
        c=random.randint(0,columnas-1)
        if (a[b][c]!="D"):
            a[b][c]="*"
    for n in range(agua):
        b=random.randint(0,filas-1)
        c=random.randint(0,columnas-1)
        if (a[b][c]!="D"):
            a[b][c]="-"
    borde = "#" * (columnas + 2)
    print(borde)
    for fila in a:
        print("#" + "".join(map(str, fila)) + "#")  
    print(borde)
    return a
generacion(42,28,15,30)
