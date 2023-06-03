#include <iostream>
#include <vector>

using namespace std;

void mostrarMatriz(const vector<vector<double> >& A) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int n;
    cout << "\t\t\tMetodo  Gauss\n\n\t Leslie Miroslava Benitez Marin\t\t183817 \n\t Guillermo Gonzalez Lara\t\t237864"<<endl<<endl;
    cout << "Ingresa el tamano de la matriz: ";
    cin >> n;

    vector<vector<double> > A(n, vector<double>(n + 1));

    cout << "Ingresa los elementos de la matriz aumentada (separados por espacios): " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Matriz aumentada inicial:" << endl;
    mostrarMatriz(A);

    for (int i = 0; i < n; i++) {
        if (A[i][i] == 0) {
            cout << "No se puede resolver por el método de Gauss." << endl;
            system("pause");
            return 0;
        }
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n + 1; k++) {
                A[j][k] -= factor * A[i][k];
            }
        }
        cout << "Paso " << i + 1 << ":" << endl;
        mostrarMatriz(A);
    }

    vector<double> solucion(n);
    for (int i = n - 1; i >= 0; i--) {
        double suma = 0;
        for (int j = i + 1; j < n; j++) {
            suma += A[i][j] * solucion[j];
        }
        solucion[i] = (A[i][n] - suma) / A[i][i];
    }

    cout << "La solucion del sistema es: ";
    for (int i = 0; i < n; i++) {
        cout << solucion[i] << " ";
    }
    cout << endl;

    system("pause");

    return 0;
}
