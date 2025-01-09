#include <iostream>
#include <fstream>
#include "Fraccion.h"
#include "MatFrac.h"
int main() {
    int opcion;
    std::cout << "Seleccione una opción:\n";
    std::cout << "1. Sumar matrices\n";
    std::cout << "2. Sumar fracciones\n";
    std::cout << "3. Multiplicar fracciones\n";
    std::cout << "Opción: ";
    std::cin >> opcion;
    if (opcion == 1) {
        MatFrac matriz1, matriz2;
        std::ifstream file1("matriz1.txt");
        std::ifstream file2("matriz2.txt");
        if (!file1.is_open() || !file2.is_open()) {
            std::cerr << "Error al abrir los archivos." << std::endl;
            return 1; 
        }
        matriz1.cargarDesdeArchivo(file1);
        matriz2.cargarDesdeArchivo(file2);
        MatFrac resultado = matriz1.sumar(matriz2);
        std::cout << "Matriz 1:" << std::endl;
        matriz1.imprimeMatriz();

        std::cout << "Matriz 2:" << std::endl;
        matriz2.imprimeMatriz();

        std::cout << "Matriz 1 + Matriz 2 = Matriz Resultado:" << std::endl;
        resultado.imprimeMatriz();
    } 
    else if (opcion == 2) {
        Fraccion f1, f2;
        f1.leerFraccion();
        f2.leerFraccion();
        Fraccion resultado = f1.sumaFracciones(f2);

        std::cout << "Resultado de la suma: ";
        resultado.imprimeFraccion();
        std::cout << std::endl;
    } 
    else if (opcion == 3) {
        Fraccion f1, f2;
        f1.leerFraccion();
        f2.leerFraccion();
        Fraccion resultado = f1.multiplicaFracciones(f2); 

        std::cout << "Resultado de la multiplicación: ";
        resultado.imprimeFraccion();
        std::cout << std::endl;
    } 
    else {
        std::cout << "Opción no válida." << std::endl;
    }

    return 0;
}