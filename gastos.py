monitor = 3199
gabinete = 2400.55
rl = 1799
psu = 1399
nvme = 2680.11
mother = 3645.20
ram = 1526.90
cpu = 3346
gpu = 7579
pc = [monitor, gabinete, rl, psu, nvme, mother, ram, cpu, gpu]

def calcularDinero(n):
    mensualidad = 2000
    pc = 0
    inv = 0
    if n <= 3:
        for i in range(n):
            pc += mensualidad
    else:
        for i in range(3):
            pc += mensualidad
        for i in range(3, n):
            pc += mensualidad / 2
            inv += mensualidad / 2
    return inv, pc

def PC(n, interes):
    a = 0
    dinero = calcularDinero(n)[1]
    inversion = calcularDinero(n)[0] * (1 + interes)

 
    print("Componentes comprados inicialmente:")
    for i in range(len(pc)):
        a += pc[i]
        if a > dinero:
            restante = dinero - (a - pc[i]) + inversion
            for j in range(0, i):
                print(f"- Componente {j + 1}: ${pc[j]:.2f}")
            print(f"Restante después de inversión: ${restante:.2f}")
            break
    else:
        print(f"Todos los componentes se pueden comprar inicialmente.")
        return

    
    print("\nComponentes comprados adicionalmente con restante:")
    a = 0  
    for k in range(i, len(pc)):
        if pc[k] <= restante:
            print(f"- Componente {k + 1}: ${pc[k]:.2f}")
            restante -= pc[k]

    print(f"\nDinero restante final: ${restante:.2f}")
print(calcularDinero(12))  
PC(2, 0.1)               
