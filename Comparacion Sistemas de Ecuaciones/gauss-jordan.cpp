#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// Prototipos Relacionados con funcionamiento gral
void printMatrix(vector<vector<double>>);
vector<vector<double>> readFile();
vector<vector<double>> getMatrix(int n, vector<double>);
long getTime();

// Prototipos relacionados con Los métodos de Solución
long GaussJordan(vector<vector<double>>);
vector<double> modifiedRow(vector<double>, vector<double>, double);
vector<double> getResults(vector<vector<double>>);
void swapRows(vector<vector<double>> &, int, int);

int n;

int main()
{
    long GaussJordanTime = 0;

    vector<vector<double>> lines = readFile();
    for (int j = 1; j < lines.size(); j += 2)
    {
        n = (int)lines[j - 1][0];
        vector<vector<double>> Matrix(n, vector<double>(n + 1));
        Matrix = getMatrix(n, lines[j]);
        cout << "Matriz Aumentada: " << endl;
        printMatrix(Matrix);
        GaussJordanTime = GaussJordan(Matrix);
    }
    cout << GaussJordanTime;
    return 0;
}

// General functions
vector<vector<double>> getMatrix(int n, vector<double> line)
{
    vector<vector<double>> Matrix(n, vector<double>(n + 1));
    int index = 0;

    for (int k = 0; k < n; k++)
    {
        for (int l = 0; l < n + 1; l++)
        {
            Matrix[k][l] = line[index];
            index++;
        }
    }
    return Matrix;
}

vector<vector<double>> readFile()
{
    vector<vector<double>> lines;
    ifstream dataset;
    string line;
    dataset.open("dataset.txt", ios::in);

    while (!dataset.eof())
    {
        getline(dataset, line);
        vector<string> str_ch;
        vector<double> row;
        string temp = "";
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] != ' ')
            {
                temp += line[i];
                if (temp.compare("-"))
                {
                    temp += line[i + 1];
                    i++;
                }
                row.push_back(std::stod(temp));
                temp = " ";
            }
        }
        lines.push_back(row);
    }

    dataset.close();
    return lines;
}

void printMatrix(vector<vector<double>> Mtx)
{

    for (int i = 0; i < Mtx.size(); i++)
    {
        for (int j = 0; j < Mtx.size() + 1; j++)
        {
            cout << Mtx[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

long getTime()
{
    return clock();
}

// Solving Method's Functions
long GaussJordan(vector<vector<double>> Mtx)
{
    // esto es... (n^3)? :(
    // Creo, tomando en cuenta que es n^2 en el principal
    // Y luego en modified row toma n, entonces n^2 * n = n^3, no?
    long start = getTime();
    for (int i = 0; i < n; i++)
    {
        // intercambio
        if (Mtx[i][i] == 0)
        {
            bool flag = false;
            // Buscar una fila no nula para intercambiar
            for (int k = i + 1; k < n; k++)
            {
                if (Mtx[k][i] != 0)
                {
                    cout << "Swap" << endl;
                    swapRows(Mtx, i, k);
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                cout << "Sin solución" << endl;
                return getTime() - start;
            }
        }
        for (int j = i + 1; j < n; j++)
        {
            double cociente = Mtx[j][i] / Mtx[i][i];
            Mtx[j] = modifiedRow(Mtx[i], Mtx[j], cociente);
        }
    }
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = i - 1; j > -1; j--)
        {
            double cociente = Mtx[j][i] / Mtx[i][i];
            Mtx[j] = modifiedRow(Mtx[i], Mtx[j], cociente);
        }
    }
    cout << "Resultado final" << endl;

    // Luego get results vuelve a hacer otro ciclo, entonces es n^3 * n = n^4
    // Chale
    vector<double> results = getResults(Mtx);
    for (int i = 0; i < results.size(); i++)
    {
        cout << "  " << results[i] << " ";
    }
    cout << endl;
    return getTime() - start;
}

vector<double> modifiedRow(vector<double> pivote,
                           vector<double> filaObjetivo,
                           double cociente)
{
    for (int i = 0; i < n + 1; i++)
    {
        filaObjetivo[i] -= (pivote[i] * cociente);
    }
    return filaObjetivo;
}

void swapRows(vector<vector<double>> &Mtx, int row1, int row2)
{
    vector<double> temp = Mtx[row1];
    Mtx[row1] = Mtx[row2];
    Mtx[row2] = temp;
}

vector<double> getResults(vector<vector<double>> Mtx)
{
    vector<double> results;
    for (int i = 0; i < n; i++)
    {
        results.push_back(Mtx[i][n] /= Mtx[i][i]);
    }
    return results;
}
