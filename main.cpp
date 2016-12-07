#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void createVariables(int n, int m){
    int cuadro[n*m][4]; //variables de cada recuadro
    int cuadro_i = 0;   //index del array cuadro
    int aux = 1;        //auxiliar para numerar variables

    while(cuadro_i < n*m){
        for(int i=0; i<n ; i++){
            cuadro[cuadro_i][0] = aux;          //superior
            cuadro[cuadro_i][1] = n+aux;        //izquierdo
            cuadro[cuadro_i][2] = n+1+aux;      //derecho
            cuadro[cuadro_i][3] = n+m+1+aux;    //inferior

            printf("cuadro %d = { %d,%d,%d,%d }\n",cuadro_i+1,cuadro[cuadro_i][0],cuadro[cuadro_i][1],cuadro[cuadro_i][2],cuadro[cuadro_i][3]);

            cuadro_i++;
            aux++;
        }
        aux += m+1; //paso a siguiente fila 
    }
}

int main(int argc, char const *argv[]) {

    int n,m; // n-filas,m-columnas

    ifstream infile("example_input.txt");
    string line;
    while (getline(infile, line)) {
        vector<string> restricciones;
        istringstream ss(line);
        string token;
        int i;

        getline(ss,token,' ');
        n = stoi(token);
        getline(ss,token,' ');
        m = stoi(token);

        printf("n=%d, m=%d\nRestricciones:\n", n,m);
        i=0;
        while (getline(ss, token,' ')){
            restricciones.push_back(token);
            cout << restricciones[i] << endl;
            i++;
        }

        createVariables(n,m);
    }
 
    return 0;
}