//Materia: Programación Científica
//Integrantes del equipo:
//	Gibrán Antonio Galván Niño de Rivera
//	Sebastian Herrera Murillo
//Método: Cramer
//Última modificación del código: 30/04/2023
#include<bits/stdc++.h>
using namespace std;

vector<vector<double> > matGen(vector<vector<double> > &s, int x){
	vector<vector<double> > matrix(s.size()-1,vector<double>(s.size()-1));
	for(int i=1;i<s.size();i++){
		for(int j=0;j<s.size();j++){
			if(j!=x){
				matrix[i-1][j > x ? j-1:j] = s[i][j];
			}
		}
	}
	return matrix;
}

double det(vector<vector<double> > &s){
	vector<vector<double> > matrix(s.size()-1,vector<double>(s.size()-1));
	if(s.size()==2){
		return((s[0][0] * s[1][1]) - (s[0][1] * s[1][0]));
	}
	double d=0;
	for(int i=0;i<s.size();i++){
		matrix = matGen(s,i);
		d+= s[0][i] * det(matrix) * (i%2 ? -1: 1);
	}
	return d;
}

int main(){
	int inc=0;
	cout<<"Ingrese la cantidad de incognitas\n";
	cin>>inc;
	vector <vector<double> > sistem(inc,vector<double>(inc));

	vector <double> results(inc);
	for(int i=0;i<inc;i++){
		cout<<"Ingrese los valores de los coheficientes\n";
		for(int j=0;j<inc;j++){
			cin>>sistem[i][j];
		}
		cout<<"Ingrese el resultado de la ecuacion\n";
		cin>>results[i];
	}
	cout<<"\n";
	cout<<"Los resultados de las incognitas son:\n";
	vector <vector<double> > s2 = sistem;
	float detA = det(sistem);
	for(int i=0;i<sistem.size();i++){
		for(int j=0;j<sistem.size();j++){
			s2[j][i] = results[j];
		}
		cout<<"x"<<i<<" = "<<(det(s2) / detA)<<"\n";
		s2 = sistem;
	}
}
