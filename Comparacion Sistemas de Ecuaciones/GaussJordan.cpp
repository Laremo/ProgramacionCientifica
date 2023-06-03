#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

// Prototipos
void printMatrix(vector<vector<double>>);
vector<vector<double>> readFile();

int main()
{
    // int n;

    // cout << "Ingresa el tamaño de la matriz" << endl;
    // cin >> n;
    // vector<vector<double>> Matrix(n, vector<double>(n + 1));

    // cout << "Ingresa los elementos de la matriz aumentada (separados por espacios): " << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n + 1; j++)
    //     {
    //         cin >> Matrix[i][j];
    //     }
    // }

    ///////////////// Estoy rehaciendo gauss-jordan con la clase vector, para que los métodos estén
    // en menor diferencia de condiciones (considerando todo ese pedo de apuntadores que no se usar bien
    // y podría afectar al rendimiento)

    vector<vector<double>> lines = readFile();
    for (int j = 1; j < lines.size(); j += 2)
    {
        cout << "\n Tamamo de la matriz " << lines[j - 1][0] << endl;
        cout << "datos:" << endl;
        for (int i = 0; i < lines[j].size(); i++)
        {
            cout << " " << lines[j][i] << " ";
        }
    }
    return 0;
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

void printMatrix(vector<vector<double>> &Mtx)
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
