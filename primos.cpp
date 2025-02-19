#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int problema(int n, int k) {
    for (int i = 0; i < k; i++) {
        if (n % 10 == 0) {
            n /= 10;
        } else {
            n--;
        }
    }
    return n;
}

int main() {
    int n, k;
    cout << "Introduce un entero: ";
    cin >> n;
    cout << "Introduce un entero: ";
    cin >> k;

    int repeticiones = 1000000;  // Ejecutar el código 1 millón de veces
    auto start = high_resolution_clock::now();

    for (int i = 0; i < repeticiones; i++) {
        problema(n, k);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    double tiempo_promedio = duration.count() / double(repeticiones);

    cout << "Tiempo promedio de ejecución: " << tiempo_promedio << " microsegundos" << endl;

    return 0;
}
